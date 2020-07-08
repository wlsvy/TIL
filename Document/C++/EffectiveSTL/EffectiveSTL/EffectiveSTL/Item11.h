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

//Ŀ���� �Ҵ��ڸ� ����� ����ϴ� ����� ��������

namespace Item11 {
	using namespace std;

	/*
		����Ʈ STL �޸� ������(allocator<T>) ��� ���ο� �޸� �����ڰ� �ʿ��� ���� �ֽ��ϴ�.

		����Ʈ STL �޸� �����ڴ� �ӵ��� ������, �޸� ȿ���� ����, �Դٰ� STL�� �䱸�� ���� ��û�� �޸� ����ȭ�� ������ �α� �Ͼ��Դϴ�.
		
		����Ʈ STL �޸� �����ڰ� ������ �������� ������ �ΰ� ���� �Ҵ��ڶ�� ����� ������ ���� �ʴ� ��쵵 �ֽ��ϴ�. 
		�� ���� ������ ȯ�濡�� ������ �־ ����ȭ ������ �ɸ��� �ʿ� ���� ������带 ���ϰ� ���� ������.
		
		Ȥ��, �����̳ʿ� ��� �ִ� ��ü���� �ϳ��� �� �ȿ��� �����Ǵ� �� ������ ������ ���� ���� �ֽ��ϴ�. 
		���� ������ ��ü�� Ư���� ���� ���ְ� �Ͽ� �޸� ���� ��ġ�� ������(locality of reference)�� �ش�ȭ�ϴ� ȿ���� ��⿡ ����������.
		
		�ƴϸ� ���� �޸𸮿� �ش��ϴ� Ư���� ���� �����, �ϳ� �̻��� �����̳ʸ� �� �޸𸮿� �ξ� ���� ���μ������� ������ �� �ְ� �ϰ� ���� ���� �ֽ��ϴ�.
	*/

	

	namespace SharedMemoryCase {
		// ���� �޸� ���� ������ �������� malloc�� free �Լ��� ������ ���� ������ ���� ��ƾ�� �ִٰ� �սô�.

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
				//vec�� ���������̹Ƿ� ���ÿ� �Ҵ�ȴ�. �� �κп� ���� ���� �ʿ�
				SharedDoubleVec vec;
			}
			{
				// SharedDoubleVec ��ü�� ���� �� �ִ� ����� ���� �޸𸮸� �Ҵ�(allocate)�մϴ�.
				void * pVectorMemory = malloc(sizeof(SharedDoubleVec));

				// "���� new(placement new)"�� �Ἥ SharedDoubleVec ��ü�� �޸𸮿� ����(construct)�մϴ�
				// �Ʒ� new ������ "���� new(placement new)"�� ����� ���Դϴ�.
				SharedDoubleVec * pv = new(pVectorMemory)SharedDoubleVec;

				// ���� �޸� ���� �ִ� �� ��ü�� �Ҹ�(destroy)��ŵ�ϴ�.
				pv->~SharedDoubleVec();

				// ���� �޸𸮿� �ִ� ó�� �޸� ������ ����(deallocate)�մϴ�.
				free(pVectorMemory);
			}
		}
	}

	namespace DoubleHeapCase {
		/*
			���� Heap1�� Heap2�� �̸��� ���� Ŭ������ �ִٰ� �����սô�. 
			�� �� ���� �� Ŭ������ �޸� �Ҵ�� ���������� ���� ��� �Լ��� ��� �ֽ��ϴ�.
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

		// ����, STL �����̳� �� ���� ������ ���߾� ������ �ٸ� ���� ��� �ΰ� �ͽ��ϴ�.
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
			//v�� s�� ��Ҵ� Heap1�� ��� ��� �����ϴ�.
			vector<int, SpecificHeapAllocator<int, Heap1> > v;  
			multiset<int, less<int>, SpecificHeapAllocator<int, Heap1>> s;
			v.push_back(1);
			s.insert(3);

			//L�� m�� ��Ҵ� Heap2�� ��� ��� �����ϴ�.
			list<Widget, SpecificHeapAllocator<Widget, Heap2>> L;
			map<int, string, less<int>, SpecificHeapAllocator<pair<const int, string>, Heap2> > m;
			L.push_front(Widget());
			m.insert({ 1, "hello" });

			/*
				Heap1�� Heap2�� ���� �ٸ� ��ü�� �ƴ� ���� �ٸ� Ÿ���ӿ� �ָ��սô�.
				ǥ�ؾȿ� ���ϸ� ���� Ÿ���� ��� �Ҵ��� ��ü�� ����(equivalent)�� ������ ����մϴ�.
			*/
		}
	}
}
