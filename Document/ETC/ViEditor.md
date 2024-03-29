# Vi Editor 명령어

## 유용한 동작

- 한줄 복사 : 원하는 라인에 커서를 위치시키고 'yy' -> 붙여넣고 싶은 곳에서 'p' (행 아래 복사) 혹은 'P' (행 위에 복사)
  - 잘라내기의 경우는 'yy' 대신 'dd'를 사용
- 블록 복사 : 'v'를 누른 후 커서를 움직여 블럭 지정, 이후 위와 마찬가지

## 편집 모드 3 가지

- 명령 모드(command mode) - 처음 vi 명령어로 vi를 시작하게 되면 들어가게 됩니다. 여기서는 방향키를 이용하여 커서를 이동할 수 있습니다.
- 입력 모드(insert mode) - 파일 내용을 수정할 수 있는 모드. 명령 모드로 다시 돌아오려면 "ESC"를 누르면 됩니다.  
- 마지막 행 모드(Last line mode) - 마지막행 모드는 명령모드에서 ":" (콜론) 을 입력하면 화면 맨 밑단에 :______ 하며 입력을 할수 있는 공간이 나옵니다. 여기서 현재까지 내가 작성한 이 내용을 저장하고 vi를 종료(wq)할지, 그냥 종료(q, q!)할지 등을 입력할 수 있습니다.

- [출처 티스토리](https://blockdmask.tistory.com/25)

## vi 시작 명령어

- `vi <파일명>` : 파일 열기, 작성
- `view <파일명>` : 읽기 전용으로 열기

## 문자 행 삽입

- a : 커서 오른쪽에 문자 삽입
- A : 커서 오른쪽 행 끝에 문자 삽입
- i : 커서 왼쪽에 문자 삽입
- I : 커서 왼쪽 행 끝에 문자 삽입
- o : 커서 아래에 행 삽입
- O : 커서 위에 행 삽입

## 텍스트 변경 명령어

- cc : 행 변경
- s : 커서가 있는 문자열 대체
- J : 현재 행과 아래 행 결합
- u : 이전 명령 취소
- U : 행 변경 사항 취소, 이전의 최종 행 취소
- . : 이전의 최종 명령 반복

## 텍스트 삭제 명령어

- dw : 커서에 있는 단어 삭제
- dd : 커서가 있는 라인 삭제
- D : 커서의 오른쪽 행 삭제
- `:5,10d`: 5~10번째 행 삭제

## 복사 및 이동 명령어

- yy : 커서가 위치한 줄 복사
- Y : 행 yank 또는 복사
- p : yank 되거나 삭제된 행을 현재 행 위로 삽입
- P : yank 되거나 삭제된 행을 현재 행 아래로 삽입
- `:1,2 co 3` : 1~2행을 3행 다음으로 복사
- `:4,5 m 6` : 4~5행을 6행 위로 이동

## 보관 및 종료 명령어

- `:w` : 변경사항 저장
- `:w {파일명}` : 변경사항을 입력한 파일명으로 저장
- `:wq` : 변경사항 보관 후 vi 종류. ZZ 명령어와 같음 . `:w`와 `:q` 를 연속으로 수행
- ZZ : 변경사항 보관 후 vi 종료. 임시 버퍼의 내용을 vi로 호출할 때 사용되었던 파일에 기록한 후 vi를 빠져나옴
- `:q!` : 변경사항을 보관하지 않고 종료
- q : 수정한 파일을 저장하지 않고 파일 종료
- `e!` : 수정 사항을 원상복구

- [출처 티스토리](https://iamfreeman.tistory.com/entry/vi-vim-%ED%8E%B8%EC%A7%91%EA%B8%B0-%EB%AA%85%EB%A0%B9%EC%96%B4-%EC%A0%95%EB%A6%AC-%EB%8B%A8%EC%B6%95%ED%82%A4-%EB%AA%A8%EC%9D%8C-%EB%AA%A9%EB%A1%9D)

## 라인 넘버

- `:set number` / `:set nu` : 에디터에서 라인 넘버를 표시합니다.
- `:set nonumber` / `:set nonu` : 에디터에서 라인 넘버를 표시하지 않습니다.
- `:set number!` / `:set nu!` : 에디터에서 라인 넘버 표시 상태를 토글링합니다.

- [출처 : linuxize](https://linuxize.com/post/how-to-show-line-numbers-in-vim/)
