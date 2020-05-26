#include <iostream>
#include <vector>
#include <string>

class Item3 {	
public:
	//�⺻Ÿ�� ��ü�� ��쿡 ���� ������ �ʱ�ȭ�� �Ǳ⵵ �ϰ� �׷��� �ʱ⵵ �Ѵ�.
	int x = 0;	//���� �ʱ�ȭ
	const char * text = "A C-style string";	//�������� ���� �ʱ�ȭ

	void DoSomething() {
		double d;
		std::cin >> d;	//�Է� ��Ʈ������ �����鼭 �ʱ�ȭ
	}

	Item3(int val, bool) {
		x = val;	//�� ������ �ʱ�ȭ�� �ƴ϶� ����. 
					//��Ȯ���� �ʱ�ȭ�� �̷���� ������ ���� ���Խ�Ű�� ��
	}
	Item3(int val) : x(val) {}	//����� �� �ʱ�ȭ

	Item3() :			//������ ȣ��
		theName(),		//string ������ ȣ��
		theAddress(),	//��������
		Numbers(),		//��������
		numTimesConsulted(0)	//0���� �ʱ�ȭ
	{}

private:
	std::string theName;
	std::string theAddress;
	std::vector<int> Numbers;
	int numTimesConsulted;
};

class FileSystem {	//Ư�� ���̺귯���� ���Ե� Ŭ������ ����.
public:
	std::size_t numDisks() const { return 0; }

};

FileSystem tfs;	//����ڰ� ���� �� ��ü

class Directory {	//���̺귯���� ����ڰ� ���� Ŭ������ ����
public:
	Directory() {
		std::size_t disks = tfs.numDisks(); //tfs ��ü�� ���⼭ �����.
											//������, tfs �� ����� ������ tfs �� �ʱ�ȭ���� �ʾ��� �� ����.
											//�ٸ� ���� ������ ���ǵ� ������ ���� ��ü.
	}
};


//////////////////////////�ذ�å////////
//�̱��� ���� Ȱ��
FileSystem& tfs2() {
	static FileSystem fs;
	return fs;
}
Directory& tempDir() {
	static Directory td = Directory();
	return td;
}