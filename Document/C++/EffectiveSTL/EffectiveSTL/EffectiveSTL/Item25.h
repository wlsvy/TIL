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
#include <unordered_map>

//����� ǥ���� �ƴ�����, �ؽ� �����̳ʿ� ���� ����� ����� ����

namespace Item25 {
	using namespace std;

	/*
		c++ 11 ���� ������ unordered_map/set�� �����Ͽ����ϴ�.
	*/

	/*
		SGI ������ �ؽ� �����̳��� hash_set�� Ÿ���� ������ ���� ��Ÿ�� �� �ֽ��ϴ�(���� ���� ���·� ���� �ٲپ����ϴ�).
	*/

	template <typename T,
		typename HashFunction = hash<T>,
		typename CompareFunction = equal_to<T>,
		typename Allocator = allocator<T> >
		class hash_set;
	/*
		������ �� ���� �� �Լ��� ���� �⺻ Ÿ������ equal_to�� ����ϰ� �ִٴ� ���Դϴ�.
		��, �� ��ü�� ������ �˾ƺ� �� ����� �ƴ� �� �˻縦 �Ѵٴ� ���Դϴ�.

		�ؽ� ���̺��� ������ ����, ǥ�� �����̳ʰ� ��� �ɰ� ��Ű�� ���� ������ �ؽ� �����̳ʿ��� ���ǹ��ϱ� ������ �̷� ������ ���̾��� ������ �ƴմϴ�.

		�߰������� �ؽ� ���̺� ���� ��, �浹 ó���� ü�̴�chaining ����� ���� Ȱ���մϴ�. 
		�����ּҹ� open addressing�� ������ ����� ��ȿ������ �������(�ؽ� �Լ��� �� �� ȣ���ϴ� ��)�� ������ �� �ֱ� �����Դϴ�.
	*/
}
