# Effective STL

예제 코드 & 개념 정리

##### Reference

- Scott Meyers, "Effective STL"
- [Effective STL 정리](http://ajwmain.iptime.org/programming/book_summary/%5B02%5Deffective_stl/effective_stl.html#I12)

## Chapter 1   효과적인 컨테이너(Container) 요리법

1. [적재적소에 알맞은 컨테이너를 사용하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item01.h)
2. ["컨테이너에 독립적인(container-independent) 코드"라는 환상을 조심하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item02.h)
3. [복사(Copy)는 컨테이너 안의 객체에 맞게 비용은 최소화하며, 동작은 정확하게 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item03.h)
4. [size()의 결과를 0과 비교할 생각이라면 차라리 empty를 호출하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item04.h)
5. [단일 요소를 단위로 동작하는 멤버 함수보다 요소의 범위를 단위로 동작하는 멤버 함수가 더 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item05.h)
6. [C++ 컴파일러의 어이없는 분석 결과를 조심하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item06.h)
7. [new로 생성한 포인터의 컨테이너를 사용할 때에는 컨테이너가 소멸되기 전에 포인터를 delete하는 일을 잊지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item07.h)
8. [auto_ptr의 컨테이너는 절대로 만들지 말자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item08.h)
9. [데이터를 삭제할 때에도 조심스럽게 선택할 것이 많다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item09.h)
10. [할당자(allocator)의 일반적인 사항과 제약 사항에 대해 잘 알아두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item10.h)
11. [커스텀 할당자를 제대로 사용하는 방법을 이해하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item11.h)
12. [STL 컨테이너가 쓰레드 안전성에 대한 기대는 현실에 맞추어 가지자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item12.h)

## Chapter 2   vector와 string

13. [동적으로 할당한 배열보다는 vector와 string이 낫다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item13.h)
14. [reserve는 필요 없이 메모리가 재할당되는 것을 막아 준다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item14.h)
15. [잊지 말자! string은 여러 가지 방식으로 구현되어 있다는 사실을](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item15.h)
16. 기존의 C API에 vector와 string을 넘기는 방법을 알아두자
17. [쓸데없이 남은 용량은 "바꿔치기(swap) 묘수"를 써서 없애 버리자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item17.h)
18. [vector<bool> 보기를 돌같이 하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item18.h)

## Chapter 3   STL 연관 컨테이너(Associative Containers)

19. [상등 관계(equality)와 동등 관계(equivalence)의 차이를 파악하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item19.h)
20. [포인터를 저장하는 연관 컨테이너에 대해서는 적합한 비교(비교 함수자) 타입을 정해주자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item20.h)
21. [연관 컨테이너용 비교 함수는 같은 값에 대해 false를 반환해야 한다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item21.h)
22. [set와 multiset에 저장된 데이터 요소에 대해 키(key)를 바꾸는 일은 피하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item22.h)
23. [연관 컨테이너 대신에 정렬된 vector를 쓰는 것이 좋을 때가 있다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item23.h)
24. [map::operator[]나 map::insert는 효율 문제에 주의하여 선택하자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item24.h)
25. [현재는 표준이 아니지만, 해쉬 컨테이너에 대해 충분히 대비해 두자](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item25.h)

## Chapter 4   반복자(Iterators)

26. [const_iterator나 reverse_iterator, const_reverse_iterator도 좋지만 역시 쓸만한 것은 iterator이다](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item26.md)



<!--
(https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/Item26.h)





const_iterator나 reverse_iterator, const_reverse_iterator도 좋지만 역시 쓸만한 것은 iterator이다 / 182
const_iterator를 iterator로 바꾸는 데에는 distance와 advance를 사용하자 / 186
reverse_iterator에 대응되는 기점 반복자(base_iterator)를 사용하는 방법을 정확하게 이해하자 / 191
★ 문자 단위의 입력에는 istreambuf_iterator의 사용도 적절하다 / 195

## Chapter 5   알고리즘(Algorithms)

알고리즘의 데이터 기록 범위(destination range)는 충분히 크게 잡자 / 200
★ 정렬시의 선택 사항들을 제대로 파악해 놓자 / 206
요소를 정말로 제거하고자 한다면 remove 류의 알고리즘에는 꼭 erase를 붙여 사용하자 / 213
remove와 비슷한 알고리즘을 포인터의 컨테이너에 적용할 때에는 각별히 조심하자 / 219
정렬된 범위에 대해 동작하는 알고리즘이 어떤 것들인지 파악해 두자 / 224
대소문자를 구분하지 않는 문자열 비교는 mismatch 아니면 lexicographical_compare를 써서 간단히 구현할 수 있다 / 229
copy_if를 적절히 구현해 사용하자 / 234
범위 내의 데이터 값을 요약하거나 더하는 데에는 accumulate나 for_each를 사용하자 / 237

## Chapter 6   함수자, 함수 객체, 함수, 기타 등등

함수자 클래스는 값으로 전달되도록(pass-by-value) 설계하자 / 246
술어 구문은 순수 함수로 만들자 / 250
함수자 클래스는 어댑터 적용이 가능하게(adaptable) 만들자 / 255
ptr_fun, mem_fun, mem_fun_ref의 존재에는 분명한 이유가 있다 / 260
less<T>는 operator<의 의미임을 꼭 알아두자 / 266

## Chapter 7   STL 프로그래밍을 더 재미있게 해주는 팁 모음

어설프게 손으로 작성한 루프보다는 알고리즘이 더 낫다 / 272
★ 같은 이름을 가진 것이 있다면 일반 알고리즘 함수보다 멤버 함수가 더 낫다 / 282
count, find, binary_search, lower_bound, upper_bound, 그리고 equal_range를 제대로 파악해 두자 / 286
★ 알고리즘의 매개 변수로는 함수 대신 함수 객체가 괜찮다 / 297
쓰기 전용(write-only) 코드는 만들지 말자 / 302
용도에 맞는 헤더를 항상 #include하자 / 306
STL에 관련된 컴파일러 진단 메시지를 해석하는 능력을 가지자 / 308
STL 관련 웹 사이트와 친구하자 / 318
-->
