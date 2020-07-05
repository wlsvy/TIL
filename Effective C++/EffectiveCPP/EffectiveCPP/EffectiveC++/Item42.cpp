#include <iostream>
#include <vector>
#include <string>
using namespace std;

//typename 의 두 가지 의미를 제대로 파악하자

namespace Item42 {

	int x = 1;

	template<typename C>
	void print(const C& container) {
		C::const_iterator * x;
		/*
			문제의 소지가 다분한 코드, C::const_iterator에 대한 포인터 지역 변수로서 x를 선언하는 것 같지만
			컴파일러 입장에서는 C::const_iterator가 타입을 말하는 건지 C의 const_iterator라는 정적 변수인지 알 수 가 없다.

			만약에 C::const_iterator가 정적 변수라면 해당 문장은 두 변수의 곱셈 연산을 수행하라는 의미를 가진다
		*/
	}
	
	template<typename C>
	void print_2(const C& container) {
		if (container.size() >= 2) {
			typename C::const_iterator iter(container.begin());
			/*
				제대로 수정한 코드. 컴파일러에게 C::const_iterator가 타입임을 알려준다
			*/
		}
	}

	template<typename C>	//typename 쓸 수 있음, class와 같은 의미
	void f(const C& container,	//typename 붙이면 안된다
		typename C::const_iterator iter);	//typename을 붙여야 한다
	/*
		C::const_iterator 에서 C는 템플릿 매개변수이며, const_iterator는 C에 종속된 의존 이름이라 볼 수 있다.
		C 에는 typename 을 붙여선 안되고, C에 의존하는 C::const_iterator 앞에는 typename을 붙여야 한다
	*/


	template<typename T>
	class Base {
	public:
		class Nested{
		public:
			Nested() {}
			Nested(int x) {}
		};
	};

	template<typename T>
	class Derived : public Base<T>::Nested {	//상속되는 기본 클래스 리스트, typename 을 붙이면 안된다
	public:
		explicit Derived(int x) : 
			Base<T>::Nested(x) {	//멤버 초기화 리스트에 있는 기본 클래스 식별자, typename을 쓰면 안된다
			
			typename Base<T>::Nested temp;	//typename 필요
		}
	};
	/*
		template 매개변수에 의존하면서 typename 키워드를 붙이지 않는 예외 경우
	*/

	template<typename IterT>
	void workWithIterator(IterT iter) {
		typedef typename std::iterator_traits<IterT>::value_type value_type;
		
		value_type temp(*iter);

		//컴파일러에게 타입정보를 알리면서 typedef 키워드로 별칭을 만들 수 있다.
	}

	/*
		템플릿 매개변수를 선언할 때, class 및 typename은 서로 바꾸어 써도 무방하다.
		중첩 의존 타입 이름을 식별하는 용도에는 반드시 typename을 사용한다. 
		단 중첩 의존 이름이 기본 클래스 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로 있는 경우에는 예외
	*/
}