# Coroutine
- 서브루틴(Subroutine, 함수/메서드 등)의 변형된 개념으로 비선점형 멀티태스킹에 쓰이는 프로그램의 요소입니다. 
- 특정 실행 시점에서 중단되거나(suspend) 중단된 지점부터 다시 시작되는(resume) 기능을 제공합니다.
- 실행 시점에서 중단될 때 해당 지점까지의 상태 정보들은 저장되었다가 동작을 재개할 때 다시 사용되어집니다.
- 코루틴은 객체로 존재할 수 있으며, 그 수가 하나가 아닌 여러개일 수도 있습니다.
- 코루틴의 기본적인 특징은 양보(yielding) 입니다. 하나의 루틴이 수행되는 중 중단 지점(ex : yield return 문)을 만나면 자신의 상태정보를 저장한 뒤 또다른 루틴이 수행될 수 있도록 권한을 양보(yield)합니다.

![](https://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/images/foo_bar_seq.png)

### 서브루틴과의 차이점
- 서브루틴에는 yield 기능이 없는 것이 큰 차이점이라고 볼 수 있습니다. 다시 말해서, 서브루틴에서는 중단 지점을 임의로 지정할 수 없습니다.

### 스레드와의 차이점
- 코루틴이 비선점적(non-preemptively, cooperatively)으로 동작한다면 스레드는 선점적(preemptively)으로 동작합니다. 이를 바꿔말하면
  - 코루틴의 경우 동시성(Concurrency, 어떤 절차가 수행될때 정해진 차례 없이 임의의 순서대로 수행되는 특징)은 가지고 있지만, 병렬성(Parallelism, 다수의 처리 절차가 동시에 수행되는 특징)은 없는 것입니다.

### Stackful Coroutine, Stackless Coroutine
- stackless 코루틴에서는 스택의 가장 아래부분의 해당하는 루틴만이 yield 되는 것이 가능합니다. 그러니 부모에 해당하는 top-level 루틴이 아니면 보통 중단될 수 없습니다.
- stackful 코루틴에서는 코루틴 객체 자체가 스택을 지니고 있습니다. 수행 도중 어떤 순간이라도 루틴을 멈추고 양보하는 것이 가능합니다.

#### Reference
- [Wikipedia : Coroutine](https://en.wikipedia.org/wiki/Coroutine#Implementations_for_C++)
- [stackoverflow : how-do-stackless-coroutines-differ-from-stackful-coroutines](https://stackoverflow.com/questions/28977302/how-do-stackless-coroutines-differ-from-stackful-coroutines)
- [boost : coroutine](https://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/intro.html#coroutine.intro.stackfulness)
