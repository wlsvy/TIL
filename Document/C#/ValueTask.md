# ValueTask

#### Reference
- [how-to-use-valuetask-in-csharp](https://www.infoworld.com/article/3565433/how-to-use-valuetask-in-csharp.html)
- [understanding-the-whys-whats-and-whens-of-valuetask](https://devblogs.microsoft.com/dotnet/understanding-the-whys-whats-and-whens-of-valuetask/)


<br>

ValueTask를 사용해야 한다면
- Task는 동작의 상태를 나타냅니다. 해당 동작이 완료되었는지(Success), 취소되었는지(Cancel), 진행중인지(Pending), 실패했는지(Fault)를 알 수 있습니다. 비동기 메서드는 Task 혹은 ValueTask를 반환할 수 있습니다.
