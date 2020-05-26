#include <iostream>
#include <vector>
#include <string>
using namespace std;

//매개변수에 독립적인 코드는 템플릿으로부터 분리시키자

namespace Item44 {

	template<typename T,	//여기서 T는 타입 매개변수 
		std::size_t n>	//n은 비타입 매개변수
	class SquareMatrix {
	public:
		void invert() {}	//주어진 행렬을 역행렬으로 만든다.
	};

	void func() {
		SquareMatrix<double, 5> sm1;	
		sm1.invert();

		SquareMatrix<double, 10> sm2;
		sm2.invert();
		/*
			n*n 행렬에 대해 역행렬을 구하는 기능 
			사실상 sm1, ms2는 n에 대해서만 차이가 있고 내부 메소드는 똑같기 때문에 
			코드 비대화의 원인이 될 수 있다.
		*/
	}
}

namespace Item44_2 {
	//클래스를 분리시켜 코드 비대화를 최소화 시키는 방법
	//하지만 기본 클래스가 파생 클래스의 데이터를 알지 못하기 때문에, 몇몇 기능을 구현하는데 장애가 있을 수 있다.
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
				비타입 매개변수로 인한 코드 비대화를 막기 위해서
				공통 기능은 기본 클래스에 정의하고, n 을 매개변수로 넘기며 파생클래스에서 호출한다.
			*/

		private:
			using SuqreMatrixBase<T>::invert;	//기본 클래스의 invert를 사용할 것이라 알림. 항목 43
	};

}

namespace Item44_3 {
	//기본클래스가 데이터를 알게 하는 방법
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
		SquareMatrix() : SuqreMatrixBase<T>(n, data) {}	//개량 방식, 파생 클래스의 데이터를 기반 클래스로 보낸다.
		void invert() { invert(n); }

	private:
		using SuqreMatrixBase<T>::invert;

		T data[n*n];
	};
	/*
		이렇게 파생 클래스를 만들면 동적 메모리 할당이 필요 없는 객체가 되지만, 객체 자체의 크기가 커질 수 있다.
	*/
}

namespace Item44_4 {
	//데이터를 힙에 올리는 방법
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
			기본 클래스의 포인터를 널로 설정하고,
			행렬 값의 메모리를 할당하고,
			파생 클래스의 포인터에 그 메모리를 물려 놓은 후,
			이 포인터의 사본을 기본 클래스로 올려보낸다.
		*/

	private:
		//boost::scoped_array<T> pData;
	};
}