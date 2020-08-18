#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

//typedef 보다 별칭 선언을 선호하라

namespace Item09 {

	//함수 포인터의 별칭을 선언할 때는 using 쪽이 보기 편한다.
	using FP = void(*)(int, const std::string&); // using
	typedef void(*FP)(int, const std::string&);	//typedef

	//별칭 템플릿(alias templates) 역시 using 쪽이 선언하기 쉽다.
	template<typename T>
	using MyList = std::list<T>;

	MyList<int> li;

	template<typename T>
	struct MyVector {
		typedef std::vector<T> type;
	};

	MyVector<int>::type vi;

	
	template<typename T>
	class Widget {
	private:
		/*
			typedef를 사용할 때 단점 또 한가지
			템플릿 안에서 typedef를 사용할 때 이름 앞에 typename을 붙여야 한다.

			MyVector<T>::type은 소위 의존적 형식(dependent type)이며, c++의 규칙에 따라 의존적 형식 앞에는 typename이 붙어야 한다.

			MyVector 구조체가 특수화(specialization)에 의해 MyVector<T>::type 이 형식이 아닌 다른 것을 지칭할 가능성이 있기 때문이다.
		*/
		typename MyVector<T>::type wVec;

		/*
			using 은 그럴 필요 없다, 
			
			컴파일러는 MyList가 형식 템플릿임을 의미 알고 있으므로, MyList<T>는 반드시 형식 이름이다.
			MyList<T> 는 비의존적 형식이다.
		*/
		MyList<T> wList;
	};

	/*
		아래 경우, 특수화에 의해 MyVector<T>::type은 타입명을 지칭하지 않는다.
	*/
	class Wine{};
	template<>
	class MyVector<Wine> {
	private:
		enum class WineType {White, Red};
		WineType type;
	};

	inline void RunSample() {
		/*
			c++에서 형식 특질(type traits)를 활용할 때, 구현 내용을 찾아보면 typedef를 사용하던 때의 잔재가 남아있다.

			(template struct를 정의한 뒤 그 안에 type을 선언한 것)

			c++14에는 std::변환_t 형태의 별칭 템플릿이 추가되었다.
		*/
		
		std::remove_const<const int>::type i0;	//int
		std::remove_const_t<const int> i1;		//int

		std::remove_reference<int&&>::type i2;	//int
		std::remove_reference_t<int&> i3;		//int
	}
}