#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

class Image_Summary {
public:
    // Horizontal increases in brightness.
    std::vector<bool> horizontal;

    // Vertical increases in brightness.
    std::vector<bool> vertical;


};

std::unordered_map<Image_Summary, std::vector<std::string>> m;
for (const auto &file :files)
    m.insert(compute_summary(load_image(file)), file);




   vector<Image> images;
    for (const auto &file : files)
        images.push_back(load_image(file).shrink(image_size, image_size));


 