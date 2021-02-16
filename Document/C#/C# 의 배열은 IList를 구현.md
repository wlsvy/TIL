> C#의 배열은 IList 인터페이스를 구현하고 있으며, 만약 시작 인덱스가 0인 1차원 배열인 경우(SZ배열) `IList<T>` 인터페이스 역시 구현합니다.

```cs
//컴파일 오류 발생 X
int[] integers = { 1, 2, 3 };
IList<int> list = integers;
IList objList = integers;

list.Add(4); //런타임 오류
objList.Add(5); //런타임 오류
```

### 참고
- [stackoverflow : why-array-implements-ilist](https://stackoverflow.com/questions/5968708/why-array-implements-ilist)

### IList에 대한 오해 한가지
- IList를 구현하는 대표적인 클래스는 List 이며 IList인터페이스가 제공하는 대표적인 동작은 Add 메서드입니다.
`즉 IList를 구현 -> 동적으로 크기가 변하는 컨테이너` 를 연상하기 쉽습니다.

### IList는 변하지 않는, 고정된 컨테이너를 의미하기도 합니다.
- IList가 제공하는 동작을 더 살펴보면, `IsFixedSize` 프로퍼티를 포함합니다. 즉 IList를 구현한 클래스는 고정 크기의 컨테이너를 의미할 수도 있는 것입니다. 더 자세히 살펴보면 `IsReadOnly` 프로퍼티도 찾을 수 있습니다.
  - 따라서 IList를 구현하는 클래스는 다음과 같이 카테고리를 분류할 수 있습니다.
    - ReadOnly
    - Fixed Size
    - Variable Size

<br>

배열의 경우 위의 카테고리에서 고정 크기 컨테이너에 속하게 될 것입니다.

### IList의 다른 기능을 살펴보면
배열의 원소에 접근하는 인덱서, 특정 배열이 어느 위치에 있는지 배열의 인덱스를 반환하는 `IndexOf` 메서드를 포함합니다. 앞의 기능들은 배열이 충분히 제공할 만한 기능들입니다. 따라서 C# Array 타입은 IList를 구현하되 배열의 크기를 조작하는 메서드(Add, Remove 등)들은 내부적으로 숨겨놓고 있습니다.
