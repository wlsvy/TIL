# Effective C#

- 빌 와그너 저
- Effective C# 예제 코드 정리 페이지

## CHAPTER 1 C# 언어 요소
01. [지역변수를 선언할 때는 var 를 사용하는 것이 낫다](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item01.cs)
02. [const 보다는 readonly 가 좋다.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item02.cs)
03. [캐스트보다는 is, as 가 좋다.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item03.cs)
04. string.Format()을 보간 문자열로 대체하라                      
05. 문화권별로 다른 문자열을 생성하려면 FormattableString을 사용하라
06. [nameof() 연산자를 적극 활용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item06.cs)
07. [델리게이트를 이용하여 콜백을 표현하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item07.cs)
08. [이벤트 호출 시에는 null 조건 연산자를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item08.cs)
09. [박싱과 언박싱을 최소화하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item09.cs)
10. [베이스 클래스가 업그레이드 된 경우에만 new 한정자를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item10.cs)
 
## CHAPTER 2 .NET 리소스 관리
11. [.NET 리소스 관리에 대한 이해](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item11.cs)
12. [할당 구무보다 멤버 초기화 구문이 좋다.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item12.cs)
13. [정적 생성자 구문을 올바르게 초기화하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item13.cs)
14. [초기화 코드가 중복되는 것을 최소화하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item14.cs)
15. [불필요한 객체를 만들지 말라.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item15.cs)
16. [생성자 내에서는 절대로 가상 함수를 호출하지 말라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item16.cs)
17. [표준 dispose 패턴을 구현하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item17.cs)
 
## CHAPTER 3 제네릭 활용
18. [반드시 필요한 제약 조건만 설정하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item18.cs)
19. [런타임에 타입을 확인하여 최적의 알고리즘을 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item19.cs)
20. [IComparable<T> 와 IComparer<T>를 이용하여 객체의 선후 관계를 정의하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item20.cs)
21. [타입 매개변수가 IDisposable을 구현한 경우를 대비하여 제네릭 클래스를 작성하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item21.cs)
22. [공변성과 반공변성을 지원하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item22.cs)
23. [타입 매개변수에 대해 메서드 제약 조건을 설정하려면 델리게이트를 활용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item23.cs)
24. [베이스 클래스나 인터페이스에 대해서 제네릭을 특화하지 말라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item24.cs)
25. [타입 매개변수로 인스턴스 필드를 만들 필요가 없다면 제네릭 메서드를 정의하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item25.cs)
26. [제네릭 인터페이스와 논 제네릭 인터페이스를 함께 구현하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item26.cs)
27. [인터페이스는 간략히 정의하고 기능의 확장은 확장 메서드를 사용하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item27.cs)
28. [확장 메서드를 이용하여 구제화된 제네릭 타입을 개선하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item28.cs)
 
## CHAPTER 4 LINQ 활용
29. [컬렉션을 반환하기보다 이터레이터를 반환하는 것이 낫다.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item29.cs)
30. [루프보다 쿼리 구문이 낫다](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item30.cs)
31. [시퀀스에 사용할 수 있는 조합 가능한 API를 작성하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item31.cs)
32. [Action, Predicate, Function 과 순회 방식을 분리하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item32.cs)
33. [필요한 시점에 필요한 요소를 생성하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item33.cs)
34. [함수를 매개변수로 사용하여 결합도를 낮춰라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item34.cs)
35. [확장 메서드는 절대 오버로드하지 마라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item35.cs)
36. [쿼리 표현식과 메서드 호출 구문이 어떻게 대응되는지 이해하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item36.cs)
37. [쿼리를 사용할 때는 즉시 평가보다 지연 평가가 낫다](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item37.cs)
38. [메서드보다 람다 표현식이 낫다](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item38.cs)
39. [function 과 action 내에서는 예외가 발생하지 않도록 해라.](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item39.cs)
40. [지연 수행과 즉시 수행을 구분하라](https://github.com/wlsvy/TIL/blob/master/Effective%20CSharp/EffectiveCSharp/Item40.cs)
41: 값비싼 리소스를 캡처하지 말라
42: IEnumerable[T] 데이터 소스와 IQueryable[T] 데이터 소스를 구분하라
43: 쿼리 결과의 의미를 명확히 강제하고, Single()과 First()를 사용하라
44: 바인딩된 변수는 수정하지 말라
 
## CHAPTER 5 예외 처리
45: 메서드가 실패했음을 알리기 위해서 예외를 이용하라
46: 리소스 정리를 위해 using과 try/finally를 활용하라
47: 사용자 지정 예외 클래스를 완벽하게 작성하라
48: 강력한 예외 보증을 준수하는 것이 좋다
49: catch 후 예외를 다시 발생시키는 것보다 예외 필터가 낫다
50: 예외 필터의 다른 활용 예를 살펴보라
