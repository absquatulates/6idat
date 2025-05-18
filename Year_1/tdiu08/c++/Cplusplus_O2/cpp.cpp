// Cplusplus_O2
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;


//1. Beräkna N-fakultet

int factorial(int const n)
{
  if (n == 0)
    {
      return 1;
    }
  else
    {   
      return n * factorial(n-1);
    }   

}

void factorial_text()
{
  int n {}; //------------------------------------------------//"{}"

  cout << "Mata in ett heltal: ";
  cin >> n;
  cout << "Fakulteten av " << n << " är " << factorial(n) << "\n";
}


//2. Multiplicera en sträng

string mult(string const& text,
	    int const multiplier) 
{
  string new_text;

  for (int i = 0; i < multiplier; ++i)
    {
      new_text += text;
    }

  return new_text;
}

void mult_get()
{

  string text;
  int multiplier {};  //<-----------------------------------------------------------------------//lagt till "{}"

  cout << "Mata in en text och ett heltal: ";
  cin >> text;
  cin >> multiplier;
  cin.ignore(1000, '\n');
  cout << "Den multiplicerade texten är " << mult(text, multiplier) << '\n';
}


//3. Byta värden på ett heltal och ett flyttal

void byt(int & a,
	 double & b)
{
  double c {};  //<-----------------------------------------------------------------------------//lagt till "{}"
  
  c = static_cast<double>(ceil(b));
  b = static_cast<int>(a);
  a = static_cast<int>(c);

}

void byt_text()
{
  int a {};       //<---------------------------------------------------------------------------//lagt till "{}"
  double b {};    //<---------------------------------------------------------------------------//lagt till "{}"
  cout << "Mata in ett heltal och ett flyttal: ";
  cin >> a >> b;
  byt(a,b);
  cout << "Heltalets värde är nu " << setw(1) << a << endl;
  cout << "Flyttalets värde är nu " << setw(2) << fixed << setprecision(1) << b << endl;
}


//4. Beräkna totala längden samt medellängden på två strängar

void two_strings(string const& text_1,
		 string const& text_2,
		 int & total_length,
		 double & mean_length)
{
  total_length = text_1.length() + text_2.length();
  mean_length = (static_cast<double>(total_length))/2.0;
}

void get_strings()
{
  string text_1;
  string text_2;
  int total_length {};
  double mean_length {};


  cout << "Mata in två ord: ";
  cin >> text_1 >> text_2;
  two_strings(text_1, text_2, total_length, mean_length);

  cout << "Totallängd: " << total_length << endl;
  cout << "Medellängd: " << fixed << setprecision(1) <<  mean_length << endl;
}


// Menu choice

void choice(int const Val)
{

  switch (Val)
    {
    case 1:
      factorial_text();
      break;
    case 2:
      mult_get();
      break;
    case 3:
      byt_text();
      break;
    case 4:
      get_strings();
      break;
    case 5:
      cout << "Ha en bra dag!";
      break;
    default:
      cout << "Fel val!\n";
    }
}


//HUVUDPROGRAM//

int main()
{
  int Val {};    //<---------------------------------------------------------------------------//lagt till "{}"

  cout << "Välkommen till huvudmenyn!\n";
  while (Val != 5) 
    {

      cout << "1. Beräkna N-fakultet.\n";
      cout << "2. Multiplicera en sträng.\n";
      cout << "3. Byta värden på ett heltal och ett flyttal.\n";
      cout << "4. Beräkna totala längden samt medellängden på två strängar.\n";
      cout << "5. Avsluta programmet.\n";
      cout << "Val: ";
      cin >> Val;
      choice(Val);              
    }

  return 0;
}
