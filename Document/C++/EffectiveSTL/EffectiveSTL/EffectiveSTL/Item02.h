#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//"�����̳ʿ� ��������(container-independent) �ڵ�"��� ȯ���� ��������

namespace Item02 {
	using namespace std;
	/*
		�����̳ʿ� �������� �ڵ�, 
		�׷��ϱ� vector�� ���ؼ� �۵��ϴ� �ڵ尡 list, map, set�� ���ؼ��� �������� �۵��� �� �ְ� �ۼ��ϴ� �õ��� ���� �ʽ��ϴ�.

		STL�� �����̳ʵ��� ������ ���� ������� Ư¡�� �ֽ��ϴ�. 
		���� �� �����̳ʿ� �������� �ڵ带 �ۼ��Ѵٸ�, �� �����̳ʰ� ���������� ���� �κи��� �̿��� �ڵ带 �ۼ��ؾ� �� ���Դϴ�. 
		�̴� Ư�� �����̳ʸ��� ���� ������ ����� Ȱ���ϱ� ��ư� ����ϴ�.
	*/

	/*
		��쿡 ���� ���÷� �����̳� Ÿ���� �ٲ� ���ۿ� ���� �����̶��, ������ ���� �����ϰ� ���ִ� ����� �� ���� �ֽ��ϴ�. 
		�ٷ� "ĸ��ȭ"������. ���� ���� ����� �����̳ʿ� �ݺ��� Ÿ�Կ� ���� ��Ī�� �����ϴ� ���Դϴ�.
	*/

	class Widget {
	};

	//å������ typedef�� Ȱ��������, ���⼭�� using ���
	//�̷��� �ϸ� WidgetContainer�� vector�� �ٲٴ� �͸����� �����̳� Ÿ���� ������ �� �ֽ��ϴ�.
	using WidgetContainer = vector<Widget>;
	using WCIterator = WidgetContainer::iterator;


	inline void RunSample() {
		WidgetContainer vw;

		Widget bestWidget;
		WCIterator i = find(vw.begin(), vw.end(), bestWidget);
	}

	/*
		��� typedef�� � Ÿ�Կ� ���� �ٸ� �̸��� �Ұ��ϱ� ������, �̰����� �� �� �ִ� ĸ��ȭ�� ȿ���� ������ '������(lexical)'�Դϴ�. 
		�׻� �� �� ����(Ȥ�� ������ �� ����) ���� ����(Ȥ�� ��������) ���ϵ��� ���� ��ġ�� ������ ���� �ʽ��ϴ�. 
		�������� ���� �ڵ带 ����� ������ '�ʿ���' �͸� ���̰� �ʹٸ� �� �� ū ������ Ŭ����(class)�� ��� �մϴ�.
	*/

	/*
		�� �����̳ʸ� �ٸ� �����̳ʷ� �ٲ� ��� �䱸�Ǵ� �ڵ��� ������ �����ϱ� ���ؼ��� Ŭ������ �����̳ʸ� �����, 
		�� �����̳ʿ� ���õ� ���� �߿� �ʿ��� �͸� Ŭ���� �������̽��� ���� �����ϸ� �˴ϴ�.

		���� ��� ��ǰ ������ '����Ʈ'�� ����ٰ� �� ���� list�� �ٷ� ������� ���ƾ� �մϴ�. 
		�� ���, CustomerList Ŭ������ �ϳ� �����, private �������ٰ� list�� ����� ���Դϴ�.
		�ܺο��� ��Ī�� �������� ���ϰ� ���� ĸ��ȭ�� ���� �� �ֽ��ϴ�.

		��Ī�� public �����ߴٸ� ���� CustomerList�� �����̳� Ÿ���� �ٲ���� ���� ���� ��, ���� ���ۿ��� ������ �� �� �����ϴ�.
	*/
	class Customer{};
	class CustomerList
	{
	private:
		using CustomerContainer = list<Customer>;
		using CCIterator = CustomerContainer::iterator;
		CustomerContainer customers;
	};
}