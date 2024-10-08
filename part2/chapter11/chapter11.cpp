#include "chapter11.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::unordered_map;
using std::multimap;
using std::string;
using std::set;
using std::vector;
using std::pair;
using std::make_pair;
using std::ifstream;

int main(int argc, char const *argv[])
{
    // Example: count frequency of words.
    #ifdef CUSTOM
    map<string, size_t> wc;
    string word;
    while (cin >> word) {   // get inputs
        ++wc[word];     // NOTE: if not present, wc[word] = 0
    }
    for (const auto& w: wc) {   // print contents of map
        cout << "Word " + w.first << " occurs " << w.second << " time(s)." << endl;
    }
    #endif

    // Exercise 11.2 - list: linked list, vector: random access, deque: queue, map: word counter, set: unique elements
    // Exercise 11.4 (assuming punctuation can appear anywhere in string) - rewriting while
    #ifdef EXERCISE4
    map<string, size_t> wc;
    string word;
    while (cin >> word) {
        string baseWord;
        for (char ch: word)
            if (!ispunct(ch))
                baseWord += tolower(ch);
        ++wc[baseWord];
    }
    #endif

    // Exercise 11.7
    #ifdef EXERCISE7
    map<string, vector<string>> fMap;
    string fName, name;
    cout << "Enter family name: ";
    cin >> fName;
    cout << "Enter children names: ";
    vector<string> cNames;
    while (cin >> name) {
        cNames.push_back(name);
    }
    fMap[fName] = cNames;
    cout << endl;
    for (auto it = fMap.cbegin(); it != fMap.cend(); ++it) {
        cout << "Family name: " << it->first;
        for (auto& n: it->second)
            cout << " Child name: " << n;
        cout << endl;
    }
    #endif

    // Example of set
    #ifdef CUSTOM
    set<string> exclude = {"the", "but", "and", "or", "an", "a"};
    #endif
    
    // Exercise 11.12 & 11.13
    #if defined(EXERCISE12) || defined(EXERCISE13)
    string s; int i;
    vector<pair<string, int>> v;
    cout << "Enter items: ";
    while(cin >> s >> i && s != "\n") {
        // v.push_back(make_pair(s, i));           // way 1 - preferable, because easier to create
        // v.push_back(pair<string, int>(s, i));   // way 2
        v.push_back({s, i});                         // way 3 - preferable, because easier to create     
    }
    cout << endl;
    for (const auto& e: v) {
        cout << "Element1 - " << e.first << ", Element2 - " << e.second << endl;
    }

    // Iterating through map object.
    map<char, int> cmap;
    for (const char ch: "flabbergasted") 
        if (ch != '\0')
            ++cmap[ch];
    for (auto it = cmap.begin(); it != cmap.end(); ++it) {
        cout << "Key: " << it->first << ", Value: " << it->second << endl;
    }
    
    // Iterating through set object.
    set<string> exclude = {"the", "but", "and", "or", "an", "a"};
    for (auto it = exclude.cbegin(); it != exclude.cend(); ++it) {
        cout << "Excluded element: " << *it << endl;
    }
    #endif

    // Exercise 11.17 - all legal except b, because multiset doesn't have push_back(equivalent of back_inserter)
    // Exercise 11.18 - map<char, int>::const_iterator

    // Using return value of insert
    #ifdef CUSTOM
    while (cin >> word) {   // get inputs
        auto ret = wc.insert({word, 1});    // initialize count
        if (!ret.second)                    // word was already added (insertion failure)
            ++ret.first->second;            // first = iterator, second = count. Increment if present. Note: ret.second is bool.
    }
    #endif
    
    // Exercise 11.23
    #ifdef EXERCISE23
    multimap<string, vector<string>> fMap;
    string fName, name;
    // stop when family name or child name is 'X'.
    while(true) {
        cout << "Enter family name: ";
        cin >> fName;
        if(fName == "X")
            break;
        cout << "Enter children names: ";
        vector<string> cNames;
        while (cin >> name && name != "X") {
            cNames.push_back(name);
        }
        fMap.insert({fName, cNames});
        cout << endl;
    }
    for (auto it = fMap.cbegin(); it != fMap.cend(); ++it) {
        cout << "Family name: " << it->first;
        for (auto& n: it->second)
            cout << " Child name: " << n;
        cout << endl;
    }
    #endif

    /**
     * word transformation
     * given a file containing mappings and another file containing text,
     * decrypt the text using mappings.
    **/
    #ifdef CUSTOM
    ifstream mf(pwd + "mapping.txt");
    ifstream ip(pwd + "input.txt");
    if (!ip || !mf)
        throw std::runtime_error("Error opening the file(s)");
    wordTransform(mf, ip);
    mf.close();
    ip.close();
    #endif

    // Exercise 11.38
    #ifdef EXERCISE38
    unordered_map<string, size_t> wc;
    string word;
    while (cin >> word) {   // get inputs
        ++wc[word];     // NOTE: if not present, wc[word] = 0
    }
    for (const auto& w: wc) {   // print contents of map
        cout << "Word " + w.first << " occurs " << w.second << " time(s)." << endl;
    }
    #endif

    return 0;
}
