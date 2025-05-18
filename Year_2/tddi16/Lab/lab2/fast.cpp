#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;



/**
 * Class that stores a summary of an image.
 *
 * This summary is intended to contain a high-level representation of the
 * important parts of an image. I.e. it shall contain what a human eye would
 * find relevant, while ignoring things that the human eye would find
 * irrelevant.
 *
 * To approximate human perception, we store a series of booleans that indicate
 * if the brightness of the image has increased or not. We do this for all
 * horizontal lines and vertical lines in a downsampled version of the image.
 *
 * See the lab instructions for more details.
 *
 * Note: You will need to use this data structure as the key in a hash table. As
 * such, you will need to implement equality checks and a hash function for this
 * data structure.
 */
class Image_Summary {
public:

    Image_Summary()
    {}

    // Horizontal increases in brightness.
    vector<bool> horizontal;
    std::vector<int> horizontal_sum{};
    // Vertical increases in brightness.
    vector<bool> vertical;
    std::vector<int> vertical_sum{};

};

bool operator==(Image_Summary const& lhs,Image_Summary const& rhs)
{
    bool match{true};

    for (unsigned int i{}; i < lhs.horizontal_sum.size(); i++)
    {
        if (!(lhs.vertical_sum.at(i) == rhs.vertical_sum.at(i)))
        {
            match = false;
            break;
        }

        if (!(lhs.horizontal_sum.at(i) == rhs.horizontal_sum.at(i)))
        {
            match = false;
            break;
        }
    }

    return match;
}

namespace std{
    template<>
    class hash<Image_Summary>
    {
    public:
        std::size_t operator()(Image_Summary const& to_hash) const
        {
            std::size_t hashVal {};

            for (int vsum : to_hash.vertical_sum)
                hashVal ^= std::hash<size_t>{}(vsum);
            for (int hsum : to_hash.horizontal_sum)
                hashVal ^= std::hash<size_t>{}(hsum);

            return hashVal;
        }
    };
}

// Compute an Image_Summary from an image. This is described in detail in the
// lab instructions.
Image_Summary compute_summary(const Image &image) 
{
    const size_t summary_size = 8;
    Image_Summary result;
    Image tmpImage{image.shrink(summary_size + 1, summary_size + 1)};

    int x{};
    int y{};
    int vbit{};
    int hbit{};

    long unsigned int compare{summary_size * (summary_size+1)};

    for (unsigned int i{}; i < compare; i++)
    {
        if (tmpImage.pixel(x, y).brightness() > tmpImage.pixel(x, y+1).brightness())
        {
            result.vertical.push_back(false);
            vbit *= 2;
        }
        else 
        {
            result.vertical.push_back(true);
            vbit *= 2;
            vbit += 1;    
        }

        if (tmpImage.pixel(y, x).brightness() > tmpImage.pixel(y+1, x).brightness())
        {
            result.horizontal.push_back(false);
            hbit *= 2;
        }
        else 
        {
            result.horizontal.push_back(true);
            hbit *= 2;
            hbit += 1;    
        }

        if (y == summary_size -1)
        {
            y = 0;
            x++;
            result.vertical_sum.push_back(vbit);
            result.horizontal_sum.push_back(hbit);
            vbit = 0;
            hbit = 0;
        }
        else
            y++;     
    }

    return result;
}

int main(int argc, const char *argv[]) {
    WindowPtr window = Window::create(argc, argv);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1], ".jpg");
    cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0) {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    }

    auto begin = std::chrono::high_resolution_clock::now();

    std::unordered_map<Image_Summary, std::vector<std::string>> um; 
    for (auto & file: files)    
        um[compute_summary(load_image(file))].push_back(file);


    auto load_time = std::chrono::high_resolution_clock::now();
    cout << "Loading images took: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(load_time - begin).count()
         << " milliseconds." << endl;
    
    int count{};
    for (auto const& key: um)
    {
        if(key.second.size() > 1)
        {
            count++;
            std::cout << "MATCH: ";
            for (auto const& filename : key.second)
                std::cout << filename << " ";
            std::cout << std::endl; 
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    cout << "Total time: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    cout << "Examine time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - load_time).count()
        << " milliseconds." << endl;

    /**
     * TODO:
     * - Display sets of files with equal summaries
     */

    return 0;
}
