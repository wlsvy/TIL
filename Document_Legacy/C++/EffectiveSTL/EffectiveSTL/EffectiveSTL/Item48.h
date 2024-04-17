#pragma once


//용도에 맞는 헤더를 항상 #include하자

namespace Item48 {
	using namespace std;

	/*
		마이너한 경우이긴 하지만 어떤 플랫폼에서 컴파일되는 소프트웨어를 다른 플랫폼으로 옮기려면 #include 지시자 몇 개를 더 붙여야 할 때가 있습니다. 
		이는 C의 표준안과 달리 C++의 표준안이 표준 헤더 사이의 인클루드 관계를 명확하게 정해두지 않았기 때문입니다.

		std 네임스페이스의 구성 요소를 사용하고 계신 한, 용도에 맞는 헤더를 #include할 책임은 여러분에게 있습니다. 
		이렇게 해야 이식성 있는 코드를 만들 수 있게 됩니다.
	*/
	
	/*
		거의 모든 컨테이너들은 같은 이름의 헤더에 정의되어 있습니다. 
		이를테면 벡터는 <vector>, 리스트는 <list>에 선언되어 있지요.
		<set>과 <map>은 예외입니다. <set>은 set과 multiset을 선언하고 있으며, <map>은 map과 multimap을 선언하고 있습니다.

		네 개를 제외한 모든 알고리즘이 <algorithm>에 선언되어 있습니다. 
		제외된 네 개는 accumulate(항목 37 참조), inner_product, adjacent_difference, partial_sum 이며, <numeric>에서 선언되어 있습니다.

		istream_iterator와 istreambuf_iterator(항목 29 참조)를 포함한 특별한 종류의 반복자는 <iterator>에 선언되어 있습니다.
		표준 함수자(예를 들면, less<T>)와 함수자 어댑터(not1, bind2nd 같은 것)는 <functional>에 선언되어 있습니다.
	*/
}