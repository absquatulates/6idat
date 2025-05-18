//Funktionsöverlagring
//- I c++ kan flera funktioner ha samma namn
//- Antal parametrar och deras typer avgör vilken som anropas
//- Kompilatorn väljer den som matchar

class Vector
{
public:

    Vector operator+(Vector const& v) const;

private:
    int x;
    int y;
};

Vector Vector::operator+(Vector const& v) const
{

}