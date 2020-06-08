#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

//std::shared_ptró�� �۵��ϵ� ����� ���� ���� �ִ� �����Ͱ� �ʿ��ϸ� std::weak_ptr�� ����϶�

namespace Item20 {

	/*
		��ü�� std::weak_ptr�� std::shared_ptr�� �̿��ؼ� �����Ѵ�. 
		std::weak_ptr�� �ڽ��� �����ϴ� �� ���� std::shared_ptr�� ����Ű�� �Ͱ� ������ ��ü�� ����Ű��, 
		�� ��ü�� ���� ī��Ʈ���� ������ ���� �ʴ´�.

		����� ���� std::weak_ptr�� ������ ����Ǿ���(expired)��� ���Ѵ�. std::weak_ptr�� ���� ���δ� ��� �Լ� expired�� �����ִ� ������ �Ǵ��� �� �ִ�.
		������� ���� std::weak_ptr�̶�� �ص� ����Ī ��ü�� ���� �����ϴ� ���� �Ұ����ϴ�. std::weak_ptr���� ������ ������ ���� �����̴�.

		������ ������ �����ϵ��� �ϴ���, ���� ���˰� ������ �и��ϸ� ���� ������ �߻��� �� �ִ�.	
		��, expired ȣ��� ������ ���̿��� �ٸ� � �����尡 �ش� ��ü�� ����Ű�� ������ std::shared_ptr�� ����� �Ǵ� �ı��� ���� �ֱ� �����̴�. 
		�׷��� �ش� ��ü�� �ı��Ǹ�, �����͸� �������ϸ� ������ �ൿ�� ���´�.

		����� �� �����, std::weak_ptr�κ��� std::shared_ptr�� �����Ͽ� ����ϴ� ���̴�.
	*/

	/*
		ȿ���� �鿡�� std::weak_ptr�� std::shared_ptr�� ���������� �����ϴ�.

		std::weak_ptr ��ü�� �� ũ�Ⱑ std::shared_ptr ��ü�� ������, 
		std::shared_ptr�� ����ϴ� �Ͱ� ���� ���� ����� ����ϸ�, �����̳� �ı�, ���� ���� ���꿡 ������ ���� ī��Ʈ ������ �����Ѵ�.

		�տ��� ����ߵ��� ���� ��Ͽ��� '�� ��°' ���� ī��Ʈ�� ������ �װ��� std::weak_ptr�� �����ϴ� ���� ī��Ʈ�̴�.
		std::weak_ptr�� �������� �뵵�δ� ĳ��, ������ ���, �׸��� std::shared_ptr ��ȯ �� ������ �ִ�.
	*/

	class Widget{};

	inline void RunSample() {

		// std::weak_ptr�� std::shared_ptr�κ��� ���� �� �ִ�.

		auto spw = std::make_shared<Widget>(); // spw�� ������ ��, ���� Widget�� ���� ī��Ʈ(���ϰ����� ī��Ʈ)�� 1�̴�

		std::weak_ptr<Widget> wpw(spw);        // wpw�� spw�� ���� Widget�� ����Ų��; ī��Ʈ�� ������ 1�̴�.

		spw = nullptr;                        // ī��Ʈ�� 0�� �ǰ� Widget�� �ı��ȴ�; ���� wpw�� ����� ���� �����̴�.

		// std::weak_ptr�� ����Ǿ����� �˰� ������,  expired ��� �Լ��� �����ִ� ���� �����ϸ� �ȴ�.
		if (wpw.expired()) {
			std::cout << "If Expired" << std::endl;
		}


		// std::weak_ptr�� ����Ű�� ����Ī ��ü�� ������ �Ϸ��� std::weak_ptr�κ��� std::shared_ptr�� ��� �� std::shared_ptr�� �������Ѵ�.

		// ��� 1: lock ��� �Լ��� ����Ѵ�.
		std::shared_ptr<Widget> spw1 = wpw.lock();   
		auto spw2 = wpw.lock();          
										

		// ��� 2: std::shared_ptr�� �����ڿ� std::weak_ptr�� �Ѱ��ش�.
		std::shared_ptr<Widget> spw3(wpw);    // wpw�� �����̸� std::bad_weak_ptr(����)�� �߻�
	}

	/*
			ĳ�̿��� weak_ptr Ȱ��

			loadWidget�� ����� ũ�� ID���� ��Ǯ���ؼ� ���̴� ��찡 ���ٰ� ����.
			�׷��ٸ� loadWidget�� ���� ���� �ϵ� ȣ�� ������� ĳ���ϴ� �Լ��� �ۼ��Ͽ� ����ȭ�� �� �� ���� ���̴�.

			�׷��� ��û�� ��� Widget�� ĳ�ÿ� ��� �дٸ� �� ��ü�� ���ɻ��� ������ �߻��� ���̹Ƿ�,
			�� �̻� ������ �ʴ� Widget�� ĳ�ÿ��� �����ϴ� ���� �ڿ�������.

			�̷��� ĳ�� ���� ���͸� �Լ��� ��ȯ Ÿ���� std::unique_ptr�� �δ� ���� �׸� �ٶ������� �ʴ�.

			ȣ���ڰ� ĳ�̵� ��ü�� ����Ű�� ����Ʈ �����͸� �޾ƾ� �Ѵٴ� ���� Ȯ���ϸ�, ĳ�ÿ� �ִ� �����͵��� �ڽ��� ����� �Ҿ����� ������ �� �־�� �Ѵ�.
			�� std::weak_ptr�̾�� �Ѵ�.
	*/

	std::shared_ptr<const Widget> loadWidget(int) {
		return std::make_shared<Widget>();
	}

	std::shared_ptr<const Widget> fastLoadWidget(int id)
	{
		static std::unordered_map<int, std::weak_ptr<const Widget> > cache;

		auto objPtr = cache[id].lock();     
		if (!objPtr) {                      
			objPtr = loadWidget(id);        
			cache[id] = objPtr;             
		}

		return objPtr;
	}
}