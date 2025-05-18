#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <array>


using std::vector;
using std::string;
using std::cout;
using std::endl;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.


struct Node
{
// Constructor
    Node()
        : previous{""}, visited{false}, edges{} {}

// Member variables
    std::string previous;
    bool visited;
    std::vector<std::string> edges;
};

typedef std::unordered_map<std::string, Node> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 * 
 * 
 */
vector<string> find_shortest(Dictionary const& dict, const string &from, const string &to) {
    vector<string> result;
    
//----------BFS----------//
    Dictionary graph{dict};
    std::queue<std::string> q;

    graph[from].visited = true;
    graph[from].previous = "";
    q.push(from);

    while(!q.empty())
    {
        std::string curr{q.front()};
        q.pop();
        
        
        if (curr == to)
        {
            for (std::string word{to}; !word.empty(); word = graph[word].previous)
                result.push_back(word);

            std::reverse(result.begin(), result.end());
            
            return result;
        }
        
        for (std::string const& neighbor : graph[curr].edges)
        {
            if (!graph[neighbor].visited)
            {
                graph[neighbor].visited = true;
                graph[neighbor].previous = curr;
                q.push(neighbor);
            }
        }
    }
//-----------------------//

    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result(1, word);
    Dictionary graph{dict};
    std::queue<std::string>  q;

    graph[word].visited = true;
    graph[word].previous = "";
    q.push(word);

    std::string lastWord;


    while (!q.empty())
    {
        std::string curr{q.front()};
        q.pop();


        for (std::string const& neighbor : graph[curr].edges)
        {
            if (!graph[neighbor].visited)
            {
                graph[neighbor].visited = true;
                graph[neighbor].previous = curr;
                q.push(neighbor);
            }
        }

       lastWord = curr;
    }

        for (std::string tmp{lastWord}; !tmp.empty(); tmp = graph[tmp].previous)
            result.push_back(tmp);
        
        std::reverse(result.begin(), result.end());
        result.pop_back();
        
        return result;
}


/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {

    string line;
    Dictionary result;
    while (std::getline(std::cin, line)) 
    {
        if (line == "#")
            break;
    
        result[line];
    }

////////////////////////////
    std::string alph{"abcdefghijklmnopqrstuvwxyz"};
    for (auto& key : result)
    {
        for (unsigned int i{}; i < alph.size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::string tmp{key.first};
                tmp.at(j) = alph.at(i);
                if (result.find(tmp) != result.end())
                    result[key.first].edges.push_back(tmp);
            } 
        }
    }
//////////////////////////
    return result;
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const vector<string> &chain) {
    if (chain.empty()) {
        cout << "ingen lösning" << endl;
    } else {
        cout << chain.size() << " ord" << endl;
        print_chain(chain);
    }
}

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
