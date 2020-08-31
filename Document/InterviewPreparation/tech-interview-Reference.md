# tech-interview-Reference 

- 기술 면접 공부할 때 참조할 만한 링크를 작성한 문서입니다.

- 👶🏻 [신입 개발자 전공 지식 & 기술 면접 백과사전(깃허브)](https://github.com/gyoogle/tech-interview-for-developer) 📖
- 👶🏻 [신입 개발자 전공 지식 & 기술 면접 백과사전(웹페이지)](https://gyoogle.dev/blog/) 📖
- :clap:[기술면접 준비하기(블로그)](https://velog.io/@hygoogi/%EA%B8%B0%EC%88%A0%EB%A9%B4%EC%A0%91-%EC%A4%80%EB%B9%84%ED%95%98%EA%B8%B0)
- [c api 참고는 여기 블로그에서](http://blog.naver.com/PostList.nhn?blogId=sharonichoya&from=postList&categoryNo=22)
- [[번역] 개발자를 위한 면접 지침](https://blog.rhostem.com/posts/2019-01-05-developer-guide-for-interview?fbclid=IwAR08010UPAKzvEXznjC9su2wzmmq0cYWSRPigJbAHxPBFAc_PUlsurBvEPk)


- effective c++ : 2, 3, 7, 9, 13, 30, 32
- effective modern C++ : 1, 2, 3, 9, 15, 18, 19, 20, 21, 22, 23


#### 세마포어 & 뮤텍스
- 문지기 역할을 합니다. 크리티컬 섹션에 프로세스 혹은 스레드가 한 번에 하나씩 접근하도록 제한합니다. 다수의 프로세스 혹은 스레드가 동시에 접근하여 레이스 컨디션이 발생하지 않도록 예방합니다.
  - 세마포어는 다수의 프로세스 혹은 스레드에 대해서, 뮤텍스는 다수의 스레드에 대해 적용 가능합니다.
  - 세마포어는 내부적으로 정수 값을 확인하여 상호 배제를 수행합니다. 뮤텍스는 0과 1 값만 가지는 binary semaphore 입니다. 즉 뮤텍스는 세마포어의 영역에 포함됩니다.
  - 세마포어의 예시는 DirectX 12 의 fence, 뮤텍스는 c++ 의 std::mutex를 예로 들 수 있습니다.
