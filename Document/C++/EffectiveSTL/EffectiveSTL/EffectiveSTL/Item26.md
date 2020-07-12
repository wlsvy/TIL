# const_iterator나 reverse_iterator, const_reverse_iterator도 좋지만 역시 쓸만한 것은 iterator이다

> 지금의 const_iterator는 더 유연한 동작을 지원하게 바뀌었습니다.

![](http://twimgs.com/ddj/cuj/images/cuj0106smeyers/diagram1.gif)

- 모든 STL 표준 컨테이너는 네 가지 타입의 반복자를 모두 제공합니다. container<T>라고 정의된 컨테이너가 있다고 하면 iterator는 T*와 같은 개념이고 const_iterator는 const T*와 똑같은 구실을 합니다. iterator나 const_iterator를 증가시키면, 해당 반복자는 현재 가리키고 있는 요소의 그 다음 요소를 가리키며, 위치는 컨테이너의 처음과 멀어지고 끝과 가까워집니다.

- iterator는 const_iterator로 암시적(implicit) 변환이 가능하며, iterator와 const_iterator는 각각 reverse_iterator와 const_reverse_iterator로 암시적 변환이 가능합니다.

- reverse_iterator는 const_reverse_iterator로 암시적 변환이 가능하며, reverse_iterator와 const_reverse_iterator는 base()를 통해 각각 iterator와 const_iterator로 변환이 가능합니다.

# - const_iterator 가 가지는 단점은 이렇습니다.
  - insert나 erase와 같은 함수는 매개변수 타입으로, 네 가지의 반복자 타입 중에 iterator만을 요구한다는 점이 중요합니다.
#####     - 현재는 const_iterator도 매개변수로 넘길 수 있습니다.
  - const_iterator를 iterator로 암묵적(implicit)으로 변환할 방법은 없으며, 굳이 바꾸려면 항목 27에서 소개하는 방법을 쓰면 되지만 일반성도 떨어지며 효율에 대한 보장도 할 수 없습니다.
  - reverse_iterator를 iterator로 변환할 수 있으나, 변환한 후에 약간의 조정이 필요합니다. 언제, 그리고 왜 이렇게 하는지에 대해서는 항목 28에서 공부하겠습니다.
  - 가장 성가신 것은 iterator와 const_iterator를 비교가 되지 않는 것입니다.
#####     - 현재는 두 종류의 반복자에 대한 비교를 지원하고 있습니다.


``` c++

	vector<int> v;
	auto it = v.begin();
	auto cit = v.cbegin();
	auto rit = v.rbegin();
	auto crit = v.crbegin();

	//_MSC_VER == 1926 기준
	//insert/erase에도 const_iterator를 매개변수로 넘길 수 있습니다.
	v.insert(cit, 3); 
	v.erase(cit);

	v.insert(crit, 5); //reverse_const_iterator는 컴파일 오류

	if (it == cit) ;
	if (cit == it) ;
	if (rit == crit);
	if (crit == rit);

	//역방향 반복자와 일반 박복자를 비교하면 컴파일 오류가 발생할 수 있습니다.
	if (rit == it) ;	//컴파일 오류

	//책에서는 이 부분이 컴파일 되지 않을 수 있다고 설명합니다.
	if (it - cit > 3);	
	//만약 그렇다면 이렇게 우회합니다.
	if (cit + 3 <= it);

```






