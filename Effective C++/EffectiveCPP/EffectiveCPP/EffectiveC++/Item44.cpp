#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�Ű������� �������� �ڵ�� ���ø����κ��� �и���Ű��

namespace Item44 {

	template<typename T,	//���⼭ T�� Ÿ�� �Ű����� 
		std::size_t n>	//n�� ��Ÿ�� �Ű�����
	class SquareMatrix {
	public:
		void invert() {}	//�־��� ����� ��������� �����.
	};

	void func() {
		SquareMatrix<double, 5> sm1;	
		sm1.invert();

		SquareMatrix<double, 10> sm2;
		sm2.invert();
		/*
			n*n ��Ŀ� ���� ������� ���ϴ� ��� 
			��ǻ� sm1, ms2�� n�� ���ؼ��� ���̰� �ְ� ���� �޼ҵ�� �Ȱ��� ������ 
			�ڵ� ���ȭ�� ������ �� �� �ִ�.
		*/
	}
}

namespace Item44_2 {
	//Ŭ������ �и����� �ڵ� ���ȭ�� �ּ�ȭ ��Ű�� ���
	//������ �⺻ Ŭ������ �Ļ� Ŭ������ �����͸� ���� ���ϱ� ������, ��� ����� �����ϴµ� ��ְ� ���� �� �ִ�.
	template<typename T>
	class SuqreMatrixBase {
	protected:
		void invert(std::size_t matrixSize) {}
	};

	template<typename T, std::size_t n>
		class SquareMatrix : private SuqreMatrixBase<T> {
		public:
			void invert() { invert(n); }
			/*
				��Ÿ�� �Ű������� ���� �ڵ� ���ȭ�� ���� ���ؼ�
				���� ����� �⺻ Ŭ������ �����ϰ�, n �� �Ű������� �ѱ�� �Ļ�Ŭ�������� ȣ���Ѵ�.
			*/

		private:
			using SuqreMatrixBase<T>::invert;	//�⺻ Ŭ������ invert�� ����� ���̶� �˸�. �׸� 43
	};

}

namespace Item44_3 {
	//�⺻Ŭ������ �����͸� �˰� �ϴ� ���
	template<typename T>
	class SuqreMatrixBase {
	protected:
		SuqreMatrixBase(std::size_t n, T *pMem) : size(n), pData(pMem) {}

		void setDataPtr(T* ptr) { pData = ptr; }

	private:
		std::size_t size;
		T *pData;
		void invert(std::size_t matrixsize) {}
	};

	template<typename T, std::size_t n>
	class SquareMatrix : private SuqreMatrixBase<T> {
	public:
		SquareMatrix() : SuqreMatrixBase<T>(n, data) {}	//���� ���, �Ļ� Ŭ������ �����͸� ��� Ŭ������ ������.
		void invert() { invert(n); }

	private:
		using SuqreMatrixBase<T>::invert;

		T data[n*n];
	};
	/*
		�̷��� �Ļ� Ŭ������ ����� ���� �޸� �Ҵ��� �ʿ� ���� ��ü�� ������, ��ü ��ü�� ũ�Ⱑ Ŀ�� �� �ִ�.
	*/
}

namespace Item44_4 {
	//�����͸� ���� �ø��� ���
	template<typename T>
	class SuqreMatrixBase {
	protected:
		SuqreMatrixBase(std::size_t n, T *pMem) : size(n), pData(pMem) {}

		void setDataPtr(T* ptr) { pData = ptr; }

	private:
		std::size_t size;
		T *pData;
		void invert(std::size_t matrixsize) {}
	};

	template<typename T, std::size_t n>
	class SquareMatrix : private SuqreMatrixBase<T> {
	public:
		SquareMatrix() 
			: SuqreMatrixBase<T>(n, 0)
			//, pData(new T[n*n])
		{
			//this->setDataPtr(pData.get());
		}
		/*
			�⺻ Ŭ������ �����͸� �η� �����ϰ�,
			��� ���� �޸𸮸� �Ҵ��ϰ�,
			�Ļ� Ŭ������ �����Ϳ� �� �޸𸮸� ���� ���� ��,
			�� �������� �纻�� �⺻ Ŭ������ �÷�������.
		*/

	private:
		//boost::scoped_array<T> pData;
	};
}