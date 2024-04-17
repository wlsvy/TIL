#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

//예외 안전성이 확보되는 그날 위해 싸우고 또 싸우자

namespace Item29 {

	class Lock {
	public:
		explicit Lock(mutex *pm) : mutexPtr(pm) { mutexPtr->lock(); }	//자원 획득 시 뮤텍스 잠금
		~Lock() { mutexPtr->unlock(); }	//소멸 시 뮤텍스 잠금 해제
	private:
		mutex *mutexPtr;
	};
	class Image {
	public:
		Image(const istream& image) {}
	};

	//배경그림을 깔고 나오는 GUI 메뉴를 구현하기 위해 클래스를 하나 만든다고 가정
	class PrettyMenu {
	public:
		void changeBackground(std::istream& imgSrc); //배경그림을 바꾸는 멤버 함수
		void changeBackground_1(std::istream& imgSrc);
		void changeBackground_2(std::istream& imgSrc);
	private:
		mutex mut;
		Image *bgImagePtr;
		int ImageChanges;

		shared_ptr<Image> bgImageSptr;
	};

	//수정 전
	void PrettyMenu::changeBackground(std::istream& imgSrc) {
		mut.lock();

		delete bgImagePtr;
		++ImageChanges;
		bgImagePtr = new Image(imgSrc);

		mut.unlock();
	}

	/*
		위의 예시는 예외 안전성이 보장되지 않는 코드
		예외 안전성을 보장하려면 다음 두 가지 사항을 만족해야 한다.

		자원이 새도록 만들지 말 것 -> new Image(imgSrce) 에서 예외가 발생하면 뮤텍스가 잠긴 상태로 남는다
		자료구조가 더럽혀지도록 허용하지 말 것 -> new Image(imgSrce)에서 예외 발생시 bgImagePtr는 댕글링 포인터 상태로 남는다

		예외 안전성을 갖출 시 다음 세 가지 보장(guarantee) 중 하나를 제공한다
		- 기본적인 보장(basic gurantee) 
			: 함수 동작 중에 예외가 발생한다면, 실행 중인 프로그램에 관련된 모든 것들을 유효한 상태로 유지하겠다는 보장
			  어떤 객체나 자료구조도 더럽혀지지 않으며, 모든 객체의 상태는 내부적으로 일관성을 유지하고있다.
		- 강력한 보장(strong gurantee)
			: 함수 동작 중에 예외가 발생하면, 프로그램의 상태를 절대로 변경하지 않겠다는 보장.
		- 예외불가 보장(nothrow gurantee)
			: 예외를 절대로 던지지 않겠다는 보장. 약소한 동작은 반드시 끝내는 보장

		
		
		어떤 함수가 제공하는 예외 안전성 보장의 강도는, 그 함수가 내부적으로 호출하는 함수들이 제공하는 가장 약한 보장을 넘지 않습니다.
	*/

	//1차 수정
	void PrettyMenu::changeBackground_1(std::istream& imgSrc) {
		Lock lock(&mut);	//유효범위를 빠져나갈때 스스로 뮤텍스 잠금 해제

		delete bgImagePtr;
		++ImageChanges;
		bgImagePtr = new Image(imgSrc);
	}

	//2차 수정
	void PrettyMenu::changeBackground_2(std::istream& imgSrc) {
		Lock lock(&mut);	

		bgImageSptr.reset(new Image(imgSrc));	//내부 포인터를 바꿔치기
		++ImageChanges;
	}

	//3차 수정
	//copy - and - swap 방식 -> 함수가 실행되는 도중 예외가 발생했을 때. 이미 진행된 동작으로 인해 기존의 데이터가 더럽혀지는 현상 방지

	struct PMImpl {	//구조체로 선언한 이유. PrettyMenu2 클래스에서는 PMImpl 이 private로 선언되어 있어 이미 캡슈화가 되어 있기 때문
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

		shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));	//객체의 데이터 부분 복사

		pNew->bgImage.reset(new Image(imgSrc));			//사본 수정
		++pNew->imageChanges;

		swap(pImpl, pNew);								//새 데이터로 바꿔 넣는다.
	}
}