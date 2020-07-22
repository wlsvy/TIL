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
#include <functional>

//함수자 클래스는 어댑터 적용이 가능하게(adaptable) 만들자

namespace Item40 {
	using namespace std;
	/*
		c++ 11 이후, 더 강력한 타입 추론 (decltype, auto) 기능이 등장하였습니다.
		
		unary_function/binary_function 이 제공하는 typedef 는 해당 클래스의 반환 타입 및 매개변수 타입을 알려주어
		not1, not2, bind1st, bind2nd 등과 같은 어댑터에 사용가능하게 해줍니다.

		하지만 c++ 11 이후 타입 추론기능이 더 강력해짐과 동시에, lambda, function 객체, variadic template(가변 길이 템플릿)가 등장하면서
		굳이 unary_function을 상속하지 않더라도 인자/반환값의 타입을 추측할 수 있게 되었습니다. 
		더불어 함수 어댑터 역시 굳이 쓸 필요가 없게 되었고요.

		그런 이유에서 unary_function/binary_function는 c++ 11이후 deprecated 되었으며 c++ 17 이후 삭제됩니다.
		함수 어댑터(not1, not2, bind1st, bind2nd) 역시 마찬가지입니다.
	*/


	/*
		4대 표준 함수 어댑터(not1, not2, bind1st, bind2nd) 모두 함수 객체에게 typedef 타입을 요구합니다. 
		따라서 이러한 typedef 타입이 없는, 함수 포인터와 같은 경우는 표준 함수 어댑터에 바로 적용할 수 없고, 
		ptr_fun을 적용한 후에 어댑터를 써야 합니다. ptr_fun은 어댑터가 요구하는 typedef 타입을 제공해 주는 역할을 합니다.
	*/

	inline void RunSample() {
		std::function<bool(int, double, char)> f = [](int, double, char) {return true; };

		using Result_Type = std::function<bool(int, double, char)>::result_type;
		using Ret_Arg_Types = std::function<bool(int, double, char)>::_Ptrt;

		auto& typeInfo = f.target_type();
		auto typeName = typeInfo.name();
	}
}