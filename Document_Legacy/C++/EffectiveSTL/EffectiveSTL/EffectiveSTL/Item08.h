#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//auto_ptr�� �����̳ʴ� ����� ������ ����

namespace Item08 {
	using namespace std;
	//c++11 ���� unique_ptr�� �Ұ��Ǹ鼭 auto_ptr����� ������� �ʴ´�.

	/*
		auto_ptr�� �����̳�(COAP: Container Of A(a)uto_P(p)tr)�� ���� �����Դϴ�. 
		COAP�� ����� �ڵ�� ���������� �Ǿ�� �ȵ˴ϴ�. 
		�̰� ������ C++ ǥ��ȭ ����ȸ������ �� ���� ����� ���� �ߴٰ� �մϴ�.

		������ ���� ��� �����Ϸ����� COAP�� ����մϴ�.

		���� ����� ���� ������, COAP�� ���� �ڵ�� �̽ļ��� �������ϴ�. 
		COAP�� ���� �ڵ��, ǥ���� ������(COAP�� ������� �ʴ�) �����Ϸ��� �׷��� ����(COAP�� ����ϴ�) �����Ϸ����� �̽��� ���� ���� ���Դϴ�.

		�ڵ��� �̽ļ��� ������ �ʴ´ٰ� �ص�, �̺��� �� �߿��� ������ �����ֽ��ϴ�. auto_ptr�� ��Ư�� ���� ����� ������ �˴ϴ�.
	*/

	class Widget{
	public:
		bool operator< (const Widget& rhs) { return true; }
	};

	/*bool WidgetAPCompare(const auto_ptr<Widget>& lhs,
		const auto_ptr<Widget>& rhs)
	{
		return *lhs < *rhs;                    
	}*/

	inline void RunSample() {
		/*auto vwp = vector<auto_ptr<Widget>>();
		for (int i = 0; i < 100; i++) {
			vwp.emplace_back(new Widget);
		}*/

		//���� ���� �۾��� �����ϰ� ����, ������ ����� ��Ÿ���ϴ�.
		//sort(vwp.begin(), vwp.end(), WidgetAPCompare);

		/*
			sort�� ���� ������ ����Ʈ �˰����� ����ϰ� �ֽ��ϴ�.
			
			�˰��� ���������� �ǹ� ��Ҹ� �����ϴ� �۾��� �����ϴµ� �ش� ������ ���� ������ ����Ǵ� auto_ptr�� NULL�� ���õ˴ϴ�.

			����Ʈ�� ��� �˰����̹Ƿ� ��� ȣ���� �Ͼ ������ �ǹ� ��Ҹ� ������ ����ϱ� ������, 
			���� ���� ���� ���(auto_ptr)�� NULL�� ���õǰ� ���� ���� Widget�� �����Ǵ� ��찡 �ٹݻ��� ���Դϴ�.
		*/
	}
}