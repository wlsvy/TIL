#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

//���� �������� Ȯ���Ǵ� �׳� ���� �ο�� �� �ο���

namespace Item29 {

	class Lock {
	public:
		explicit Lock(mutex *pm) : mutexPtr(pm) { mutexPtr->lock(); }	//�ڿ� ȹ�� �� ���ؽ� ���
		~Lock() { mutexPtr->unlock(); }	//�Ҹ� �� ���ؽ� ��� ����
	private:
		mutex *mutexPtr;
	};
	class Image {
	public:
		Image(const istream& image) {}
	};

	//���׸��� ��� ������ GUI �޴��� �����ϱ� ���� Ŭ������ �ϳ� ����ٰ� ����
	class PrettyMenu {
	public:
		void changeBackground(std::istream& imgSrc); //���׸��� �ٲٴ� ��� �Լ�
		void changeBackground_1(std::istream& imgSrc);
		void changeBackground_2(std::istream& imgSrc);
	private:
		mutex mut;
		Image *bgImagePtr;
		int ImageChanges;

		shared_ptr<Image> bgImageSptr;
	};

	//���� ��
	void PrettyMenu::changeBackground(std::istream& imgSrc) {
		mut.lock();

		delete bgImagePtr;
		++ImageChanges;
		bgImagePtr = new Image(imgSrc);

		mut.unlock();
	}

	/*
		���� ���ô� ���� �������� ������� �ʴ� �ڵ�
		���� �������� �����Ϸ��� ���� �� ���� ������ �����ؾ� �Ѵ�.

		�ڿ��� ������ ������ �� �� -> new Image(imgSrce) ���� ���ܰ� �߻��ϸ� ���ؽ��� ��� ���·� ���´�
		�ڷᱸ���� ������������ ������� �� �� -> new Image(imgSrce)���� ���� �߻��� bgImagePtr�� ��۸� ������ ���·� ���´�

		���� �������� ���� �� ���� �� ���� ����(guarantee) �� �ϳ��� �����Ѵ�
		- �⺻���� ����(basic gurantee) 
			: �Լ� ���� �߿� ���ܰ� �߻��Ѵٸ�, ���� ���� ���α׷��� ���õ� ��� �͵��� ��ȿ�� ���·� �����ϰڴٴ� ����
			  � ��ü�� �ڷᱸ���� ���������� ������, ��� ��ü�� ���´� ���������� �ϰ����� �����ϰ��ִ�.
		- ������ ����(strong gurantee)
			: �Լ� ���� �߿� ���ܰ� �߻��ϸ�, ���α׷��� ���¸� ����� �������� �ʰڴٴ� ����.
		- ���ܺҰ� ����(nothrow gurantee)
			: ���ܸ� ����� ������ �ʰڴٴ� ����. ����� ������ �ݵ�� ������ ����

		
		
		� �Լ��� �����ϴ� ���� ������ ������ ������, �� �Լ��� ���������� ȣ���ϴ� �Լ����� �����ϴ� ���� ���� ������ ���� �ʽ��ϴ�.
	*/

	//1�� ����
	void PrettyMenu::changeBackground_1(std::istream& imgSrc) {
		Lock lock(&mut);	//��ȿ������ ���������� ������ ���ؽ� ��� ����

		delete bgImagePtr;
		++ImageChanges;
		bgImagePtr = new Image(imgSrc);
	}

	//2�� ����
	void PrettyMenu::changeBackground_2(std::istream& imgSrc) {
		Lock lock(&mut);	

		bgImageSptr.reset(new Image(imgSrc));	//���� �����͸� �ٲ�ġ��
		++ImageChanges;
	}

	//3�� ����
	//copy - and - swap ��� -> �Լ��� ����Ǵ� ���� ���ܰ� �߻����� ��. �̹� ����� �������� ���� ������ �����Ͱ� ���������� ���� ����

	struct PMImpl {	//����ü�� ������ ����. PrettyMenu2 Ŭ���������� PMImpl �� private�� ����Ǿ� �־� �̹� ĸ��ȭ�� �Ǿ� �ֱ� ����
		shared_ptr<Image> bgImage;
		int imageChanges;
	};

	class PrettyMenu2 {
	public:
		void changeBackground(std::istream& imgSrc);
	private:
		mutex mut;
		shared_ptr<PMImpl> pImpl;
	};

	void PrettyMenu2::changeBackground(std::istream& imgSrc) {
		using std::swap;

		Lock lock(&mut);

		shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));	//��ü�� ������ �κ� ����

		pNew->bgImage.reset(new Image(imgSrc));			//�纻 ����
		++pNew->imageChanges;

		swap(pImpl, pNew);								//�� �����ͷ� �ٲ� �ִ´�.
	}
}