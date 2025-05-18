#include <iomanip>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

class TablePrinter
{
public:
    TablePrinter(ostream & os, size_t width, size_t columns = 10)
       : stream{os}, columns{columns}, width{width}
    {}

   template <typename T>
   void operator()(T const & val)
   {
        stream << setw(width) << val;
        if ( ++column == columns )
        {
            column = 0;
            stream << '\n';
        }
   }

private:
    size_t column {};
    ostream & stream;
    size_t const columns;
    size_t const width;
};

int main()
{
    vector vals {1,2,3,4,5,6,7,8,9,10,11,12,13};
    for_each(begin(vals), end(vals), TablePrinter{cout, 8, 5});
    cout << endl;
}
