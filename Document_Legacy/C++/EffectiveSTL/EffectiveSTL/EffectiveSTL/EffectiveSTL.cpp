#include <iostream>
#include <string>

#include "Cpp17StlExample.h"
#include "Item07.h"
#include "Item08.h"
#include "Item09.h"
#include "Item11.h"
#include "Item12.h"
#include "Item14.h"
#include "Item17.h"
#include "Item20.h"
#include "Item21.h"
#include "Item23.h"
#include "Item24.h"
#include "Item27.h"
#include "Item28.h"
#include "Item29.h"
#include "Item30.h"
#include "Item31.h"
#include "Item34.h"
#include "Item35.h"
#include "Item37.h"
#include "Item38.h"
#include "Item39.h"
#include "Item40.h"
#include "Item41.h"
#include "Item42.h"
#include "Item43.h"
#include "Item44.h"
#include "Item46.h"
#include "Item47.h"
#include "Item49.h"

int main() {

	//Example::RunSample();
	Example::RunIosSample();

	//Item07::UsingFunctionObject::RunSample();
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
	//Item27::RunSample();
	//Item28::RunSample();
	//Item29::RunSample();
	//Item30::RunSample();
	//Item31::RunSample();
	//Item34::RunSample();
	//Item35::RunSample();
	//Item37::RunSample();
	//Item38::RunSample();
	//Item39::RunSample();
	//Item40::RunSample();
	//Item41::RunSample();
	//Item42::RunSample();
	//Item43::RunSample();
	//Item44::RunSample();
	//Item46::RunSample();
	//Item47::RunSample();
	//Item49::RunSample();

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
#include <numeric>

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
		Widget(int i) : value(i) { std::cout << "Int ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }

		Widget& operator=(const Widget& rhs) {
			std::cout << "assign operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept {
			std::cout << "move assign operator =" << std::endl;
			return *this;
		}
		Widget& operator=(const int i) {
			value = i;
			std::cout << "interger assign operator =" << std::endl;
			return *this;
		}

		//operator int() const { return 0; }
		//operator float() const { return 0.0f; }

		int value;
	};
*/

/*


*/