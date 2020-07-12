#include <iostream>
#include <vector>
#include <string>
using namespace std;

//템플릿 프로그래밍의 천릿길도 암시적 인터페이스와 컴파일 타임 다형성부터

namespace Item41 {
	class Widget {
	public:
		Widget() {}

		bool operator!=(const Widget& rhs) {
			return false;
		}

		virtual std::size_t size() const { return 0; }
		virtual void normalize() {}
		void swap(Widget& other) { 
			using std::swap;
			swap(*this, other); 
		}
	};

	Widget someNastyWidget;

	/*
		※ w는 Widget 타입으로 선언되었기 때문에, w는 Widget 인터페이스를 지원해야 합니다.
		
		이 인터페이스를 소스 코드(Widget이 선언된 .h 파일 등)에서 찾으면 이것이 어떤 형태인지를 확인할 수 있으므로, 이런 인터페이스를 가리켜 명시적 인터페이스라고 합니다.
		다시 말해 소스 코드에 명시적으로 드러나는 인터페이스를 일컫습니다.
		
		Widget의 멤버 함수 중 몇 개는 가상 함수이므로, 이 가상 함수에 대한 호출은 런타임 다형성에 의해 이루어집니다.
		다시 말해, 특정한 함수에 대한 실제 호출은 w의 동적 타입을 기반으로 프로그램 실행 중, 즉 런타임에 결정됩니다.
	*/
	void doProcessing(Widget& w)
	{
		if (w.size() > 10 && w != someNastyWidget) {
			Widget temp(w);
			temp.normalize();
			temp.swap(w);
		}
	}

	/*
		w가 지원해야 하는 인터페이스는 이 템플릿 안에서 w에 대해 실행되는 연산이 결정합니다. 
		지금의 경우를 보면, size·normalize·swap  멤버 함수를 지원해야 하는 쪽은 w의 타입 즉 T입니다. 
		 
		그 뿐 아니라 T는 복사 생성자도 지원해야 하고, 부등 비교를 위한 연산도 지원해야 합니다. 
		 
		진짜 중요한 점은 이 템플릿이 제대로 컴파일되려면 몇 개의 표현식이 '유효(valid)'해야 하는데 이 표현식들은 바로 T가 지원해야 하는 암시적 인터페이스라는 점입니다.
		
		w가 수반되는 함수 호출이 일어날 때 템플릿의 인스턴스화가 일어납니다.
		
		이러한 인스턴스화가 일어나는 시점은 컴파일 도중입니다. 
		인스턴스화를 진행하는 함수 템플릿에 어떤 템플릿 매개변수가 들어가느냐에 따라 호출되는 함수가 달라지기 때문에, 이것을 가리켜 컴파일 타임 다형성이라고 합니다.
	*/
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
		클래스 및 템플릿은 모두 인터페이스와 다형성을 지원한다. 


		클래스의 경우, 인터페이스는 명시적이며 함수의 시그너처를 중심으로 구성되어 있습니다. 다형성은 프로그램 실행 중에 가상 함수를 통해 나타납니다.

		템플릿 매개변수의 경우, 인터페이스는 암시적이며 유효 표현식에 기반을 두어 구성됩니다. 
		다형성은 컴파일 중에 템플릿 인스턴스화와 함수 오버로딩 모호성 해결을 통해 나타납니다.
	*/
}