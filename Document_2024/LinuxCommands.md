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
  - head -3 file1 : file1 내용을 앞에서 3줄 출력
  - tail -3 file1 : file1 내용을 끝에서 3줄 출력
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
- lsof (list open files)
  - lsof -i :<포트번호> 명령을 실행하면 해당 포트를 사용하고 있는 프로세스의 PID를 확인할 수 있습니다. 
  - -u 옵션으로 사용자를 지정
  - -i 옵션은 모든 네트워크 포트를 표시
  - -U(대문자) 옵션을 사용하면 유닉스 도메인 소켓만 표시
  - -t 옵션은 자세한 정보를 출력하지 않고 pid 정보만 출력
  - > $ lsof -u^lesstif -u ^root
    - ^ 특정 사용자 제외
  - [lsof 사용법](https://www.lesstif.com/system-admin/lsof-20776078.html)

## 명령어 검색 및 정규 표현식

- find
  - ex) `find *.txt SomeDirectory/` : SomeDirectory 하위에 모든 txt 파일 찾기 (재귀)
  - name '패턴': 주어진 패턴과 일치하는 파일 이름을 검색
  - ex) `find /path/to/search -name "*.txt"`
  - type f: 일반 파일만 검색
  - type d: 디렉토리만 검색
  - ex) `find /path/to/search -type d`
  - exec 명령어 {} \;: 검색된 각 파일에 대해 지정된 명령을 실행
  - ex) `find /path/to/search -type f -name "*.tmp" -exec rm {} \;`
  - ex) `find . -type f -exec echo "File:" {} \;`
    - `-exec` 옵션은 검색된 각 파일에 대해 지정된 명령을 실행합니다. 명령은 {}로 표시된 위치에 파일 이름이 대체되며, 명령의 끝은 반드시 \;로 종료되어야 합니다.
    - 이 명령은 /path/to/search 디렉토리와 그 하위에서 .tmp 확장자를 가진 모든 파일을 찾아서 삭제합니다.
    - `-exec` 옵션에서 {}는 검색된 각 파일의 경로와 이름을 대체하는 자리 표시자입니다
  - delete: 검색된 파일을 삭제
  - ex) `find /path/to/search -type f -name "*.bak" -delete`
  - ex) `find /path/to/directory -type f \( -name "*.txt" ! -name "*.bak" \)`: 특정 확장자를 포함하면서 다른 확장자는 제외하는 경우
  - size +크기: 지정된 크기보다 큰 파일 검색
  - mtime -일수: 지정된 일수 내에 수정된 파일 검색
  - user 사용자명: 지정된 사용자가 소유한 파일 검색
  - perm -권한: 특정 권한을 가진 파일 검색
- grep
  - `-i` 옵션은 대소문자 구분 ignore
  - ex) `grep -H -n "문자열" *.txt` : 현재 디렉토리의 모든 txt 파일에서 문자열 검색, 라인 인버 표시(`-n`), 파일 이름 표시 (`-H`)
  - ex) `grep -Hn "문자열" *.txt`
  - ex) `grep -Hnr "문자열" SomeDirectory` : r 옵션은 recursive
  - ex) `egrep 'error|warning' log.txt` : egrep 은 -E 옵션을 사용한 것과 동일 (-E : extended regular expression)
  - ex) `grep 'pattern1' filename | grep 'pattern2` : grep 명령어 결합
  - ex) `grep '^start.*end$' filename` : 'start'로 시작하고 'end'로 끝나는 라인
  - ex) `egrep 'pattern1.*pattern2' filename` : pattern1 뒤에 pattern2 가 오는 라인
  - ex) `grep -l 'pattern'` : 파일 이름만 출력
  - ex) `grep -L 'pattern'` : 패턴과 일치하지 않는 파일 이름만 출력
  - ex) `grep -v 'pattern'` : 패턴과 일치하지 않는 라인 력력
  - C [n]: 매치되는 라인의 위아래로 n 줄씩 출력합니다.
  - ex) `grep -C 4 '검색할 단어' 파일명` : 단어 검색 후 해당 단어가 포함된 라인의 위 아래로 4 줄을 함께 출력
  - B [n]: 매치되는 라인의 위 n 줄을 출력합니다.
  - A [n]: 매치되는 라인의 아래 n 줄을 출력합니다.
  - ex) `grep -Hnir "IDBCustomType" --include=*.cs Directory/` : 지정 디렉토리 내 검색 대상인 파일 패턴을 지정(*.cs)

- wc
  - wc(word count) 명령어는 텍스트 파일의 줄, 단어, 그리고 바이트 수를 세는 데 사용됩니다. 다음은 wc 명령어의 기본적인 옵션들과 그 사용 예시입니다:
  - l : 줄의 수를 출력합니다.
   -w : 단어의 수를 출력합니다.
   -c : 바이트 수를 출력합니다.
   -m : 문자의 수를 출력합니다. (멀티바이트 문자를 정확히 세기 위해 사용)

- sed (stream editor) : 주로 파일 내의 문자열을 검색, 대체, 삭제하거나 삽입할 때 사용
- `sed [옵션] '명령어' 파일명`
  - `-e, --expression` : 여러 명령을 순차적으로 실행할 때 사용됩니다.
    - `sed -e 's/foo/bar/' -e 's/baz/qux/' filename`
  - `-f, --file` 스크립트 파일에 작성된 명령어를 실행합니다.
    - `sed -f script.sed filename`
  - `-i, --in-place`: 파일을 직접 수정합니다. 백업 파일을 생성할 수도 있습니다.
    - `sed -i.bak 's/foo/bar/' filename`
  - `-n --quiet, --silent`: 출력을 억제합니다. 일반적으로 `p` 명령과 함께 사용됩니다.
    - `sed -n 's/foo/bar/p' filename`
  - 주요 명령어
    1. **s/정규식/대체문자열/플래그**
     - 문자열을 대체합니다. 플래그에는 g(모든 발생), p(출력), i(대소문자 무시)가 포함됩니다.
     - `sed 's/foo/bar/g' filename`
    2. **d**
     - 라인을 삭제합니다.
     - `sed '/foo/d' filename`
    3. **p**
     - 라인을 출력합니다. `-n` 옵션과 함께 사용하여 특정 라인만 출력할 수 있습니다.
     - `sed -n '/foo/p' filename`
    4. **a\ 텍스트**
     - 지정한 라인 이후에 텍스트를 추가합니다.
     - `sed '/foo/a\New Text' filename`
    5. **i\ 텍스트**
     - 지정한 라인 이전에 텍스트를 추가합니다.
     - `sed '/foo/i\New Text' filename`
    6. c\ 텍스트
     - 지정한 라인을 텍스트로 변경합니다.
     - `sed '/foo/c\New Text' filename`
    7. r 파일명
     - 파일의 내용을 읽어와 삽입합니다.
     - `sed '/foo/r file.txt' filename`
    8. w 파일명
     - 지정한 라인을 파일에 저장합니다.
     - `sed -n '/foo/w output.txt' filename`

### sed 예제

1. **파일의 모든 'foo'를 'bar'로 대체하기**
   - `sed 's/foo/bar/g' filename`

2. **특정 패턴이 있는 라인 삭제하기**
   - `sed '/pattern/d' filename`

3. **특정 패턴이 있는 라인만 출력하기**
   - `sed -n '/pattern/p' filename`

4. **파일의 마지막에 텍스트 추가하기**
   - `sed '$a\New Text' filename`

주의

- Unix/Linux와 Windows의 라인 엔딩 차이: Unix/Linux 시스템에서는 줄 끝을 LF(Line Feed, \n)로 표시합니다. 반면에 Windows 시스템에서는 CRLF(Carriage Return + Line Feed, \r\n)로 줄 끝을 표시합니다. sed 명령어는 기본적으로 Unix 스타일(LF)로 작동하기 때문에 Windows에서 sed를 사용하면 라인 엔딩이 LF로 바뀔 수 있습니다.

### xargs 명령어

`xargs`는 표준 입력에서 읽은 데이터를 인수로 받아서 지정한 명령어를 실행하는 데 사용됩니다. 주로 명령어 결과나 파일 목록을 받아서 반복적으로 명령어를 실행해야 할 때 유용합니다.

- 기본 사용법 :`xargs`는 표준 입력 또는 파일로부터 데이터를 읽고 이를 명령어의 인수로 전달합니다.
  - `command | xargs [options] [command]`

#### 주요 옵션
- `-I {}` (Replace-strings): 입력 줄의 특정 부분을 치환하여 사용합니다.
- `-P num` (Max-procs): 병렬로 명령을 실행할 프로세스 수를 지정합니다.
- `-d delimiter` (Delimiter): 입력 구분자를 지정합니다.
- `-n num` (Max-args): 한 번에 전달할 인수의 수를 지정합니다.
- `-0` (Null): 널 문자(`\0`)를 구분자로 사용합니다. 이는 `find -print0`와 함께 사용할 때 유용합니다.

#### 예제

- 입력된 파일들을 한 번에 `rm` 명령어로 삭제합니다.
  - `echo "file1 file2 file3" | xargs rm`
- 현재 디렉토리와 하위 디렉토리에서 `.txt` 확장자를 가진 모든 파일을 찾아 삭제합니다.
  - `find . -name "*.txt" | xargs rm`
- -I 옵션 사용: 각 파일을 개별적으로 `mv` 명령어로 이동합니다.
  - `echo "file1 file2 file3" | xargs -I {} mv {} /path/to/destination/`
- 병렬 실행 : 한 번에 5개의 병렬 프로세스로 URL들을 다운로드합니다.
  - `cat urls.txt | xargs -P 5 -I {} wget {}`
- 다른 구분자 사용: `:`를 구분자로 사용하여 파일들을 삭제합니다.
  - `echo "file1:file2:file3" | xargs -d ':' rm`
- 한 번에 전달할 인수의 수 지정 : 한 번에 2개의 파일씩 `ls` 명령어로 리스트합니다.
  - `echo "file1 file2 file3 file4" | xargs -n 2 ls`
- 널 문자로 구분된 파일들을 `rm` 명령어로 삭제합니다.
  - `find . -type f -print0 | xargs -0 rm`


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

> fg %<Job Number> <br/>
> ex : fg %1

- [출처 : 스택오버플로우](https://serverfault.com/questions/34750/is-it-possible-to-detach-a-process-from-its-terminal-or-i-should-have-used-s)
  
## 환경 변수
  
- printenv : 환경변수 리스트 나열
  - `env | grep -i <keyword>` : keyword를 포함하는 환경변수 필터링해서 나열
- `export <name>='<value>` : 환경변수 추가/업데이트
  - > export EnvVar='environmentVariable'
- `unset <name>` : 환경 변수 제거 
  - > unset EnvVar
  
## Vim

- vim : vim 에디터
- ex) `vim filepath` : 경로의 파일을 vim 에디터로 열기  

- vim +[num] filename - 파일을 열고 지정된 줄 번호로 이동합니다.
  - 예: vim +10 example.txt는 example.txt 파일을 열고 10번째 줄로 이동합니다.
- vim -o file1 file2 - 여러 파일을 가로로 분할하여 엽니다.
- vim -O file1 file2 - 여러 파일을 세로로 분할하여 엽니다.
- vim -b filename - 파일을 바이너리 모드로 엽니다.
- vim -R filename - 파일을 읽기 전용 모드로 엽니다.
- vim -u vimrc - 특정 vimrc 설정 파일을 사용하여 Vim을 엽니다.
  - 예: vim -u ~/.myvimrc example.txt는 ~/.myvimrc 설정 파일을 사용하여 example.txt를 엽니다.
- vim -p file1 file2 - 여러 파일을 탭으로 엽니다.
- vim -c 'command' filename - 파일을 연 후 특정 Vim 명령을 실행합니다.
  - 예: vim -c 'set number' example.txt는 example.txt를 열고 줄 번호를 표시합니다.
- vim --version - Vim의 버전 정보를 출력합니다.

## SSH

**SSH 키 새로 생성하고 Github 에 공개키를 등록**

1. 기존 SSH 키 삭제

`rm -f ~/.ssh/id_rsa ~/.ssh/id_rsa.pub`

2. 새로운 SSH 키 생성 및 설정

 `ssh-keygen` 명령어는 SSH 키 쌍(공개 키와 개인 키)을 생성하는 데 사용됩니다. 일반적인 사용법은 다음과 같습니다:

`ssh-keygen -t rsa -b 4096 -C "your_email@example.com"`

- `-t rsa`: RSA 알고리즘을 사용하여 키를 생성
- `-b 4096`: 4096비트 길이의 키를 생성
- `-C "your_email@example.com"`: 키에 추가할 주석(일반적으로 이메일 주소)을 설정

```plaintext
Enter file in which to save the key (/Users/your_username/.ssh/id_rsa): [Enter Path or press Enter] 
Enter passphrase (empty for no passphrase): [Enter passphrase or press Enter]  
Enter same passphrase again: [Repeat passphrase or press Enter]
```

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    Permissions 0644 for '/home/ubuntu/.ssh/id_rsa_github_wlsvy' are too open.
    It is required that your private key files are NOT accessible by others.
    This private key will be ignored.

- 보안 경고 확인 시

`chmod 600 <private ssh key file path>`

1. SSH 에이전트에 새 키 추가

`eval "$(ssh-agent -s)"`

`ssh-add ~/.ssh/id_rsa`

4. 공개 키를 GitHub에 추가

`cat ~/.ssh/id_rsa.pub`

- GitHub에 로그인
- 오른쪽 상단의 프로필 아이콘 클릭 후 **Settings** 선택
- 왼쪽 메뉴에서 **SSH and GPG keys** 선택
- **New SSH key** 버튼 클릭
- 제목(Title)과 키(Key) 필드에 공개 키 내용 붙여넣기
- **Add SSH key** 버튼 클릭

5. SSH 구성 파일 설정

`vim ~/.ssh/config`

```plaintext
Host github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_rsa
```
6. SSH 키 인증 테스트

[Testing your SSH connection](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/testing-your-ssh-connection)

`ssh -T` 명령어는 SSH를 통해 원격 서버에 연결할 때 터미널을 할당하지 않고 명령을 실행하는 데 사용됩니다. 특히 GitHub와 같은 서비스에 SSH 키를 사용하여 인증을 테스트할 때 유용합니다.

- `-T`: "Pseudo-terminal allocation"을 비활성화합니다. 이는 원격 서버에서 명령을 실행하지만 대화형 쉘을 제공하지 않는 경우에 사용됩니다.

`ssh -T git@github.com`

```plaintext
Hi <username>! You've successfully authenticated, but GitHub does not provide shell access.
```

- `eval "$(ssh-agent -s)"`: SSH 에이전트 시작
- `ssh-add ~/.ssh/id_rsa` : SSH 키 추가
- `ssh-add -l`: SSH 에이전트에 등록된 키 확인

7. 깃 저장소에서 ssh 전용 url 로 작업

- `git remote -v` : 원격 저장소 정보 확인
- `git remote set-url origin git@github.com:<username>/<repo name>.git` : 원격 저장소 url 설정
  - `git@github.com:<username>/<repo name>.git` : github 측 ssh url은 보통 이런 모습


**SSH 에이전트란 무엇인지, SSH 에이전트에 등록된 내용 확인하는 방법**

SSH 에이전트는 사용자의 SSH 키를 메모리에 저장하여 여러 번 인증을 하지 않도록 도와주는 프로그램입니다. SSH 에이전트를 사용하면 비밀번호 입력 없이 여러 SSH 연결에서 키를 사용할 수 있습니다.

- `eval "$(ssh-agent -s)"`: SSH 에이전트 시작
- `ssh-add ~/.ssh/id_rsa` : SSH 키 추가
- `ssh-add -l`: SSH 에이전트에 등록된 키 확인
  - 이 명령어는 현재 SSH 에이전트에 로드된 모든 키를 나열합니다.