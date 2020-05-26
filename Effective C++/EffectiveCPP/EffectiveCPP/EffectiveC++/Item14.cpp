#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;


namespace Item14 {

	//�ڿ� ���� Ŭ������ ���� ���ۿ� ���� �����ϰ� ��������
	class Lock {
	public:
		explicit Lock(mutex *pm) : mutexPtr(pm) { mutexPtr->lock(); }	//�ڿ� ȹ�� �� ���ؽ� ���
		~Lock() { mutexPtr->unlock(); }	//�Ҹ� �� ���ؽ� ��� ����
	private:
		mutex *mutexPtr;
	};

	void doSomething() {
		mutex m;

		{					//Ȱ�� ��������
			Lock m1(&m);	//���ؽ��� ��� ����
			//�Ӱ� �������� ���� ����
		}					//����� ��� ��� ���ؽ� ��� ����


		{
			Lock m1(&m);
			Lock m2(m1);	//Lock �����ϴ� ���� ��� ó���ؾ� �ϴ���??

			/*
				1. ���縦 ���� : 
				�������� �������� ���� RAII Ŭ������ 
				���ʿ� ���縦 ���� �δ� ���� ����ȴ�.

				class Lock : private Uncopyable {...};

				2. �����ϰ� �ִ� �ڿ��� ���� ���� ī���� ���� :
				shared_ptr �� Ȱ���ϴ� ����� �ִ�.

				3.�����ϰ� �ִ� �ڿ��� ��¥�� ����
				string �� ���÷� �� �� �ִ�. 
				���� ���縦 Ȱ���Ͽ� �� �޸��� �����ͱ��� ����
				
				4. �����ϰ� �ִ� �ڿ��� �������� ����
				unique_ptr �� ������ ������ ���� ������� �����ϰԲ� ����
			*/
		}
	}

	class SharedLock {
	public:
		explicit SharedLock(mutex* pm) : mutexPtr(pm, SharedLock::Unlock) { mutexPtr->lock(); }	
		//�����ڷ� unlock �Լ��� ����ؼ� mutex ��ü�� ��ȯ�ϴ� ���� �ƴ� �ٽ� ��Ź����� ������ ����
	private:
		static void Unlock(mutex* pm) { pm->unlock(); }	//������(deleter) �� ����� �Լ�
		std::shared_ptr<mutex> mutexPtr;	//shared_ptr ���
	};
}