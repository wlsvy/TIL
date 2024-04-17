#include <iostream>
#include <vector>
#include <string>
using namespace std;

//타입에 대한 정보가 필요하다면 특성정보 클래스를 사용하자

namespace Item47 {

	//C++ 표준 라이브러리에는 반복자 범주 각각을 식별하는데 쓰이는 "tag 태그 구조체" 가 정의되어 있다
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//만약 반복자를 전진시키려 할 경우, 반복자의 특성에 따라 다른 방식으로 구현해야 한다
	
	//stl 컨테이너의 간략한 예시
	template<typename T>
	class deaue {
	public:
		class iterator {
		public:
			typedef random_access_iterator_tag iterator_category; //반복자 태그를 iterator_category 란 별칭으로 매겨 놓는다
		};
	};

	template<typename T>
	class list {
	public:
		class iterator {
		public:
			typedef bidirectional_iterator_tag iterator_category; 
		};
	};

	//아래 구조체는 템플릿 매개변수로 들어온 클래스의 태그 타입을 말해준다
	template<typename IterT>
	struct iterator_traits {
		typedef typename IterT::iterator_category iterator_category;
	};
	//반복자의 실제 타입이 포인터인 경우, 그에 해당하는 처리가 따로 필요하다
	//부분 템플릿 특수화
	template<typename IterT>
	struct iterator_traits<IterT*> {
		//임의 접근 반복자에 활용 -> 포인터의 동작원리는 임의접근 반복자와 똑같기 때문
		typedef typename random_access_iterator_tag iterator_category;	
	};

	template<typename IterT, typename DistT>
	void tempAdvance(IterT &iter, DistT d) {
		//좋지 못한 방식. 특정정보는 컴파일 시간에 알 수 있는데 굳이 런타임 시간에 확인할 이유가 있다.
		if (typeid(typename std::iterator_traits<IterT>::iterator_category) == typeid(std::random_access_iterator_tag))
			;
	}

	//오버로딩을 활용한 방법
	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		random_access_iterator_tag)
	{
		iter += d;
	}
	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		bidirectional_iterator_tag)
	{
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}

	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		input_iterator_tag)
	{
		if (d < 0) {
			throw std::out_of_range("Negative distance");
		}
		while (d--) ++iter;
	}
	template<typename IterT, typename DistT>
	void advance(IterT& iter, DistT d)
	{
		doAdvance(iter, d,
			typename iterator_traits<IterT>::iterator_category());
	};
	/*
		작업자(worker) 역할을 맡은 함수 혹은 함수 템플릿은 특성정보 매개변수를 다르게 하여 오버로딩

		주작업자(master) 역할을 맡은 함수 혹은 함수 템플릿은 
		특성정보 클래스에서 제공되는 정보를 넘겨서 작업자를 호출하도록 구현
	*/
}