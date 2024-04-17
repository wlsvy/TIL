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

//범위 내의 데이터 값을 요약하거나 더하는 데에는 accumulate나 for_each를 사용하자

namespace Item37 {
	using namespace std;

	/*
		예를 들어 컨테이너 안의 string의 길이의 합을 구한다든지, 주어진 범위의 숫자들의 곱을 구한다든지 하거나, 
		1차원적인 정보가 아니라 좌표 같은 2차원 이상의 값들의 평균을 구하고 싶을 때도 있습니다. 
		이런 각각의 경우를 통칭하여 "범위를 요약한다(summarize)"라고 합니다.

		범위의 요약에는 어떤 요약을 할 것인지를 정해줄 수 있어야 합니다. 
		STL에는 이런 작업을 하기 위한 accumulate라는 수치 알고리즘이 제공되고 있습니다. 

		수치 알고리즘에는 이것 외에 세 개가 더 있는데, inner_product, adjacent_difference, partial_sum입니다.
	*/

	struct Point {
		double X = 0.0;
		double Y = 0.0;
	};

	const Point & operator+(const Point& lhs, const Point& rhs) {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}

	struct PointAverage {
		//foreach 용
		void operator()(const Point& p) {
			++numPoints;
			Xsum += p.X;
			Ysum += p.Y;
		}
		//accumulate 용
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

		//책에서는 형변환 문제로 인해 intResult가 0일 수 있다고 하지만 c++17 에서 수행결과는 정상입니다.
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
		
		//accumulate를 활용해 구하는 방법
		tmp = accumulate(vp.begin(), vp.end(), Point());

		averagePoint.X = tmp.X / vd.size();
		averagePoint.Y = tmp.Y / vd.size();

		//혹은

		/*
			아래 코드는 아주 잘 작동할 가능성이 크지만, "accumulate에 넘겨지는 함수의 부가적 효과는 없어야 한다"는 표준에 위배됩니다.
			PointAverage의 멤버 변수 numPoints, xSum, 그리고 ySum를 수정하게 되면, 그 자체로 부가적 효과가 발생하기 때문이죠
		*/
		averagePoint = accumulate(vp.begin(), vp.end(), Point(), PointAverage());

		/*
			방금 전 표준에 위배되는 예제 코드와 같은 상황에서는 accumulate 대신 for_each를 사용해야 합니다.
			for_each 알고리즘은 범위 내의 데이터를 요약할 수 있는 또 하나의 알고리즘이면서 accumulate가 가진 이상한 제한도 받지 않습니다.
		*/
		averagePoint = for_each(vp.begin(), vp.end(), PointAverage()).result();
	}
}