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
#include <fstream>

//���� ������ �Է¿��� istreambuf_iterator�� ��뵵 �����ϴ�

namespace Item29 {
	using namespace std;


	inline void RunSample() {
		{
			ifstream inputFile("FileReadSample.txt");

			string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>());
		}
		
		/*
			�� ����� ����(whitespace) ���ڸ� string ��ü�� �������� ���մϴ�.
 
			�ֳ�!? istream_iterator�� ���� ��Ʈ�� �б⸦ ������ ���� operator<< �Լ��� ����ϸ�, 
			�⺻������ �� ������ �Լ��� ���� ���ڸ� �ǳʶٱ� ��������.

			���� ���ڸ� �ǳʶ��� �ʰ� �Ϸ��� �Է� ��Ʈ���� skipws �÷��׸� ��������(unset)�մϴ�.
		*/

		{
			ifstream inputFile("FileReadSample.txt");

			inputFile.unsetf(ios::skipws);
			string fileData2((istream_iterator<char>(inputFile)), istream_iterator<char>());
		}

		/*
			������ ���� ����� ������ ���� �ð��� �׸� ������ �ʽ��ϴ�. 
			istream_iterator �� ����ϴ� operator>> �Լ��� ����ȭ �Է�(formatted input)�� �����մϴ�.
			�� ���� �������� �ؾ� �ϴ� ���� ���� ���������� ��ó���� �˾Ƽ� �̸� ���شٴ� ���Դϴ�.

			�̷��� ���۵��� �������� ����ȭ �Է��� �� ������ �ſ� �����ϰ� ���� ��������,
			�׳� �Է� ��Ʈ�����κ��� ���� ���ڸ� �̾Ƴ��� �ϸ��� �����̶�� ��û�� �ս��̿� ���� �ƴ� �� �����ϴ�.
		*/
		

		/*
			���⼭ STL�� ������ ���⸦ �ϳ� �Ұ��ϰ��� �մϴ�. �ٷ� istreambuf_iterator ��� �ϴ� ���Դϴ�.
			�� �ݺ��ڴ� istream_iteratoró�� �� �� �ֽ��ϴ�. 
			istreambuf_iterator<char> ��ü�� ��Ʈ�� ��ü�� ���۸� ���� �ǵ���� ���� ���ڵ��� �ٷ� �о� ���Դϴ�.
		*/

		{
			ifstream inputFile("FileReadSample.txt");

			/*
				skipws �÷��׸� "��������"�� �ʿ䵵 �����ϴ�.
				��Ʈ�� ���� �ȿ��� ���� ��ġ�� �ִ� ���ڴ� ��� ���̵� ������ ���� ���� �� �ݺ����� Ư���Դϴ�.
			*/
			string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

			//istream_iterator�� ���� �� �� �ݺ����� �ӵ��� ��ô �����ϴ�. �����ϰ� �غ� ��ġ��ũ���� ���� 40%�� �������ϴ�.
		}
	}
}