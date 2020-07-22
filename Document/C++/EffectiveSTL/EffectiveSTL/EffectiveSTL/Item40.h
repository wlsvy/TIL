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

//�Լ��� Ŭ������ ����� ������ �����ϰ�(adaptable) ������

namespace Item40 {
	using namespace std;
	/*
		c++ 11 ����, �� ������ Ÿ�� �߷� (decltype, auto) ����� �����Ͽ����ϴ�.
		
		unary_function/binary_function �� �����ϴ� typedef �� �ش� Ŭ������ ��ȯ Ÿ�� �� �Ű����� Ÿ���� �˷��־�
		not1, not2, bind1st, bind2nd ��� ���� ����Ϳ� ��밡���ϰ� ���ݴϴ�.

		������ c++ 11 ���� Ÿ�� �߷б���� �� ���������� ���ÿ�, lambda, function ��ü, variadic template(���� ���� ���ø�)�� �����ϸ鼭
		���� unary_function�� ������� �ʴ��� ����/��ȯ���� Ÿ���� ������ �� �ְ� �Ǿ����ϴ�. 
		���Ҿ� �Լ� ����� ���� ���� �� �ʿ䰡 ���� �Ǿ����.

		�׷� �������� unary_function/binary_function�� c++ 11���� deprecated �Ǿ����� c++ 17 ���� �����˴ϴ�.
		�Լ� �����(not1, not2, bind1st, bind2nd) ���� ���������Դϴ�.
	*/


	/*
		4�� ǥ�� �Լ� �����(not1, not2, bind1st, bind2nd) ��� �Լ� ��ü���� typedef Ÿ���� �䱸�մϴ�. 
		���� �̷��� typedef Ÿ���� ����, �Լ� �����Ϳ� ���� ���� ǥ�� �Լ� ����Ϳ� �ٷ� ������ �� ����, 
		ptr_fun�� ������ �Ŀ� ����͸� ��� �մϴ�. ptr_fun�� ����Ͱ� �䱸�ϴ� typedef Ÿ���� ������ �ִ� ������ �մϴ�.
	*/

	inline void RunSample() {
		std::function<bool(int, double, char)> f = [](int, double, char) {return true; };

		using Result_Type = std::function<bool(int, double, char)>::result_type;
		using Ret_Arg_Types = std::function<bool(int, double, char)>::_Ptrt;

		auto& typeInfo = f.target_type();
		auto typeName = typeInfo.name();
	}
}