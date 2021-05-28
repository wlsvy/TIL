# Redis

- Redis는 윈도우 환경을 지원하지 않는다. 윈도우에서는 MS 가 별도로 지원하는 서버를 이용해야 한다.
- [c# Redis](https://github.com/StackExchange/StackExchange.Redis)

#### Reference
- [Redis Document](https://redis.io/documentation)
- [Redis Data Type Introduction](https://redis.io/topics/data-types-intro)
- [Redis Master and Replica](https://ssup2.github.io/theory_analysis/Redis_Master_Slave_Cluster/)

## Data Structure In Redis

### string
- [strings in redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-1-strings-in-redis/)
  - string 키값, string 밸류 쌍으로 이루어집니다.

<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-01.svg" width="60%" height="60%">

- [list in redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-2-lists-in-redis/)
  - LPUSH/RPUSH 로 자료구조 양 옆에서 데이터 삽입 가능(마찬가지로 제거도 가능)
  - 다수의 문자열이 Linked List 구조로 연결
  - 중복된 값 포함 가능
  - LISTs in Redis store an ordered sequence of strings,

<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-02.svg" width="60%" height="60%">

- [Sets in Redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-3-sets-in-redis/)
  - 내부적으로 해쉬 테이블 사용
  - 중복된 값을 포함할 수 없습니다.
   
<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-03.svg" width="60%" height="60%">

- [Hashes in Redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-4-hashes-in-redis/)
  - SubKey 값은 컨테이너 내에 유일하게 존재합니다.(중복 불가)
  - 물론 Value 값은 중복된 값이 포함될 수 있습니다.

<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-04.svg" width="60%" height="60%">

- [Sorted Sets in Redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-5-sorted-sets-in-redis/)
  - member는 유일한 값만 포함될 수 있습니다.
  - score라고 불리는 values 값은 부동 수소점만을 포함할 수 있습니다.
  - 내부 멤버는 정렬된 순서로 접근 가능합니다.
  - 참고 : https://jupiny.com/2020/03/28/redis-sorted-set/
  
<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-05.svg" width="60%" height="60%">
