# count, find, binary_search, lower_bound, upper_bound, 그리고 equal_range를 제대로 파악해 두자

#### 컨테이너에서 어떤 값을 찾고 싶을 때, cout, count_if, find, find_if, binary_search, lower_bound, upper_bound를 사용할 수 있습니다.

이후부터는 count나 find 같은 _if의 변종을 가진 알고리즘은 _if를 생략하겠습니다. 술어 구문을 받아들이는 binary_search, lower_bound와 upper_bound, equal_range의 변종도 무시하겠습니다.



#### 탐색 전략의 선택은 반복자가 정렬된 범위를 지정하고 있느냐에 상당 부분이 걸려 있습니다. 만일 그렇다면 binary_search, lower_bound, upper_bound, equal_range 등의 알고리즘(대개 로그 시간에 수행됩니다. 항목 34를 참고하세요)을 써서 높은 속도를 얻을 수 있습니다.

정렬되지 않은 범위가 정렬된다는 것은 정렬 이외의 또 하나의 변화를 뜻합니다. 두 개의 값이 같은지를 비교할 때 사용되던 상등성(equality) 기준이 동등성(equivalence)으로 바뀐다는 것이죠(항목19 참조).



- count나 find 알고리즘은 상등성을 가지고 탐색하는 반면, binary_search, lower_bound, upper_bound, equal_range는 동등성을 사용한다는 사실만 주의하시면 됩니다.

#### 하지만 정렬된 범위가 아니라면 선형 시간의 알고리즘인 count나 find 밖에 사용할 수 없습니다.

값의 존재 여부를 점검하는 목적으로는 count를 사용한 코드가 약간 더 간단합니다. 그와 동시에 탐색이 성공했을 때 효율이 좋지 않아서 문제죠.

왜냐하면, find는 탐색이 성공하면 바로 끝내지만, count는 같은 값이 더 있는지를 찾기 위해 범위의 끝까지 갑니다.(선형탐색)



#### 정렬된 범위에서 어떤 값이 있는지를 알아 보는데에는 binary_search가 그만입니다. 표준 C 라이브러리의 bsearch와 달리, binary_search는 값이 있는지, 없는지를 나타내는 bool 값만을 반환합니다.

```c++
//정렬된 벡터 입니다.
		vector<int> vi;
		generate_n(back_inserter(vi), 100, [count = 0]() mutable {return count++ / 3; });

		if (binary_search(vi.begin(), vi.end(), 10)) {
			//10 이 컨테이너 안에 있습니다.
		}
		else {
			//없습니다.
		}
```



#### 정렬된 범위가 있고 그 안에서 특정 값을 갖는 객체의 위치를 찾고 싶다면, equal_range가 우선적인 답입니다만, lower_bound도 고려해 보는 것이 좋습니다.

값을 찾는 데에 lower_bound를 호출하면, 이 알고리즘은 원하는 값을 가진 객체의 첫째 사본(찾았을 때) 아니면 그 값이 삽입될 적당한 위치(찾지 못했을 때)를 가리키는 반복자를 반환합니다.

find와 마찬가지로, lower_bound의 결과(반복자)가 여러분이 원하는 값을 제대로 가리키고 있는지 점검해야 하는데요, 이 경우에는 반복자가 가리키는 객체가 여러분이 원하던 값을 가리키고 있는지를 점검하면 됩니다.

이 때 많은 분들이 상등성 검사를 해서 점검을 하더군요. 많은 경우 상등성 검사를 해도 문제가 없지만, 항목 19에서 볼 수 있듯이 상등성 검사와 동등성 검사의 결과가 얼마든지 달라질 수 있습니다.

따라서 상등성 검사 대신 동등성 검사를 하는 것이 맞다고 할 수 있습니다(항목 19에는 그 방법이, 항목 24에는 그렇게 해도 괜찮은 예가 설명되어 있습니다).

```c++
auto iter = lower_bound(vi.begin(), vi.end(), 10);
		/*
			i가 객체를 가리키고 있는지 확인합니다 
			확인해야 하죠. 이 코드엔 버그가 있습니다!

			*iter = 10 은 상등성 검사를 수행합니다. 
			하지만 binary_search는 동등성 검사를 기반으로 동작하기 때문에 원하지 않는 동작을 할 가능성이 존재합니다.
		*/
		if (iter != vi.end() && *iter == 10) {      
			//원하는 값의 앞에 있지 않은 값을 가진 첫째 객체를 가리킵니다.
		}
		else {
			//못 찾았습니다.                              
		}

		//아래가 더 정확합니다. 동등성 검사를 수행합니다.
		if (iter != vi.end() && !(less<int>()(10, *iter))) {}
```

```c++
//20 보다 큰 값들을 전부 제거합니다.
vi.erase(upper_bound(vi.begin(), vi.end(), 20), vi.end());

//10보다 작은 값들을 전부 제거합니다.
vi.erase(vi.begin(), lower_bound(vi.begin(), vi.end(), 10));
```



#### lower_bound보다 좀 더 쉬운 방법은 equal_range를 쓰는 것입니다. equal_range는 반복자 쌍으로 구성된 pair 객체를 반환하는데, 첫째 반복자는 lower_bound가 반환하는 그것과 같고, 둘째 반복자는 upper_bound가 반환하는 그것(찾고자하는 것과 동등한 값을 가진 범위의 끝의 바로 다음)과 같습니다.

```c++
auto iterPair = equal_range(vi.begin(), vi.end(), 10);
		if (iterPair.first != iterPair.second) {
			cout << "There are " << distance(iterPair.first, iterPair.second)
				<< " elements in vw equivalent to 10.";
		}
```



#### 표준 시퀸스 컨테이너(vector, string, deque, list)에 대해서는 지금까지 설명한 내용을 그대로 적용해도 무방합니다. 하지만, 표준 연관 컨테이너(set, multiset, map, multimap)을 쓴다면 이야기가 달라집니다. 이들은 STL 알고리즘보다 일반적으로 더 잘 쓰이는 탐색용 멤버 함수를 가지고 있기 때문이죠.

이런 전차로, 연관 컨테이너에서 탐색할 때에는 count, find, equal_range, lower_bound, upper_bound에 대해서는 똑같은 이름의 멤버 함수를 사용하는 것이 좋다는 결론이 내려지겠죠?

binary_search만 예외인데, 이 알고리즘과 비슷한 멤버 함수는 없습니다. 어쨌든 set이나 map에서 어떤 값이 있는지를 알아낼 땐 count를 쓸 수 있습니다.

multiset이나 multimap에서 어떤 값이 있는지 알아보는 데에는 count보다 find가 일반적으로 좋습니다. find는 값을 찾으면 바로 멈추는 반면에, count는 최악의 경우에 컨테이너 안의 모든 객체를 일일이 찾게 됩니다.

하지만 연관 컨테이너에서 count로 객체 세기(counting)는 매우 안정적입니다. 특히 equal_range가 반환하는 두 반복자의 거리를 구하는 것보다 더 좋습니다.

첫째로, count가 더 명확합니다. 둘째로, 더 쉽습니다. 셋째로, 아마도 count가 더 빠를 것입니다.

|                    우리가 궁금해 하는 것                     |    사용할 알고리즘     |                 | 사용할 멤버 함수 |                       |
| :----------------------------------------------------------: | :--------------------: | --------------- | ---------------- | --------------------- |
|                         정렬/미정렬                          | 정렬되지 않은 범위에서 | 정렬된 범위에서 | set/map          | multiset/multimap     |
|                     원하는 값이 있나요?                      |          find          | binary_search   | count            | find                  |
| 원하는 값이 있나요? 그럼 그 값을 가진 첫째 객체는 어디에 있나요? |          find          | equal_range     | find             | find 또는 lower_bound |
| 원하는 값의 앞에 있지 않은 값을 가진 첫째 객체는 어디에 있나요? |        find_if         | lower_bound     | lower_bound      | lower_bound           |
| 원하는 값의 뒤에 있는 값을 가진 첫 번재 객체는 어디에 있나요? |        find_if         | upper_bound     | upper_bound      | upper_bound           |
|             원하는 값을 가진 객체는 몇 개인가요?             |         count          | equal_range     | count            | count                 |
|         원하는 값을 가진 객체는 모두 어디에 있나요?          |    find(연속 호출)     | equal_range     | equal_range      | equal_range           |