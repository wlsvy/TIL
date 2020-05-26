#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ø� ��Ÿ ���α׷��� ���� �ʰڴ°�

namespace Item48 {

	/*
		Tmp(���ø� ��Ÿ ���α׷���, template meta programming)���� ������ �� ���� �ִ�. 
		
		1. Tmp�� ���� �ٸ� ������δ� ��ٷӰų� �Ұ����� ���� ������ ���� �� �� �ִ�.
		
		2. ���ø� ��Ÿ ���α׷��� c++ �������� ����Ǵ� ���ȿ� ����Ǳ� ������, 
		���� �۾��� ��Ÿ�� �������� ������ Ÿ�� �������� ��ȯ�� �� �ִ�.

		�� ���� �ｼ, �Ϲ������� ���α׷� ���� ���߿� ���� �Դ� ��� �������� ������ ���߿� ã�� �� �ִٴ� ���̸�, 
		��Ÿ�� �ð��� ������ �۾��� ������ �ð��� �̸� �����ϱ� ������ ���� �ڵ尡 �۾�����(??), ���� �ð��� ª������ �޸𸮵� ������ �� �ִٰ� �Ѵ�.

	*/

	//TMP������ ������ ������ ���� ���µ�, ��� TMP������ �ݺ�(iteration) �ǹ��� ������ ������ ���� ������, ���(recursion)�� ����ؼ� ������ ȿ���� ����. 
	//TMP�� ��� �Լ� ȣ���� ������ �ʰ� ��ͽ� ���ø� �ν��Ͻ�ȭ(recursive template instantiation)�� �Ѵ�.
	template<unsigned n>
	struct Factorial {
		enum { value = n * Factorial<n - 1>::value };
	};

	template<>	//���ø� Ư��ȭ�� ��� ���� ���� ����
	struct Factorial<0> {
		enum { value = 1 };
	};

	void func() {
		std::cout << Factorial<0>::value << std::endl;
		std::cout << Factorial<1>::value << std::endl;
		std::cout << Factorial<2>::value << std::endl;
		std::cout << Factorial<3>::value << std::endl;
		std::cout << Factorial<4>::value << std::endl;
	}

	/*
		TMP�� ������ ������ �ϴ� �о߰� �ִ�.

		ġ�� ����(dimensional unit)�� ��Ȯ�� Ȯ�� - ����, �Ÿ�, �ð� � ���ؼ� ���. TMP�� ����Ѵٸ� ��� ġ�� ������ ������ ������ Ÿ�ӿ� Ȯ�ΰ����ϴ�.

		��� ������ ����ȭ - ǥ���� ���ø�(expression template)�� ����ϸ� ��û�� ȿ���� ���� �� �ִٰ� �Ѵ�.

		����� ������ ���� ������ ���� - ���� ����, ������ ����, �湮�� ���� ���� ������ ���Ͽ��� ���. 
		TMP�� ��å ��� ����(policy-based design)��� ���� ����ϸ� ���ε��� ���õ� ������� ������ ��Ÿ���� ���ø��� ���� �� �ְ� �ȴ�. ������ ���α׷���(generative programming)�� ���ʶ�� �ϴ���.


	*/
}
