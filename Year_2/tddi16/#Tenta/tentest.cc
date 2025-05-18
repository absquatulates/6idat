#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

struct Date
{
    int year;
    int month;
    int day;
};

struct Transaction
{
    int id;
    Date date;
    int price;
    std::string seller;
    std::string description;
};

struct SellerInfo
{
    int totalprice;
    std::vector<Transaction> transactions;
};


std::unordered_map<std::string, SellerInfo> dataToScreen(const std::vector<Transaction> &table)
{
    std::unordered_map<std::string, SellerInfo> info;
    for (const Transaction &t : table)
    {
        info[t.seller].totalprice += t.price;
        info[t.seller].transactions.push_back(t);
    }
    return info;
}




int main()
{
    std::vector<Transaction> input;
    std::unordered_map<std::string, SellerInfo> info{dataToScreen(input)};

}


using namespace std;

1

a
13 24 26 6 18 19 30 8
30 24 13 18 19 26 8 6
26 6 19 18 30 8 13 24
19 30 18 13 26 6 8 24

b
1. Ersätter 26 med en tombstone så att kommande hashningar
   vet att det går att stoppa in ett värde där. Elementet
   fungerar som ett null-element då det visar att det
   inte finns något element på den platsen.
   En tombstone skiljer sig från ett null-element i
   uppslagningen då uppslagningen inte avslutas
   när ett sådant element hittas utan i det fallet
   fungerar som ett "vanligt" element.
2. Tar bort elementet och kollar igenom de iterera
   igenom arrayen tills ett null hittas.
   Varje element påvägen tas bort och sätts in igen
   med vår insert-funktion. Då hamnar alla element
   på rätt plats

c
Implementationen kan ha allokerat en ny dubbelt så
stor array på annan plats i minnet och kopierat
över de element som redan fanns. 
Då hashfunktionen ändras "hashas" alla element in 
på nytt i nya arrayen vid kopiering. 
Detta med insert-funktionen

2.
A B H C F G E 
A B C F E H G

3.
 1-a
 2-b
 3-c
 4-e
 5-d

4.
 a - O(n)
 b - O(logn) * O(n) = O(nlogn)
 c - O(n) * O(n) = O(n²)
 d - O(nlogn) + O(2n) + nO(1) = O(nlogn)

5.
 a.
 För att beräkna ett medelvärde behöver jag endast
 lagra de k senaste mätvärderna. Jag lagrar detta
 i en kö implementerad med en cirklär array av integers,
 storlek k. Detta ger O(1) insättning och borttagning. 
 Jag behöver också lagra en integer med summan av
 köns element.

 b.
 Kön initieras med storlek k. Jag sätter sedan in
 k 0:or i kön. Medelvärdet sätts till 0.

 c.
  1. läser nästa mätvärde
  2. tar bort ett element från kön
  3. Subtraherar elementet från summan
  4. lägger till det nya mätvärdet i kön
  5. adderar mätvärdet till summan
  6. skriver ut summan/k för att få medelvärdet

 d.
  Tidskomplexiteten blir O(1) då listan redan är 
  initierad och varje steg i instättningen av det 
  nya mätvärdet tar O(1). 
  Dvs 5*O(1) = O(1)

 e.
  O(n) då det tar O(1) att hantera varje element och
  vi gör detta n gånger. Dvs n*O(1) = O(n)

 f.
  Jag lagrar k värden.
  Dvs O(k) minnesallokering

6.
 a)
  Om jag lagrar alla städer och vägar som en graf, där alla städer är noder och
  vägarna är bågar med längden som vikt. Jag vill därefter hitta den vägen med 
  minst vikt som fortfarande skapar en väg till alla noder.
  Jag gör detta på följande vis (Prims algoritm):
  1. skapar en prioritetskö som sorteras på bågens vikt
  2. Lagrar en bool visited = false i varje node
  3. Lägger till alla bågar från en startnode i prioritetskön.
  4. Sätter visited till true i startnoden
  5. Plockar ut bågen med minst vikt ur prioritetskön
     Om bågen leder till en besökt node görs 5 igen
  6. Markerar den nya noden som besökt och lägger till dens bågar i prioritetskön
 
  5-6 repeteras tills alla noder är besökta, dvs prioritetskön är tom
 
 b)
  Prims algoritm har tidskomplexitet O(|E|log|V|)
 
 c)
 d)






1.
 1-a
 2-b
 3-n/a
 4-d
 5-c

 Heap-sort, syns genom att de sista elementen i listan är sorterade samt
            att det största elementet är längst till vänster, resterande
            element är i form av en heap.

2.
 a) 
  nej, eftersom att alla vänsternoder inte är mindre än rotnoden och alla
  högerelement inte är större än rotnoden. Det är dock ett binärt träd, men
  inte ett sökträd i denna implementation

 b)
  Ja, eftersom att det inte har några "hål" i sig. Det skulle inte vara komplett
  om t.ex noden 38 inte fanns eftersom att det då finns ett "hål" i trädet när vi
  gör en level-order travesering
 
 c)
  Ja, eftersom att rotnoden är det minsta värdet i trädet och alla barn-noder är
  större än sin föräldernod.
 
 d)
  3 7 8 15 20 12 28 42 21 38 42 22

2.
 