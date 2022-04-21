# LinuxCommand 명령어 모음

- [출처 : 티스토리 블로그](https://cocoon1787.tistory.com/717?category=888102)
- [출처 : 티스토리 블로그](https://cocoon1787.tistory.com/197?category=888102)

## 파일 시스템 탐색

- pwd : Print Work Directory. 현재 작업 중인 디렉토리를 보여준다.
- ls : list segments. 파일과 디렉터리 정보 제공
  - ls -l : 파일의 상세정보
  - ls -a : 숨김 파일 표시
  - ls -t : 파일들을 생성시간순(제일 최신 것부터)으로 표시
  - ls -rt : 파일들을 생성시간순(제일 오래된 것부터)으로 표시
  - ls -f : 파일 표시 시 마지막 유형에 나타내는 파일명을 끝에 표시
  - l : long list (display lots of info)
  - t : 수정 시간에 따라 정렬
  - S : size에 따라 정렬
  - h : 사전순으로 정렬
  - r : 역순으로 정렬
- cd : 디렉터리 이동
  - cd ~ : 홈 디렉터리로 이동
  - cd / : 최상위 디렉터리로 이동
  - cd . : 현재 디렉터리 
  - cd .. : 상위 디렉터리로 이동
  - cd - : 이전 경로로 이동
- mkdir : 새 디렉터리 생성
- rmdir : remove directory. 비어 있는 디렉터리 삭제
- df : 파일 시스템의 디스크 공간 정보 표시

## 시스템 조작

- uname : 시스템 정보(os및 커널 정보) 표시
- ps : 현재 시스템에서 실행 중인 프로세스 시각화
  - ps -ef : 좀더 자세히
- kill : 프로세스 중지 (기본값은 TERM)
  - kill -l : kill 시그널 목록 확인
  - PID # 1234 인 프로세스에 kill 시그널을 보내는 예시
    - > kill -9 1234
    - > kill -KILL 1234
    - > kill -SIGKILL 1234
- service : 시스템 전체 서비스 호출
- batch : 
- shutdown : 시스템 종료

## 파일 관리

- touch : 빈 파일 작성 혹은 기존 파일의 타임 스탬프 갱신
- cat : 파일의 내용을 화면에 출력, 리다이렉션 기호('>')를 사용하여 새로운 파일 생성
  - cat file1 : file1의 내용을 출력
  - cat file1 file2 : file1과 file2의 내용을 출력
  - cat file1 file2 | more : file1과 file2의 내용을 페이지별로 출력
  - cat file1 file2 | head : file1과 file2의 내용을 처음부터 10번째 줄까지만 출력
  - cat file1 file2 | tail : file1과 file2의 내용을 끝에서부터 10번째 줄까지만 출력
- cp : 파일 복사
  - cp file1 file2 : file1을 file2라는 이름으로 복사
  - cp -f file1 file2 : 강제 복사(file2라는 파일이 이미 있을 경우 강제로 기존 file2를 지우고 복사 진행)
  - cp -r dir1 dir2 : 디렉터리 복사. 폴더 안의 모든 하위 경로와 파일들을 복사
  - i : 파일을 복사할 때 파일명이 동일하다면 덮어쓰기를 할 것인지 물어본다. 
  - f : 동일한 파일명이 있는 경우에도 강제로 삭제 후 복사한다.
  - p : 원본 파일 소유주, 그룹, 권한, 시간 정보들을 그대로 복사한다.
  - r : [원본파일명]이 경로일 경우, 그 경로에 있는 모든 하위 디렉토리들을 포함하여 모두 복사한다. 일반 파일일 경우는 그냥 복사한다.
  - u : 복사할 대상이 이미 존재하고 파일의 날짜가 같거나 더 최신이라면 복사하지 않는다
- mv : 파일 이동
  - mv file1 file2 : file1 파일을 file2 파일로 변경
  - mv file1 /dir : file1 파일을 dir 디렉터리로 이동
  - mv file1 file2 /dir : 여러 개의 파일을 dir 디렉터리로 이동
  - mv /dir1 /dir2 : dir1 디렉터리를 dir2 디렉터리로 이름 변경
  - f : 이동할 위치에 파일 이름이 겹치면 강제로 이동한다.
  - i : 이동할 위치에 파일 이름이 겹치면 사용자에게 물어본다.
- rm : 파일 삭제
  - rm file1 : file1을 삭제
  - rm -f file1 : file1을 강제 삭제
  - rm -r dir : dir 디렉터리 삭제 (디렉터리는 -r 옵션 없이 삭제 불가)
  - i : 파일이나 디렉토리가 삭제될 때마다 확인한다.(y : 삭제, n : 취소)
  - f : 사용자에게 확인하지 않고 삭제한다.
  - v : 각각의 파일 지우는 정보를 자세하게 모두 보여준다.
  - r : 해당 디렉토리의 하위 디렉토리까지 모두 삭제
- cmp
- alias : 명령어 별칭 지정
  - alias 를 그대로 입력 시, 현재 별칭 지정된 명령어를 확인
  - alias 별명 = '명령어 정의'
  > alias lsa = 'ls -a' <br/>
  > unalias lsa

## 명령어 검색 및 정규 표현식

- find
- grep

## I/O 및 소유권

- clear : 터미널 화면 정리
- echo : 텍스트 출력
- sudo : 루트 
- chmod : 시스템 파일 또는 객체의 액세스 권한 변경
- chwon : 시스템 파일 또는 객체의 소유권 변경

## 프로세스를 백그라운드에서 실행

You can press `ctrl-z` to interrupt the process and then run `bg` to make it run in the background.

You can show a numbered list all processes backgrounded in this manner with `jobs`.

Then you can run `disown %1` (replace `1` with the process number output by `jobs`) to detach the process from the terminal.

In spite of the name, the process will still be owned by you after running `disown`, it will just be detached from the terminal you started it in.

백그라운드의 작업을 다시 포그라운드 작업으로 변경할려면

> fg #<Job Number> <br/>
> ex : fg #1

- [출처 : 스택오버플로우](https://serverfault.com/questions/34750/is-it-possible-to-detach-a-process-from-its-terminal-or-i-should-have-used-s)
