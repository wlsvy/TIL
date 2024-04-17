## string in C#

- .Net 프레임워크에서 string은 immutable 타입. 즉 객체가 초기화 되고 나면 그 이후로 절대 값을 변경할 수 없습니다.
  - string은 final class 이기도 합니다. 클래스 상속으로 인해 string의 immutable 특성을 해치는 것을 방지합니다.
- StringBuilder는 mutable 특성을 가집니다. c++의 std::string 과 동작이 비슷합니다.(메모리 재할당 등등)

- C#에서는 class 객체가 힙에 할당되어 레퍼런스를 통해 참조하는 점. c++ 에서는 string이 값 형식으로(그래도 내부 데이터는 힙에 할당되긴 합니다. string 객체를 복사할 때는 copy-on-write 혹은 깊은 복사가 발생하고요) 활용되는 점에 큰 차이가 있습니다. C#의 string이 immutable 특성을 가지게 된 것은 이런 맥락에서 나타납니다.
  - SortedDictionary 컨테이너에서 키값으로 string을 활용한다고 가정합시다. 내부적으로 키값은 레퍼런스로 공유되기 때문에 만약에 키에 해당하는 객체가 외부에서 수정되게 된다면, SortedDictionary 에서 수행되는 비교 연산에서 문제를 유발할 가능성이 생깁니다. c++의 std::map 의 경우라면 string을 복사해버리면 그만이지만, 클래스 객체는 레퍼런스로 참조하는 c#의 특징 차이에 의해 나타나는 현상입니다.
  - immutable 특성은 곧 스레드 안정성을 포함합니다. 즉 C#의 string은 멀티스레딩 환경에서 아무 문제가 없습니다.
  - immutable 특성은 컴파일러에게 상당한 최적화 여지를 제공합니다.

#### Reference 
- [Microsoft : String](https://docs.microsoft.com/en-us/dotnet/api/system.string?view=netcore-3.1)
- [Microsoft : best-practices-strings](https://docs.microsoft.com/en-us/dotnet/standard/base-types/best-practices-strings)
- [Microsoft : StringBuilder](https://docs.microsoft.com/en-us/dotnet/api/system.text.stringbuilder?view=netcore-3.1)
- [StackOverflow : Why .Net String is immutable](https://stackoverflow.com/questions/2365272/why-net-string-is-immutable)
