# c# 소켓 관련 api 정리

#### 참고
- [Microsoft : Socket](https://docs.microsoft.com/ko-kr/dotnet/api/system.net.sockets.socket?view=net-5.0)
- [Microsoft : SocketAsyncEventArgs](https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.socketasynceventargs?view=net-5.0)

- 소켓Socket : 네트워크 상의 두 개의 프로그램이 연결되어 있다면 해당 연결점의 양 끝 지점(endpoint)는 소켓이 됩니다. 각 소켓은 특정한 port 번호가 지정되어 있습니다.
- SocketAsyncEventArgs : System.Net.Sockets.Socket 클래스를 좀더 개선한 버전을 볼 수 있으며, 비동기 고성능 소켓 애플리케이션에 사용할 수 있는 화용 패턴을 제공합니다.
  - SocketAsyncEventArgs는 네트워크 고성능(high performance)을 요구하는 서버를 구현하는 것에 특화되어 있으며 해당 클래스를 활용한다면 특정 데이터 영역에 대해서 강화된 비동기 동작을 구현할 수 있습니다.
  - SocketAsyncEventArgs의 주요 특징 중 하나는 비동기 소켓 I/O가 발생할 때 반복적인 오브젝트 할당과 동기화가 발생하는 것을 피한다는 것입니다. socket의 begin/end 디자인 패턴은 소켓의 비동기 작동이 발생할 때마다 System.IAsyncResult 객체를 할당하게 합니다.
