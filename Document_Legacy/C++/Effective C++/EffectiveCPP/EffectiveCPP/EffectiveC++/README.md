# Effective C++

- 3판 번역서 예제 코드 정리
- 스콧 마이어스 지음

## 1. C++에 왔으면 C++의 법을 따릅시다.

1. [C++를 언어들의 집합체로 바라보는 안목은 필수](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item01.h)
2. [#define을 쓰려거든 const, enum, inline을 떠올리자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item02.h)
3. [낌새만 보이면 const를 들이대 보자!](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item03.cpp)
4. [객체를 사용하기 전에 반드시 그 객체를 초기화 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item04.cpp)

## 2. 생성자, 소멸자 및 대입 연산자

5. [C++가 은근슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item05.h)
6. [컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item06.cpp)
7. [다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item07.cpp)
8. [예외가 소멸자를 떠나지 못하도록 붙들어 놓자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item08.cpp)
9. [객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item09.cpp)
10. [대입 연산자는 *this의 참조자를 반환하게 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item10.cpp)
11. [operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item11.cpp)
12. [객체의 모든 부분을 빠짐없이 복사하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/item12.cpp)

## 3. 자원 관리

13. [자원 관리에는 객체가 그만](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item13.cpp)
14. [자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item14.cpp)
15. [자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item15.cpp)
16. [new 및 delete를 사용할 때는 형태를 반드시 맞추자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item16.cpp)
17. [new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item17.cpp)

## 4. 설계 및 선언

18. [인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item18.cpp)
19. [클래스 설계는 타입 설계와 똑같이 취급하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item19.h)
20. ['값에 의한 전달'보다는 '상수객체 참조자에 의한 전달' 방식을 택하는 편이 대개 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item20.cpp)
21. [함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item21.cpp)
22. [데이터 멤버가 선언될 곳은 private 영역임을 명심하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item22.h)
23. [멤버 함수보다는 비멤버 비프렌드 함수와 더 가까워지자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item23.cpp)
24. [타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item24.cpp)
25. [예외를 던지지 않는 swap에 대한 지원도 생각해 보자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item25.cpp)

## 5. 구현

26. [변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item26.cpp)
27. [캐스팅은 절약, 또 절약! 잊지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item27.cpp)
28. [내부에서 사용하는 객체에 대한 "핸들"을 반환하는 코드는 되도록 피하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item28.cpp)
29. [예외 안전성이 확보되는 그날 위해 싸우고 또 싸우자!](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item29.cpp)
30. [인라인 함수는 미주알고주알 따져서 이해해 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item30.cpp)
31. [파일 사이의 컴파일 의존성을 최대로 줄이자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item31.h)

## 6. 상속, 그리고 객체 지향 설계

32. [public 상속 모형은 반드시 "is-a(...는 ...의 일종이다)"를 따르도록 만들자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item32.h)
33. [상속된 이름을 숨기는 일은 피하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item33.cpp)
34. [인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item34.h)
35. [가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item35.cpp)
36. [상속받은 비가상 함수를 파생 클래스에서 재정의하는 것은 절대 금물!](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item36.h)
37. [어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item37.cpp)
38. ["has-a(...는 ...를 가짐)" 혹은 "is-implemented-in-terms-of(...는 ...를 써서 구현됨)"를 모형화할 때는 객체 합성을 사용하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item38.h)
39. [private 상속은 심사숙고해서 구사하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item39.cpp)
40. [다중 상속은 심사숙고해서 사용하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item40.cpp)

## 7. 템플릿과 일반화 프로그래밍

41. [템플릿 프로그래밍의 천릿길도 암시적 인터페이스와 컴파일 타임 다형성부터](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item41.cpp)
42. [typename의 두 가지 의미를 제대로 파악하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item42.cpp)
43. [템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item43.cpp)
44. [매개변수에 독립적인 코드는 템플릿으로부터 분리시키자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item44.cpp)
45. ["호환되는 모든 타입"을 받아들이는 데는 멤버 함수 템플릿이 직방!](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item45.cpp)
46. [타입 변환이 바람직할 경우에는 비멤버 함수를 클래스 템플릿 안에 정의해 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item46.cpp)
47. [타입에 대한 정보가 필요하다면 특성정보 클래스를 사용하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item47.cpp)
48. [템플릿 메타프로그래밍, 하지 않겠는가?](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item48.cpp)

## 8. new와 delete를 내 맘대로

49. [new 처리자의 동작 원리를 제대로 이해하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item49.cpp)
50. [new 및 delete를 언제 바꿔야 좋은 소리를 들을지를 파악해 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item50.cpp)
51. [new 및 delete를 작성할 때 따라야 할 기존의 관례를 잘 알아 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item51.cpp)
52. [위치지정 new를 작성한다면 위치지정 delete도 같이 준비하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item52.h)

## 9. 그 밖의 이야기들

53. [컴파일러 경고를 지나치지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item53.h)
54. [TR1을 포함한 표준 라이브러리 구성요소와 편안한 친구가 되자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item54.h)
55. [Boo子有親(부자유친)! 부스트를 늘 여러분 가까이에](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item55.h)