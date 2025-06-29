#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <array>
#include <unordered_set>


using std::vector;
using std::string;
using std::cout;
using std::endl;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.


typedef std::unordered_set<std::string> Dictionary;

std::vector<std::string> findNeighbors(std::string const& curr, Dictionary const& words)
{
    std::vector<std::string> neighbors;
    std::string alph{"abcdefghijklmnopqrstuvwxyz"};
    std::string tmp;
    for (unsigned int i{}; i < alph.size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp = curr;
                tmp.at(j) = alph.at(i);
                if (words.find(tmp) != words.end())
                    neighbors.push_back(tmp);
            } 
        }
    return neighbors;
}
/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(Dictionary const& dict, const string &from, const string &to) {
    vector<string> result;
    Dictionary visitedWords{};
    std::unordered_map<std::string, std::string> graph;
    std::queue<std::string> q;
    std::string previous{};

    if(!(dict.find(from) != dict.end()))
        return result;
   
    q.push(from);
    visitedWords.insert(from);
    while(!q.empty())
    {
        std::string curr{q.front()};
        q.pop();
        
        
        if (curr == to)
        {
            std::string step{to};
            while (!step.empty())
            {
                result.push_back(step);
                step = graph[step];
            }
            std::reverse(result.begin(), result.end());
            
            return result;
        }
        
        for (std::string const& neighbor : findNeighbors(curr, dict))
        {
            if (!(visitedWords.find(neighbor) != visitedWords.end()))
            {
                visitedWords.insert(neighbor);
                graph[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result(1, word);
    Dictionary visitedWords{};
    std::unordered_map<std::string, std::string> graph;
    std::queue<std::string>  q;
    std::string previous{};

    if(!(dict.find(word) != dict.end()))
    {
        result.clear();
        return result;
    }
    
    q.push(word);
    visitedWords.insert(word);

    std::string lastWord;

    while (!q.empty())
    {
        std::string curr{q.front()};
        q.pop();

        for (std::string const& neighbor : findNeighbors(curr, dict))
        {
            if (!(visitedWords.find(neighbor) != visitedWords.end()))
            {
                visitedWords.insert(neighbor);
                graph[neighbor] = curr;
                q.push(neighbor);
            }
        }

       lastWord = curr;
    }

        std::string step{lastWord};
            while (!step.empty())
            {
                result.push_back(step);
                step = graph[step];
            }
            result.erase(result.begin());

        
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
    
        result.insert(line);
    }

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
