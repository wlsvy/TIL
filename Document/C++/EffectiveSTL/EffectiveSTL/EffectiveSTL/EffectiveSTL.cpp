#include <iostream>
#include <string>

int main() {

	system("pause");
	return 0;
}

/*
Item 파일 템플릿

#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>


namespace Item00{
	using namespace std;

	inline void RunSample(){

	}
}

*/

/*
Widget 클래스 템플릿


	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
			Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
			Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
			~Widget() { std::cout << "dtor" << std::endl; }

			Widget& operator=(const Widget& rhs)
			{
				std::cout << "copy operator =" << std::endl;
				return *this;
			}
			Widget& operator=(Widget&& rhs) noexcept
			{
				std::cout << "move operator =" << std::endl;
				return *this;
			}

		//operator int() const { return 0; }
		//operator float() const { return 0.0f; }
	};
*/

/*


*/