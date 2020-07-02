# Effective C++

## 1. C++에 왔으면 C++의 법을 따릅시다.

1. [C++를 언어들의 집합체로 바라보는 안목은 필수](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item01.h)
2. [#define을 쓰려거든 const, enum, inline을 떠올리자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item02.h)
3. [낌새만 보이면 const를 들이대 보자!](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item03.cpp)
4. [객체를 사용하기 전에 반드시 그 객체를 초기화 하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item04.cpp)

## 2. 생성자, 소멸자 및 대입 연산자

5. [C++가 은근슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item05.h)
6. [컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item06.cpp)
7. [다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item07.cpp)
8. [예외가 소멸자를 떠나지 못하도록 붙들어 놓자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item08.cpp)
9. [객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item09.cpp)
10. [대입 연산자는 *this의 참조자를 반환하게 하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item10.cpp)
11. [operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item11.cpp)
12. [객체의 모든 부분을 빠짐없이 복사하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item12.cpp)

## 3. 자원 관리

13. [자원 관리에는 객체가 그만](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item13.cpp)
14. [자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item14.cpp)
15. [자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item15.cpp)
16. [new 및 delete를 사용할 때는 형태를 반드시 맞추자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item16.cpp)
17. [new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item17.cpp)

## 4. 설계 및 선언

18. [인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item18.cpp)
19. [클래스 설계는 타입 설계와 똑같이 취급하자](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item19.h)
20. ['값에 의한 전달'보다는 '상수객체 참조자에 의한 전달' 방식을 택하는 편이 대개 낫다](https://github.com/wlsvy/TIL/blob/master/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item20.cpp)
