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

//���� ���� ������ ���� ����ϰų� ���ϴ� ������ accumulate�� for_each�� �������

namespace Item37 {
	using namespace std;

	/*
		���� ��� �����̳� ���� string�� ������ ���� ���Ѵٵ���, �־��� ������ ���ڵ��� ���� ���Ѵٵ��� �ϰų�, 
		1�������� ������ �ƴ϶� ��ǥ ���� 2���� �̻��� ������ ����� ���ϰ� ���� ���� �ֽ��ϴ�. 
		�̷� ������ ��츦 ��Ī�Ͽ� "������ ����Ѵ�(summarize)"��� �մϴ�.

		������ ��࿡�� � ����� �� �������� ������ �� �־�� �մϴ�. 
		STL���� �̷� �۾��� �ϱ� ���� accumulate��� ��ġ �˰����� �����ǰ� �ֽ��ϴ�. 

		��ġ �˰��򿡴� �̰� �ܿ� �� ���� �� �ִµ�, inner_product, adjacent_difference, partial_sum�Դϴ�.
	*/

	struct Point {
		double X = 0.0;
		double Y = 0.0;
	};

	const Point & operator+(const Point& lhs, const Point& rhs) {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}

	struct PointAverage {
		//foreach ��
		void operator()(const Point& p) {
			++numPoints;
			Xsum += p.X;
			Ysum += p.Y;
		}
		//accumulate ��
		const Point operator()(const Point& avgSoFar, const Point& p) {
			++numPoints;
			Xsum += p.X;
			Ysum += p.Y;
			return { Xsum / numPoints, Ysum / numPoints };
		}
		Point result() const {
			return { Xsum / numPoints, Ysum / numPoints };
		}

		int numPoints = 0;
		double Xsum = 0.0;
		double Ysum = 0.0;
	};

	inline void RunSample() {
		vector<double> vd(10);
		iota(vd.begin(), vd.end(), 1.0);

		//å������ ����ȯ ������ ���� intResult�� 0�� �� �ִٰ� ������ c++17 ���� �������� �����Դϴ�.
		auto intResult = accumulate(vd.begin(), vd.end(), 0);
		auto doubleResult = accumulate(vd.begin(), vd.end(), 0.0);
		auto product = accumulate(vd.begin(), vd.end(), 1.0, multiplies<double>());
		auto sumOfPow = accumulate(vd.begin(), vd.end(), 1.0, [](auto v1, auto v2) { return v1 * v2; });

		vector<Point> vp(10);
		generate(vp.begin(), vp.end(), 
			[initVal = 0.0]() mutable ->Point  
			{ 
				return { initVal, initVal++ };
			});

		Point averagePoint, tmp;
		
		//accumulate�� Ȱ���� ���ϴ� ���
		tmp = accumulate(vp.begin(), vp.end(), Point());

		averagePoint.X = tmp.X / vd.size();
		averagePoint.Y = tmp.Y / vd.size();

		//Ȥ��

		/*
			�Ʒ� �ڵ�� ���� �� �۵��� ���ɼ��� ũ����, "accumulate�� �Ѱ����� �Լ��� �ΰ��� ȿ���� ����� �Ѵ�"�� ǥ�ؿ� ����˴ϴ�.
			PointAverage�� ��� ���� numPoints, xSum, �׸��� ySum�� �����ϰ� �Ǹ�, �� ��ü�� �ΰ��� ȿ���� �߻��ϱ� ��������
		*/
		averagePoint = accumulate(vp.begin(), vp.end(), Point(), PointAverage());

		/*
			��� �� ǥ�ؿ� ����Ǵ� ���� �ڵ�� ���� ��Ȳ������ accumulate ��� for_each�� ����ؾ� �մϴ�.
			for_each �˰����� ���� ���� �����͸� ����� �� �ִ� �� �ϳ��� �˰����̸鼭 accumulate�� ���� �̻��� ���ѵ� ���� �ʽ��ϴ�.
		*/
		averagePoint = for_each(vp.begin(), vp.end(), PointAverage()).result();
	}
}