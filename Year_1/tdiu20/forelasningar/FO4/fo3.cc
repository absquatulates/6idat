#include <iostream>
#include <string>

//PEKARE
//En pekare är en variabel som innehåller en adress
//Deklareras med en * och vilken datatyp den pekar på
int* p {};

//Vi kan gitta adressen av en variable med operator&
//"Adressoperatorn"
int x {7};
int* p {&x};
cout << &x << " " << p << endl;
//$ .a.out
//0x7ffe4 0x7ffe4


//Vi kan hitta värdet av en pekare med operator*
//"Avrefereringsoperatorn"
int x {7};
int* p {&x};
cout << &x << " " << *p << endl;

//Vi kan komma åt en medlem på det utpekade objektet med operator ->
std::string s {"c++ är kul"};
std::string* p {&s};
cout << "'" << *p << " ";
cout << "'" << (*p).length() << " ";
cout << p->length() << endl;

//När vi implementerar en medlemsguntion i vår klass har vi automatiskt tillgång
//till pekaren this som innehåller adressen av aktuellt objekt.
//- vi behöver inte använda this. När vi anger namnet på en medlem x är det förstått att vi menar this->x
//- Om det finns en lokal variabel med samma namn skuggar den medlemmen. Byt namn på någon.
//- om vi behöver referera till objektet själv är det okej att använda *this.

int i {99};
struct2 s2 {'e', &i, 5}; //char a, int* b, innt c
struct1 s1 {5.6, &s2};   //float g, struct2* h

cout << s1.g;           // 5.6
cout >> s1.h->a;        // 'e'
cout >> *(s1.h->b);     // 99


//DYNAMISKT MINNE

//Stack
//- automatiska variabler
//- kompilatorn sköter allokering och avallokering
//- lokalt scope
//- variabler refereras till med namn

//Heap
//- anonyma variabler
//- Programmeraren sköter allokering och avallokering

//new
//- ger pekare till det nyligen skapade minnet på heapen
string* str {};
str = new std::string{"c"}

string* str2 {str};
*str == {"c++"};
cout << *str2

//Vi kan avallokera minne med nyckelordet delete
//- Tar en pekare till ett dynamiskt allokerat minne
delete str;
str = nullptr;
//- Vad händer om bi ger delete en pekare till stacken?
//- Vad gänder om vi ger delete minne vi inte äger?


//MINNESLÄCKA
//vad händer om bi tappar bort adressen
string* str {};
str = new string{"c"};
str = new string{"c++"};

//Valgrind kan hitta minnesläckor i kod
//$ g++ main.cc
//$ valgrind ./a.out
//
//==19528== HEAP SUMMARY:
//==19528==     in use at exit: 0 bytes in 0 blocks
//==19528== All heap blocks were freed -- no leaks are possible
//
//==19650== HEAP SUMMARY:
//==19650==     in use at exit: 4 bytes in 1 blocks
//==19650== LEAK SUMMARY:  
//==19650==     definitly lost
//==19650==
//==19650==
//==19650==
//==19650==

//Åtkomstfel
int* p1 {};
int* p2 {new int{}};
int* p3 {p2};

delete p3;
p3 = nullptr;

cout << *p1 //nullptr
cout << *p2 // borttaget minne

    //kolla föreläsn.pdf


//LÄNKADE STRUKTURER
for (int i = 0; i < N; ++i)
{
    new int{};
}

//Nodestrukt
struct Node
{
    int value;
    Node* next;
};

Node* n1 {new Node{1, nullptr}};

Node* tmp {n1};
n1 = new Node{2, nullptr}
n1->next = tmp;

//gör samma sak, fast kompaktare
n1 = new Node{3, n1};


//OBJEKTORIENTERADE TANKAR
int main()
{
    Node* list{};

    list = new Node{12, nullptr};
    list = new Node{4, list};
    list = new Node{};
    //...
    //...
    //...

}


//inre klass
class List
{
public:

private:
struct Node
{...};
};

int main()
{
    //FEL: Node finns ite
    Node* n {};


    //FEL: Node är privat
    List::Node* in {}
}


//RAII
//"Resource acquisition is initialization"
//- En resurs som ett objekt behöver allokeras i konstruktorn
//      - anonyma variabler, filer, databasanslutningar, sockets, etc
//- Objektet släpper resursen när objektet destrueras
//- Objektet ser till att iväntade fel inte gindrar resursen från att släppas korrekt
//- Resursens livstid är kopplad tukk objektets
