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

//less<T>�� operator<�� �ǹ����� �� �˾Ƶ���

namespace Item42 {
	/*
		less�� ����ϰڴٸ� �ݵ�� operator<�� �ǹ̸� ������ �ϼ���.
		C++ ���α׷��Ӵ� �� ���� ���׿� ���� �ƹ� ���� ���� �̷� ������ �մϴ�.

		�̸��׸� �׵��� ���� �����ڴ� ���縦 �� ���̶�� �����մϴ�(�׸� 8���� ���̰� �ֵ�, �� ��Ģ�� ��Ű�� ������ ������ ���� ����ϴ�).

		�׵��� ��ü�� �ּҸ� �޾Ƴ��� �����Ͱ� ���´ٴ� ������ �մϴ�(�׸� 18�� ���ż�, �׷��� ���� �� � ���� ������� �˾ƺ�����).

		bind1st�� not2 ���� ����ʹ� �Լ� ��ü�� ����� ���̶�� �����մϴ�(�׸� 40������ �׷��� ���� �� ��� ������ �������� �����ϰ� �ֽ��ϴ�).

		C++ ���α׷��Ӵ� operator+�� ���ϱ⸦ �ϰ�(string�� �����ϰ��. ������ ���ڿ� �ձ⿡ "+"�� ����ϴ� ���� �� ������ ������ �ֽ��ϴ�), operator-�� ���⸦ �ϰ�, operator==�� ���Ѵٰ� ��������.

		���������� less�� operator<�� �ٸ����ٰ� ������ �����ϴ�.

		�̷��� ���α׷����� ��븦 �������� �Ǹ� �������� ȥ���� ����ϴ�. operator+�� ���⸦ �Ѵٰ� ������ ������. ��������?
	*/



	class Widget {
	public:
		int GetSize() const { return size; }
		int GetSpeed() const { return speed; }

		int size;
		int speed;
	};
}

namespace std {
	
	//�Ʒ��� operator < �� �ǹ̿��� ũ�� ����� �ʽ��ϴ�. �������ϴ�
	template <typename T>
	struct less<shared_ptr<T> > {
		bool operator()(const shared_ptr<T>& a, const shared_ptr<T>& b) const
		{
			return less<T>()(*a, *b);
		}
	};

	/*
		�Ʒ��� ������ ������ �ֽ��ϴ�. Widget�� Ư�� ������� ���Ѵٸ� operator < �� ��Ҵٰ� ���ϱ� ��ƽ��ϴ�.
		�̷��� ������ �𸣴� ����� less<Widget>�� ����Ϸ� �Ҷ�, less<Widget>�� �翬�� ���������� Widget�� operator<�� ����Ѵٰ� ������ ���Դϴ�.
	*/
	template <>
	struct less<Item42::Widget> {
		bool operator()(const Item42::Widget& a, const Item42::Widget& b) const
		{
			return less<int>()(a.GetSpeed(), b.GetSpeed());
		}
	};

	/*
		less(�׷��ϱ� operator<)�� �ƴ� '�ٸ�' ������ ������ ��ü�� �����ϰڴٸ� less��� �Ҹ��� �ʴ� Ư���� �Լ��� Ŭ������ ���弼��.
		���� ���� �ڵ��, ��� �� ���� �ڵ��� ��Ȳ�� ���� �ٶ����ϰ� �ذ��� ���� �ڵ��Դϴ�.
	*/

	//���ٸ� ����� �� �ֽ��ϴ�.
	auto WidgetSpeedCompareLess = [](const Item42::Widget& a, const Item42::Widget& b)
	{
		return less<int>()(a.GetSpeed(), b.GetSpeed());
	};

	//�Լ� ��ü�� ���ٺ��� ü������ ������ �ִ� �� �����ϴ�.(�������� ����)
	struct WidgetSpeedCompareGreater {
		bool operator()(const Item42::Widget& a, const Item42::Widget& b) const
		{
			return greater<int>()(a.GetSpeed(), b.GetSpeed());
		}
	};
}

namespace Item42 {
	using namespace std;

	inline void RunSample() {

		vector<shared_ptr<Widget>> vsw(5);
		generate(vsw.begin(), vsw.end(),
			[count = 0]() mutable->shared_ptr<Widget> 
		{
			auto ptr = make_shared<Widget>();
			ptr->size = count++;
			ptr->speed = count * 2 % 5;
			return ptr;
		});
		sort(vsw.begin(), vsw.end(), less<shared_ptr<Widget>>());


		vector<Widget> vw(5);
		generate(vw.begin(), vw.end(), [count = 0]() mutable->Widget {return { count++, count * 2 % 5 }; });

		sort(vw.begin(), vw.end(), WidgetSpeedCompareGreater());
		sort(vw.begin(), vw.end(), WidgetSpeedCompareLess);

		//set���� ���� �����̳��� �� ���� Ÿ���� ������ ���� �ֽ��ϴ�.
		set<Widget, WidgetSpeedCompareGreater> swGreater(vw.begin(), vw.end());
		/*
			���ٸ� Ȱ���ϴ� ��� ��¦ ���������ϴ�. 
			decltype���� Ŭ���� ��ü�� Ÿ���� �˷���� �ϸ�, ���� ��ü�� ���Ƿ� ������ �� ���⿡ �����ڿ� Ŭ���� ��ü�� ���� �Ѱ���� �մϴ�.

			�Լ� ��ü�� Ȱ���ϴ� ���� ���, �ش� Ÿ���� ���ο� ��ü�� �����Ǿ� set�� ���ε�������
			���ٸ� Ȱ���ϴ� ���, �Ű������� �ѱ� ���� ��ü�� �״�� set�� ���ε� �˴ϴ�.

			������ ���, ���ٰ� ���� ĸ�ĸ� ���� �ܺ��� ���� �����ϴ� ��찡 �ִٸ�, ������ �����ֱ⸦ ����ؼ� ����ؾ� �� ���Դϴ�.
		*/
		set<Widget, decltype(WidgetSpeedCompareLess)> swGreater2(vw.begin(), vw.end(), WidgetSpeedCompareLess);

	}
}