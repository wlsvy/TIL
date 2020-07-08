#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>

//데이터를 삭제할 때에도 조심스럽게 선택할 것이 많다

namespace Item09 {
	using namespace std;

	inline void RunSample() {

		auto isBad = [](int i) { return i % 2 == 0; };

		//컨테이너에서 특정한 값을 가진 객체를 모두 없애려면:
		{
			//컨테이너가 vector, string 혹은 deque이면, erase - remove 합성문을 씁니다.
			vector<int> c;
			c.erase(remove(c.begin(), c.end(), 1963),
				c.end());
		}
		{
			//컨테이너가 list이면, list::remove를 씁니다.

			/*
				list에도 erase-remove 합성문이 통하지만 멤버 함수인 remove가 더 효율적입니다.
			*/
			list<int> c;
			c.remove(1963);
		}
		{
			//컨테이너가 표준 연관 컨테이너이면, erase 멤버 함수를 씁니다.
			multiset<int> c;
			c.erase(1963);
		}
		
		//컨테이너에서 특정한 술어 구문을 만족하는 객체를 모두 없애려면:
		{
			//컨테이너가 vector, string, deque이면, erase - remove_if 합성문을 씁니다.
			vector<int> c;
			c.erase(remove_if(c.begin(), c.end(), isBad),
				c.end());
		}
		{
			//컨테이너가 list이면, list::remove_if를 씁니다.
			list<int> c;
			c.remove_if(isBad);
		}
		{
			//표준 연관 컨테이너는 두 가지 방법이 있습니다.
			
			multiset<int> c;
			multiset<int> goodValues;
			/*
				연관 컨테이너는 트리 노드 구조로 구성되기에 시퀀스 컨테이너의 경우처럼 remove를 통해 원소들의 위치를 바꿔버리는 동작은 안됩니다.
				remove_if(c.begin(), c.end(), [](int i) { return i % 2 == 0; }); //안됩니다.
			*/

			for (int i = 0; i < 7; i++) c.insert(i);

			// 삭제되지 말아야 할 값들을 c에서 goodValues로 옮깁니다.
			remove_copy_if(c.begin(), c.end(),    
				inserter(goodValues,    
					goodValues.end()),  
				isBad);

			// c와 goodValues의 내용을 맞바꿉니다.
			c.swap(goodValues);

			/*
				이 방법의 단점은 삭제되지 않는 요소를 모두 복사했다가 옮기기 때문에 복사에 걸리는 비용이 우리가 생각한 가격보다 비싸다는 것입니다.
			*/

			c.clear();
			for (int i = 0; i < 7; i++) c.insert(i);

			//두번째 방법 for 루프
			/*
				컨테이너의 어떤 요소가 erase될 때, 이 요소를 가리키고 있는 모든 반복자들이 한꺼번에 무효화되고 맙니다.
				일단 단순히 c.erase(i)를 한다면 동작이 끝나자마자 i는 바로 무효화됩니다.
				이후 루프의 ++i부분에서 무효화된 반복자를 증가시켜 에러가 납니다.

				이 문제를 해결하기 위해서 erase를 호출하기 전에 반복자 i가 c의 다음 요소를 가리키도록 세팅하면 됩니다.(postfix ++)를 활용합니다.
			*/
			for (auto i = c.begin(); i != c.end();) {
				//원소를 삭제하는 경우 지우기 전에 미리 반복자를 한단계 전진시킵니다.
				if (*i % 2 == 0) {
					c.erase(i++);
				}
				else {
					i++;
				}
			}
		}
		//루프 안에서 무엇인가를 하려면(객체 삭제도 포함해서)
		{
			/*
				컨테이너가 표준 시퀸스 컨테이너이면, 컨테이너 요소를 하나씩 사용하는 루프를 작성합니다. 
				이때 erase를 호출할 때마다 그 함수의 반환값으로 반복자를 업데이트하는 일을 꼭 해야 합니다.
			*/
			vector<int> c;
			for (auto i = c.begin(); i != c.end();) {
				if (isBad(*i)) {
					cout << "Erasing " << *i << '\n';

					// erase의 반환값을 i에 저장해서 유효성을 유지합니다.
					i = c.erase(i);        
				}                        
				else ++i;
			}
		}
		{
			/*
				루프 안에서 삭제한 데이터에 대한 로그를 기록한다고 합시다.
				연관 컨테이너의 경우에는 삭제를 위한 루프에 로그를 기록하는 코드를 삽입하기만 하면 됩니다.
			*/
			multiset<int> c;

			for (auto i = c.begin(); i != c.end();) {
				if (isBad(*i)) {
					cout << "Erasing " << *i << '\n'; 
					c.erase(i++);
				}
				else ++i;
			}
		}
		/*
			list의 경우 위의 두 가지 방법을 모두 사용할 수 있지만, 일반적인 관례는 vector/string/deque에 쓰는 방법처럼 list를 처리하는 것입니다. 
			list도 마찬가지로 시퀸스 컨테이너이기 때문입니다.
		*/
	}
}