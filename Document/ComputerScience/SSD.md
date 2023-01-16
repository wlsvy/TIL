# ssd

하드디스크와 많이 비교가 된다.

- 간단히 설명해서, 하드는 디스크를 빙글 돌리며 헤드 아래에 찾고자 하는 섹터가 위치해야 한다. 그 다음에서야 데이터를 읽어들일 수 있는데, 당연히 물리적인 동작이니 cpu 속도를 따라잡을 수 없었다.
- ssd 는 flash 메모리 기반 (floating gate transistor 쓴다고 하더라) 그러니까 전기 작용을 사용한다. 헤더가 돌아가는 걸 기다릴 필요가 없으니 빠를 수 밖에 없다. 그리고 하드디스크가 가지고 있던 문제 한 가지, 헤더를 사용하면 데이터 병렬 처리가 까다로울 텐데 SSD 에서는 장애가 되지 않는다. 병렬 flash chip 이 사용된다.

[Quora: Why-are-solid-state-drives-so-fast](https://www.quora.com/Why-are-solid-state-drives-so-fast)