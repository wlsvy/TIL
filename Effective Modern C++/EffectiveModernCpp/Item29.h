#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//�̵� ������� �������� �ʰ�, �������� �ʰ�, ������� ���� ���̶�� �����϶�.

namespace Item29 {

	/*
		 �̵� �ǹ̷��� �������� �ʴ� Ÿ�Ե��� ���� �ʴ�
		
		C++11�� C++98 ǥ�� ���̺귯���� ��ü������ �����ߴµ�, 
		Ư�� �̵��� ���纸�� ������ ������ �� �ִ� Ÿ�Ե鿡�� �̵� ������� �߰��ߴ�. 
		���� ���̺귯�� ������ҵ��� ������ �׷� ������� ������ ���ϵ��� �����ߴ�.

		�Ϻ� ���α׷��ӵ��� �ٷ�� �ڵ� ����� C++11�� ������ ���ϵ��� ������ �������� �ʾ��� ���ɼ��� �ִ�. 
		�������� ���� ���α׷�(�Ǵ� �������� ����ϴ� ���̺귯��)�� �ִ� Ÿ�Ե��� C++11�� �°� ������ �������� �ʾҴٸ�, 
		�����Ϸ��� �̵��� �����Ѵٰ� �ص� ���� ���α׷��� ������ ������ ���������� ���� ���̴�.

		*Ŭ���� �� �Ҹ���/����� ���� ���� ������ ����Ǿ��� �� �̵������ڰ� �ڵ� �������� �ʴ� ��
		* C++11 ǥ�� ���̺귯���� ��� �����̳ʴ� �̵��� ����������, ��� �����̳��� �̵��� ���������� �ʴٴ� ��

		-> std::array : ���� �迭�� std �������̽��� ���� ������ ���빰�� ���� �����ϴ� �ٸ� �����̳ʵ�� �ٸ���.
		�̵� ������ ������ ���� ���� �Ҵ�� �޸𸮸� ����Ű�� ������ ���� ��븸 �����ϱ� ����������, 
		std::array���� �׷� �����Ͱ� ���� �迭���� ��ü ��ü�� ���޵ȴ�. ���� ���ҵ��� ���� ������ �̵����Ѿ� �Ѵ�.

		-> std::string ���ڿ� ���� �߿��� ���� ���ڿ� ����ȭ(small string optimization, SSO)�� ����ϴ� ���� ����.
		SSO �� ��� ũ�Ⱑ ���� ���ڿ�(���� ��� �뷮�� 15�� ����)�� ���ؼ��� ������ ���� �Ҵ����� �ʰ� string ��ü �ȿ� �����ϴ� ���̴�.
		�� ���, �̵� ������ ���翬�꿡 ���� ũ�� �����ٰ� �� �� ����.

		���� �̵��� �����ϴ� Ÿ�Կ�����, ������ ���⿡ �̵��� �Ͼ ���� ��Ȳ���� ����� ���簡 �Ͼ�� ��찡 ����⵵ �Ѵ�.

		-> ǥ�� ���̺귯���� �Ϻ� �����̳� ������� ���� ���� �������� �����Ѵ�.
		�̸� ���� �̵� ������� ���ܸ� ������ ������ Ȯ���� ��쿡�� ���� ���� ������� �̵� ������ ��ü�Ѵ�.

		�� ������, �ش� ���� ���꺸�� ȿ������ �̵� ������ �����ϴ� Ÿ���̶�� �ص�,
		�׸��� �ڵ��� Ư�� �������� �Ϲ������� �̵� ������ �����ϴٰ� �ص�,
		�ش� �̵� ������ noexcept�� ����Ǿ� ���� ������ �����Ϸ��� ������ ���� ������ ȣ���� �� �ִ�.

	*/


	/*
		
		C++11���� �̵� �ǹ̷��� ũ�� ������ ���� �ʴ� �ó�����
		- �̵� ������ ����: �̵��� ��ü�� �̵� ������� �������� �ʴ´�. �� ��� �̵� ��û�� ���� ��û�� �ȴ�.
		- �̵��� �� ������ �ʴ�: �̵��� ��ü�� �̵� ������ �ش� ���� ���꺸�� ������ �ʴ�.
		- �̵��� ����� �� ����: �̵��� �Ͼ���� �̵� ������ ���ܸ� �������� �ʾƾ� �ϴ� ���ƿ���, �ش� ������ noexcept�� ����Ǿ� ���� �ʴ�.
		- ���� ��ü�� �������̴�: ���� �幮 ���(�̸��׸� �׸� 25)������, ���� �������� �̵� ������ ������ �� �� �ִ� ��쵵 �ִ�.


	*/
}