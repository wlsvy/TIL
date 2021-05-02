# ValueTask

#### Reference
- [how-to-use-valuetask-in-csharp](https://www.infoworld.com/article/3565433/how-to-use-valuetask-in-csharp.html)
- [understanding-the-whys-whats-and-whens-of-valuetask](https://devblogs.microsoft.com/dotnet/understanding-the-whys-whats-and-whens-of-valuetask/)
- [task-whenall-for-valuetask](https://stackoverflow.com/questions/45689327/task-whenall-for-valuetask)

<br>


Task는 동작의 상태를 나타냅니다. 해당 동작이 완료되었는지(Success), 취소되었는지(Cancel), 진행중인지(Pending), 실패했는지(Fault)를 알 수 있습니다. 동작이 
- 비동기 메서드는 Task 혹은 ValueTask를 반환할 수 있습니다.
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

표면적 관점에서 ValueTask는 Task에 비해 제약사항을 가집니다. 하지만 괜찮습니다. 보통 비동기 메서드는 대게 await를 수행해서 결과값을 확인하니까요.
- 그렇지만 ValueTask는 재사용 가능한 객체를 감싸고 있을 수 있습니다. 이 경우 Task와 비교할 때 중요한 제약이 생기게 되는데, 시스템 로직 어디선가 ValueTask를 단순히 await 하는 것으로 끝내지 않고, 다른 방식으로 활용한다면 문제가 생길 수 있다는 것입니다.

ValueTask 사용 시 아래의 동작은 피해야 합니다.
- ValueTask 객체애 대해 여러 번 await 수행 : underlying 값은 이미 사용되었을 수 있습니다. Task의 경우는 반대로 완료 상태에서 완료되지 않음 상태로 변화하는 일이 없기 때문에 여러번 await를 해도 괜찮습니다. 결과는 항상 동일합니다.
- ValueTask 객체에 대해 병렬적으로 await 수행 : underlying 값은 단 한번 하나의 호출자에 의해 사용될 것을 기대합니다. 병렬적으로 await를 수행한다면 race condition을 야기할 수 있습니다.
- 수행 완료되지 않은 ValueTask 객체에 대해 GetAwaiter, GetReult 호출 : IValueTaskSource 구현은 동작 수행을 마칠 때까지 시스템을 블록(blocking) 시키는 동작을 지원하지 않습니다. 이런 시도는 race condition을 유발할 수 있습니다. Task의 경우에는 대조적으로 사용 가능합니다.

피치 못할 이유로 위의 동작을 수행해야 한다면 AsTask()를 통해 Task객체를 획득한 뒤 Task 객체해 수행하는 것을 권장합니다.

```cs

// Given this ValueTask<int>-returning method…
public ValueTask<int> SomeValueTaskReturningMethodAsync();
…
// GOOD
int result = await SomeValueTaskReturningMethodAsync();

// GOOD
int result = await SomeValueTaskReturningMethodAsync().ConfigureAwait(false);

// GOOD
Task<int> t = SomeValueTaskReturningMethodAsync().AsTask();

// WARNING
ValueTask<int> vt = SomeValueTaskReturningMethodAsync();
... // storing the instance into a local makes it much more likely it'll be misused,
    // but it could still be ok

// BAD: awaits multiple times
ValueTask<int> vt = SomeValueTaskReturningMethodAsync();
int result = await vt;
int result2 = await vt;

// BAD: awaits concurrently (and, by definition then, multiple times)
ValueTask<int> vt = SomeValueTaskReturningMethodAsync();
Task.Run(async () => await vt);
Task.Run(async () => await vt);

// BAD: uses GetAwaiter().GetResult() when it's not known to be done
ValueTask<int> vt = SomeValueTaskReturningMethodAsync();
int result = vt.GetAwaiter().GetResult();
```


<br>

ValueTask에서는 작업의 수행 상태를 반환하는 프로퍼티가 있습니다.(IsCompletedSuccessfully) 로직을 작성할 때 ValueTask의 수행 상태에 따라 동작을 달리해야 한다면 아래와 같은 패턴을 제안합니다.
```cs
int bytesRead;
{
    ValueTask<int> readTask = _connection.ReadAsync(buffer);
    if (readTask.IsCompletedSuccessfully)
    {
        bytesRead = readTask.Result;
    }
    else
    {
        using (_connection.RegisterCancellation())
        {
            bytesRead = await readTask;
        }
    }
}
```

<br>

ValueTask를 다룰 때 권장되는 방법이란
- 어떤 동작이 장시간 비동기적으로 수행해야 한다면 Task를 사용하는 것을 권장합니다. 동작이 호출 즉시 종료되지 않는 그런 경우에 말이지요.
- 반면에 호출된 비동기 동작이 즉시 끝나는 경우에는 ValueTask 사용을 권장합니다. 이 경우 힙에 할당되지 않아 성능적 이점을 볼 수 있을 것입니다.
- WhenAll 메서드 등의 활용될 경우라면 Task를 활용하세요. ValueTask 를 이때 활용하게 된다면 ValueTask.AsTask()를 통해서 다시 Task객체를 생성하게 되는데, 이 때 힙 할당이 발생하게 되고 이럴 것이라면 애초에 Task를 활용하는 편이 오버헤드를 절약합니다.

<br>

비동기 태스크를 활용할 때 첫 번째로는 Task 를 고려해야 합니다. 반드시 ValueTask를 사용을 고려해야 하는 것은 아닙니다.
- Task의 경우 ValueTask에 비해 실수 없이 올바르게 사용하기 쉽습니다. 성능상의 단점이 있음에도 Task의  이런 장점은 간과할 수 없습니다.
- Task가 ValueTask에 비해 포함하는 멤버 수가 작다는 점을 명심하세요. async method state machine 에서 ValueTask를 await 하는 동작보다, Task를 awiat 하는 동작이 약간 더 빠릅니다.


However, ValueTask / ValueTask<TResult> are great choices when 
- a) you expect consumers of your API to only await them directly, 
- b) allocation-related overhead is important to avoid for your API, and 
- c) either you expect synchronous completion to be a very common case, or you’re able to effectively pool objects for use with asynchronous completion. 
When adding abstract, virtual, or interface methods, you also need to consider whether these situations will exist for overrides/implementations of that method.
