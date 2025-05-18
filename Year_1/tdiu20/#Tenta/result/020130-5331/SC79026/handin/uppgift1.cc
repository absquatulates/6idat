#include <iostream>
#include <string>
#include <stdexcept>


class Four_letter_word
{
public:

    Four_letter_word(std::string s)
        :s{s}
    {
        check();
    }

    std::string get()
    {
        return s;
    }

    void set(std::string const& new_s)
    {
        s = new_s;
        check();
    }
    
private:

    std::string s{""};
    
    void check()
    {
        if (s.length() != 4)
        {
            throw std::length_error("Must be 4.");
        }
    }

};
    

int main()
{
    Four_letter_word s{"heja"};

    std::cout << s.get() << std::endl; 
    
    s.set("hej");

    std::cout << s.get() << std::endl;


    return 0;
}
