# More Effective C#

- 빌 와그너 지음
- 예제 코드 정리 페이지

## Chapter 1 데이터 타입
01. [접근 가능한 데이터 멤버 대신 속성을 사용하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item01.cs)
02. [변경 가능한 데이터에는 암묵적 속성을 사용하는 것이 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item02.cs)
03. [값 타입은 변경 불가능한 것이 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item03.cs)
04. [값 타입과 참조 타입을 구분하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item04.cs)
05. [값 타입에서는 0이 유효한 상태가 되도록 설계하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item05.cs)
06. [속성을 데이터처럼 동작하게 만들어라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item06.cs)
07. [튜플을 사용해서 타입의 사용 범위를 제한하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item07.cs)
08. [익명 타입은 함수를 벗어나지 않게 사용하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item08.cs)
09. [다양한 동일성 개념들 사이의 상관관계를 이해하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item09.cs)
10. [GetHashCode()의 위험성을 이해하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item10.cs)

## Chapter 2 API 디자인
11. [API에는 변환 연산자를 작성하지 말라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item11.cs)
12. [선택적 매개변수를 사용하여 메서드 오버로드를 최소화하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item12.cs)
13. 타입의 가시성을 제한하라
14. [상속보다는 인터페이스를 정의하고 구현하는 것이 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item14.cs)
15. [인터페이스 메서드와 가상 메서드의 차이를 이해하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item15.cs)
16. [상태 전달을 위한 이벤트 패턴을 구현하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item16.cs)
17. 내부 객체를 참조로 반환해서는 안된다
18. 이벤트 핸들러보다는 오버라이딩을 사용하라
19. 베이스 클래스에 정의된 메서드를 오버로드해서는 안 된다
20. [이벤트 런타임 시 객체 간의 결합도를 증가시킨다는 것을 이해하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item20.cs)
21. 이벤트는 가상으로 선언하지 말라.
22. [명확하고 간결하며 완결된 메서드 그룹을 생성하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item22.cs)
23. [생성자, 변경자, 이벤트 핸들러를 위해 partial 클래스와 메서드를 제공하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item23.cs)
24. [설계 선택지를 제한하는 ICloneable은 사용을 피하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item24.cs)
25. [배열 매개변수에는 params 배열만 사용해야 한다](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item25.cs)
26. [지역 함수를 사용해서 반복자와 비동기 메서드의 오류를 즉시 보고하라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item26.cs)

## Chapter 3 태스크 기반 비동기 프로그래밍
27. 비동기 작업에는 비동기 메서드를 사용하라
28. [async void 메서드는 절대 작성하지 말라](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item28.cs)
29. [동기, 비동기 메서드를 함께 사용해서는 안된다](https://github.com/wlsvy/TIL/blob/master/Document/C%23/MoreEffectiveCSharp/MoreEffectiveCSharp/Item29.cs)

