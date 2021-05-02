# ValueTask

#### Reference
- [how-to-use-valuetask-in-csharp](https://www.infoworld.com/article/3565433/how-to-use-valuetask-in-csharp.html)
- [understanding-the-whys-whats-and-whens-of-valuetask](https://devblogs.microsoft.com/dotnet/understanding-the-whys-whats-and-whens-of-valuetask/)


<br>

ValueTask를 사용해야 한다면
- Task는 동작의 상태를 나타냅니다. 해당 동작이 완료되었는지(Success), 취소되었는지(Cancel), 진행중인지(Pending), 실패했는지(Fault)를 알 수 있습니다. 비동기 메서드는 Task 혹은 ValueTask를 반환할 수 있습니다.
- 여기서 Task는 참조 타입입니다. 비동기 메서드가 Task를 반환할 때면 이는 Task 객체가 힙에 할당된다는 것을 의미합니다. 그러므로 Task를 반환하는 비동기 메서드를 사용할 시 힙 할당이 발생한다는 사실을 인지하고 있어야 합니다.
- 만약 비동기 동작이 즉시/동기적으로 완료된다면 이런 힙 할당은 불필요한 비용이 될 수 있습니다.

<br>

여기서 ValueTask의 장점이 돋보입니다.
- ValueTask<T> 는 값 타입으로서 힙에 할당되지 않습니다.
- 구현이 쉽고 유연합니다. 단순히 비동기 메서드의 반환값을 Task<T> 가 아닌 ValueTask<T> 로 변경하면 됩니다.


<br>

ValueTask 사용 예시
```cs
// 아래 예시처럼 비동기 동작이 즉시 수행됨을 기대할 수 있는 경우에, ValueTask를 활용할 수 있습니다.

//아래의 경우 Task를 반환하며 힙 할당이 발생합니다.
public static Task<int> TASK_GetIntergerAsync()
{
    return Task.FromResult(1);
}

//위와 똑같은 동작을 수행하나 반환값이 ValueTask로 힙 할당이 발생하지 않습니다.
public static ValueTask<int> VALUETASK_GetIntergerAsync()
{
    return new ValueTask<int>(1);
}

```

```cs
// asnyc 메서드 혹은, ValueTask<T> 를 그대로 반환하는 메서드 예시입니다.
public static async ValueTask<T> GetData<T>()
{
    var result = default(T);
    await Task.Delay(100);
    return result;
}

public static ValueTask<T> GetDataAsync<T>()
{
    var result = default(T);
    return new ValueTask<T>(result);
}
```

<br>

ValueTask의 장점에도 불구하고, 주의해야 할 점은 분명히 있습니다.
- Task는 내부적으로 하나의 멤버 필드를 가지는 반면에, ValueTask는 두 개의 멤버 필드를 가집니다.
- 그리고 ValueTask를 사용하는 경우에, 비동기 동작을 처리하는 state machine 이 더 커질 수 있습니다. 멤버가 하나인 Task 타입이 아닌 멤버 필드가 두 개인 구조체 타입을 다뤄야 하기 때문입니다.

<br>

ValueTask를 다룰 때 권장되는 방법이란
- 어떤 동작이 장시간 비동기적으로 수행해야 한다면 Task를 사용하는 것을 권장합니다. 동작이 호출 즉시 종료되지 않는 그런 경우에 말이지요.
- 반면에 호출된 비동기 동작이 즉시 끝나는 경우에는 ValueTask 사용을 권장합니다. 이 경우 힙에 할당되지 않아 성능적 이점을 볼 수 있을 것입니다.
- WhenAll 메서드 등의 활용될 경우라면 Task를 활용하세요. ValueTask 를 이때 활용하게 된다면 ValueTask.AsTask()를 통해서 다시 Task객체를 생성하게 되는데, 이 때 힙 할당이 발생하게 되고 이럴 것이라면 애초에 Task를 활용하는 편이 오버헤드를 절약합니다.
