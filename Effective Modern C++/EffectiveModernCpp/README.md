# Effective Modern C++

## Chapter 1   타입 추론

1. [템플릿 타입 추론 규칙을 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item01.h)
2. [auto의 타입 추론 규칙을 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item02.h)
3. [decltype의 작동 방식을 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item03.h)
4. [추론된 타입을 파악하는 방법을 알아두라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item04.h)

## Chapter 2   auto

5. [명시적 타입 선언보다는 auto를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item05.h)
6. [auto가 원치 않은 타입으로 추론될 때에는 명시적 타입의 초기치를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item06.h)


## Chapter 3   현대적 C++에 적응히기

7. [객체 생성시 괄호(())와 중괄호({})를 구분하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item07.h)
8. [0과 NULL보다 nullptr를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item08.h)
9. [typedef보다 별칭 선언을 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item09.h)
10. [범위 없는 enum보다 범위 있는 enum을 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item10.h)
11. [정의되지 않은 비공개 함수보다 삭제된 함수를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item11.h)
12. [재정의 함수들을 override로 선언하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item12.h)
13. [iterator보다 const_iterator를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item13.h)
14. [예외를 방출하지 않을 함수는 noexcept로 선언하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item14.h)
15. [가능하면 항상 constexpr을 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item15.h)
16. [const 멤버 함수를 스레드에 안전하게 작성하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item16.h)
17. [특수 멤버 함수들의 자동 작성 조건을 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item17.h)


## Chapter 4   스마트 포인터

18. [소유권 독점 자원의 관리에는 std::unique_ptr를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item18.h)
19. [소유권 공유 자원의 관리에는 std::shared_ptr를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item19.h)
20. [std::shared_ptr처럼 작동하되 대상을 잃을 수도 있는 포인터가 필요하면 std::weak_ptr를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item20.h)
21. [new를 직접 사용하는 것보다 std::make_unique와 std::make_shared를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item21.h)
22. [Pimpl 관용구를 사용할 때에는 특수 멤버 함수들을 구현 파일에서 정의하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item22.h)


## Chapter 5   우측값 참조, 이동 의미론, 완벽 전달

23. [std::move와 std::forward를 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item23.h)
24. [보편 참조(universal reference)와 우측값 참조를 구별하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item24.h)
25. [우측값 참조에는 std::move를, 보편 참조(universal reference)에는 std::forward를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item25.h)
26. [보편 참조(universal reference)에 대한 오버로딩을 피하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item26.h)
27. [보편 참조(universal reference)에 대한 오버로딩 대신 사용할 수 있는 기법들을 알아 두라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item27.h)
28. [참조 축약(collapse)을 숙지하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item28.h)
29. [이동 연산이 존재하지 않고, 저렴하지 않고, 적용되지 않는다고 가정하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item29.h)
30. [완벽 전달이 실패하는 경우들을 잘 알아두라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item30.h)


## Chapter 6   람다 표현식

31.	[기본 갈무리 모드를 피하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item31.h)
32.	[객체를 클로저 안으로 이동하려면 초기화 갈무리를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item32.h)
33.	[std::forward를 통해서 전달할 auto&& 매개변수에는 decltype을 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item33.h)
34. [std::bind보다 람다를 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item34.h)

## Chapter 7   동시성 API

35.	[스레드 기반 프로그래밍보다 task 기반 프로그래밍을 선호하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item35.h)
36.	[비동기성이 필수일 때에는 std::launch::async를 지정하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item36.h)
37.	std::thread들을 모든 경로에서 join 불가능하게 만들어라
38.	스레드 핸들 소멸자들의 다양한 행동 방식을 주의하라
39.	일회성(one-shot) 사건 통신에는 void future 객체를 고려하라
40. 동시성에는 std::atomic을 사용하고, volatile은 특별한 메모리에 사용하라

## Chapter 8   다듬기

41.	[이동이 저렴하고 항상 복사되는 복사 가능 매개변수에 대해서는 값 전달을 고려하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item41.h)
42.	[삽입 대신 생성 삽입을 고려하라](https://github.com/wlsvy/TIL/blob/master/Effective%20Modern%20C%2B%2B/EffectiveModernCpp/Item42.h)
