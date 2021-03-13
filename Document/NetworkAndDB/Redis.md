# Redis

#### Reference
- [Redis Document](https://redis.io/documentation)
- [Redis Data Type Introduction](https://redis.io/topics/data-types-intro)


### string
- [strings in redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-1-strings-in-redis/)
  - string 키값, string 밸류 쌍으로 이루어집니다.

<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-01.svg" width="60%" height="60%">

- [list in redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-2-lists-in-redis/)
  - LPUSH/RPUSH 로 자료구조 양 옆에서 데이터 삽입 가능(마찬가지로 제거도 가능)
  - 중복된 값 포함 가능
  - LISTs in Redis store an ordered sequence of strings,

<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-02.svg" width="60%" height="60%">

- [Sets in Redis](https://redislabs.com/ebook/part-1-getting-started/chapter-1-getting-to-know-redis/1-2-what-redis-data-structures-look-like/1-2-3-sets-in-redis/)
  - 내부적으로 해쉬 테이블 사용
  - 중복된 값을 포함할 수 없다.
   
<img src="https://www.redislabs.com/wp-content/images/academy/redis-in-action/RIA_fig1-03.svg" width="60%" height="60%">
