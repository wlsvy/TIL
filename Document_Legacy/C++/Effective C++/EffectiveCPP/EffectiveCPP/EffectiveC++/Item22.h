#include <iostream>
#include <vector>
#include <string>
using namespace std;

//데이터 멤버가 선언될 곳은 private 영역임을 명심하자

namespace Item22 {

	/*
		데이터 멤버는 private 멤버로 선언합시다. 이를 통해 클래스 제작자는 문법적으로 일관성 있는 데이터 접근 통로를 제공할 수 있고, 
		필요에 따라서는 세밀한 접근 제어도 가능하며, 클래스의 불변속성을 강화할 수 있을 뿐 아니라, 내부 구현의 융통성도 발휘할 수 있습니다.

		protected는 public보다 더 많이 '보호'받고 있는 것이 절대로 아닙니다.

		왜냐하면 파생 클래스에서는 여전히 protected 데이터 멤버에 직접 접근할 수 있기 때문입니다.
	*/
}