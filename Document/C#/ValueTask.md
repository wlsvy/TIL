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
