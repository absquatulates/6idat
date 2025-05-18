#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> read_dict() {
	ifstream f("/usr/share/dict/words");
	vector<string> result;
	string word;
	while (getline(f, word))
		result.push_back(word);

	cout << result.size() << " words in the dictionary" << endl;

	return result;
}

#if 0
int main() {
	while (cin >> word) {             //!\tikzmark{c}!//
		if (find(...) == d.end()) //!\tikzmark{a}!//
			cout << ...;            //!\tikzmark{b}!//
	}                                 //!\tikzmark{d}!//
// end DETAIL
}

template <typename Iter, typename Elem>
Iter find(Iter begin, Iter end, Elem elem) {

	for (Iter i = begin; i != end; ++i) { //!\tikzmark{fc}!//
		if (*i == elem) { //!\tikzmark{fa}!//
			return i;
		}                 //!\tikzmark{fb}!//
	}                                     //!\tikzmark{fd}!//
	return end;
}
// end FIND
#endif

int main() {
	vector<string> d = read_dict();

	int count{};
	string word;
	while (cin >> word) {
		if (find(d.begin(), d.end(), word) == d.end())
			cout << "Wrong: " << word << endl;
		count++;
	}
	cout << "Checked " << count << " words" << endl;
	return 0;
}
// end CODE
