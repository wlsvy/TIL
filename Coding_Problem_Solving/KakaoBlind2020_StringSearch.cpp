/*
  ===========
  첫번째 방법 - 트라이(Trie)
  ===========
  
포인트
	
	트라이trie 알고리즘
	정방향, 역방향 문자열에 대해 분리해서 trie 구현
	모든 문자가 ? 인 경우 주의

실수
	트라이 초기 insert 미스
	fill을 사용해서 root 배열 new Trie로 초기화 한 것. - 메모리 할당은 한번만 일어나고 얕은 복사 발생
*/
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <queue>

using namespace std;

struct Trie {
	Trie *next[26];
	unsigned int count = 0;

	void Insert(string & s, int pos) {
		count++;

		if (pos == s.size() - 1) return;

		auto ni = s[pos + 1] - 'a';

		if (next[ni] == nullptr) next[ni] = new Trie;
		next[ni]->Insert(s, pos + 1);
	}

	int find(string &s, int pos) {
		if (s[pos + 1] == '?') {
			return count;
		}
		auto ni = s[pos + 1] - 'a';

		if (next[ni] == nullptr) return 0;
		return next[ni]->find(s, pos + 1);
	}
};

Trie* root[10001];
Trie* reroot[10001];

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer(queries.size());
	for (int i = 0; i < 10001; i++) {
		root[i] = new Trie;
		reroot[i] = new Trie;
	}

	for (int i = 0; i < words.size(); i++) {
		int size = words[i].size();

		root[size]->Insert(words[i], -1);

		reverse(words[i].begin(), words[i].end());
		reroot[size]->Insert(words[i], -1);
	}

	for (int i = 0; i < queries.size(); i++) {
		auto q = queries[i];
		int size = q.size();

		if (q[0] == '?') {
			reverse(q.begin(), q.end());
			answer[i] = reroot[size] ? reroot[size]->find(q, -1) : 0;
		}
		else {
			answer[i] = root[size] ? root[size]->find(q, -1) : 0;
		}
	}

	return answer;
}

/*
  ===========
  두번째 방법 - 해쉬
  ===========
  
  포인트
	
	트라이trie 알고리즘
	정방향, 역방향 문자열을 전부 해쉬맵에 넣는다.
	모든 문자가 ? 인 경우 주의
 */
 
 #include <string>
#include <vector>
#include <unordered_map>

using namespace std;



bool match(string &query, string &word) {
	if (query.length() != word.length()) {
		return false;
	}

	for (int i = 0; i < query.length(); ++i) {
		if (query[i] != '?' && query[i] != word[i]) {
			return false;
		}
	}

	return true;
}

void create_map(vector<string> &words, unordered_map<string, int> &map) {
	for (string &word : words) {
		for (int i = 0; i < word.length(); ++i) { //query가 모두 ? 인 경우가 있으니 i 초기값은 0 
			map[word.substr(0, i) + string(word.length() - i, '?')]++;
			map[string(i, '?') + word.substr(i)]++;
		}
	}
}
vector<int> solution(vector<string> words, vector<string> queries) {
	unsigned long max_length = 0;

	for (string &word : words) {
		max_length = max(max_length, word.length());
	}

	vector<int> answer;

	/*
			max_length가 1000 초과일때는 왜 단순비교를 하게끔 해놨는지 실행해보니까,
			해쉬써서 속도가 느려서 효율성 테스트4,5 시간초과.

			하지만 앞에 1000넘는 경우만 따로 단순비교로 처리해주면 통과
			테스트 케이스가 완벽하지 않아서 임시방편으로 하신거같은데 이것도 창의적이네요
	*/
	if (max_length > 1000) {
		for (string &query : queries) {
			int num_matched = 0;

			for (string &word : words) {
				if (match(query, word)) {
					num_matched++;
				}
			}

			answer.push_back(num_matched);
		}
	}
	else {
		unordered_map<string, int> map;
		create_map(words, map);

		for (string &query : queries) {
			answer.push_back(map[query]);
		}
	}

	return answer;
}
