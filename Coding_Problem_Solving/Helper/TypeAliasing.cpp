#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using UCHAR = unsigned char;
using UINT = unsigned int;
using ULONG = unsigned long;
using LL = long long;
using ULL = unsigned long long;

#define FORI(n) for(int i = 0; i < (n); i++)
#define FORJ(n) for(int j = 0; j < (n); j++)
#define FORK(n) for(int k = 0; k < (n); k++)
#define FORIR(n) for(int i = (n) - 1; i >= 0; i--)
#define FORJR(n) for(int j = (n) - 1; j >= 0; j--)
#define FORKR(n) for(int k = (n) - 1; k >= 0; k--)

using VC = std::vector<char>;
using VVC = std::vector<std::vector<char>>;
using VB = std::vector<bool>;
using VVB = std::vector<std::vector<bool>>;
using VI = std::vector<int>;
using VVI = std::vector<std::vector<int>>;
using VS = std::vector<std::string>;
using VVS = std::vector<std::vector<std::string>>;
using UMII = std::unordered_map<int, int>;
using UMIVI = std::unordered_map<int, std::vector<int>>;
using MII = std::map<int, int>;
using MIVI = std::map<int, std::vector<int>>;
using PII = std::pair<int, int>;
using PIVI = std::pair<int, std::vector<int>>;
