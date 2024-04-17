#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

//"has-a(...�� ...�� ����)" Ȥ�� "is-implemented-in-terms-of(...�� ...�� �Ἥ ������)"�� ����ȭ�� ���� ��ü �ռ��� �������

namespace Item38 {
	using namespace std;

	/*
		��ü �ռ�(composition)�� �ǹ̴� public ����� ���� �ǹ̿� ������ �ٸ��ϴ�.

		public ��� : is-a(...�� ...�� ����)
		��ü �ռ� : has-a(...�� ...�� ����) Ȥ�� is-implemented-in-terms-of(...�� ...�� �Ἥ ������)
	
	*/

	/*
			- ����Ʈ���� ���߿��� ����(domain)�� �� ������ ������. 
			���� ����(application domain) : ���, �̵����� �� ���� �繰�� �� ���� ���� ��ü���� ���� ����
			���� ����(implementation domain) : ����, ���ؽ�, Ž�� Ʈ�� �� �����ϰ� �ý��� �������� ���� �ΰ������� ���� ����. 
			
			���⼭ ��ü �ռ��� ���� ������ ��ü�� ���̿��� �Ͼ�� has-a �����̴�. 
			�ݸ� ���� �������� �Ͼ�� �� ��ü �ռ��� �ǹ̴� (is-implemented-in-terms-of) ���踦 ��Ÿ����.

			�Ἥ �����Ǵ� ����(is implemented in terms of) ������ ����
			-> Ư�� �Ļ�Ŭ������ ���Ŭ������ is-a ���谡 �ƴ�����, �Ļ�Ŭ������ ��� Ŭ������ ����� Ȱ���ؼ� ������ ��
	*/
}