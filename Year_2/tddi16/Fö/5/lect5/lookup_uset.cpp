#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

unordered_set<string> read_dict() {
	ifstream f("/usr/share/dict/words");
	unordered_set<string> result;
	string word;
	while (getline(f, word))
		result.insert(word);

	cout << result.size() << " words in the dictionary" << endl;

	return result;
}

#if 0
int main() {
	while (cin >> word) {               //!\tikzmark{sc}!//
		if (d.find(...) == d.end()) //!\tikzmark{sa}!//
			cout << ...;              //!\tikzmark{sb}!//
	}                                   //!\tikzmark{sd}!//
// end DETAIL
}
#endif

int main() {
	unordered_set<string> d = read_dict();

	int count{};
	string word;
	while (cin >> word) {
		if (d.find(word) == d.end())
			cout << "Wrong: " << word << endl;
		count++;
	}

	cout << "Checked " << count << " words" << endl;
	return 0;
}
// end CODE
