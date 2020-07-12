#include <iostream>
#include <string>

//#include "Item08.h"
//#include "Item09.h"
//#include "Item11.h"
//#include "Item12.h"
//#include "Item14.h"
//#include "Item17.h"
//#include "Item20.h"
//#include "Item21.h"
//#include "Item23.h"
//#include "Item24.h"
#include "Item27.h"

int main() {
	//Item08::RunSample();
	//Item09::RunSample();
	//Item11::SharedMemoryCase::RunSample();
	//Item11::DoubleHeapCase::RunSample();
	//Item12::RunSample();
	//Item14::RunSample();
	//Item17::RunSample();
	//Item20::RunSample();
	//Item21::RunSample();
	//Item23::RunSample();
	//Item24::RunSample();
	Item27::RunSample();

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
#include <set>
#include <memory>

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
		Widget()						{ std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs)		{ std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept	{ std::cout << "move ctor" << std::endl; }
		~Widget()						{ std::cout << "dtor" << std::endl; }

		Widget& operator=(const Widget& rhs) {
			std::cout << "copy operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept {
			std::cout << "move operator =" << std::endl;
			return *this;
		}

		//operator int() const { return 0; }
		//operator float() const { return 0.0f; }
	};
*/

/*


*/