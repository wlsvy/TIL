#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

//�ڿ� ���� Ŭ������ ���� ���ۿ� ���� �����ϰ� ��������

namespace Item14 {

	
	class Lock {
	public:
		explicit Lock(mutex *pm) : mutexPtr(pm) 
		{ 
			//�ڿ� ȹ�� �� ���ؽ� ���
			mutexPtr->lock(); 
		}	
		~Lock() 
		{ 
			//�Ҹ� �� ���ؽ� ��� ����
			mutexPtr->unlock(); 
		}	
	private:
		mutex *mutexPtr;
	};

	void doSomething() {
		mutex m;

		//�������� ���� Ȱ�� ��������
		{	
			//���ؽ��� ��� ����
			Lock m1(&m);	

			//... -> �Ӱ� �������� ���� ����
		}					
		//����� ��� ��� ���ؽ� ��� ����


		{
			//Lock �����ϴ� ���� ��� ó���ؾ� �ϴ���??
			Lock m1(&m);
			Lock m2(m1);	

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
		//�����ڷ� unlock �Լ��� ����ؼ� mutex ��ü�� ��ȯ�ϴ� ���� �ƴ� �ٽ� ��������ϴ� ������ ����
		explicit SharedLock(mutex* pm) : mutexPtr(pm, SharedLock::Unlock) 
		{
			mutexPtr->lock(); 
		}	
		
	private:
		//������(deleter) �� ����� �Լ�
		static void Unlock(mutex* pm) { pm->unlock(); }	

		//shared_ptr ���
		std::shared_ptr<mutex> mutexPtr;	
	};
}