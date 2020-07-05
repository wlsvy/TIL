#include <iostream>
#include <vector>
#include <string>
using namespace std;

//컴파일러 경고를 지나치지 말자

namespace Item53 {

	class B {
	public:
		virtual void f(void) const;
	};

	class D : public B {
	public:
		virtual void f(void);
	};
	/*
		 B::f는 const 멤버인데 반해  D::f는 const 멤버가 아닙니다.
		 재정의 된 것이 아니라, 완전히 가려져 버린 것입니다.

		 이런 실수가 있는 경우 컴파일러 경고가 뜹니다.
		
		 warning: D::f() hides virtual B::f()
		
		 하지만 어떤 컴파일러의 경우 아무런 경고를 띄우지 않을 수도 있습니다.
	*/

	/*
		컴파일러 경고를 쉽게 지나치지 맙시다. 
		여러분의 컴파일러에서 지원하는 최고 경고 수준에도 경고 메시지를 내지 않고 컴파일되는 코드를 만드는 쪽에 전력을 다 하십시오.
		
		컴파일러 경고에 너무 기대는 인생을 지양하십시오. 
		컴파일러마다 트집을 잡고 경고를 내는 부분들이 천차만별이기 때문입니다. 
		지금 코드를 다른 컴파일러로 이식하면서 여러분이 익숙해져 있는 경고 메시지가 온 데 간 데 없이 사라질 수도 있습니다.
	*/
}