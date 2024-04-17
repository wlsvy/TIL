#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//����(Copy)�� �����̳� ���� ��ü�� �°� ����� �ּ�ȭ�ϸ�, ������ ��Ȯ�ϰ� ����

namespace Item03 {
	using namespace std;

	//move semantic �� �Ұ��Ǳ� ������ �������� ��������.
	/*
		���� ���� STL�� ��ģ���� ���縸 �ϴ� ���̺귯����� ������ �� �� ���� �� �����ϴ�. 
		�и��� STL�� ���縦 ���� �ϱ� ������, STL�� �Ϲ������� "���ʿ���" ���縦 ���ϵ��� ����Ǿ����ϴ�. 
		�̰��� ����Դϴ�. ������ STL�� �Ϲ������� ���ʿ��� ���� "����"�� ���ϵ��� ����Ǿ����ϴ�.
	*/

	class Widget{};

	inline void RunSample() {
		const unsigned int maxNumWidgets = 100;

		Widget w[maxNumWidgets];
		
		vector<Widget> vw;
		vw.reserve(maxNumWidgets);

		/*
			�迭�� ��� ��� ������ ������ ����������

			������ ��� reserve�� ���� ������ �̸� �Ҵ���� �� ������, ������� ���ð� ������ ��ü�� �ٷ� �������� �ʽ��ϴ�.
		*/
	}
}