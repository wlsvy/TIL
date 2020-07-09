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
#include <mutex>
#include <thread>

//STL �����̳ʰ� ������ �������� ���� ���� ���ǿ� ���߾� ������

namespace Item12 {
	using namespace std;

	/*
		STL �����̳ʿ� �־�� ���߾����� �����̶�� SGI(�Ǹ��� �׷��Ƚ���)���� ������ ����� ���� ���� �ִ� ǥ���Դϴ�. 
		SGI���� STL �� ����Ʈ�� �����Ǿ� �����Ƿ� �����ϸ� �Ǵµ�, �ٽɸ� �����ϸ� ������ �����ϴ�.

		- ���� �����忡�� �д� ���� �����ϴ�(Multiple readers are safe).
		�����尡 �ϳ��� �����̳��� ������ ���ÿ� �о� ���� ��찡 �ִµ�, ����� �����մϴ�. �翬�� �̾߱������� �б� ���߿� ���� ������ ����Ǹ� �� �˴ϴ�.
		
		- ���� �����忡�� �ٸ� �����̳ʿ� ���� ���� �����ϴ�(Multiple writers to different containers are safe).
		�ϳ� �̻��� �����尡 �ٸ� �����̳ʿ� ���ÿ� �� �� �ֽ��ϴ�.
	*/

	/*
		�����̳��� �Ϻ��� ������ �������� �����Ϸ���

		1. �����̳��� ��� �Լ��� ȣ���ϴ� �ð� ���ȿ� �����̳ʿ� ��(lock)�� �ɱ�.
		2. �����̳ʰ� ����� ���� �ִ� �ݺ����� ��ȿ �Ⱓ ���ȿ� �����̳ʿ� ���� �ɱ�.
		3. �����̳ʿ� ���� ����� �˰����� ���� �ð� ���ȿ� �����̳ʿ� ���� �ɱ�
		(��� �Ұ����� �̾߱��Դϴ�. �˰����� �ڽ��� �����ϰ� �ִ� �����̳ʸ� �ĺ��� �� �ִ� ����� ������ ���� �����ϱ��).
	*/

	vector<int> v(15, 5);

	inline void UnSafeSample() {

		//�Ʒ� �ڵ尡 ������ �������� ���� �� �ֵ��� �غ��ô�.
		auto first5 = find(v.begin(), v.end(), 5);
		if (first5 != v.end()) {
			*first5 = 0;
			cout << " Change" << " Value " << endl;
		}
		

		/*
			�� �ڵ尡 ������ �������� �������� v�� ù° �ٺ��� ��° �ٱ��� ����� ���� ��� ���� �ɸ� ä�� ���� �־�� �մϴ�.
			�׷��� STL �����ڰ� �̷� ��츦 �ڵ����� �����ؼ� �����ϱ�� ����ϱ⵵ ��ƽ��ϴ�.

			�Դٰ� ������ ����ȭ�� ����ϴ� �⺻ ��ġ(��������, ���ؽ� ��)�� ����� �׸� ������ ���� �����ϸ�,
			���� �ϳ��� �����常�� ù° �ٺ��� ��° �ٱ��� ������ �� �ֵ��� �ۼ��ϴ� ���α׷��� ��� "�ɰ��� ���༺���� ���� ����" ������ �� �������� ���� �����ϱ� ����ϴ�.

			STL �����̳ʿ��� ������ ���� �ذ��� �������� �ϰ� �ñ� ���� �����ϴ�. ������ �������� ���� ������ ����ȭ�� ������ �ִ� ���� �����ϴ�.
		*/
	}

	inline void SafeSample() {
		static std::mutex m;
		lock_guard<mutex> lock(m);

		// ���� �� �ڵ�� �����մϴ�.
		vector<int>::iterator first5(find(v.begin(), v.end(), 5));
		if (first5 != v.end()) {
			*first5 = 0;
			cout << " Change" << " Value " << endl;
		}
	}

	inline void RunSample() {
		vector<thread> workers;

		cout << "============= Unsafe Sample ==============" << endl;
		for (int i = 0; i < 15; i++) {
			workers.emplace_back(UnSafeSample);
		}
		for (auto& w : workers) {
			w.join();
		}
		
		workers.clear();
		v = vector<int>(15, 5);


		cout << "============= Safe Sample ==============" << endl;
		for (int i = 0; i < 15; i++) {
			workers.emplace_back(SafeSample);
		}
		for (auto& w : workers) {
			w.join();
		}
	}
}