## DisposeAsync

#### Reference
- [msdn : implementing-disposeasync](https://docs.microsoft.com/ko-kr/dotnet/standard/garbage-collection/implementing-disposeasync)
- [msdn : IAsyncDisposable](https://docs.microsoft.com/ko-kr/dotnet/api/system.iasyncdisposable?view=net-5.0)
- [ConfigureAwait FAQ](https://devblogs.microsoft.com/dotnet/configureawait-faq/)

<br>
<br>

### Dispose Async

- System.IAsyncDisposable 인터페이스는 C# 8.0의 일부로 도입되었습니다. IAsyncDisposable.DisposeAsync() 메서드는 Dispose 메서드를 구현할 때와 마찬가지로 리소스 정리를 수행하는 경우에 구현합니다. 그러나 중요한 차이점 하나는 이 구현에서는 비동기 정리 작업이 가능하다는 것입니다. DisposeAsync()는 비동기 삭제 작업을 나타내는 ValueTask를 반환합니다.

```cs
public interface IAsyncDisposable
{
    ValueTask DisposeAsync();
}
```

- DisposeAsync 는 비동기적으로 (관리되는, 관리되지 않는)자원 정리 작업을 수행하거나, 종료자가 (있다면) 호출될 필요가 없음을 지정합니다.
  - Dispose 패턴에서 파생 클래스에 대해 자원 정리 동작을 재정의할 여지를 제공하기 위해 Dispose(bool) virtual 메서드를 작성하는 것처럼, DisposeAsync 의 경우에는 이를 위해 DisposeAsyncCore virtual 메서드를 작성합니다.

```cs
protected virtual ValueTask DisposeAsyncCore()
{
}
```

### DisposeAsync 패턴
- Dispose 메서드가 using 문에서 암시적으로 호출된다면 DisposeAsync는 await using 문에서 암시적으로 호출됩니다.
- One primary difference in the async dispose pattern compared to the dispose pattern, is that the call from DisposeAsync() to the Dispose(bool) overload method is given false as an argument. When implementing the IDisposable.Dispose() method, however, true is passed instead. This helps ensure functional equivalence with the synchronous dispose pattern, and further ensures that finalizer code paths still get invoked. In other words, the DisposeAsyncCore() method will dispose of managed resources asynchronously, so you don't want to dispose of them synchronously as well. Therefore, call Dispose(false) instead of Dispose(true).
  - DisposeAsync 에서는 dispose(false)를 호출합니다. 이는 관리되지 않는 자원을 정리하기 위함입니다. DisposeAsync에서 dispose(true)를 호출하는 것이 안되는 것은 아닙니다. 하지만 이는 관리되지 않는 작업을 동기적으로 정리하는 것과 동일한 맥락이기에 DisposeAsync를 사용하는 의미를 잃게 될 수도 있습니다. 따라서 DisposeAsync 내에서는 관리되지 않는 자원 정리를 위해 Dispose(false)를 호출합니다.
  

 ```cs
 public async ValueTask DisposeAsync()
{
    // Perform async cleanup.
    await DisposeAsyncCore();

    // Dispose of unmanaged resources.
    Dispose(false);
    // Suppress finalization.
    GC.SuppressFinalize(this);
}
```

```cs
using System;
using System.IO;
using System.Text.Json;
using System.Threading.Tasks;

public class ExampleAsyncDisposable : IAsyncDisposable, IDisposable
{
    private Utf8JsonWriter _jsonWriter = new Utf8JsonWriter(new MemoryStream());

    public void Dispose()
    {
        Dispose(disposing: true);
        GC.SuppressFinalize(this);
    }

    public async ValueTask DisposeAsync()
    {
        await DisposeAsyncCore();

        Dispose(disposing: false);
        GC.SuppressFinalize(this);
    }

    protected virtual void Dispose(bool disposing)
    {
        if (disposing)
        {
            _jsonWriter?.Dispose();
        }

        _jsonWriter = null;
    }

    protected virtual async ValueTask DisposeAsyncCore()
    {
        if (_jsonWriter is not null)
        {
            await _jsonWriter.DisposeAsync().ConfigureAwait(false);
        }

        _jsonWriter = null;
    }
}
```

<br>

- 일반적으로 IAsyncDisposable 인터페이스를 구현한다면 IDisposable 인터페이스를 같이 구현해야 할 것입니다.
