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
#include <stdlib.h>

//커스텀 할당자를 제대로 사용하는 방법을 이해하자

namespace Item11 {
	using namespace std;

	/*
		디폴트 STL 메모리 관리자(allocator<T>) 대신 새로운 메모리 관리자가 필요할 때가 있습니다.

		디폴트 STL 메모리 관리자는 속도는 느리고, 메모리 효율은 낮고, 게다가 STL의 요구로 인한 엄청난 메모리 단편화에 몸살을 앓기 일쑤입니다.
		
		디폴트 STL 메모리 관리자가 쓰레드 안전성을 염두해 두고 만든 할당자라는 사실이 마음에 들지 않는 경우도 있습니다. 
		즉 단일 쓰레드 환경에만 관심이 있어서 동기화 때문에 걸리는 필요 없는 오버헤드를 피하고 싶은 것이죠.
		
		혹은, 컨테이너에 들어 있는 객체들이 하나의 힙 안에서 관리되는 점 때문에 문제를 느낄 수도 있습니다. 
		같은 종류의 객체를 특정한 힙에 모여있게 하여 메모리 참조 위치의 근접성(locality of reference)을 극대화하는 효과를 얻기에 부족하지요.
		
		아니면 공유 메모리에 해당하는 특수한 힙을 만들어, 하나 이상의 컨테이너를 그 메모리에 두어 여러 프로세스들이 공유할 수 있게 하고 싶을 수도 있습니다.
	*/

	

	namespace SharedMemoryCase {
		// 공유 메모리 힙을 관리할 목적으로 malloc과 free 함수를 본떠서 만든 다음과 같은 루틴이 있다고 합시다.

		template <class T>
		class SharedMemoryAllocator
		{
		public:
			using size_type = size_t;
			using pointer = T * ;
			using reference = T & ;
			using value_type = T;

			SharedMemoryAllocator() = default;

			template <class U>
			SharedMemoryAllocator(const SharedMemoryAllocator<U>&) {}

			pointer allocate(size_type n, const void * = 0) {
				T* t = (T*)malloc(n * sizeof(T));
				std::cout
					<< "  used my_allocator to allocate   at address "
					<< t << " (+)" << std::endl;
				return t;
			}

			void deallocate(void* p, size_type) {
				if (p) {
					free(p);
					std::cout
						<< "  used my_allocator to deallocate at address "
						<< p << " (-)" <<
						std::endl;
				}
			}

			template <class U>
			struct rebind {
				using other = SharedMemoryAllocator<U>;
			};
		};

		inline void RunSample() {
			using SharedDoubleVec = vector<int, SharedMemoryAllocator<int>>;

			vector<int, SharedMemoryAllocator<int>> v;
			{
				//vec은 지역변수이므로 스택에 할당된다. 이 부분에 대한 수정 필요
				SharedDoubleVec vec;
			}
			{
				// SharedDoubleVec 객체를 담을 수 있는 충분한 공유 메모리를 할당(allocate)합니다.
				void * pVectorMemory = malloc(sizeof(SharedDoubleVec));

				// "전용 new(placement new)"를 써서 SharedDoubleVec 객체를 메모리에 생성(construct)합니다
				// 아래 new 문장은 "전용 new(placement new)"를 사용한 것입니다.
				SharedDoubleVec * pv = new(pVectorMemory)SharedDoubleVec;

				// 공유 메모리 내에 있는 이 객체를 소멸(destroy)시킵니다.
				pv->~SharedDoubleVec();

				// 공유 메모리에 있는 처음 메모리 단위를 해제(deallocate)합니다.
				free(pVectorMemory);
			}
		}
	}

	namespace DoubleHeapCase {
		/*
			각각 Heap1과 Heap2란 이름을 가진 클래스가 있다고 가정합시다. 
			이 두 개의 힙 클래스에 메모리 할당과 해제용으로 정적 멤버 함수가 들어 있습니다.
		*/
		class Widget{};

		class Heap1 {
		public:
			static void* alloc(size_t numBytes, const void *memoryBlockToBeNear = 0) { 
				cout << "Alloc in Heap1" << endl;
				return malloc(numBytes);
			}
			static void dealloc(void *ptr) { delete ptr; }
		};
		class Heap2 {
		public:
			static void* alloc(size_t numBytes, const void *memoryBlockToBeNear = 0) {
				cout << "Alloc in Heap2" << endl;
				return malloc(numBytes);
			}
			static void dealloc(void *ptr) { delete ptr; }
		};

		// 이제, STL 컨테이너 몇 개를 종류에 맞추어 제각기 다른 힙에 모아 두고 싶습니다.
		template <typename T, typename Heap>
		class SpecificHeapAllocator {
		public:
			using pointer = T * ;
			using reference = T & ;
			using size_type = size_t;
			using value_type = T;

			SpecificHeapAllocator() = default;

			template <class U>
			SpecificHeapAllocator(const SpecificHeapAllocator<U, Heap>&) {}

			pointer allocate(size_t numObjects, const void *localityHint = 0)
			{
				return static_cast<pointer>(Heap::alloc(numObjects * sizeof(T), localityHint));
			}
			void deallocate(pointer ptrToMemory, size_t numObjects)
			{
				Heap::dealloc(ptrToMemory);
			}

			template<class U>
			struct rebind {
				using other = SpecificHeapAllocator<U, Heap>;
			};
		};

		inline void RunSample() {
			//v와 s의 요소는 Heap1에 모두 모아 놓습니다.
			vector<int, SpecificHeapAllocator<int, Heap1> > v;  
			multiset<int, less<int>, SpecificHeapAllocator<int, Heap1>> s;
			v.push_back(1);
			s.insert(3);

			//L과 m의 요소는 Heap2에 모두 모아 놓습니다.
			list<Widget, SpecificHeapAllocator<Widget, Heap2>> L;
			map<int, string, less<int>, SpecificHeapAllocator<pair<const int, string>, Heap2> > m;
			L.push_front(Widget());
			m.insert({ 1, "hello" });

			/*
				Heap1과 Heap2는 서로 다른 객체가 아닌 서로 다른 타입임에 주목합시다.
				표준안에 의하면 같은 타입의 모든 할당자 객체는 동등(equivalent)한 것으로 취급합니다.
			*/
		}
	}
}
