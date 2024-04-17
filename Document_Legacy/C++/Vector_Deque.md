# Vector, Deque

![](https://i.stack.imgur.com/QullW.png)

- deque(double-ended queue) 는 가변크기의 배열을 가지는 벡터와는 다르게, 고정 크기의 배열을 여러개 이어붙여 만든 컨테이너입니다. 그러니 모든 원소가 메모리상에 연속적으로 배치되는 것이 아닙니다.
  - deque의 특성상 벡터와는 다르게 컨테이너 앞부분(front)에 원소를 삽입하는 동작이 효율적입니다.
  - 컨테이너 앞부분과 뒷부분에 원소를 할당할 때, 메모리 재할당이 일어나지 않습니다. 컨테이너가 가득 또다른 고정 크기 배열을 만들어 기존의 배열 앞 혹은 뒤에 연결하면 되니까요.
    - 즉 앞/뒤 부분 삽입 삭제 과정에서 기존에 있던 반복자가 무효화되는 일도 없습니다.
  - 컨테이너 중간 부분에 원소를 삽입/삭제할 때는 벡터와 마찬가지로 원소의 위치를 다시 옮겨야 하기 때문에 동작 비용이 비쌉니다.
  
- 겉보기에는 벡터가 가지는 단점 중 컨테이너 앞쪽 원소를 삭제하는 동작이 비싼 것, 메모리 재할당 등은 deque를 사용하면 보완되므로 vector 보다 deque를 활용하는 것이 유리하게 보일 수 있습니다.
  - 하지만 vector의 원소는 메모리상 연속적으로 배치되어 있고 deque는 불연속적으로 배치될 수 있다는 점에 주목합시다. 수 많은 원소를 다룰 때, sort 와 같은 작업을 수행할 때는 vector가 더 빠릅니다. 아래의 vector와 deque의 성능 차이를 비교한 웹 페이지에서 확인할 수 있습니다.


#### Reference
- [cppreference : deque](https://en.cppreference.com/w/cpp/container/deque)
- [C++ benchmark – std::vector VS std::list VS std::deque](https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html)
- [Geeks for Geeks : Deque vs Vector](https://www.geeksforgeeks.org/deque-vs-vector-in-c-stl/)
