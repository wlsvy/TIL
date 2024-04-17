#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>
#include <numeric>

//STL에 관련된 컴파일러 진단 메시지를 해석하는 능력을 가지자

namespace Item49 {
	using namespace std;

	/*
		책과는 다르게 c++ 11 이후로는 SFINAE 개념이 들어갑니다.
	*/

	inline void RunSample() {
		//아래의 코드는 더 아래의 에러메세지를 출력합니다.
		//string s(10);
		/*
			심각도	코드	설명	프로젝트	파일	줄	비표시 오류(Suppression) 상태

			오류(활성)	E0289	인수 목록이 일치하는 생성자 
			"std::basic_string<_Elem, _Traits, _Alloc>::basic_string 
			[대상 _Elem=char, _Traits=std::char_traits<char>, _Alloc=std::allocator<char>]"의 인스턴스가 없습니다.
			EffectiveSTL	C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	19	

			심각도	코드	설명	프로젝트	파일	줄	비표시 오류(Suppression) 상태

			오류	C2664	
			'std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(const std::basic_string<char,std::char_traits<char>,std::allocator<char>> &)': 인수 1을(를) 'int'에서 'std::initializer_list<_Elem>'(으)로 변환할 수 없습니다.	
			EffectiveSTL	C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	19
		*/

		/*
			std::basic_string<char,std::char_traits<char>,std::allocator<char>> 를 string 으로 고쳐보면

			std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(const std::basic_string<char,std::char_traits<char>,std::allocator<char>> &)': 인수 1을(를) 'int'에서 'std::initializer_list<_Elem>'(으)로 변환할 수 없습니다.

			=>

			string::string(const string&)': 인수 1을(를) 'int'에서 'std::initializer_list<_Elem>'(으)로 변환할 수 없습니다.
			로 간단하게 요약할 수 있습니다. 즉, 생성자에 전달되는 인자가 잘못되었다는 것입니다.
		*/







		/*
			아래의 구조체는 어마어마하게 긴 에러메시지를 출력합니다.
			struct {
				map<string, string> m;
				void showValue(const string& key) const
				{
					if (map<string, string>::iterator i = m.find(key); i != m.end()) { <= 이 라인에서 에러가 발생합니다.
						//... 찾은 경우
					}
					//... 못 찾은 경우
				}
			};
		*/
		



		/*
			심각도	코드	설명	프로젝트	파일	줄	비표시 오류(Suppression) 상태
			오류(활성)	E0312	
			"std::_Tree_const_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>"
			에서 "std::conditional_t<false, std::_Tree_const_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>, std::_Tree_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>>"(으)로의 사용자 정의 변환이 적절하지 않습니다.	EffectiveSTL	
			
			C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	51	

			너무 길어서 이를 펼쳐보면 아래와 같습니다.






		"std::_Tree_const_iterator
		<
			std::_Tree_val
			<
				std::conditional_t
				<
					true, 
					std::_Tree_simple_types
					<
						std::pair<const std::string, std::string>>, 
						std::_Tree_iter_types
						<
							std::pair<const std::string, std::string>, 
							size_t, 
							ptrdiff_t, 
							std::pair<const std::string, std::string> *, 
							const std::pair<const std::string, std::string> *, 
							std::pair<const std::string, std::string> &, 
							const std::pair<const std::string, std::string> &, 
							std::_Tree_node
							<
								std::pair<const std::string, std::string>, 
								void *
							> *
						>
					>
				>
			>"

			
			에서 
			"std::conditional_t
			<false, 
				std::_Tree_const_iterator<std::_Tree_val
				<
					std::conditional_t
					<
						true, 
						std::_Tree_simple_types
						<
							std::pair<const std::string, std::string>>, 
							std::_Tree_iter_types
							<
								std::pair<const std::string, std::string>, 
								size_t, 
								ptrdiff_t, 
								std::pair<const std::string, std::string> *, 
								const std::pair<const std::string, std::string> *, 
								std::pair<const std::string, std::string> &, 
								const std::pair<const std::string, std::string> &, 
								std::_Tree_node<std::pair<const std::string, std::string>, void *> *
							>
						>
					>
				>, 
				std::_Tree_iterator
				<
					std::_Tree_val
					<
						std::conditional_t
						<
							true, 
							std::_Tree_simple_types
							<
								std::pair<const std::string, std::string>>, 
								std::_Tree_iter_types
								<
									std::pair<const std::string, std::string>, 
									size_t, 
									ptrdiff_t, 
									std::pair<const std::string, std::string> *, 
									const std::pair<const std::string, std::string> *, 
									std::pair<const std::string, std::string> &, 
									const std::pair<const std::string, std::string> &, 
									std::_Tree_node<std::pair<const std::string, std::string>, 
									void *
								> *
							>
						>
					>
				>
			>"(으)로의 사용자 정의 변환이 적절하지 않습니다.	EffectiveSTL







			에러 메시지를 줄여봅시다. 책과는 다르게 c++ 11 이후로는 SFINAE 개념이 들어갑니다.(conditional_t)
			std::conditional_t<bool B, class T, class F> 은 B가 true이면 type이 T를 가리키고, false이면 F를 가리킵니다.

			템플릿 클래스 std::_Tree_const_iterator/ _Tree_iterator의 타입 매개변수는 지금 단계에서 크게 중요하지 않습니다. 
			SOMETHING으로 줄여봅시다.

			아래와 같이 줄일 수 있습니다.





			"std::_Tree_const_iterator<SOMETHING>

			에서

			"std::conditional_t
			<
				false,
				std::_Tree_const_iterator<SOMETHING>
				std::_Tree_iterator<SOMETHING>
			>"
			(으)로의 사용자 정의 변환이 적절하지 않습니다.	EffectiveSTL





			conditional_t 부분에서 bool 타입이 false이므로 우측 타입인 std::_Tree_iterator 타입을 가리키게 됩니다.
			즉 const_iterator 타입을 iterator 타입으로 변환할 수 없어서 위와 같은 (엄청 긴) 오류메시지를 출력한 것입니다.

		*/

		/*
			마지막으로 STL의 신비스럽고 오묘한 컴파일러 메시지를 이해하는데 도움을 줄 힌트를 몇 개 정리해 보았습니다.

			1. vector와 string의 경우, 반복자는 포인터와 똑같습니다. 
			따라서, iterator를 가지고 실수를 했다면 컴파일러 진단 메시지는 포인터 타입을 언급할 가능성이 높습니다.

			2. back_insert_iterator, insert_iterator 등을 운운하는 메시지는 거의 항상 back_inserter나, inserter를 호출할 때 실수를 저질렀다는 뜻입니다
		
			3. 출력 반복자(예를 들면, ostream_iterator 그리고 back_inserter에서 반환된 반복자들)는 
			대입 연산자(operator=)의 내부에서 출력 혹은 삽입 동작을 취하기 때문에, 
			이런 반복자에 대해 실수했을 때에는 전혀 여러분이 듣지도 못한 대입 연산자를 들먹이는 부분을 에러 메시지에서 찾을 수 있습니다.

			4. STL 알고리즘의 내부가 잘못 되었다고 불평하는 메시지라면(즉, 에러를 일으킨 소스 코드가 <algorithm>에 있었다면), 
			그 알고리즘과 함께 사용한 타입에 문제가 있었다는 뜻으로 알아들으세요.

			5. vector나 string, for_each와 같이 자주 쓰이는 STL 컴포넌트를 사용하고 있는데 
			컴파일러 쪽에서 여러분이 의도한 바를 파악하지 못하겠다는 에러 메시지를 내면, 십중팔구는 필요한 헤더를 #include하지 않은 까닭입니다.
		*/
	}
}