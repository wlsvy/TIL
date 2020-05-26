#include <iostream>
#include <vector>
#include <string>
using namespace std;

//템플릿 프로그래밍의 천릿길도 암시적 인터페이스와 컴파일 타임 다형성부터

namespace Item41 {
	class Widget {
	public:
		Widget() {}
		virtual ~Widget() {}
		virtual std::size_t size() const { return 0; }
		virtual void normalize() {}
		void swap(Widget& other) { 
			using std::swap;
			swap(*this, other); 
		}
	};

	Widget someNastyWidget;

	template<typename T>
	void doProcessing(T& w) {
		if (w.size() > 10 && w != someNastyWidget) {
			T temp(w);
			temp.normalize();
			temp.swap(w);
			/*
				암시적 인터페이스
				-> 타입 T는 normalize(), swap(T), operator !=(Widget) 메소드를 포함하고 있어야 한다
			*/
		}
	}

	/*
		W가 수반되는 함수 호출이 일어날 때, 
		이를테면 operator > 및 operator != 함수가 호출될 때는 해당 호출을 성공시키기 위해 템플릿의 인스턴스화가 일어난다. 
		
		이러한 인스턴스화가 일어나는 시점은 컴파일 도중
		인스턴스화를 진행하는 함수 템플릿에 어떤 템플릿 매개변수가 들어가느냐에 따라 호출되는 함수가 달라지기 때문에, 이것을 가리켜 '컴파일 타임 다형성'이라고 한다.
		
		클래스 및 템플릿은 모두 인터페이스와 다형성을 지원한다. 

		이때 클래스의 경우, 인터페이스는 명시적이며 함수의 시그니처를 중심으로 구성되어 있다. 
		다형성은 프로그램 실행 중에 가상 함수를 통해 나타난다. 

		템플릿 매개변수의 경우, 인터페이스는 암시적이며 유효 표현식에 기반을 두어 구성된다. 
		다형성은 컴파일 중에 템플릿 인스턴스화와 함수 오버로딩 모호성 해결을 통해 나타난다.
	*/
}