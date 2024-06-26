#include <iostream>
#include <memory>



//헤더 파일에 전역함수 선언/정의를 동시에 하면 LNK2005 오류 발생 -> inline 키워드 삽입할 것.
//클래스 멤버함수의 경우는 inline 필요없음. 헤더 파일에 선언/정의해도 암시적으로 inline 선언되기 때문

//#include "Item04.h"
//#include "Item07.h"
//#include "Item08.h"
//#include "Item09.h"
//#include "Item10.h"
//#include "Item11.h"
//#include "Item12.h"
//#include "Item13.h"
//#include "Item14.h"
//#include "Item15.h"
//#include "Item16.h"
//#include "Item19.h"
//#include "Item21.h"
//#include "Item22.h"
//#include "Item23.h"
//#include "Item26.h"
//#include "Item27.h"
//#include "Item28.h"
//#include "Item30.h"
//#include "Item31.h"
//#include "Item32.h"
//#include "Item33.h"
#include "Item34.h"
//#include "Item41.h"
#include "Item42.h"

using namespace std;

int main() {
	cout << "Hello EMC++" << endl;

	//Item01::ParamType_Function::RunSample();
	//Item04::RunSample();
	//Item07::OtherCase::RunSample();
	//Item09::RunSample();
	//Item10::RunSample();
	//Item10::Scoped::RunUserInfoSample();
	//Item10::Unscoped::RunUserInfoSample();
	//Item11::RunSample();
	//Item12::RunSample();
	//Item13::RunSample();
	//Item14::RunSample();
	//Item15::ConstexprFunc::RunSample();
	//Item16::UsingAtomic::RunSample();
	//Item16::UsingMutex::RunSample();
	//Item19::RunSample();
	//Item21::Make_Disadvantage::RunSample();
	//Item22::RunSample();
	//Item23::RunSample();
	//Item26::Case0::RunSample();
	//Item26::Case1::RunSample();
	//Item26::Case2::RunSample();
	//Item26::CaseConstructor::RunSample();
	//Item27::Case_Tag0::RunSample();
	//Item27::Case_Tag1::RunSample();
	//Item27::Case_Constructor1::RunSample();
	//Item28::RunSample();
	//Item30::Case0::RunSample();
	//Item30::Case1::RunSample();
	//Item30::Case4::RunSample();
	//Item31::Case1::RunSample();
	//Item32::Case1::RunSample();
	//Item33::RunSample();
	Item34::Case0::RunSample();
	//Item34::Case1::RunSample();
	//Item34::Case2::RunSample();
	//Item34::Case3::RunSample();
	//Item41::Case2::RunSample();
	//Item41::Case3::RunSample();
	//Item42::Case1::RunSample();
	//Item42::Case2::RunSample();
	Item42::Case3::RunSample();

	system("pause");
	return 0;
}


/*
Item 파일 템플릿

#pragma once
#include <iostream>
#include <vector>
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