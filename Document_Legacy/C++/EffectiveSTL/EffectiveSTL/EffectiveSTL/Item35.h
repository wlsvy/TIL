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
#include <numeric>

//��ҹ��ڸ� �������� �ʴ� ���ڿ� �񱳴� mismatch �ƴϸ� lexicographical_compare�� �Ἥ ������ ������ �� �ִ�

namespace Item35 {
	using namespace std;

	/*
		��ҹ��ڸ� �������� �ʴ� ���ڿ� ���� ������ ���� ���� �ְ� �׷��� ���� ���� �ֽ��ϴ�. "�������� �ʴ� ������ ��ŭ�̳� ���ϳ�"�� ���� �޶�����.
		����ȭ(internationalization)�� ���� ������ �׳� ������ ������ ���� strcmp���� ���� ������ ���Ѵٸ� �� �۾��� ��ô �����ϴ�.

		�׷��� strcmp�� �Ѻ��⿡�� ���� �� ���ڿ��� ó������ �����ϰ� �ϰų� �⺻ ������ �̿��� �������� ����ϴ� ����� ���� ���ܷ� ��ƽ��ϴ�.
		(�̸��׸� �ѱ�� ���� �̿��� �ٸ� ���� ������ �ؽ�Ʈ�� ���� ���ڿ�)
	*/

	auto ciCharEquality = [](const char c1, const char c2) {
		return tolower(static_cast<unsigned char>(c1)) == tolower(static_cast<unsigned char>(c2));
	};
	auto ciCharLess = [](const char c1, const char c2) {
		return tolower(static_cast<unsigned char>(c1)) < tolower(static_cast<unsigned char>(c2));
	};
	auto ciCharCompare = [](const char c1, const char c2) {
		//tolower�� �Ű� ������ ��ȯ���� int Ÿ��������, int�� EOF�� �ƴϾ�� �ϸ鼭	unsigned char�� ��Ÿ�� �� �ִ� �����̾�� �մϴ�.
		auto lc1 = tolower(static_cast<unsigned char>(c1));
		auto lc2 = tolower(static_cast<unsigned char>(c2));


		//c1 < c2�̸� - 1��, c1 == c2�̸� 0�� c1 > c2�̸� 1�� ��ȯ�մϴ�.
		if (lc1 < lc2) return -1;
		if (lc1 > lc2) return 1;
		return 0;
	};

	namespace UseMismatch {

		/*
			�켱�� �� ���� ���ڰ� "��ҹ����� ���θ� �����ϰ�" �������� �˾Ƴ��� ����� �ʿ��մϴ�.
			�� ���� ���ڸ� ��� �ҹ���(Ȥ�� �빮��)�� ���� �ڿ� �񱳸� �ϸ� ������ �ذ�˴ϴ�
		*/

		int ciStringCompareImpl(const string& s1, const string& s2);
			

		int ciStringCompare(const string& s1, const string& s2)
		{
			if (s1.size() <= s2.size()) return ciStringCompareImpl(s1, s2);
			else return -ciStringCompareImpl(s2, s1);
		}

		int ciStringCompareImpl(const string& s1, const string& s2)
		{
			auto p = mismatch(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharEquality);

			// true�̸�, s1�� s2�� ������, s1�� s2���� ���̰� ª���� �� �� �ϳ��Դϴ�.
			if (p.first == s1.end()) {
				if (p.second == s2.end()) return 0;
				else return -1;
			}

			return ciCharCompare(*p.first, *p.second);
		}
	}

	namespace UseLexicographical {
		/*
			���� �� �� �ִ� "��ҹ��� �񱸺� ���ڿ� �񱳹�" �� ��° ����� STL�� ������ ���� ���� ������ �����,
			�̰��� ���� �����̳��� �� �Լ�ó�� ����ϴ� ���Դϴ�.���� �ڵ�� ����� �����ϰ� �����ϱ� �����ϴ�.

			������ ciCharCompare �������̽��� ���� ������ �°� ��ġ��, ���ڿ� �� �κ��� lexicographical_compare�� ��ü�ϱ⸸ �ϸ� �˴ϴ�.

			�ٸ� ������� �ٸ��� ��ȯ Ÿ���� bool���� ����սô�.
		*/

		bool ciStringCompare(const string& s1, const string& s2)
		{
			return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
		}
	}

	namespace UseStricmp {
		/*
			��� �̹� �׸񿡼� ������ �� ��ҹ��� �񱸺� ���ڿ� �� �Լ��� ����� �͵��� �̹� ǥ�� C ���̺귯�� ���� ��ǥ�� Ȯ�� �Լ��� ������� �ְ�, ���а� ���ǰ� �ֽ��ϴ�. 
			�̸��� stricmp Ȥ�� strcmpi ���̸�, �̹� �׸񿡼� �Բ� ������ �� �Լ��麸�ٵ� ����ȭ ������ ����մϴ�.
			
			�������� �̽ļ��� �� �Ű��� ���� �ʰ�, 
			�������� ����ϴ� ���ڿ����� NULL ���ڰ� ���ļ� ���� ������, 
			����ȭ�� ģ���� ������ ���� ���ٸ� STL�� ���� ������� �ʰ� ��ҹ��� �񱸺� ���ڿ� �񱳸� ������ �� �ֽ��ϴ�.

			string ��ü�� const char* �����ͷ� ��ȯ�� ���� strcmpi�� stricmp�� �ѱ�� �Ǵϱ��.

			���� ���� ���������, stricmp/strcmpi�� ���� ���ڿ� �񱳸��� �ϵ��� ����ȭ�� �Լ��̱� ������ ,
			mismatch�� lexicographical_compare ���� ���� �˰��򺸴� �� ���ڿ� ó������ ������ �����ϴ�.
		*/

		auto ciStringCompare(const string& s1, const string& s2)
		{
			return _stricmp(s1.c_str(), s2.c_str());
		}
	}

	inline void RunSample() {
		auto str0 = "Hello World", str1 = "GoodBye World", sameStr = "Same String";
		
		auto res = UseMismatch::ciStringCompare(str0, str1);
		res = UseMismatch::ciStringCompare(str1, str0);
		res = UseMismatch::ciStringCompare(sameStr, sameStr);

		res = UseLexicographical::ciStringCompare(str0, str1);
		res = UseLexicographical::ciStringCompare(str1, str0);
		res = UseLexicographical::ciStringCompare(sameStr, sameStr);

		res = UseStricmp::ciStringCompare(str0, str1);
		res = UseStricmp::ciStringCompare(str1, str0);
		res = UseStricmp::ciStringCompare(sameStr, sameStr);
	}
}