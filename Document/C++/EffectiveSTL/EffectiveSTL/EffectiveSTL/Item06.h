#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//C++ �����Ϸ��� ���̾��� �м� ����� ��������

namespace Item06 {
	using namespace std;


	
	inline void RunSample() {
		/*
			C++ �����Ϸ��� ���� ������ �ǵ����� ���� ������� �ؼ��� ���� �ֽ��ϴ�.
			int �����Ͱ� ��� �ִ� ������ ������ �ְ�, �� ���Ͽ� ��� �ִ� int�� list�� �����Ѵٰ� ������ ����. ������ �ڵ� ������ ���� �� ���� ���Դϴ�.

			ifstream dataFile("ints.dat");
			list<int> data(istream_iterator<int>(dataFile), istream_iterator<int>());

			�� �ڵ�� �� �����ϵ����� ��Ÿ�ӿ� �ƹ��� �ϵ� ���� �ʽ��ϴ�.

			���Ͽ��� �����͸� ������ ���� �Ӵ��� list ��ü�� �������� �ʽ��ϴ�.
			������ �����Ϸ��� �� ������ list ��ü�� ������ �ƴ϶� data��� �̸��� �Լ� �������� �ؼ��ϱ� �����Դϴ�.

			list<int>�� ��ȯ Ÿ���� ���� �Լ� ���Դϴ�. �� �Լ��� �� ���� �Ű� ������ �޽��ϴ�. �ϳ��� ������ ����.

			ù° �Ű� ������ dataFile�̶� �̸��� ������ �ֽ��ϴ�. Ÿ���� istream_iterator<int>�Դϴ�. 
			dataFile�� �ѷ��ΰ� �ִ� ��ȣ�� ���ʿ��� ���̹Ƿ� �����Ϸ��� ������ �����ϴ�.

			��° �Ű� ������ �̸��� ������ ���� �ʽ��ϴ�. Ÿ���� �ƹ� �͵� �޾Ƶ����� �ʰ� istream_iterator<int>�� ��ȯ�ϴ� �Լ� �������Դϴ�.
		*/
		
		//�̷��� �����ϸ� ���������� �����մϴ�.
		/*
			istream dataFile("ints.dat");
			istream_iterator<int> dataBegin(dataFile);
			istream_iterator<int> dataEnd;
				
			list<int> data(dataBegin, dataEnd);
		*/
		
	}
}