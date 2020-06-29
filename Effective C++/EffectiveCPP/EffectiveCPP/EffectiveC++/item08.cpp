#include <iostream>
#include <vector>
#include <string>

//���ܰ� �Ҹ��ڸ� ������ ���ϵ��� �ٵ�� ����
namespace Item08 {
	/*
		 �Ҹ��� �ȿ��� ȣ��� �Լ��� ���ܸ� ���� ���ɼ��� �ִٸ� �Ҹ��ڿ��� ��� �޾Ƴ� �Ŀ� ���ѹ�������(try/catch ��) ���α׷��� ��������(std::abort()) �ؾ� �Ѵ�.
		 - ���ܸ� ����Ű�� �Ҹ��ڴ� ���α׷��� �ҿ��� ���� Ȥ�� ������ ������ ������ �����ϰ� �ֱ� �����̴�.

		� Ŭ������ ������ ����Ǵٰ� ���� ���ܿ� ���� ����ڰ� �����ؾ� �� �ʿ䰡 �ִٸ�, 
		�ش� ������ �����ϴ� �Լ��� �ݵ�� ������ �Լ�(��, �Ҹ����� �ƴ� �Լ�)�̾�� �Ѵ�.
	*/

	class Widget {
	public:
		~Widget() {}
		//�Ҹ��ڿ��� ������ �߻��Ѵٰ� ����
		//c++ �� ���ܸ� �ѱ�� �Ҹ��ڸ� �������� �ʴ´�
	};

	void DoSomething() {
		std::vector<Widget> v(10);
		//���Ϳ� ����� Ŭ���� ��ü�� ��ȯ�Ҷ� �� å���� ���Ϳ� �ִ�.
		//���� ������ ��ü�� �Ҹ�� �� ������ �����ٸ�?? 
	}

	class DBConnection {
	public:
		static DBConnection create() { return DBConnection(); }

		//������ ���̽� ���� ����, �̶� ������ �����ϸ� ���� �߻�
		void close() {}
	};

	class DBConn {
	public:
		DBConn(DBConnection target) : db(target) {}

		void close() {
			//public ���� �����Ͽ� ���α׷��Ӱ� ����� �� �ֵ���
			//1������ ���������� ������ ���α׷��ӿ���
			db.close();
			closed = true;
		}

		//���ܴ� �Ҹ��尡 �ƴ� �ٸ� �Լ����� ��ԵǾ�� �Ѵ�
		~DBConn() {	
			
			//����ڰ� ������ �� �ݾ����� ���⼭ �ݱ�
			if (!closed) {	
				try {
					db.close();
				}
				catch (std::exception& e) {
					//close ���� �α� �ۼ� - ���� �˸���
					//std::abort(); - ���α׷� �����ϴ� ����� ����
				}
			}
		}

	private:
		DBConnection db;
		bool closed;
	};

	void DoSomething2() {
		DBConn dbc(DBConnection::create());
		//DBConn ��ü ������ �Ҹ��� �̷��������, ���ÿ� DBConnection �� ���� ������ �Ҹ굵 �߻�
	}
}