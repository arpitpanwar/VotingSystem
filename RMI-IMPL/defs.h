#ifndef DEFS_H

//#define ADDVOTER "ADDVOTER"
//#define ZEROIZE "ZEROIZE"
//#define VOTEFOR "VOTEFOR"
//#define CANDIDATES "CANDIDATES"
//#define COUNT "COUNT"

#include<list>
#include<map>
#include<string>

using namespace std;

extern map<int, bool> voterlist;

extern list<std::string> candidateList;

extern map<std::string, int> votecounts;

#endif
