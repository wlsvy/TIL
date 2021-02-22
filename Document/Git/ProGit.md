# ProGit

참조 : [git-scm.com](https://git-scm.com/book/ko/v2)

## 1. 시작하기

### Git 기초

#### 차이가 아니라 스냅샷

- Subversion과 Subversion 비슷한 놈들과 Git의 가장 큰 차이점은 데이터를 다루는 방법에 있다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/Git/ProGit_Image/1-4.png" width="40%" height="40%">

- Git은 이런 식으로 데이터를 저장하지도 취급하지도 않는다. 대신 Git은 데이터를 파일 시스템 스냅샷의 연속으로 취급하고 크기가 아주 작다. Git은 커밋하거나 프로젝트의 상태를 저장할 때마다 파일이 존재하는 그 순간을 중요하게 여긴다. 파일이 달라지지 않았으면 Git은 성능을 위해서 파일을 새로 저장하지 않는다. 단지 이전 상태의 파일에 대한 링크만 저장한다. Git은 데이터를 스냅샷의 스트림처럼 취급한다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/Git/ProGit_Image/1-5.png" width="40%" height="40%">

#### Git의 무결성
- Git은 데이터를 저장하기 전에 항상 체크섬을 구하고 그 체크섬으로 데이터를 관리한다. 그래서 체크섬을 이해하는 Git 없이는 어떠한 파일이나 디렉토리도 변경할 수 없다.
- Git은 SHA-1 해시를 사용하여 체크섬을 만든다. 만든 체크섬은 40자 길이의 16진수 문자열이다. 파일의 내용이나 디렉토리 구조를 이용하여 체크섬을 구한다.
