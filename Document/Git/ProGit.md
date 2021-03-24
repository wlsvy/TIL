# ProGit

참조 : [git-scm.com](https://git-scm.com/book/ko/v2)

## 1. 시작하기

<details>
<summary>fold/unfold</summary>

### Git 기초

#### 차이가 아니라 스냅샷

- Subversion과 Subversion 비슷한 놈들과 Git의 가장 큰 차이점은 데이터를 다루는 방법에 있다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/Git/ProGit_Image/1-4.png" width="40%" height="40%">

- Git은 이런 식으로 데이터를 저장하지도 취급하지도 않는다. 대신 Git은 데이터를 파일 시스템 스냅샷의 연속으로 취급하고 크기가 아주 작다. Git은 커밋하거나 프로젝트의 상태를 저장할 때마다 파일이 존재하는 그 순간을 중요하게 여긴다. 파일이 달라지지 않았으면 Git은 성능을 위해서 파일을 새로 저장하지 않는다. 단지 이전 상태의 파일에 대한 링크만 저장한다. Git은 데이터를 스냅샷의 스트림처럼 취급한다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/Git/ProGit_Image/1-5.png" width="40%" height="40%">

#### Git의 무결성
- Git은 데이터를 저장하기 전에 항상 체크섬을 구하고 그 체크섬으로 데이터를 관리한다. 그래서 체크섬을 이해하는 Git 없이는 어떠한 파일이나 디렉토리도 변경할 수 없다.
- Git은 SHA-1 해시를 사용하여 체크섬을 만든다. 만든 체크섬은 40자 길이의 16진수 문자열이다. 파일의 내용이나 디렉토리 구조를 이용하여 체크섬을 구한다.

#### 세 가지 상태
- Git 은 파일을 Committed, Modified, Staged 세 가지 상태로 관리한다.
  - Committed란 데이터가 로컬 데이터베이스에 안전하게 저장됐다는 것을 의미한다.
  - Modified는 수정한 파일을 아직 로컬 데이터베이스에 커밋하지 않은 것을 말한다.
  - Staged란 현재 수정한 파일을 곧 커밋할 것이라고 표시한 상태를 의미한다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/Git/ProGit_Image/1-6.png" width="40%" height="40%">

- Git 디렉토리는 Git이 프로젝트의 메타데이터와 객체 데이터베이스를 저장하는 곳을 말한다.
- 워킹 트리는 프로젝트의 특정 버전을 Checkout 한 것이다. Git 디렉토리는 지금 작업하는 디스크에 있고 그 디렉토리 안에 압축된 데이터베이스에서 파일을 가져와서 워킹 트리를 만든다.
- Staging Area는 Git 디렉토리에 있다. 단순한 파일이고 곧 커밋할 파일에 대한 정보를 저장한다. Git에서는 기술용어로는 “Index” 라고 하지만, “Staging Area” 라는 용어를 써도 상관 없다.

<br>

Git으로 하는 일은 기본적으로 아래와 같다.
1. 워킹 트리에서 파일을 수정한다.
2. Staging Area에 파일을 Stage 해서 커밋할 스냅샷을 만든다. 모든 파일을 추가할 수도 있고 선택하여 추가할 수도 있다.
3. Staging Area에 있는 파일들을 커밋해서 Git 디렉토리에 영구적인 스냅샷으로 저장한다.

- Git 디렉토리에 있는 파일들은 Committed 상태이다. 파일을 수정하고 Staging Area에 추가했다면 Staged이다. 그리고 Checkout 하고 나서 수정했지만, 아직 Staging Area에 추가하지 않았으면 Modified이다.

<br>

- [Git 최초 설정](https://git-scm.com/book/ko/v2/%EC%8B%9C%EC%9E%91%ED%95%98%EA%B8%B0-Git-%EC%B5%9C%EC%B4%88-%EC%84%A4%EC%A0%95)
  - git config

</details>


## 2. Git의 기초

<details>
<summary>fold/unfold</summary>

- [Git 저장소 만들기](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-Git-%EC%A0%80%EC%9E%A5%EC%86%8C-%EB%A7%8C%EB%93%A4%EA%B8%B0)
- [수정하고 저장소에 저장하기](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%EC%88%98%EC%A0%95%ED%95%98%EA%B3%A0-%EC%A0%80%EC%9E%A5%EC%86%8C%EC%97%90-%EC%A0%80%EC%9E%A5%ED%95%98%EA%B8%B0)
  - 워킹 디렉토리의 모든 파일은 크게 Tracked(관리대상임)와 Untracked(관리대상이 아님)로 나눈다. 
  - Tracked 파일은 이미 스냅샷에 포함돼 있던 파일이다. Tracked 파일은 또 Unmodified(수정하지 않음)와 Modified(수정함) 그리고 Staged(커밋으로 저장소에 기록할) 상태 중 하나이다. 간단히 말하자면 Git이 알고 있는 파일이라는 것이다.
  - 그리고 나머지 파일은 모두 Untracked 파일이다. Untracked 파일은 워킹 디렉토리에 있는 파일 중 스냅샷에도 Staging Area에도 포함되지 않은 파일이다.
  - 처음 저장소를 Clone 하면 모든 파일은 Tracked이면서 Unmodified 상태이다. 파일을 Checkout 하고 나서 아무것도 수정하지 않았기 때문에 그렇다.
  - 마지막 커밋 이후 아직 아무것도 수정하지 않은 상태에서 어떤 파일을 수정하면 Git은 그 파일을 Modified 상태로 인식한다. 실제로 커밋을 하기 위해서는 이 수정한 파일을 Staged 상태로 만들고, Staged 상태의 파일을 커밋한다. 이런 라이프사이클을 계속 반복한다.
  - add, status, .gitignore, diff, commit, rm, mv

<img src="https://git-scm.com/book/en/v2/images/lifecycle.png" width="60%" height="60%">

- [커밋 히스토리 조회하기](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%EC%BB%A4%EB%B0%8B-%ED%9E%88%EC%8A%A4%ED%86%A0%EB%A6%AC-%EC%A1%B0%ED%9A%8C%ED%95%98%EA%B8%B0)
  - git log
  - 저자(Author) 와 커미터(Committer) 를 구분하는 것이 조금 이상해 보일 수 있다. 저자는 원래 작업을 수행한 원작자이고 커밋터는 마지막으로 이 작업을 적용한(저장소에 포함시킨) 사람이다. 만약 당신이 어떤 프로젝트에 패치를 보냈고 그 프로젝트의 담당자가 패치를 적용했다면 두 명의 정보를 모두 알 필요가 있다.

- [되돌리기](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%EB%90%98%EB%8F%8C%EB%A6%AC%EA%B8%B0)
  - amend : 커밋 수정, reset : 파일 상태를 Unstage로 변경, checkout 을 통해 Modified 파일 되돌리기

- [리모트 저장소](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%EB%A6%AC%EB%AA%A8%ED%8A%B8-%EC%A0%80%EC%9E%A5%EC%86%8C)
  - 리모트 저장소는 인터넷이나 네트워크 어딘가에 있는 저장소를 말한다. 저장소는 여러 개가 있을 수 있는데 어떤 저장소는 읽고 쓰기 모두 할 수 있고 어떤 저장소는 읽기만 가능할 수 있다. 간단히 말해서 다른 사람들과 함께 일한다는 것은 리모트 저장소를 관리하면서 데이터를 거기에 Push 하고 Pull 하는 것이다.
  - remote : 현재 프로젝트에 등록된 리모트 저장소 확인, Clone/remote add : 리모트 저장소 추가
    - 저장소를 Clone 하면 'origin'이라는 리모트 저장소가 자동으로 등록
  - fetch : 리모트 저장소에는 있는 데이터를 모두 가져온다. 그러면 리모트 저장소의 모든 브랜치를 로컬에서 접근할 수 있어서 언제든지 Merge를 하거나 내용을 살펴볼 수 있다.
  - pull : 리모트 저장소 브랜치에서 데이터를 가져올 뿐만 아니라 자동으로 로컬 브랜치와 Merge 시킬 수 있다

- [태그](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%ED%83%9C%EA%B7%B8)
- [Git Alias](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-Git-Alias)

</details>

## 3. Git 브랜치

<details>
<summary>fold/unfold</summary>

- 커밋하면 Git은 현 Staging Area에 있는 데이터의 스냅샷에 대한 포인터, 저자나 커밋 메시지 같은 메타데이터, 이전 커밋에 대한 포인터 등을 포함하는 커밋 개체(커밋 Object)를 저장한다. 이전 커밋 포인터가 있어서 현재 커밋이 무엇을 기준으로 바뀌었는지를 알 수 있다. 최초 커밋을 제외한 나머지 커밋은 이전 커밋 포인터가 적어도 하나씩 있고 브랜치를 합친 Merge 커밋 같은 경우에는 이전 커밋 포인터가 여러 개 있다.
- Git이 아닌 다른 버전 관리 도구에서는 브랜치를 하나 만드는 데 큰 비용이 든다. Git에서는 매우 일상적으로 브랜치를 만들고 Merge 하고 삭제한다. 다른 버전관리 도구에서는 브랜치를 하나 만드는 데 큰 비용이 든다.

<br>

[브랜치란 무엇인가](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EB%B8%8C%EB%9E%9C%EC%B9%98%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80)

- 파일이 3개 있는 디렉토리가 하나 있고 이 파일을 Staging Area에 저장하고 커밋하는 예제를 살펴 보자. 파일을 Stage 하면 Git 저장소에 파일을 저장하고(Git은 이것을 Blob이라고 부른다) Staging Area에 해당 파일의 체크섬을 저장한다
- git commit 으로 커밋하면 먼저 루트 디렉토리와 각 하위 디렉토리의 트리 개체를 체크섬과 함께 저장소에 저장한다. 그다음에 커밋 개체를 만들고 메타데이터와 루트 디렉토리 트리 개체를 가리키는 포인터 정보를 커밋 개체에 넣어 저장한다. 그래서 필요하면 언제든지 스냅샷을 다시 만들 수 있다.
- 이 작업을 마치고 나면 Git 저장소에는 다섯 개의 데이터 개체가 생긴다. 각 파일에 대한 Blob 세 개, 파일과 디렉토리 구조가 들어 있는 트리 개체 하나, 메타데이터와 루트 트리를 가리키는 포인터가 담긴 커밋 개체 하나이다.

<img src="https://git-scm.com/book/en/v2/images/commit-and-tree.png" width="60%" height="60%">

다시 파일을 수정하고 커밋하면 이전 커밋이 무엇인지도 저장한다.

<img src="https://git-scm.com/book/en/v2/images/commits-and-parents.png" width="60%" height="60%">

- Git의 브랜치는 커밋 사이를 가볍게 이동할 수 있는 어떤 포인터 같은 것이다. 기본적으로 Git은 master 브랜치를 만든다. 처음 커밋하면 이 master 브랜치가 생성된 커밋을 가리킨다.

<img src="https://git-scm.com/book/en/v2/images/branch-and-history.png" width="60%" height="60%">

- 만약 위의 과정에서 새로 testing 브랜치를 생성한다고 가정하자.
  - 새로 만든 브랜치도 지금 작업하고 있던 마지막 커밋을 가리킨다.

<img src="https://git-scm.com/book/en/v2/images/two-branches.png" width="60%" height="60%">

- 지금 작업 중인 브랜치가 무엇인지 Git은 어떻게 파악할까. 다른 버전 관리 시스템과는 달리 Git은 'HEAD’라는 특수한 포인터가 있다. 이 포인터는 지금 작업하는 로컬 브랜치를 가리킨다. 브랜치를 새로 만들었지만, Git은 아직 master 브랜치를 가리키고 있다. git branch 명령은 브랜치를 만들기만 하고 브랜치를 옮기지 않는다.

<img src="https://git-scm.com/book/en/v2/images/head-to-master.png" width="60%" height="60%">

- git log 명령에 --decorate 옵션을 사용하면 브랜치가 어떤 커밋을 가리키고 있는지 확인가능
- git checkout 명령으로 다른 브랜치로 이동할 수 있다.

<br>

[브랜치와 Merge의 기초](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EB%B8%8C%EB%9E%9C%EC%B9%98%EC%99%80-Merge-%EC%9D%98-%EA%B8%B0%EC%B4%88)
- Fast-Forward Merge : A 브랜치에서 다른 B 브랜치를 Merge 할 때 B 브랜치가 A 브랜치 이후의 커밋을 가리키고 있으면 그저 A 브랜치가 B 브랜치와 동일한 커밋을 가리키도록 이동시키는 방식
- 3-way Merge : 현재 브랜치가 가리키는 커밋이 Merge 할 브랜치의 조상이 아닌 경우, Git은 'Fast-forward’로 Merge 하지 않는다. 이 경우에는 Git은 각 브랜치가 가리키는 커밋 두 개와 공통 조상 하나를 사용하여 3-way Merge를 한다.
  - 단순히 브랜치 포인터를 최신 커밋으로 옮기는 게 아니라 3-way Merge 의 결과를 별도의 커밋으로 만들고 나서 해당 브랜치가 그 커밋을 가리키도록 이동시킨다. 그래서 이런 커밋은 부모가 여러 개고 Merge 커밋이라고 부른다.
<img src="https://git-scm.com/book/en/v2/images/basic-merging-1.png" width="60%" height="60%">
<img src="https://git-scm.com/book/en/v2/images/basic-merging-2.png" width="60%" height="60%">

<br>

[브랜치 관리](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EA%B4%80%EB%A6%AC)

<br>

[브랜치 워크플로](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EC%9B%8C%ED%81%AC%ED%94%8C%EB%A1%9C)

<br>

[리모트 브랜치](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-%EB%A6%AC%EB%AA%A8%ED%8A%B8-%EB%B8%8C%EB%9E%9C%EC%B9%98)
- 리모트 Refs는 리모트 저장소에 있는 포인터인 레퍼런스다. 리모트 저장소에 있는 브랜치, 태그, 등등을 의미한다. git ls-remote [remote] 명령으로 모든 리모트 Refs를 조회할 수 있다. git remote show [remote] 명령은 모든 리모트 브랜치와 그 정보를 보여준다. 리모트 Refs가 있지만 보통은 리모트 트래킹 브랜치를 사용한다.
- 리모트 트래킹 브랜치는 리모트 브랜치를 추적하는 레퍼런스이며 브랜치다. 리모트 트래킹 브랜치는 로컬에 있지만 임의로 움직일 수 없다. 리모트 서버에 연결할 때마다 리모트의 브랜치 업데이트 내용에 따라서 자동으로 갱신될 뿐이다. 리모트 트래킹 브랜치는 일종의 북마크라고 할 수 있다. 리모트 저장소에 마지막으로 연결했던 순간에 브랜치가 무슨 커밋을 가리키고 있었는지를 나타낸다.
- 리모트 트래킹 브랜치를 로컬 브랜치로 Checkout 하면 자동으로 “트래킹(Tracking) 브랜치” 가 만들어진다 (트래킹 하는 대상 브랜치를 “Upstream 브랜치” 라고 부른다). 트래킹 브랜치는 리모트 브랜치와 직접적인 연결고리가 있는 로컬 브랜치이다. 트래킹 브랜치에서 git pull 명령을 내리면 리모트 저장소로부터 데이터를 내려받아 연결된 리모트 브랜치와 자동으로 Merge 한다.

<br>

[Rebase 하기](https://git-scm.com/book/ko/v2/Git-%EB%B8%8C%EB%9E%9C%EC%B9%98-Rebase-%ED%95%98%EA%B8%B0)

</details>

## 4. Git 서버

<details>
<summary>fold/unfold</summary>
  
- [프로토콜](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C)
  - Git은 Local, HTTP, SSH, Git 이렇게 네 가지의 프로토콜을 사용할 수 있다.
  - 로컬 프로토콜 : 가장 기본적인 것이 로컬 프로토콜 이다. 리모트 저장소가 단순히 같은 시스템의 다른 디렉토리에 있을 때 사용한다. 팀원들이 전부 한 시스템에 로그인하여 개발하거나 아니면 NFS같은 것으로 파일시스템을 공유하고 있을 때 사용한다. 이런 상황은 문제가 될 수 있다. 모든 저장소가 한 시스템에 있기 때문에 한순간에 모두 잃을 수 있다.
  - HTTPS 프로토콜 : Git은 HTTP로 통신할 때, 서로 다른 두 방법으로 HTTP를 사용할 수 있다. 1.6.6 이전 버전에서는 읽기만 가능한 단순한 방법밖에 사용할 수 없었다. 1.6.6 버전부터는 똑똑한 프로토콜을 사용할 수 있다. 이 프로토콜은 Git 데이터를 전송할 때 SSH처럼 서로 협상한다. 새로운 HTTP 프로토콜은 사용이 쉽고 기능도 좋아서 많은 사람들이 사용하고 있다. 이 프로토콜을 보통 스마트 HTTP 프로토콜이라 하고 예전의 HTTP 프로토콜을 멍청한 HTTP 프로토콜이라고 한다.
    - 스마트 HTTP : 스마트 HTTP 프로토콜은 SSH나 Git 프로토콜처럼 통신한다. 다만 HTTP나 HTTPS 포트를 이용해 통신하고 다양한 HTTP 인증 방식을 사용한다는 것이 다르다. SSH는 키를 발급하고 관리해야 하는 번거로움이 있지만, HTTP는 사용자이름과 암호만으로 인증할 수 있기 때문에 더 편리하게 사용할 수 있다. 아마 지금은 Git에서 가장 많이 사용하는 프로토콜일 것이다. 실제로 GitHub 같은 서비스에서 제공하는 저장소는 Clone을 할 때나 Push를 할 때 같은 URL을 사용한다.
  - SSH 프로토콜 : Git의 대표 프로토콜은 SSH이다. SSH를 이용하면 아무런 외부 도구 없이 Git 서버를 구축할 수 있다. 대부분 서버는 SSH로 접근할 수 있도록 설정돼 있다. 뭐, 설정돼 있지 않더라도 쉽게 설정할 수 있다. 그리고 SSH는 인증 기능이 있고 어디에서든 사용할 수 있으며 사용하기도 쉽다.
  - Git 프로토콜 : Git 프로토콜은 Git에 포함된 데몬을 사용하는 것이다. 포트는 9418이며 SSH 프로토콜과 비슷한 서비스를 제공하지만, 인증 메커니즘이 없다. 저장소에 git-export-daemon-ok 파일을 만들면 Git 프로토콜로 서비스할 수 있지만, 보안은 없다. 이 파일이 없는 저장소는 서비스되지 않는다. 이 저장소는 누구나 Clone 할 수 있거나 아무도 Clone 할 수 없거나 둘 중의 하나만 선택할 수 있다. 그래서 이 프로토콜로는 Push 하게 할 수 없다. 엄밀히 말하자면 Push 할 수 있도록 설정할 수 있지만, 인증하도록 할 수 없다. 그러니까 당신이 Push 할 수 있으면 이 프로젝트의 URL을 아는 사람은 누구나 Push 할 수 있다. 그냥 이런 것도 있지만 잘 안 쓴다고 알고 있으면 된다.

<br>

- [서버에 Git 설치하기](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-%EC%84%9C%EB%B2%84%EC%97%90-Git-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0)
- [SSH 공개키 만들기](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-SSH-%EA%B3%B5%EA%B0%9C%ED%82%A4-%EB%A7%8C%EB%93%A4%EA%B8%B0)
- [서버 설정하기](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-%EC%84%9C%EB%B2%84-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0)
- [Git 데몬](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-%EC%84%9C%EB%B2%84-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0)
- [스마트 HTTP](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-%EC%8A%A4%EB%A7%88%ED%8A%B8-HTTP)
- [GitWeb](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-GitWeb)
- [GitLab](https://git-scm.com/book/ko/v2/Git-%EC%84%9C%EB%B2%84-GitLab)

</details>

## 5. 분산 환경에서의 Git

<details>
<summary>fold/unfold</summary>

- [분산 환경에서의 워크플로](https://git-scm.com/book/ko/v2/%EB%B6%84%EC%82%B0-%ED%99%98%EA%B2%BD%EC%97%90%EC%84%9C%EC%9D%98-Git-%EB%B6%84%EC%82%B0-%ED%99%98%EA%B2%BD%EC%97%90%EC%84%9C%EC%9D%98-%EC%9B%8C%ED%81%AC%ED%94%8C%EB%A1%9C)
  - Git에서는 각 개발자의 저장소가 하나의 노드이기도 하고 중앙 저장소 같은 역할도 할 수 있다. 즉, 모든 개발자는 다른 개발자의 저장소에 일한 내용을 전송하거나, 다른 개발자들이 참여할 수 있도록 자신이 운영하는 저장소 위치를 공개할 수도 있다. 
  - 중앙집중식 워크플로, Integration-Manager 워크플로, Dictator and Lieutenants 워크플로
- [프로젝트에 기여하기](https://git-scm.com/book/ko/v2/%EB%B6%84%EC%82%B0-%ED%99%98%EA%B2%BD%EC%97%90%EC%84%9C%EC%9D%98-Git-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%EC%97%90-%EA%B8%B0%EC%97%AC%ED%95%98%EA%B8%B0)
  - 기여하는 방식에 영향을 끼치는 몇 가지 변수가 있다. 활발히 기여하는 개발자의 수가 얼마인지, 선택한 워크플로가 무엇인지, 각 개발자에게 접근 권한을 어떻게 부여했는지, 외부에서도 기여할 수 있는지 등이 변수다.
  - 첫 번째로 살펴볼 변수는 활발히 활동하는 개발자의 수이다. 얼마나 많은 개발자가 얼마나 자주 코드를 쏟아 내는가 하는 점이 활발한 개발자의 기준이다.
  - 두 번째 변수는 프로젝트에서 선택한 워크플로다. 개발자 모두가 메인 저장소에 쓰기 권한을 갖는 중앙집중형 방식인가?
  - 세 번째 변수는 접근 권한이다. '프로젝트에 쓰기 권한이 있어서 직접 쓸 수 있는가? 아니면 읽기만 가능한가?'에 따라서 프로젝트에 기여하는 방식이 매우 달라진다. 
  
  <br>

  - Git은 공백문자를 검사해볼 수 있는 간단한 명령을 제공한다. 커밋을 하기 전에 git diff --check 명령으로 공백문자에 대한 오류를 확인할 수 있다.

  <br>

- [프로젝트 관리하기](https://git-scm.com/book/ko/v2/%EB%B6%84%EC%82%B0-%ED%99%98%EA%B2%BD%EC%97%90%EC%84%9C%EC%9D%98-Git-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EA%B4%80%EB%A6%AC%ED%95%98%EA%B8%B0)
</details>

## 6. GitHub

<details>
<summary>fold/unfold</summary>

- [계정 만들고 설정하기](https://git-scm.com/book/ko/v2/GitHub-%EA%B3%84%EC%A0%95-%EB%A7%8C%EB%93%A4%EA%B3%A0-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0)
- [프로젝트에 기여하기](https://git-scm.com/book/ko/v2/GitHub-GitHub-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%EC%97%90-%EA%B8%B0%EC%97%AC%ED%95%98%EA%B8%B0)
- [프로젝트에 관리하기](https://git-scm.com/book/ko/v2/GitHub-GitHub-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EA%B4%80%EB%A6%AC%ED%95%98%EA%B8%B0)
- [Organization 관리하기](https://git-scm.com/book/ko/v2/GitHub-Organization-%EA%B4%80%EB%A6%AC%ED%95%98%EA%B8%B0)
- [GitHub 스크립팅](https://git-scm.com/book/ko/v2/GitHub-GitHub-%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8C%85)
  - 서비스와 훅은 저장소에서 발생한 이벤트의 알림을 받는 방법이다.
  - 서비스 :훅과 서비스는 저장소의 설정 페이지에서 연동할 수 있다.
    - CI, 버그 트래커, 이슈 트래커, 채팅, 문서 시스템 등과 연동하는 데 사용하는 서비스가 수십 개 준비돼 있다.
  - 훅 : GitHub 서비스에 없는 사이트나 외부 서비스와 연동하고 싶거나 좀 더 세세한 설정을 하고 싶으면 GitHub 훅을 이용한다. GitHub 저장소의 훅은 단순하다. URL을 하나 주면 그 URL로 HTTP 페이로드를 보내준다.

</details>

## 7. Git 도구

<details>
<summary>fold/unfold</summary>

- [리비전 조회하기](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EB%A6%AC%EB%B9%84%EC%A0%84-%EC%A1%B0%ED%9A%8C%ED%95%98%EA%B8%B0)
  - SHA-1 줄여 쓰기 : Git은 해시 값의 앞 몇 글자만으로도 어떤 커밋인지 충분히 식별할 수 있다. 저장소 안에서 해시 값이 중복되지 않으면 해시 값의 앞 4자만으로도 나타낼 수 있다. 즉 짧은 SHA-1 값이라고 해도 유일해야 한다.
  - 브랜치로 가리키기 : git show 
  - RefLog 로 가리키기 : git reflog 
  - 계통 관계로 가리키기 : git show HEAD^
  - 범위로 커밋 가리키기 : Double Dot, 세 개 이상의 Refs, Triple Dot

<br>

- [대화형 명령](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EB%8C%80%ED%99%94%ED%98%95-%EB%AA%85%EB%A0%B9)
  - git add -i : 이 명령을 수행하면 git 은 대화형 모드로 들어간다. Staging Area의 현재 상태가 어떻고 할 수 있는 일이 무엇인지 보여준다.

<br>

- [Stashing 과 Cleaning](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Stashing%EA%B3%BC-Cleaning)
  - 당신이 어떤 프로젝트에서 한 부분을 담당하고 있다고 하자. 그리고 여기에서 뭔가 작업하던 일이 있고 다른 요청이 들어와서 잠시 브랜치를 변경해야 할 일이 생겼다고 치자. 그런데 이런 상황에서 아직 완료하지 않은 일을 커밋하는 것이 껄끄럽다는 것이 문제다. 커밋하지 않고 나중에 다시 돌아와서 작업을 다시 하고 싶을 것이다. 이 문제는 git stash 라는 명령으로 해결할 수 있다.
  - Stash는 Modified이면서 Tracked 상태인 파일과 Staging Area에 있는 파일들을 보관해두는 장소다.

<br>

- [내 작업에 서명하기](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EB%82%B4-%EC%9E%91%EC%97%85%EC%97%90-%EC%84%9C%EB%AA%85%ED%95%98%EA%B8%B0)
  - Git은 암호학적으로 안전하다. 하지만, 그냥 되는 건 아니다. 저장소에 아무나 접근하지 못하게 하고 진짜로 확인된 사람에게서만 커밋을 받으려면 GPG를 이용한다.

<br>

- [검색](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EA%B2%80%EC%83%89)
  - Git Grep : grep 명령을 이용하면 커밋 트리의 내용이나 워킹 디렉토리의 내용을 문자열이나 정규표현식을 이용해 쉽게 찾을 수 있다.
    - 기본적으로 대상을 지정하지 않으면 워킹 디렉토리의 파일에서 찾는다. 명령을 실행할 때 -n 또는 --line-number 옵션을 추가하면 찾을 문자열이 위치한 라인 번호도 같이 출력한다.
  - git log : 어떤 변수가 어디에 있는지를 찾아보는 게 아니라, 히스토리에서 언제 추가되거나 변경됐는지 찾아볼 수도 있다. log 명령을 이용하면 Diff 내용도 검색하여 어떤 커밋에서 찾고자 하는 내용을 추가했는지 찾을 수 있다.

<br>

- [히스토리 단장하기](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%ED%9E%88%EC%8A%A4%ED%86%A0%EB%A6%AC-%EB%8B%A8%EC%9E%A5%ED%95%98%EA%B8%B0)
  - 커밋 메세지 수정, 합치기 등

<br>

- [Reset 명확히 알고 가기](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Reset-%EB%AA%85%ED%99%95%ED%9E%88-%EC%95%8C%EA%B3%A0-%EA%B0%80%EA%B8%B0)
  - Git을 서로 다른 세 트리를 관리하는 컨텐츠 관리자로 생각하면 reset 과 checkout 을 좀 더 쉽게 이해할 수 있다. 여기서 “트리” 란 실제로는 “파일의 묶음” 이다. 자료구조의 트리가 아니다
    - Git 은 일반적으로 세 가지 트리를 관리하는 시스템이다. 
      - HEAD : 마지막 커밋 스냅샷, 다음 커밋의 부모 커밋
      - Index : 다음에 커밋할 스냅샷
      - 워킹 디렉토리 : 샌드박스
     
<br>

  - HEAD : HEAD는 현재 브랜치를 가리키는 포인터이며, 브랜치는 브랜치에 담긴 커밋 중 가장 마지막 커밋을 가리킨다. 지금의 HEAD가 가리키는 커밋은 바로 다음 커밋의 부모가 된다. 단순하게 생각하면 HEAD는 *현재 브랜치 마지막 커밋의 스냅샷*이다.
  - Index : Index는 바로 다음에 커밋할 것들이다. 이미 앞에서 우리는 이런 개념을 “Staging Area” 라고 배운 바 있다. “Staging Area” 는 사용자가 git commit 명령을 실행했을 때 Git이 처리할 것들이 있는 곳이다.
    - 먼저 Index는 워킹 디렉토리에서 마지막으로 Checkout 한 브랜치의 파일 목록과 파일 내용으로 채워진다. 이후 파일 변경작업을 하고 변경한 내용으로 Index를 업데이트 할 수 있다. 이렇게 업데이트 하고 git commit 명령을 실행하면 Index는 새 커밋으로 변환된다.
  - 워킹 디렉토리 : 마지막으로 워킹 디렉토리를 살펴보자. 위의 두 트리는 파일과 그 내용을 효율적인 형태로 .git 디렉토리에 저장한다. 하지만, 사람이 알아보기 어렵다. 워킹 디렉토리는 실제 파일로 존재한다. 바로 눈에 보이기 때문에 사용자가 편집하기 수월하다. 워킹 디렉토리는 샌드박스로 생각하자. 커밋하기 전에는 Index(Staging Area)에 올려놓고 얼마든지 변경할 수 있다.

<br>

  - Git의 주목적은 프로젝트의 스냅샷을 지속적으로 저장하는 것이다. 이 트리 세 개를 사용해 더 나은 상태로 관리한다.
<img src="https://git-scm.com/book/en/v2/images/reset-workflow.png" width="60%" height="60%">

  - Reset의 조작
    - 1단계 HEAD 이동 : reset 명령이 하는 첫 번째 일은 HEAD 브랜치를 이동시킨다. checkout 명령처럼 HEAD가 가리키는 브랜치를 바꾸지는 않는다. HEAD는 계속 현재 브랜치를 가리키고 있고, 현재 브랜치가 가리키는 커밋을 바꾼다. HEAD가 master 브랜치를 가리키고 있다면(즉 master 브랜치를 Checkout 하고 작업하고 있다면) git reset 9e5e6a4 명령은 master 브랜치가 `9e5e6a4`를 가리키게 한다.
    - 2단계 Index 업데이트 (--mixed) : 여기서 git status 명령을 실행하면 Index와 reset 명령으로 이동시킨 HEAD의 다른 점이 녹색으로 출력된다. reset 명령은 여기서 한 발짝 더 나아가 Index를 현재 HEAD가 가리키는 스냅샷으로 업데이트할 수 있다. --mixed 옵션을 주고 실행하면 reset 명령은 여기까지 하고 멈춘다. reset 명령을 실행할 때 아무 옵션도 주지 않으면 기본적으로 --mixed 옵션으로 동작한다(예제와 같이 git reset HEAD~ 처럼 명령을 실행하는 경우).
      - 가리키는 대상을 가장 최근의 커밋 으로 되돌리는 것은 같다. 그러고 나서 Staging Area 를 비우기까지 한다. git commit 명령도 되돌리고 git add 명령까지 되돌리는 것이다.
    - 3단계 워킹 디렉토리 업데이트(--hard) : reset 명령은 세 번째로 워킹 디렉토리까지 업데이트한다. --hard 옵션을 사용하면 reset 명령은 이 단계까지 수행한다.

<br>

  - squash : 여러 개의 커밋을 하나로 합치는 도구
  - checkout : 
    - 첫 번째로 reset --hard 명령과는 달리 checkout 명령은 워킹 디렉토리를 안전하게 다룬다. 저장하지 않은 것이 있는지 확인해서 날려버리지 않는다는 것을 보장한다. 사실 보기보다 좀 더 똑똑하게 동작한다. 워킹 디렉토리에서 Merge 작업을 한번 시도해보고 변경하지 않은 파일만 업데이트한다. 반면 reset --hard 명령은 확인하지 않고 단순히 모든 것을 바꿔버린다.
    - 두 번째 중요한 차이점은 어떻게 checkout 명령이 HEAD를 업데이트 하는가이다. reset 명령은 HEAD가 가리키는 브랜치를 움직이지만(브랜치 Refs를 업데이트하지만), checkout 명령은 HEAD 자체를 다른 브랜치로 옮긴다.
    
<br>

- [고급 Merge](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EA%B3%A0%EA%B8%89-Merge)
  - Merge 취소하기 : git merge --abort
  - 공백 무시하기 : Merge 할 때 무수한 공백 때문에 문제가 생기면 그냥 Merge를 취소한 다음 -Xignore-all-space 나 -Xignore-space-change 옵션을 주어 다시 Merge 한다. 
  - 수동으로 Merge 하기
    - Merge 커밋을 완료하기 전에 양쪽 부모에 대해서 무엇이 바뀌었는지 확인하려면 git diff 를 사용한다.
    - Merge 후의 결과를 Merge 하기 전의 브랜치와 비교하려면, 다시 말해 무엇이 합쳐졌는지 알려면 git diff --ours 명령을 실행한다.
    - Merge 할 파일을 가져온 쪽과 비교해서 무엇이 바뀌었는지 보려면 git diff --theirs 를 실행한다. 공백을 빼고 비교하고 싶다면 -b 옵션을 같이 사용할 수 있다.
    - 마지막으로 git diff --base 를 사용해서 양쪽 모두와 비교하여 바뀐 점을 알아볼 수 있다.
  - 충돌 파일 Checkout
  - Merge 로그 : “Triple Dot” 문법을 이용하면 Merge 에 사용한 양 브랜치의 모든 커밋의 목록을 얻을 수 있다.
  - Combined Diff 형식
  - Merge 되돌리기
  - Refs 수정 : 실수로 생긴 Merge 커밋이 로컬 저장소에만 있을 때는 브랜치를 원하는 커밋을 가리키도록 옮기는 것이 쉽고 빠르다. 잘못 Merge 하고 나서 git reset --hard HEAD~ 명령으로 브랜치를 되돌리면 된다.
  - 커밋 되돌리기 : 브랜치를 옮기는 것을 할 수 없는 경우는 모든 변경사항을 취소하는 새로운 커밋을 만들 수도 있다. Git에서 이 기능을 “revert” 라고 부른다.
  - 다른 방식의 Merge

<br>

- [Rerere](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Rerere)
  - git rerere 기능은 약간 숨겨진 기능이다. “reuse recorded resolution” 이라고 해서 기록한 해결책 재사용하기란 뜻의 이름이고 이름 그대로 동작한다. Git은 충돌이 났을 때 각 코드 덩어리를 어떻게 해결했는지 기록을 해 두었다가 나중에 같은 충돌이 나면 기록을 참고하여 자동으로 해결한다.
    - 문서에서 드는 예제 중 하나는 긴 호흡의 브랜치를 깔끔하게 Merge 하고 싶은데 Merge 커밋은 많이 만들고 싶지 않을 때 사용하는 것이다. rerere 기능을 켜고 자주 Merge를 해서 충돌을 해결하고 Merge 이전으로 돌아간다. 이 과정을 반복해서 기록을 쌓아두면 rerere 기능은 나중에 한 번에 Merge 할 때 기록을 참고한다. 자동으로 충돌이 날 만한 부분을 다 해결해주시니 몸과 마음이 평안하다.
    - 브랜치를 Rebase 할 때도 같은 전략을 사용할 수 있다. 쌓인 충돌 해결 기록을 참고하여 Git은 Rebase 할 때 발생한 충돌도 최대한 해결한다. 충돌 덩어리들을 해결하고 Merge 했는데 다시 Rebase 하기로 마음을 바꿨을 때 같은 충돌을 두 번 해결할 필요 없다.

<br>

- [Git으로 버그 찾기](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Git%EC%9C%BC%EB%A1%9C-%EB%B2%84%EA%B7%B8-%EC%B0%BE%EA%B8%B0)
  - 파일 어노테이션(Blame) : 버그를 찾을 때 먼저 그 코드가 왜, 언제 추가했는지 알고 싶을 것이다. 이때는 파일 어노테이션을 활용한다. 한 줄 한 줄 마지막으로 커밋한 사람이 누구인지, 언제 마지막으로 커밋했는지 볼 수 있다. 어떤 메소드에 버그가 있으면 git blame 명령으로 그 메소드의 각 라인을 누가 언제 마지막으로 고쳤는지 찾아낼 수 있다.
  - 이진 탐색 : 파일 어노테이션은 특정 이슈와 관련된 커밋을 찾는 데에도 좋다. 문제가 생겼을 때 의심스러운 커밋이 수십, 수백 개에 이르는 경우 도대체 어디서부터 시작해야 할지 모를 수 있다. 이때는 git bisect 명령이 유용하다. bisect 명령은 커밋 히스토리를 이진 탐색 방법으로 좁혀 주기 때문에 이슈와 관련된 커밋을 최대한 빠르게 찾아낼 수 있도록 도와준다.
- [서브모듈](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EC%84%9C%EB%B8%8C%EB%AA%A8%EB%93%88)
- [Bundle](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Bundle)
  - Git에는 “Bundle” 이란 것이 있다. 데이터를 한 파일에 몰아넣는 것이다. 이 방법은 다양한 경우 유용하게 사용할 수 있다. 예를 들어 네트워크가 불통인데 변경사항을 동료에게 보낼 때, 출장을 나갔는데 보안상의 이유로 로컬 네트워크에 접속하지 못할 때, 통신 인터페이스 장비가 고장났을 때, 갑자기 공용 서버에 접근하지 못할 때, 누군가에게 수정사항을 이메일로 보내야 하는데 40개 씩이나 되는 커밋을 format-patch 로 보내고 싶지 않을 때를 예로 들 수 있다.
- [Replace](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Replace)
  - Git의 replace 명령은 "어떤 개체를 읽을 때 항상 다른 개체로 보이게" 한다. 히스토리에서 어떤 커밋이 다른 커밋처럼 보이도록 할 때 이 명령이 유용하다(`git filter-branch`를 사용하여 전체 히스토리를 다시 작성할 필요가 없는 것이다).
- [Credential 저장소](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Credential-%EC%A0%80%EC%9E%A5%EC%86%8C)
  - SSH 프로토콜을 사용하여 리모트 저장소에 접근할 때 Passphase 없이 생성한 SSH Key를 사용하면 사용자이름과 암호를 입력하지 않고도 안전하게 데이터를 주고받을 수 있다. 반면 HTTP 프로토콜을 사용하는 경우는 매번 사용자이름과 암호를 입력해야 한다.
  - 다행히도 Git은 이렇게 매번 인증정보(Credential)를 입력하는 경우 인증정보를 저장해두고 자동으로 입력해주는 시스템을 제공한다.

</details>

## 8. Git 맞춤

<details>
<summary>fold/unfold</summary>

- [Git 설정하기](https://git-scm.com/book/ko/v2/Git%EB%A7%9E%EC%B6%A4-Git-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0)
  - core.editor
  - commit.template
  - core.pager
  - user.signingkey
  - core.excludesfile
  - help.autocorrect
  - color.ui
  - 다른 Merge, Diff 도구 사용하기
  - core.autocrlf : Windows는 라인 바꿈 문자로 CR(Carriage-Return)과 LF(Line Feed) 문자를 둘 다 사용하지만, Mac과 Linux는 LF 문자만 사용한다. 아무것도 아닌 것 같지만, 크로스 플랫폼 프로젝트에서는 꽤 성가신 문제다. Git은 커밋할 때 자동으로 CRLF를 LF로 변환해주고 반대로 Checkout 할 때 LF를 CRLF로 변환해 주는 기능이 있다. core.autocrlf 설정으로 이 기능을 켤 수 있다. Windows에서 이 값을 true로 설정하면 Checkout 할 때 LF 문자가 CRLF 문자로 변환된다.
  - core.whitespace
  - 서버설정
  - ....

</details>
