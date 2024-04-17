#pragma region PRE DEFINE

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>

template <class Element>
std::ostream& operator<< (std::ostream& os, const std::vector<Element> & c);
template <class Element>
std::ostream& operator<< (std::ostream& os, const std::list<Element> & c);
template <class Element>
std::ostream& operator<< (std::ostream& os, const std::set<Element> & c);
template <class Key, class Value>
std::ostream& operator<< (std::ostream& os, const std::unordered_map<Key, Value> & c);
template <class Key, class Value>
std::ostream& operator<< (std::ostream& os, const std::map<Key, Value> & c);

template<typename T, typename U>
std::ostream& operator<< (std::ostream& os, const std::pair<T, U> & p) {
	std::cout << "{ " << p.first << ", " << p.second << " }";
	return os;
}

#define PRINT_CONTAINER(container)	\
std::cout << "[ ";					\
for (auto& val : container) {		\
	std::cout << val << " ";		\
}									\
std::cout << " ]" << std::endl;		\
return os;							\


template <class Element>
std::ostream& operator<< (std::ostream& os, const std::vector<Element> & c) { PRINT_CONTAINER(c) }
template <class Element>
std::ostream& operator<< (std::ostream& os, const std::list<Element> & c) { PRINT_CONTAINER(c) }
template <class Element>
std::ostream& operator<< (std::ostream& os, const std::set<Element> & c) { PRINT_CONTAINER(c) }
template <class Key, class Value>
std::ostream& operator<< (std::ostream& os, const std::unordered_map<Key, Value> & c) { PRINT_CONTAINER(c) }
template <class Key, class Value>
std::ostream& operator<< (std::ostream& os, const std::map<Key, Value> & c){ PRINT_CONTAINER(c) }

#pragma endregion



inline void RunOutstreamSample() {
	using namespace std;
	std::string st;
	cout << endl << "===========VECTOR==============" << endl << endl;
	cout << vector<int>(10, 1);
	cout << vector<string>(10, "vector");
	cout << vector<vector<string>>(10, vector<string>(3, "nested_vector"));

	cout << endl << "===========LIST==============" << endl << endl;
	cout << list<int>(10, 2);
	cout << list<string>(10, "List");

	cout << endl << "===========SET==============" << endl << endl;
	set<int> si;
	si.insert(100);
	si.insert(200);
	si.insert(300);
	cout << si;


	set<string> ss;
	ss.insert("set_0");
	ss.insert("set_1");
	ss.insert("set_2");
	cout << ss;

	cout << endl << "===========UNORDERED_MAP==============" << endl << endl;
	unordered_map<int, int> umi;
	umi.insert(make_pair(1, 1));
	umi.insert(make_pair(2, 2));
	umi.insert(make_pair(3, 3));
	cout << umi;

	unordered_map<int, vector<string>> umvs;
	umvs.insert(make_pair(1, vector<string>(3, "string_vector")));
	umvs.insert(make_pair(2, vector<string>(3, "string_vector")));
	umvs.insert(make_pair(3, vector<string>(3, "string_vector")));
	cout << umvs;
}
