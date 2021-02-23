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

</details>
