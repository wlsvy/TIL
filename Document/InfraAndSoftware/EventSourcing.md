# EventSourcing

#### Reference

- [blog: Just hack'em](https://justhackem.wordpress.com/2017/02/05/introducing-event-sourcing/)
- [microsoft : eventsourcing](https://docs.microsoft.com/en-us/azure/architecture/patterns/event-sourcing)

## 이벤트 소싱이란

- Instead of storing just the current state of the data in a domain, use an append-only store to record the full series of actions taken on that data. The store acts as the system of record and can be used to materialize the domain objects. This can simplify tasks in complex domains, by avoiding the need to synchronize the data model and the business domain, while improving performance, scalability, and responsiveness. It can also provide consistency for transactional data, and maintain full audit trails and history that can enable compensating actions.
- 데이터의 현 상태를 저장하는 대신 해당 데이터에 취해질 동작의 시퀀스를 기록하는 방법입니다.(append-only) 이 접근법은 데이터 모델을 동기화해야 하는 부담을 덜 수 있고 퍼포먼스와 확장성/응답성을 개선하는 데 유리합니다. 또한 Transactional 데이터의 일관성을 유지하거나, 데이터 변경 내역을 추적할 때도 유리합니다.

## 기존 CRUD 접근법의 한계점

- 곧바로 데이터를 조작하는 방법은 성능을 낮출 수 있다.
- 동시성 문제가 발생할 수 있는데, 다수의 유저가 동일한 명령을 동시에 요청했을 경우, 충돌이 발생할 수 있다.
- 데이터 변경 내역을 위한 특별한 로그 시스템이 없는 이상 데이터 히스토리를 알 수 없다.

## 이벤트 소싱 특징과 장점

- Event는 불변성을 가지고 저장될 수 있다.
- 이벤트는 곧바로 데이터를 조작하지는 않지만 잠시 저장되었다가 한꺼번에 적용되게 된다. 이는 간단하게 구현이 가능하고 관리도 용이하다.
- 이벤트 소싱은 동시성 문제를 방지할 수 있다.
- 이벤트를 처리하는 측과 이벤트를 생성하는 측을 디커플링 할 수 있다.

## 단점

- 조회작업에 적합하지 않은데 이벤트 저장소는 비즈니스의 다양한 데이터 조회 요구를 수용하기 어려움.

## 예를 들면

명령 목록

1. 주문을 생성한다.
2. 식별자가 9a37인 상품 3개를 주문에 추가한다.
3. 식별자가 c52a인 상품 1개를 주문에 추가한다.
4. 식별자가 c52a인 상품을 주문에서 삭제한다.
5. 식별자가 a974인 상품 10개를 주문에 추가한다.
6. 식별자가 9a37인 상품 수량을 5로 변경한다