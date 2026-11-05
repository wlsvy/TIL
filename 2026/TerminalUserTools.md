**2026 / TerminalUserTools**

# Vim & NeoVim

**Insert 모드에서 사용할 수 있는 주요 동작**

1. **문자 삭제**
   - **백스페이스**: `Backspace` 키를 사용하여 커서 앞의 문자를 삭제합니다.
   - **Ctrl + w**: 커서 앞의 단어를 삭제합니다.
   - **Ctrl + u**: 커서 앞의 전체 라인을 삭제합니다.

2. **텍스트 입력과 관련된 기능**
   - **Esc**: Insert 모드를 종료하고 Normal 모드로 돌아갑니다.
   - **Ctrl + o**: Insert 모드를 유지하면서 Normal 모드의 단일 명령을 실행할 수 있게 해줍니다. 예를 들어, `Ctrl + o`를 누른 후 `w`를 입력하면 다음 단어로 이동합니다. 명령이 끝나면 Insert 모드로 자동 복귀합니다.

3. **자동 완성**
   - **Ctrl + n**: 단어 자동 완성 기능을 사용하여 다음 후보를 제시합니다.
   - **Ctrl + p**: 단어 자동 완성 기능을 사용하여 이전 후보를 제시합니다.

4. **현재 라인 복사**
   - **Ctrl + y**: 현재 라인의 한 줄 위에 있는 텍스트를 현재 커서 위치에 복사합니다.

5. **삽입된 텍스트 취소**
   - **Ctrl + u**: 커서 위치에서 현재 라인의 앞쪽 텍스트를 모두 삭제합니다.

6. **계산기(Calculator)**
  - **Ctrl-r 누른 뒤 =** : Insert 모드에서 계산기 사용

**현재 라인에서 키워드 교체**

현재 라인에서 특정 키워드를 다른 키워드로 교체하려면 다음 명령을 사용할 수 있습니다.

    :s/old_keyword/new_keyword/g

- `:s`: substitute 명령어.
- `old_keyword`: 변경할 키워드.
- `new_keyword`: 새로 바꿀 키워드.
- `g`: 해당 라인에서 일치하는 모든 키워드를 변경 (없으면 첫 번째 키워드만 변경).

**특정 범위에서 키워드 교체**

일정 범위의 라인에서 키워드를 교체하려면 다음과 같이 할 수 있습니다.

    :10,20s/old_keyword/new_keyword/g

- `10,20`: 10번 라인부터 20번 라인까지.

**파일 전체에서 키워드 교체**

파일 전체에서 키워드를 일괄 교체하려면 다음 명령어를 사용할 수 있습니다.

    :%s/old_keyword/new_keyword/g

- `%`: 파일 전체.

**특정 문자열을 포함한 라인 제거**

- `:g/특정문자열/d`
- `:g/^$/d`: 공백 라인만 찾아서 제거
- `:1,n g/특정문자열/d` : 특정 라인 범위에서 찾기

**임시버퍼 열기**

- `:enew`

**파일 열면서 명령 실행**

파일을 열면서 set number 명령 실행

`vim +':set number' 파일이름`\
or
`vim +set\ number path/to/file`

**라인 번호로 이동하기**

- :숫자를 입력한 후 Enter를 누르면 해당 라인으로 이동합니다.
- 예: `:25`를 입력하면 25번째 라인으로 이동합니다.
- 숫자를 입력한 후 G를 사용
- 예: `25G`를 입력하면 25번째 라인으로 이동합니다.

**클립보드에 파일 복사**

- `"+y` : 클립보드에 복사
- `"+p` : 클립보드에서 붙여넣기
- `"+yy` : 클립보드에 라인 전체 복사
- `ggvG"+y` : 전체파일 클립보드에 복사

**정렬**

- `==`: 라인 정렬

### 터미널 관련 (term)

- 터미널 열기: `:term`
- 터미널 모드 -> Normal 모드 : `<C-\><C-n>`

- 터미널 shell 설정 (ex: powershell)
  - vim script : `set shell=powershell`
  - lua : `vim.o.shell = 'powershell'`

- 터미널 명령 실행 후 stdout 을 가져오기
  - ex: `reader ! git --version` : git 버전 정보를 현재 버퍼에 입력한다.

혹은 shell 경로 지정 가능

```lua
vim.o.shell = 'C:/Program Files/PowerShell/7/pwsh.exe'
-- Lua에서는 경로 구분자로 슬래시(/)를 사용하는 것이 일반적입니다.
```

### Macro

[Practical Vim 팁 요약 시리즈 - Macros !--- @n0lb00's Blog--](https://nolboo.kim/blog/2017/02/10/practical-vim/)

- `qa`: 매크로 기록 시작, 레지스터 a 에 저장된다. (참고: `:reg a`)
  - `qA` : `qa` 명령으로 매크로 기록 반복 시, 기존 레지스터에 덮어쓰지만 `qA` 의 경우 기존 애'
- `q` : 매크로 기록 종료
- `@{register}` : 특정 레지스터의 내용을 실행(`:h @`), 예를 들어 `@a` 으로 a 레지스터의 기록된 매크로 실행 가능
  - 반복 실행은 `10@a` 같은 명령어로 수행 가능

### File Encoding

- `set fileencoding?` : 현재 파일 인코딩 확인
- `set fileencoding=<encoding>` : 현재 파일의 인코딩을 설정합니다. (저장 시 적용)
  * `set fileencoding=utf-8`
  * `set fileencoding=euc-kr`

- `e ++encoding=<encoding> <filepath>` : 파일 경로를 특정 인코딩으로 열기
  * `e ++encoding=euc-kr <filepath>` : utf8 이 아닌 한글 텍스트 파일은 이걸로 열어볼 수 있다.
  * `e ++encoding=utf-8 <filepath>`

- `:set fileencodings?` : Neovim이 파일을 열 때 시도하는 인코딩 목록을 확인합니다.
- `:set fileencodings=ucs-bom,utf-8,euc-kr,latin1` : 파일 열기 시도 순서를 설정합니다.
  * 일반적으로 `ucs-bom` (BOM이 있는 UTF), `utf-8`, `euc-kr` (또는 해당 지역 인코딩), `latin1` (기본값) 순으로 설정하여 파일을 정확하게 인식하도록 합니다.
  * `fileencodings`는 파일을 *읽을 때* 사용하는 인코딩 목록이며, `fileencoding`은 현재 버퍼의 인코딩이자 파일을 *저장할 때* 사용할 인코딩입니다.

- `:w ++enc=<encoding>` : 현재 파일을 다른 인코딩으로 저장합니다.
  * `:w ++enc=euc-kr`
  * `:w ++enc=utf-8`

### File Type

- `set filetype=ps1` : 현재 파일 타입 수정
  - filetype -> ft : `set ft=ps1`

### Local CD

* `:lcd [경로]`는 Neovim의 **현재 창(window)에만** 한정하여 작업 디렉토리를 변경하는 명령어입니다.
* Neovim 전체에 영향을 주는 `:cd`와 달리, 다른 창에 열린 프로젝트에 영향을 주지 않아 여러 프로젝트를 동시에 관리할 때 안전합니다.
* 무명 버퍼(unnamed buffer)에서 경로 자동 완성을 사용할 때, 이 명령어로 프로젝트 루트를 지정하면 경로 추천이 올바르게 동작합니다.

### cursor & selection

- [Incremental selection in Neovim 0.12 : r/neovim](https://www.reddit.com/r/neovim/comments/1s9q0pi/incremental_selection_in_neovim_012/)

| 모드 | 명령어 | 설명 |
| --- | --- | --- |
| `v` | `an` | 부모 노드 선택 |
| `v` | `in` | 자식 노드 선택 |
| `v` | `]n` | 이전 노드 선택 |
| `v` | `[n` | 다음 노드 선택 |


---

#### Jumplist, Mark 등


| 모드 | 명령어 | 설명 |
| --- | --- | --- |
| n | `Ctrl` + `o` | 일반 점프 목록(Jump List)에서 이전 위치로 이동 |
| n | `Ctrl` + `i` | 일반 점프 목록(Jump List)에서 다음 위치로 이동 |
| n | `:jumps` | 전체 점프 목록 확인 (/ 검색, gg, G 등 크게 이동한 기록) |
| n | `g` + `;` | 수정 목록(Change List)에서 이전 수정 위치로 이동 |
| n | `g` + `,` | 수정 목록(Change List)에서 다음 수정 위치로 이동 |
| n | `gi` | 가장 최근 수정 위치로 바로 이동하여 입력(Insert) 모드 전환 |
| n | `:changes` | 전체 텍스트 수정(변경) 목록 확인 |
| n | `Ctrl` + `^` | 방금 전까지 편집하던 직전 파일로 토글 이동 |
| n | `%` | 현재 커서가 위치한 괄호 `()`, `{}`, `[]` 의 반대쪽 짝으로 이동 |
| n | `*` | 현재 커서가 있는 단어와 동일한 다음 단어 검색 및 이동 |
| n | `#` | 현재 커서가 있는 단어와 동일한 이전 단어 검색 및 이동 |
| n | `m` + `[a-z]` | 현재 위치에 소문자 북마크(Mark) 지정 |
| n | ``` + `[a-z]` | 지정해 둔 소문자 북마크(Mark) 위치로 정확히 이동 |

1. 점프 (Jump List)

사용자가 의도하지 않아도 Neovim이 커서의 큰 움직임을 감지해 **발자취를 자동으로 남기는 기능**입니다. Ctrl + o와 Ctrl + i를 사용하면 마치 웹 브라우저의 '뒤로 가기', '앞으로 가기'처럼 직전 행동 흐름을 그대로 따라갈 수 있습니다.

2. 마크 (Mark)

코드가 길어질 때 나중에 반드시 돌아와야 하는 중요한 위치에 핀을 꽂아두는(북마크) 기능입니다. 오직 ma, mb 처럼 수동으로 지정한 위치만 고정되어 유지되며, 대문자 마크(mA 등)를 쓰면 다른 파일 간에도 이동이 가능합니다.



### 분할된 창 관리 (Window Splits)

#### **창 분할 (Split 생성)**

| 명령어              | 설명                                             |
| ------------------- | ------------------------------------------------ |
| `:split` / `:sp`    | 가로 분할 (위/아래)                              |
| `:vsplit` / `:vsp`  | 세로 분할 (좌/우)                                |
| `<C-w>s`            | 현재 창을 가로 분할                              |
| `<C-w>v`            | 현재 창을 세로 분할                              |
| `<C-w>n`            | 새 빈 버퍼로 가로 분할                           |
| `:new`              | 새 빈 버퍼로 가로 분할                           |
| `:vnew`             | 새 빈 버퍼로 세로 분할                           |
| `:sp <file>`        | 특정 파일을 가로 분할로 열기                     |
| `:vsp <file>`       | 특정 파일을 세로 분할로 열기                     |

#### **창 간 이동**

| 명령어     | 설명                              |
| ---------- | --------------------------------- |
| `<C-w>h`   | 왼쪽 창으로 이동                  |
| `<C-w>j`   | 아래쪽 창으로 이동                |
| `<C-w>k`   | 위쪽 창으로 이동                  |
| `<C-w>l`   | 오른쪽 창으로 이동                |
| `<C-w>w`   | 다음 창으로 순환 이동             |
| `<C-w>W`   | 이전 창으로 순환 이동             |
| `<C-w>p`   | 직전(previous) 창으로 이동        |
| `<C-w>t`   | 최상단(top) 창으로 이동           |
| `<C-w>b`   | 최하단(bottom) 창으로 이동        |

#### **창 위치 재배치**

| 명령어     | 설명                                       |
| ---------- | ------------------------------------------ |
| `<C-w>H`   | 현재 창을 가장 왼쪽으로 이동               |
| `<C-w>J`   | 현재 창을 가장 아래로 이동                 |
| `<C-w>K`   | 현재 창을 가장 위로 이동                   |
| `<C-w>L`   | 현재 창을 가장 오른쪽으로 이동             |
| `<C-w>r`   | 창 순서를 시계 방향으로 회전               |
| `<C-w>R`   | 창 순서를 반시계 방향으로 회전             |
| `<C-w>x`   | 현재 창과 다음 창의 위치를 교환            |
| `<C-w>T`   | 현재 창을 새 탭으로 분리                   |

#### **창 크기 조절 (Resize / Zoom)**

| 명령어               | 설명                                          |
| -------------------- | --------------------------------------------- |
| `<C-w>_`             | 현재 창을 세로로 최대화 (높이)                |
| `<C-w>|`             | 현재 창을 가로로 최대화 (너비)                |
| `<C-w>=`             | 모든 창 크기 균등하게 복원                    |
| `<C-w>+`             | 현재 창 높이 1줄 증가                         |
| `<C-w>-`             | 현재 창 높이 1줄 감소                         |
| `<C-w>>`             | 현재 창 너비 1칸 증가                         |
| `<C-w><`             | 현재 창 너비 1칸 감소                         |
| `{N}<C-w>+/-/</>`    | N만큼 크기 조절 (예: `10<C-w>+`)              |
| `:resize {N}`        | 현재 창 높이를 N줄로 설정                     |
| `:resize +{N}`       | 높이 N줄 증가                                 |
| `:vertical resize N` | 현재 창 너비를 N칸으로 설정                   |
| `<C-w>{N}_`          | 현재 창 높이를 N줄로 고정                     |
| `<C-w>{N}|`          | 현재 창 너비를 N칸으로 고정                   |

#### **창 닫기**

| 명령어              | 설명                                              |
| ------------------- | ------------------------------------------------- |
| `<C-w>q` / `:q`     | 현재 창 닫기                                      |
| `<C-w>c` / `:close` | 현재 창 닫기 (마지막 창이면 닫히지 않음)          |
| `<C-w>o` / `:only`  | 현재 창만 남기고 나머지 닫기 (주의: 되돌릴 수 없음) |

#### **Zoom In/Out 흉내내기 (플러그인 없이)**

- `<C-w>_` + `<C-w>|` 조합: 현재 창을 최대화 → `<C-w>=`로 복원
- `<C-w>T`: 현재 창을 새 탭으로 분리하여 zoom처럼 사용, 탭 닫으면(`:tabclose`) 원래 레이아웃 복귀

#### **창 이동·최대화 단축키 (내 설정)**

Normal, Insert, Visual, Terminal 모드에서 모두 동작하도록 매핑했습니다.

| 단축키 | 환경 | 동작 | 설정 파일 |
| ------ | ---- | ---- | --------- |
| `Cmd + Shift + h/j/k/l` | macOS | 분할 창을 왼쪽/아래/위/오른쪽으로 이동합니다. | `lua/macos-settings.lua` |
| `Cmd + Shift + 방향키` | macOS | 분할 창을 해당 방향으로 이동합니다. | `lua/macos-settings.lua` |
| `Alt + Shift + h/j/k/l` | Windows | 분할 창을 왼쪽/아래/위/오른쪽으로 이동합니다. | `lua/windows-settings.lua` |
| `Alt + Shift + z` | 공통 | 현재 창을 최대화하고, 다시 누르면 원래 레이아웃으로 복원합니다. | `init.lua` |

```lua
-- macos-settings.lua (Windows는 <A-S-h> 형태의 키로 같은 동작을 매핑합니다)
vim.keymap.set({ "n", "i", "v", "t" }, "<D-S-h>", "<Cmd>wincmd h<CR>", { silent = true })

-- init.lua
vim.keymap.set({ "n", "i", "v", "t" }, "<A-S-z>", function() Snacks.zen.zoom() end, { silent = true })
```

- `<D-…>`는 Command 키 또는 super 키를 뜻합니다. Windows에서는 Win 키에 해당하며, `Win + Shift + 방향키`처럼 OS가 먼저 처리하는 조합이 있어 Windows 매핑에는 Alt를 사용했습니다.
- `Ctrl + Shift + z`는 kitty 기본 단축키(`scroll_to_prompt -1`)와 겹칩니다. 그래서 kitty 설정을 고치지 않아도 되는 `Alt + Shift + z`를 선택했습니다.
- macOS에서는 kitty의 `macos_option_as_alt yes` 설정 덕분에 `Option + Shift + z`로 입력합니다.
- `Snacks.zen.zoom()`은 같은 버퍼를 띄운 플로팅 창을 덮는 방식이므로, 아래의 레이아웃이 그대로 유지됩니다.
- `:map`에서는 Neovim이 키 이름을 정규화하여 `<D-S-h>`를 `<D-H>`로, `<A-S-z>`를 `<M-Z>`로 표시합니다.

### Neovim 파일 경로 정보

#### 1. ShaDa 파일 경로
- **Windows**:  
  `C:\Users\<사용자 이름>\AppData\Local\nvim-data\shada\main.shada`
- **macOS**:  
  `~/.local/share/nvim/shada/main.shada`

#### 2. Neovim 설정 파일(`init.vim`) 경로
- **Windows**:  
  `C:\Users\<사용자 이름>\AppData\Local\nvim\init.vim`
- **macOS**:  
  `~/.config/nvim/init.vim`

#### 키맵핑 충돌 확인 방법 (key map collision check)

> 설정한 키맵핑이 다른 플러그인이나 기존 설정과 충돌하지 않는지 확인하려면 :verbose map 명령어를 사용하여 현재 사용 중인 모든 키맵핑을 확인할 수 있습니다.
- `:verbose map <A-j>`

- `:verbose map <A-k>`

## Commands


| 명령어         | 의미 (Stands for)             | 설명                            | 예시                                        |
| -------------- | ----------------------------- | ------------------------------- | --------------------------------            |
| `:g`           | Global                        | 패턴에 매칭되는 라인 처리       | `:g/error/d` → 'error' 삭제                 |
| `:v`           | InVerse (반대의 Global)       | 패턴에 매칭되지 않는 라인 처리  | `:v/error/d` → 'error' 제외 삭제, `:v/error | \warn/d` -> 여러 키워드 지정 가능 |
| `:s`           | Substitute                    | 문자열 대체                     | `:%s/foo/bar/g`                             |
| `:d`           | Delete                        | 라인 삭제                       | `:3,5d` → 3~5라인 삭제                      |
| `:t` / `:co`   | Transfer / Copy               | 라인 복사                       | `:3t$` → 3번 라인 복사                      |
| `:m`           | Move                          | 라인 이동                       | `:3m$` → 3번 라인 이동                      |
| `:!`           | Shell Command                 | 외부 명령 실행                  | `:!ls`                                      |
| `:r`           | Read                          | 파일/명령 결과 읽어오기         | `:r other.txt`                              |
| `:normal`      | Normal Mode                   | 노멀 모드 명령 실행             | `:g/error/normal dd`                        |
| `:join`        | Join                          | 라인 합치기                     | `:3,5join`                                  |
| `:>` / `:<`    | Indent Right / Indent Left    | 들여쓰기 증가/감소              | `:%>`                                       |

- grep 명령어 응용 예시
  - `g/keyword1/ | v/keyword2/ normal echo`

---

### filename modifier

##### 1. 경로 관련
- **`:p`** - **Full Path** (절대 경로로 변환)
- **`:~`** - **Home** (홈 디렉토리를 `~`로 축약)
- **`:h`** - **Head** (디렉토리 부분만, 파일명 제외)
- **`:t`** - **Tail** (파일명만, 경로 제외)

##### 2. 파일명 관련
- **`:r`** - **Root** (확장자 제거, 루트 파일명)
- **`:e`** - **Extension** (확장자만)

##### 3. 상대 경로 관련
- **`:.`** - **Relative to current** (현재 작업 디렉토리 기준 상대 경로)
- **`:~:.`** - **Smart relative** (홈 디렉토리와 현재 디렉토리 모두 고려한 최적 경로)

##### 4. 특수 Modifier
- **`:S`** - **Shell escape** (쉘에서 안전하게 사용할 수 있도록 이스케이프)
- **`:gs?/?\\?`** - **Global substitute** (경로 구분자 변경, Windows용)

#### **Modifier 조합 예시**

| **표현식**          | **설명**                            | **예시**                              |
| ------------------- | ----------------------------------- | ------------------------------------- |
| `expand('%')`       | 현재 파일 이름 (상대 경로)          | `src/test.txt`                        |
| `expand('%:p')`     | 현재 파일의 절대 경로               | `/home/user/project/src/test.txt`     |
| `expand('%:t')`     | 파일 이름만 (경로 제외)             | `test.txt`                            |
| `expand('%:r')`     | 확장자 제거한 파일명                | `src/test`                            |
| `expand('%:e')`     | 확장자만                            | `txt`                                 |
| `expand('%:h')`     | 현재 파일의 디렉토리 경로           | `src`                                 |
| `expand('%:h:h')`   | 상위 디렉토리 경로 (중첩 가능)      | `.` (프로젝트 루트)                   |
| `expand('%:p:h')`   | 절대 경로의 디렉토리 부분           | `/home/user/project/src`              |
| `expand('%:p:t')`   | 절대 경로의 파일명 부분             | `test.txt`                            |
| `expand('%:p:r')`   | 절대 경로에서 확장자 제거           | `/home/user/project/src/test`         |
| `expand('%:t:r')`   | 파일명에서 확장자 제거              | `test`                                |
| `expand('%:~')`     | 홈 디렉토리를 ~ 로 축약             | `~/project/src/test.txt`              |
| `expand('%:.')`     | 현재 작업 디렉토리 기준 상대 경로   | `./src/test.txt`                      |
| `expand('%:~:.')`   | 최적화된 상대 경로                  | `src/test.txt` 또는 `~/project/...`   |

#### **특수 키워드**

| **키워드**          | **설명**                            | **예시**                              |
| ------------------- | ----------------------------------- | ------------------------------------- |
| `expand('<cfile>')` | 커서 아래에 있는 파일 경로          | `./myfile.txt`                        |
| `expand('<cword>')` | 커서 아래 단어 (word)               | `function_name`                       |
| `expand('<cWORD>')` | 커서 아래 WORD (공백으로 구분)      | `path/to/file.txt`                    |
| `expand('<sfile>')` | 현재 스크립트 파일 경로             | `/path/to/script.vim`                 |

- `<cmd>put = expand('%:p')<CR>`: ex) 현재 파일 절대 경로를 열린 버퍼에 입력

---

| **명령어**                 | **설명**                                                | **예시**                                                      |
| -------------------------- | ------------------------------------------------------- | ----------------------------------------------------          |
| `line('w0')`               | 현재 커서의 위치를 라인 번호로 반환.                    | `line('.')` → 현재 커서가 위치한 라인 번호를 반환.            |
| `line('w0')`               | 윈도우의 첫 번째 행 번호를 반환.                        | `line('w0')` → 창의 첫 번째 행 번호 반환.                     |
| `line('$')`                | 파일의 마지막 라인 번호를 반환.                         | `line('$')` → 파일의 마지막 라인 번호 반환.                   |
| `line('w$')`               | 윈도우의 마지막 행 번호를 반환.                         | `line('w$')` → 창의 마지막 행 번호 반환.                      |
| `line('0')`                | 첫 번째 라인 번호를 반환.                               | `line('0')` → 1번 라인 번호 반환 (0은 첫 번째 줄을 의미).     |
| `line('v')`                | 비주얼 모드에서 선택된 영역의 시작 라인 번호를 반환.    | `line('v')` → 비주얼 영역의 시작 라인 번호 반환.              |
| `line('v$')`               | 비주얼 모드에서 선택된 영역의 끝 라인 번호를 반환.      | `line('v$')` → 비주얼 영역의 끝 라인 번호 반환.               |
| `line('w')`                | 현재 윈도우의 첫 번째 라인 번호를 반환.                 | `line('w')` → 현재 창에서 첫 번째 라인 번호 반환.             |
| `line('.')`                | 현재 커서 위치의 라인 번호를 반환.                      | `line('.')` → 현재 커서가 위치한 라인 번호 반환.              |
| `line('cursor')`           | 커서가 위치한 라인 번호 반환 (일반적으로 동일).         | `line('cursor')` → 커서가 있는 라인 번호 반환.                |
| `line('search')`           | 특정 텍스트 패턴을 찾은 라인 번호 반환.                 | `line('/pattern')` → 해당 패턴이 있는 첫 번째 라인 번호 반환. |
| `line('n')`                | `n`번 째 라인 번호를 반환.                              | `line(5)` → 5번째 라인 번호 반환.                             |

---

### **Neovim의 명령줄(Command-line)에서 사용할 수 있는 단축키**

| **단축키**  | **설명**                                                  |
| <C-b>       | 커서를 줄의 시작으로 이동.                                |
| <C-e>       | 커서를 줄의 끝으로 이동.                                  |
| <C-h>       | 백스페이스, 이전 문자 삭제.                               |
| <C-w>       | 이전 단어 삭제.                                           |
| <C-u>       | 커서 왼쪽의 모든 텍스트 삭제.                             |
| <C-a>       | 현재 명령줄의 내용을 커맨드 기록(history)에서 불러오기.   |
| <C-r>       | 레지스터 내용을 삽입. (예: <C-r>0는 0 레지스터 내용 삽입) |
| <C-d>       | 명령어 자동 완성 후보를 표시.                             | 
| <C-n>       | 다음 자동 완성 후보로 이동.                               |
| <C-p>       | 이전 자동 완성 후보로 이동.                               |
| <C-f>       | 명령줄 편집 모드를 창으로 열기 (cmdwin).                  |
| <Esc>       | 명령 입력 취소.                                           |
| <Tab>       | 명령어, 파일 이름 등 자동 완성.                           |
| <Shift-Tab> | 자동 완성에서 이전 후보로 이동.                           |

### **Normal**

Neovim의 `normal` 명령어는 **Ex 모드(`:`)에서 일반 모드(Normal Mode)의 키 입력을 실행**하는 기능을 한다.

- `:normal {keys}`
- `{keys}` → 일반 모드에서 실행할 키 입력

| 명령어  | 설명                                       |
| normal  | 사용자 매핑이 적용된 상태에서 키 입력 실행 |
| normal! | 사용자 매핑을 무시하고 기본 동작을 실행    |

### **Highlight**

| 명령어               | 기능 설명                                                                                          |
| -------------------- | ------------------------------------------------------------------------------------------------   |
| `:syntax enable`     | 문법 강조 기능을 활성화합니다. 기본적인 컬러 스킴을 유지하면서 문법 강조를 활성화합니다.           |
| `:syntax on`         | 문법 강조를 강제 활성화합니다. 컬러 스킴을 무시하고 문법 강조를 적용합니다.                        |
| `:syntax off`        | 문법 강조를 비활성화합니다.                                                                        |
| `:syntax list`       | 현재 적용된 모든 문법 강조 그룹을 출력합니다.                                                      |
| `:syntax clear`      | 모든 문법 강조 설정을 제거합니다.                                                                  |
| `:syntax keyword`    | 특정 키워드를 하이라이트하는 문법 그룹을 정의합니다. 예: `:syntax keyword MyGroup TODO FIXME NOTE` |
| `:syntax match`      | 정규식을 사용하여 특정 패턴을 하이라이트합니다. 예: `:syntax match MyGroup /ERROR/`                |
| `:highlight`         | 문법 그룹에 스타일을 적용합니다. 예: `:highlight MyGroup ctermfg=red guifg=red ctermbg=yellow`     |

- `:syntax enable`과 `:syntax on`은 문법 강조를 활성화하지만, `:syntax on`은 컬러 스킴을 무시하고 강제로 문법 강조를 적용합니다.
- `:syntax list`는 현재 활성화된 문법 그룹을 확인하는 데 유용하며, `:syntax clear`로 모든 강조 설정을 제거할 수 있습니다.
- `:syntax keyword`와 `:syntax match`는 특정 단어나 패턴을 하이라이트하는 데 사용되며, `:highlight` 명령어를 통해 하이라이트된 단어에 스타일을 적용할 수 있습니다.
- ctermfg, guifg : 글자 색상 변경 (터미널/GUI)
- ctermbg, guibg : 배경 색상 변경 (터미널/GUI)

### **Search History**

| 기능                        | 단축키               |
| ------                      | ------               |
| 검색 히스토리 창 열기       | `q/`                 |
| 검색 히스토리 목록 확인     | `:history /`         |
| 검색 모드에서 히스토리 탐색 | `/` 입력 후 `Ctrl-f` |

### **Neovim 이전 커서 위치 이동 방법**

| 카테고리        | 명령               | 설명                                                                                                                                                                                                                                                                             |
| :-------------  | :---------         | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------          |
| **점프 리스트** | **`Ctrl-o`**       | 이전 점프 위치로 이동합니다. (점프: 특정 명령으로 이동하거나 파일을 열었을 때 기록되는 위치)                                                                                                                                                                                     |
|                 | **`Ctrl-i`**       | `Ctrl-o`로 뒤로 이동한 후 다시 앞으로 이동합니다.                                                                                                                                                                                                                                |
|                 | **`:jumps`**       | 현재 점프 리스트를 보여줍니다.                                                                                                                                                                                                                                                   |
| **편집 위치**   | **`g;`**           | 마지막으로 \*\*변경(편집)\*\*한 위치로 이동합니다.                                                                                                                                                                                                                               |
|                 | **`g,`**           | `g;`로 뒤로 이동한 후 다시 앞으로 이동합니다.                                                                                                                                                                                                                                    |
|                 | **`:changes`**     | 변경 리스트를 보여줍니다.                                                                                                                                                                                                                                                        |
| **마크(Marks)** | **`m{소문자}`**    | 현재 커서 위치를 `{소문자}`로 마크합니다. (예: `ma`) 파일 내에서만 유효합니다.                                                                                                                                                                                                   |
|                 | **`m{대문자}`**    | 현재 커서 위치를 `{대문자}`로 마크합니다. (예: `mA`) 파일을 닫고 다시 열어도 유지되는 **글로벌 마크**입니다.                                                                                                                                                                     |
|                 | **`` ` {마크} ``** | 해당 마크의 **정확한 위치** (줄 번호 및 열 번호)로 이동합니다. (예: `` `a` ``)                                                                                                                                                                                                   |
|                 | **`' {마크}`**     | 해당 마크의 **줄의 첫 번째 비어있지 않은 문자열**로 이동합니다. (예: `  'a ` `)`                                                                                                                                                                                                 |
|                 | **`:marks`**       | 설정된 모든 마크를 보여줍니다.                                                                                                                                                                                                                                                   |
| **파일 열 때**  | 설정 필요          | `.vimrc` 또는 `init.lua` 파일에 설정을 추가하여, 파일을 다시 열었을 때 마지막으로 편집했던 위치로 자동으로 이동하게 할 수 있습니다. \<br\> (`.vimrc` 예시 참조: `augroup remember_cursor ...`) \<br\> (`init.lua` 예시 참조: `vim.api.nvim_create_autocmd("BufReadPost", ...)`). |

### **Do 계열 명령어**

| 명령어       | 대상 범위 (Scope)               | 사용 예시             | 설명                                                                        |
| :---         | :---                            | :---                  | :---                                                                        |
| **`:windo`** | 현재 탭의 **모든 창** (Splits)  | `:windo e!`           | 현재 탭의 모든 분할 창에서 파일을 다시 로드합니다. |
| **`:tabdo`** | **모든 탭** (Tabs)              | `:tabdo w`            | 열려있는 모든 탭을 순회하며 저장합니다.                                     |
| **`:bufdo`** | (메모리에 로드된) **모든 버퍼** | `:bufdo %s/foo/bar/g` | 열려있는 모든 버퍼의 전체 내용에서 'foo'를 'bar'로 치환합니다.              |
| **`:argdo`** | `:args` 목록의 **모든 파일**    | `:argdo wq`           | Vim 시작 시 `vim *.txt`처럼 열었던 모든 파일을 저장하고 닫습니다.           |
| **`:cdo`**   | **Quickfix** 리스트의 모든 항목 | `:cdo s/error/fix/`   | Quickfix 창에 나열된 모든 위치에서 'error'를 'fix'로 바꿉니다.              |
| **`:ldo`**   | **Location** 리스트의 모든 항목 | `:ldo s/old/new/`     | Location 창(창 전용 Quickfix)의 모든 위치를 수정합니다.                     |

* 이 명령어들은 중첩해서 사용할 수 있습니다.
  * ex) **모든 탭(`:tabdo`)**의 **모든 창(`:windo`)**에서 `:e!` 실행:
    ```vim
    :tabdo windo e!
    ```

## E.T.C

### `g<C-g>` — 파일/커서 통계 보기

노멀 모드에서 `g<C-g>`를 누르면 현재 파일의 통계 정보를 상태바에 표시한다.

```
Col 1, Line 42, Word 318, Char 1842, Byte 1892 of 9801
```

| 항목   | 설명                             |
| ------ | -------------------------------- |
| Col    | 현재 커서의 열 번호              |
| Line   | 현재 커서의 라인 번호            |
| Word   | 파일 전체 단어 수                |
| Char   | 파일 전체 문자 수 (유니코드 기준)|
| Byte   | 현재 커서 위치의 바이트 오프셋   |
| of N   | 파일 전체 바이트 수              |

- 비주얼 모드에서 사용하면 **선택 영역**에 대한 통계를 보여줌 (선택된 라인 수, 단어 수, 문자 수 등)
- 파일 크기 확인, 문서 작성 중 단어 수 체크 등에 유용

## Folding (foldmethod)

| 값 | 동작 |
|----|------|
| `manual` | 직접 `zf` 로 fold 생성 |
| `indent` | 들여쓰기 기준 |
| `expr` | `foldexpr` 로 커스텀 로직 |
| `marker` | `{{{` / `}}}` 마커 기준 |
| `syntax` | 문법 그룹 기준 (느릴 수 있음) |
| `treesitter` | TS 파서 기준 (neovim 0.10+) |

**키 참고**

- `za` — 토글, `zM` / `zR` — 모두 닫기 / 열기, `zc` / `zo` — 닫기 / 열기

### 파일 타입별 추천

| 파일 | 추천 | 이유 |
|------|------|------|
| **Markdown** | `treesitter` | 헤딩 기준 fold. 없으면 `indent` fallback |
| **C#** | `treesitter` | 클래스·메서드 블록 정확하게 인식 |
| **HTML** | `indent` | TS fold가 어트리뷰트 때문에 깨지는 경우 많음 |
| **XML** | `indent` | 태그 중첩 구조가 들여쓰기와 1:1 대응 |

```lua
-- ftplugin/markdown.lua
vim.opt_local.foldmethod = "expr"
vim.opt_local.foldexpr = "v:lua.vim.treesitter.foldexpr()"
vim.opt_local.foldlevel = 99  -- 기본 펼침

-- ftplugin/cs.lua
vim.opt_local.foldmethod = "expr"
vim.opt_local.foldexpr = "v:lua.vim.treesitter.foldexpr()"
vim.opt_local.foldlevel = 2   -- 메서드까지 펼침

-- ftplugin/html.lua
vim.opt_local.foldmethod = "indent"
vim.opt_local.foldlevel = 2

-- ftplugin/xml.lua
vim.opt_local.foldmethod = "indent"
vim.opt_local.foldlevel = 1   -- 최상위 노드만 펼침
```

C# treesitter 파서 설치: `:TSInstall c_sharp`

# nvim-surround

- [nvim-surround/doc/nvim-surround.txt at main · kylechui/nvim-surround · GitHub](https://github.com/kylechui/nvim-surround/blob/main/doc/nvim-surround.txt)

제공해주신 공식 도움말 문서를 바탕으로 `nvim-surround` 플러그인의 핵심 사용 방법을 깔끔하게 정리해 드립니다.

## 1. 기본 3대 작업 (추가, 삭제, 변경)

가장 자주 사용하는 기본 기능입니다. 단축키 뒤에 올 연산 대상(Motion / Text-object)과 기호를 조합하여 사용합니다.

### ➕ 추가 (Add) : `ys` (You Surround)

* **형식:** `ys{motion}{char}`
* **Visual 모드:** 블록을 지정한 후 대문자 `S{char}`를 누르면 선택 영역을 감쌉니다.
* **Insert 모드:** `<C-g>s{char}`를 누르면 커서 위치에 추가됩니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `H*ello` | `ysiw"` | `"Hello"` | 현재 단어(`iw`)를 `"`로 감싸기 |
| `require"nvim-surroun*d"` | `ysa")` | `require("nvim-surround")` | `"`로 감싸진 영역 주변(`a"`)을 `)`로 감싸기 |
| `*x;` | `ysl'` | `'x';` | 현재 글자(`l`)를 `'`로 감싸기 |
| ` | some text | ` | (Visual) `S'` |

### ❌ 삭제 (Delete) : `ds` (Delete Surrounding)

* **형식:** `ds{char}` (커서가 대상 내부에 있으면 해당 기호를 찾아서 지웁니다)

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `({ *32 })` | `ds)` | `{ 32 }` | 가장 가까운 괄호 `)` 세트 삭제 |
| `See ':h h*elp'` | `ds'` | `See :h help` | 작은따옴표 `'` 세트 삭제 |

### 🔄 변경 (Change) : `cs` (Change Surrounding)

* **형식:** `cs{target}{replacement}`

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `'*some string'` | `cs'"` | `"some string"` | `'`를 `"`로 변경 |
| `use<*"hello">` | `cs>)` | `use("hello")` | `<>`를 `()`로 변경 |


## 2. 공백 제어 규칙 (열기 기호 vs 닫기 기호)

`()`, `{}`, `[]`, `<>`와 같이 쌍을 이루는 기호들은 **여는 기호**를 쓰느냐, **닫는 기호**를 쓰느냐에 따라 공백 처리가 달라집니다.

* **추가할 때:**
* **닫는 기호**(`}`, `)`, `]`, `>`) 사용 ➡️ 텍스트와 기호 사이에 공백 없음: `{text}`
* **여는 기호**(`{`, `(`, `[`, `<`) 사용 ➡️ 텍스트와 기호 사이에 **공백 한 칸 추가**: `{ text }`


* **삭제/변경할 때:**
* **여는 기호**를 사용해 지우거나 바꾸면 안쪽의 **공백까지 같이 지우려고 시도**합니다.
* **닫는 기호**를 사용하면 공백을 그대로 유지합니다.


## 3. 특수 대상 (HTML 태그 및 함수 호출)

일반 기호 외에 HTML 태그나 프로그래밍 언어의 함수 구조도 지원합니다.

### 🌐 HTML 태그 (`t`, `T`)

* 태그를 추가하거나 변경할 때 `t`를 입력하면 하단 프롬프트에 태그를 입력할 수 있으며, 입력 후 `<CR>`(엔터)를 누르면 적용됩니다.
* `cst`는 **태그 이름만** 변경하고 속성(Attributes)은 유지합니다.
* `csT`는 속성을 포함한 **태그 전체**를 새로 변경합니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `*div contents` | `ys$tdiv<CR>` | `<div>div contents</div>` | 줄 끝까지(`$`) `div` 태그 추가 |
| `<div>d*iv contents</div>` | `dst` | `div contents` | 감싸고 있는 HTML 태그 삭제 |
| `<h1 id="x">t*ext</h1>` | `cstdiv<CR>` | `<div id="x">text</div>` | `cst` 사용 시 `id="x"` 속성 유지 |
| `<h1 id="x">text*</h1>` | `csTdiv<CR>` | `<div>text</div>` | `csT` 사용 시 속성까지 전부 날림 |

### 󰡷 함수 호출 (`f`)

* 함수로 감싸거나 함수를 제거할 때 사용합니다. 변경(`csf`) 시에는 새로운 함수 이름만 입력하면 됩니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `arg*s` | `ysiwffunc<CR>` | `func(args)` | 단어를 `func()`로 감싸기 |
| `f*unc_name(a, b, x)` | `dsf` | `a, b, x` | 함수 호출 구조를 벗겨내고 인자만 남기기 |
| `f*unc_name(a, b, x)` | `csfnew_name<CR>` | `new_name(a, b, x)` | 함수 이름만 변경 |

---

## 4. 확장 단축키 및 편의 기능

### 줄 단위 작업 및 개행 추가

* `yss{char}`: 현재 줄 전체(앞뒤 공백 제외)를 감쌉니다.
* `yS` / `ySS` / `<C-g>S` / `cS`: 대문자 `S`가 포함된 명령어들은 대상을 감쌀 때 **새로운 줄(개행)로 분리하고 자동 들여쓰기**를 적용합니다.

### 별칭 (Aliasing) 기능

* 기본적으로 자주 쓰는 별칭이 지정되어 있습니다.
* `b` ➡️ `)` (parentheses)
* `r` ➡️ `]` (brackets)
* `B` ➡️ `}` (braces)


* **포괄 별칭 (Tabular Alias):** `q`는 따옴표 세트(`'`, `"`, ```) 전체를 대표합니다. 삭제(`dsq`)나 변경(`csq`)을 수행할 때 커서에서 가장 가까운 따옴표를 자동으로 찾아서 처리합니다. (단, 추가할 때는 모호하므로 사용할 수 없습니다)

### ✈️ 자동 점프 (Jumps)

* 현재 커서를 직접적으로 감싸고 있는 기호가 없다면, `ds`나 `cs` 실행 시 **줄 바꿈을 넘나들며 가장 가까이 있는 다음 기호(또는 이전 기호)를 자동으로 찾아가서** 작업을 수행합니다. (단, 따옴표 종류는 일반적인 vim text-object 동작과 맞추기 위해 줄 바꿈 점프를 하지 않습니다)

### 🔁 반복 및 카운트 (Repeating & Count)

* Vim의 `.` (반복 명령)과 완벽히 호환됩니다.
* **중요:** 카운트 횟수를 지정할 때는 **명령어 입력 전에 먼저 숫자를 입력**해야 합니다. (예: `3dsq` ➡️ 가장 가까운 따옴표 세트 3개를 연속으로 제거)
* 명령어 뒤에 숫자를 넣으면 Motion의 단위나 추가할 문자 자체로 인식되니 주의하세요. (예: `ysiw2` ➡️ 단어 양옆에 문자 `2`를 추가)

## 3. 특수 대상 (HTML 태그, 함수 호출, 직접 입력)

### 🌐 HTML 태그 (`t`, `T`)

* 태그를 추가하거나 변경할 때 `t`를 입력하면 하단 프롬프트에 태그를 지정할 수 있으며, 입력 후 `<CR>`(엔터)를 누르면 적용됩니다.
* `cst`는 **태그 이름만** 변경하고 기존 속성(Attributes)은 그대로 유지합니다.
* `csT`는 속성을 포함한 **태그 전체**를 새로 입력한 태그로 교체합니다.
* *참고:* 태그를 변경할 때(`cst`, `csT`)는 두 번째 교체용 기호를 입력할 필요 없이 바로 새 태그명만 치면 됩니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `*div contents` | `ys$tdiv<CR>` | `<div>div contents</div>` | 줄 끝까지(`$`) `div` 태그 추가 |
| `*h1 contents` | `ys$th1 id="x"<CR>` | `<h1 id="x">h1 contents</h1>` | 줄 끝까지 속성을 포함한 `h1` 태그 추가 |
| `<div>d*iv contents</div>` | `dst` | `div contents` | 감싸고 있는 HTML 태그 삭제 |
| `<h1 id="head">t*ext</h1>` | `cstdiv<CR>` | `<div id="head">text</div>` | `cst`: `id="head"` 속성을 유지하며 태그명만 변경 |
| `<h1 id="head">text*</h1>` | `csTdiv<CR>` | `<div>text</div>` | `csT`: 속성까지 포함하여 태그 전체를 완전 교체 |

### 󰡷 함수 호출 (`f`)

* 일반적인 프로그래밍 언어의 함수 호출 구조(`함수명(인자)`)를 다룹니다.
* *참고:* HTML 태그와 마찬가지로 함수를 변경할 때(`csf`) 두 번째 교체용 기호가 필요하지 않습니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `arg*s` | `ysiwffunc<CR>` | `func(args)` | 현재 단어를 `func()` 함수로 감싸기 |
| `f*unc_name(a, b, x)` | `dsf` | `a, b, x` | 함수 구조를 제거하고 안의 인자들만 남기기 |
| `f*unc_name(a, b, x)` | `csfnew_name<CR>` | `new_name(a, b, x)` | 기존 함수 이름을 `new_name`으로 변경 |

### ⌨️ 사용자 직접 입력 (`i`)

* 여는 기호와 닫는 기호를 사용자가 프롬프트에서 각각 직접 입력하여 감싸는 방식입니다.
* 현재 추가(`ys`) 작업만 지원하며, 삭제나 변경은 지원하지 않습니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `*inner text` | `ys$i/<CR>\` | `/inner text\` | 시작 기호로 `/`, 종료 기호로 `\`를 직접 입력해 감싸기 |



#### etc

Q. ysiwi <- 이러면 서라운드 앞/뒤 문자를 직접 지정하게 되는데, 보통 그렇지 않겠지만 ''i" 문자로 감싸고 싶을때는 어떻게 하는지?

A. 그 부분은 Neovim 프롬프트가 문자 i를 "직접 입력(insert) 기능의 트리거"로 먼저 인식하기 때문에 발생하는 현상입니다.

만약 아주 예외적인 상황으로 텍스트를 진짜 알파벳 문자 i로 감싸고 싶다면, i 명령어가 제공하는 프롬프트를 역으로 이용하시면 됩니다.

- ysiwi 입력 후, 추가 프롬프트에 각각 i 입력

## 4. 반복 및 카운트 제어 (Repeating & Count)

### 🔁 작업 반복 (`.`) 및 카운트 연산

* Vim의 `.` (마지막 명령 반복) 및 숫자 카운트와 완벽하게 결합됩니다.
* **중요 규칙:** 전체 감싸기 작업을 여러 번 반복 적용하려면 **명령어 입력 전에 카운트 숫자를 먼저 입력**해야 합니다.

| 기존 텍스트 | 명령어 | 결과 텍스트 | 설명 |
| --- | --- | --- | --- |
| `tw*o words` | `ysiw)W.` | `(two) (words)` | 단어를 `)`로 감싸고, 다음 단어 이동(`W`) 후 `.`으로 작업 반복 |
| `Pyt*hon docstring` | `3yss"` | `"""Python docstring"""` | 현재 줄 전체를 `"`로 3번 연속 감싸기 (Docstring 형태) |
| `<wrong <b*rackets>>` | `2cs>}` | `{wrong {brackets}}` | 바깥쪽 2개의 `<>` 세트를 연속으로 `{}`로 변경 |
| `"Remove `all` 'qu*otes'"` | `3dsq` | `Remove all quotes` | 커서 위치에서 가장 가까운 따옴표 세트 3개를 연속 삭제 |

### ⚠️ 카운트 위치 지정 시 주의사항

명령어 **뒤**에 오는 숫자는 연산 대상(Motion)의 범위나 추가할 문자 자체로 인식되므로 주의해야 합니다.

* `one paren, *two words` + **`ys2w)`** -> `one paren, (two words)`
* **설명:** `2w`가 명령 뒤에 붙어 '두 단어'를 지정하고 `)`로 감쌉니다.


* `*three pipes, three WORDS` + **`3ys2W|`** -> `|||three pipes, three||| WORDS`
* **설명:** 앞의 `3`은 3번 반복, `2W`는 두 단어 지정 ➡️ 두 단어를 파이프(`|`) 문자로 3번 감쌉니다.


* `two dollars, *three chars` + **`2ys3l$`** -> `two dollars, $$thr$$ee chars`
* **설명:** 앞의 `2`는 2번 반복, `3l`은 세 글자 지정 ➡️ 세 글자를 `$`로 2번 감쌉니다.


* `number ne*eds to be prefix` + **`ysiw2`** -> `number 2needs2 to be prefix`
* **설명:** 숫자 `2`가 가장 뒤에 오므로 감싸는 기호 자체를 문자 `2`로 인식하여 추가합니다.


* `<wrong <b*rackets>>` + **`cs>3`** -> `<wrong 3brackets3>`
* **설명:** 숫자 `3`이 가장 뒤에 오므로 `<>` 기호를 문자 `3`으로 변경합니다.

## **특수문자digraphs**

`Ctrl+K`를 누른 뒤, 표의 **'입력 키'**에 해당하는 두 글자를 차례로 입력하면 해당 **'문자'**가 나옵니다.

- 자주 쓰이는 기호

| 문자  | 입력 키            | 설명                        |
| :---: | :---:              | :---                        |
| **°** | `DG`               | 도 (Degree)                 |
| **·** | `.` (마침표 두 번) | 가운데 점 (middot)          |
| **…** | `..`               | 말줄임표 (ellipsis)         |
| **©** | `Co`               | 저작권 (Copyright)          |
| **®** | `Rg`               | 등록 상표 (Registered)      |
| **™** | `TM`               | 상표 (Trademark)            |
| **§** | `SE`               | 섹션 (Section)              |
| **¶** | `PI`               | 문단 (Pilcrow)              |
| **†** | `dg`               | 단검표 (Dagger)             |
| **‡** | `dd`               | 이중 단검표 (Double dagger) |
| **•** | `bu`               | 글머리 기호 (Bullet)        |
| **✓** | `OK`               | 체크 표시                   |

- 수학 및 과학 (위 첨자/아래 첨자)

| 문자  | 입력 키 | 설명                    |
| :---: | :---:   | :---                    |
| **¹** | `s1`    | 위 첨자 1 (Superscript) |
| **²** | `s2`    | 위 첨자 2               |
| **³** | `s3`    | 위 첨자 3               |
| **⁰** | `s0`    | 위 첨자 0               |
| **ⁿ** | `sn`    | 위 첨자 n               |
| **₁** | `S1`    | 아래 첨자 1 (Subscript) |
| **₂** | `S2`    | 아래 첨자 2             |
| **₃** | `S3`    | 아래 첨자 3             |
| **₀** | `S0`    | 아래 첨자 0             |

- 수학 연산자

| 문자  | 입력 키 | 설명                |
| :---: | :---:   | :---                |
| **±** | `+-`    | 더하기/빼기         |
| **×** | `*X`    | 곱하기 (Times)      |
| **÷** | `:-`    | 나누기 (Divide)     |
| **≠** | `/=`    | 같지 않음           |
| **≤** | `<=`    | 작거나 같음         |
| **≥** | `>=`    | 크거나 같음         |
| **≈** | `~=`    | 거의 같음 (Approx.) |
| **√** | `RT`    | 제곱근 (Root)       |
| **∞** | `oo`    | 무한대 (Infinity)   |
| **∑** | `SU`    | 합계 (Sum)          |
| **∫** | `IN`    | 적분 (Integral)     |

- 그리스 문자 (일부)

| 문자  | 입력 키 | 설명            |
| :---: | :---:   | :---            |
| **α** | `*a`    | 알파 (Alpha)    |
| **β** | `*b`    | 베타 (Beta)     |
| **γ** | `*g`    | 감마 (Gamma)    |
| **δ** | `*d`    | 델타 (Delta)    |
| **π** | `*p`    | 파이 (Pi)       |
| **Ω** | `*O`    | 오메가 (대문자) |
| **Δ** | `*D`    | 델타 (대문자)   |
| **Σ** | `*S`    | 시그마 (대문자) |

- 화폐 기호

| 문자  | 입력 키 | 설명           |
| :---: | :---:   | :---           |
| **€** | `Eu`    | 유로 (Euro)    |
| **£** | `Pd`    | 파운드 (Pound) |
| **¥** | `Ye`    | 엔 (Yen)       |
| **¢** | `Ct`    | 센트 (Cent)    |
| **₩** | `W=`    | 원 (Won)       |

- 화살표 및 기타 기호

| 문자  | 입력 키 | 설명               |
| :---: | :---:   | :---               |
| **→** | `->`    | 오른쪽 화살표      |
| **←** | `<-`    | 왼쪽 화살표        |
| **↑** | `ua`    | 위쪽 화살표        |
| **↓** | `da`    | 아래쪽 화살표      |
| **↔** | `<>`    | 양쪽 화살표        |
| **⇒** | `=>`    | 오른쪽 굵은 화살표 |
| **⇐** | `<=`    | 왼쪽 굵은 화살표   |
| **★** | `*?`    | 별 (채워진)        |
| **☆** | `'?`    | 별 (빈)            |
| **½** | `12`    | 1/2                |
| **¼** | `14`    | 1/4                |
| **¾** | `34`    | 3/4                |


현재 설정에서 사용 가능한 모든 Digraph 목록과 입력 키 목록 확인

```vim
:digraphs
--
:redir @a | digraphs | redir END -- 레지스터 'a' 에 복사
```

# Neovim AI 플러그인

2026년 11월 기준으로 정리했습니다. 두 플러그인은 역할이 달라 함께 사용합니다.

| 플러그인 | 역할 | 인증 |
| -------- | ---- | ---- |
| `claudecode.nvim` | 사이드바의 Claude Code에 작업을 맡기고 변경안을 검토합니다. | Claude Code 로그인을 사용하므로 구독으로 쓸 수 있습니다. |
| `minuet-ai.nvim` | 타이핑 중 커서 위치의 코드를 완성합니다. | API 키가 필요하며 구독으로는 쓸 수 없습니다. |

## **claudecode.nvim**

- [coder/claudecode.nvim: Claude Code Neovim IDE Extension](https://github.com/coder/claudecode.nvim)

Neovim이 WebSocket 서버가 되고, 사이드바의 Claude CLI가 클라이언트로 접속합니다. Claude는 독립된 프로세스이므로 버퍼 메모리를 공유하지 않고 소켓으로 통신합니다.

```text
Neovim                                      Claude CLI (사이드바 터미널)
 selection.lua, 명령어  -- selection_changed -->  WebSocket 클라이언트
 WebSocket 서버         -- at_mentioned ------->  파일은 직접 읽고 씀
 tools/, diff.lua       <-- tools/call ---------
```

### 연결 과정

1. 플러그인이 처음 로드될 때 `127.0.0.1`의 포트에 서버를 열고 인증 토큰을 만듭니다. 현재 설정은 지연 로딩이므로 `<leader>A…` 키나 `:ClaudeCode…` 명령을 처음 쓸 때 시작됩니다.
2. `~/.claude/ide/<port>.lock`에 IDE 이름, 작업 폴더, PID, 인증 토큰을 기록합니다.
3. `CLAUDE_CODE_SSE_PORT=<port>`, `ENABLE_IDE_INTEGRATION=true` 환경 변수와 함께 `claude`를 실행합니다.
4. CLI가 `x-claude-code-ide-authorization` 헤더로 토큰을 보내면 서버가 검증합니다.

### 버퍼 내용의 전달 경로

버퍼 전체를 보내는 경로는 없고, 선택 영역 텍스트와 파일 경로·줄 범위만 전달됩니다.

| 경로 | 시점 | 전달 내용 |
| ---- | ---- | --------- |
| `selection_changed` | 커서 이동, 모드 변경, 텍스트 변경 시 100ms 디바운스 후 자동으로 보냅니다. | 선택 텍스트, 파일 경로, 시작·끝 위치를 보냅니다. 선택이 없으면 텍스트는 비어 있습니다. |
| `at_mentioned` | `<leader>Ab`, `<leader>As`로 직접 보낼 때입니다. | 파일 경로와 줄 범위만 보내고 텍스트는 보내지 않습니다. |
| MCP 도구 호출 | Claude가 요청할 때입니다. | 선택 영역, 열린 파일 목록, 진단 정보 등을 돌려줍니다. |

### 주요 단축키 (내 설정)

| 단축키 | 동작 |
| ------ | ---- |
| `<leader>Ac` | Claude 터미널을 열거나 닫습니다. |
| `<leader>Af` | Claude 터미널로 포커스를 옮깁니다. |
| `<leader>Ar` / `<leader>AC` | 이전 세션을 골라 재개하거나, 마지막 세션을 이어 갑니다. |
| `<leader>Am` | 모델을 선택합니다. |
| `<leader>Ab` | 현재 파일을 컨텍스트로 추가합니다. |
| `<leader>As` | Visual 모드에서 선택한 줄 범위를 보냅니다. |
| `<leader>Aa` / `<leader>Ad` | Claude가 제안한 diff를 수락하거나 거부합니다. |

### 주의 사항

- `<leader>Ab`, `<leader>As`는 경로만 보내므로 Claude는 디스크의 내용을 볼 가능성이 높습니다. CLI 내부 동작이라 확인하지는 못했지만, 보내기 전에 `:w`를 하는 편이 안전합니다.
- Visual 모드로 선택만 해도 텍스트가 Claude CLI로 전달됩니다.
- Visual Block 선택은 정확한 사각형이 아니라 이어진 문자 범위로 근사해서 전달됩니다.

## **minuet-ai.nvim**

- [milanglacier/minuet-ai.nvim](https://github.com/milanglacier/minuet-ai.nvim)

커서 앞뒤 코드를 LLM에 보내 완성 코드를 받아 표시하는 플러그인입니다. 별도 백그라운드 프로그램 없이 `curl`로 동작합니다.

### 주요 기능

- 제공자는 Claude, OpenAI, Gemini, Codestral, Ollama, llama.cpp와 OpenAI 호환 서비스를 지원합니다.
- 표시 방식은 가상 텍스트, nvim-cmp, blink.cmp, 내장 완성, LSP 서버 방식을 지원합니다.
- 여러 줄 제안을 줄 단위로 수락할 수 있습니다.
- 응답을 스트리밍으로 표시하고, 입력에 맞춰 제안을 동기화해 불필요한 요청을 줄입니다.
- `:Minuet duet` 명령으로 다음 편집 예측을 실험 기능으로 제공합니다.

### 내 설정

설정 파일은 `lua/plugins/minuet.lua`입니다. 제공자는 `claude`, 표시 방식은 가상 텍스트입니다. 버퍼 내용이 자동으로 전송되지 않도록 자동 트리거는 꺼 두었습니다.

API 키는 `~/.zshrc`에 전용 환경 변수로 설정합니다. `ANTHROPIC_API_KEY`를 셸에 설정하면 Claude Code CLI도 그 키를 써서 구독 대신 API 요금이 청구될 수 있기 때문입니다.

```bash
export MINUET_ANTHROPIC_API_KEY="sk-ant-..."
```

Claude Haiku 5.5는 thinking이 기본으로 켜져 있습니다. 응답이 thinking 블록으로 시작하면 minuet은 텍스트를 받지 못해 제안이 표시되지 않고 `Claude returns no text on streaming` 오류가 날 수 있으므로, thinking을 꺼 두었습니다.

```lua
provider_options = {
    claude = {
        api_key = "MINUET_ANTHROPIC_API_KEY",
        optional = { thinking = { type = "disabled" } },
    },
},
```

제안이 표시되지 않을 때는 다음 순서로 확인합니다. noice.nvim이 `vim.notify`를 가로챌 수 있으므로, 로그를 `:messages`에서 보려면 임시로 재정의합니다. 재시작하면 원래대로 돌아갑니다.

```vim
:lua require('minuet').config.notify = 'debug'
:lua vim.notify = function(m) print('notify: ' .. tostring(m)) end
:verbose imap <M-]>
```

### 단축키 (Insert 모드)

macOS에서는 Alt 대신 Option을 누릅니다.

| 단축키 | 동작 |
| ------ | ---- |
| `Alt + ]` / `Alt + [` | 완성을 수동으로 요청하거나 다음·이전 제안으로 이동합니다. |
| `Alt + Shift + a` | 제안 전체를 수락합니다. |
| `Alt + a` | 한 줄만 수락합니다. |
| `Alt + e` | 제안을 닫습니다. |

### 주요 명령어

| 명령어 | 동작 |
| ------ | ---- |
| `:Minuet virtualtext toggle` | 현재 버퍼의 자동 트리거를 켜거나 끕니다. |
| `:Minuet change_provider <name>` | 제공자를 바꿉니다. |
| `:Minuet change_model` | 모델을 바꿉니다. |
| `:Minuet duet predict` / `apply` / `dismiss` | 다음 편집을 예측하고, 적용하거나 닫습니다. |

### 기본값과 비용

| 항목 | 값 |
| ---- | --- |
| Claude 기본 모델 | `claude-haiku-5-5`입니다. |
| 디바운스 / 요청 간격 | 400ms / 1000ms입니다. |
| 문맥 크기 | 16,000자이며, 약 4,000토큰입니다. |
| Haiku 5.5 단가 | 100만 토큰당 입력 $0.10, 출력 $0.50입니다(프롬프트 10만 토큰 이하). |

요청 1회의 비용은 최대 문맥 기준 약 $0.0005로 추정됩니다. 하루 100회 수동으로 쓰면 월(22일 기준) 약 $1, 자동 트리거로 하루 2,000회 쓰면 약 $22입니다. 실측이 아닌 계산치이며, thinking을 끈 설정을 기준으로 합니다.

월 사용 한도는 [Claude Console Billing](https://platform.claude.com/settings/billing)의 **Spend limits**에서 설정합니다. 이 한도는 조직 전체에 적용되므로, minuet만 제한하려면 전용 Workspace를 만들어 한도를 걸고 그 안에서 키를 발급합니다.

# Regex(정규식)

## **이스케이프 시퀀스(Escape Sequence)** 또는 사전 정의된 문자 클래스(Predefined Character Classes)

### 1. 핵심 문자 집합 (대소문자 대립 구조)

정규식에서 대문자는 소문자의 반대(NOT)를 의미하는 대칭 구조를 가집니다.

| 패턴 | 설명 | 실제 매칭되는 대상 | 대괄호 표현식으로 변환 시 |
| --- | --- | --- | --- |
| **`\s`** | **S**pace (공백) | 스페이스, 탭(`\t`), 줄바꿈(`\n`, `\r`) 등 모든 공백 문자 | `[ \t\n\r\f\v]` |
| **`\S`** | Not **S**pace | 공백이 **아닌** 모든 문자 (글자, 숫자, 기호 등) | `[^ \t\n\r\f\v]` |
| **`\d`** | **D**igit (숫자) | `0`부터 `9`까지의 모든 숫자 | `[0-9]` |
| **`\D`** | Not **D**igit | 숫자가 **아닌** 모든 문자 | `[^0-9]` |
| **`\w`** | **W**ord (단어 구성 문자) | 알파벳 대소문자, 숫자, 언더바(`_`) | `[a-zA-Z0-9_]` |
| **`\W`** | Not **W**ord | 알파벳, 숫자, `_`가 **아닌** 문자 (공백, 특수문자, 한글 등) | `[^a-zA-Z0-9_]` |

### 2. 공백 및 제어 문자 관련 패턴

`\s` 안에 포함되기도 하는, 개별 제어 문자들을 직접 지칭하는 패턴입니다.

* **`\t`** : 탭(Tab) 문자
* **`\n`** : 줄바꿈(Newline / Line Feed) 문자
* **`\r`** : 캐리지 리턴(Carriage Return) 문자
* **`\h`** : 가로 공백(Horizontal Space) ➡️ 스페이스와 탭만 포함 (줄바꿈 제외, 엔진에 따라 지원 여부 다름)
* **`\v`** : 세로 공백(Vertical Space) ➡️ 줄바꿈 관련 문자만 포함 *(※ Neovim/Vim 검색창 스크립트 모드 키워드인 `\v`와는 별개입니다)*

### 3. Neovim / Vim 전용 확장 패턴

Vim 계열 엔진은 표준 정규식 외에 자체적인 단축 패턴을 몇 가지 더 제공합니다. (Vim 기본 모드에서는 그대로 사용 가능하며, Very Magic `\v` 모드에서도 유효합니다.)

* **`\a`** : 모든 알파벳 문자 (`[a-zA-Z]`와 동일)
* **`\A`** : 알파벳이 아닌 문자
* **`\l`** : 소문자 알파벳 (`[a-z]`)
* **`\u`** : 대문자 알파벳 (`[A-Z]`)
* **`\x`** : 16진수 숫자 (`[0-9a-fA-F]`)
* **`\o`** : 8진수 숫자 (`[0-7]`)

### 💡 팁: 대괄호 `[...]` 안에서의 사용

앞서 질문하신 내용과 연결하자면, `[\s\d]`처럼 **대괄호 안에 이 기호들을 넣는 것은 가능**합니다. 이 경우 "공백이거나 또는 숫자 중 하나"라는 의미로 정상 작동합니다. 단, 수량자(`+`)나 역슬래시가 없는 일반 특수문자만 대괄호 안에서 기능을 잃을 뿐, `\s`나 `\d` 같은 이스케이프 문자 집합은 대괄호 안에서도 본래의 집합 기능을 유지합니다.

## **캡처 그룹 사용**

 **점(`.`) 뒤에 공백이 아닌 문자가 오면, 그 사이를 줄바꿈(`\r`)하되 뒤의 문자는 살려두기**

- 기본 원리: "괄호로 감싸고, 번호로 부른다"
- 저장(Capture): 정규식 내에서 기억하고 싶은 부분을 **괄호 ( )**로 감쌉니다.
- 호출(Backreference): 저장된 순서대로 \1, \2, \3... 과 같이 번호로 불러옵니다.

뒤에 오는 문자를 괄호 `\(` ... `\)` 로 감싸서 저장(캡처)한 뒤, 치환할 때 `\1`로 다시 불러오는 방식

```vim
:%s/\.\([^ ]\)/.\r\1/g
```

* **`\.`** : 점(`.`)을 찾습니다.
* **`\([^ ]\)`** : 공백이 아닌 문자를 찾아서 **1번 그룹**으로 저장합니다.
* **`.\r\1`** : 점(`.`)을 다시 쓰고 + 줄바꿈(`\r`)을 넣고 + **1번 그룹(`\1`)에 저장된 문자**를 복원합니다.

---

**예시: 순서 뒤집기 (Swap)**

`Apple: Fruit` 라는 텍스트를 `Fruit (Apple)` 로 바꾸고 싶다면?

```vim
:%s/\(\w\+\): \(\w\+\)/\2 (\1)/g
```

* **분석:**
* `\(\w\+\)` (첫 번째 그룹, `\1`): `Apple`이 저장됨
* `: ` : 그냥 매칭되는 문자 (저장 안 됨)
* `\(\w\+\)` (두 번째 그룹, `\2`): `Fruit`이 저장됨
* **바꿀 문자:** `\2 (\1)`  `Fruit (Apple)`

**그룹 번호 매기는 규칙**

괄호가 여러 개 중첩되어 있을 때, 번호는 **"여는 괄호 `(`가 나오는 순서"**대로 매겨집니다.

**예시 정규식:** `( A ( B ) C )`

1. `\1`: 가장 바깥쪽 전체 `( A ( B ) C )`
2. `\2`: 안쪽 `( B )`

**캡처 그룹의 활용 사례**

1. **날짜 형식 변경**

`2026-01-10`  `01월 10일 (2026년)`

```vim
" 찾을 때: (연도)-(월)-(일)
:%s/\(\d\{4\}\)-\(\d\{2\}\)-\(\d\{2\}\)/\2월 \3일 (\1년)/g

```

* `\1`: 2026
* `\2`: 01
* `\3`: 10

2. **중복 단어 찾기 (검색에서 활용)**

치환(`:s`)뿐만 아니라 검색(`/`)에서도 사용할 수 있습니다. "연속해서 두 번 나오는 단어"를 찾을 때 유용합니다.

```vim
" 검색 모드 (/)
/\(\w\+\) \1

```

* `\(\w\+\)`: 어떤 단어를 찾아서 저장하고,
* ` \1`: **"방금 찾은 그 단어"**가 공백 뒤에 똑같이 또 나오는지 확인합니다.
* 찾는 것: `the the`, `test test` 등

3. **(심화) 캡처하지 않는 그룹 (Non-capturing group)**

가끔 괄호로 묶어서 `or` 조건(`|`)이나 수량자(`*`, `+`)를 적용하고 싶지만, **굳이 저장해서 메모리를 쓰고 싶지는 않을 때** 사용합니다.

* **Vim 구문:** `\%( ... \)`
* **일반 정규식(PCRE):** `(?: ... )`

**예시:**
`abc` 혹은 `def`가 반복되지만 나중에 `\1`로 부를 일은 없을 때:
`\%(abc\|def\)\+` (이렇게 하면 그룹 번호가 밀리지 않아 관리가 편합니다.)

### 대화문 앞 뒤로 line spacing


```markdown
그들은 술병을 하나 들고 왔으며, 그들의 관심은 한 잔 하면서 긴장을 푸는 것 뿐이었다."정말 대단해." 하고 아델이 입을 열었다. 그의 넓다란 얼굴은 피로로 인해 주름져 보였다. 그는 술잔 속의 얼음을 무심히 쳐다보며 유리막대로 잔을 저었다. "에너지를 영원히 공짜로 사용할 수 있다니. 지구를 몽땅 녹여서 쇳물로 만들더라도 거기에 사용될 에너지를 아까와할 필요가 없쟎아. 이젠 공짜로 에너지를 영원히 영원히 또 영원히 쓸 수 있겠지."루포브는 머리를 옆으로 비스듬히 기울였다. 그에게는 반대하고 싶을 때면 즉시 핑겟거리를 생각해내는 재주가 있었고, 또 지금은 그가 얼음과 잔을 가지러 다녀와야 했었기 때문에 약간 심술이 나 있었다. "영원한 건 아니지." 하고 그가 말했다."이런, 제기랄, 거의 영원하다고 할 수 있쟎아. 태양이 없어질 때 까지는 말야."
```

정규식을 사용해서 대화문 앞뒤에 줄 간격을 추가하는 vim 명령어를 제공하겠습니다.

````vim
:s/\([^"]\)"\([^"]*\)"/\1\r\r"\2"\r/g
````

**더 정확한 패턴 (문장 끝 구두점 고려)**

````vim
:s/\([.!?]\)"/\1"\r\r/g | s/\([^"]\)"/\1\r\r"/g
````

### **온점(.) 및 따옴표("' ) 기준 줄 바꿈**

```vim
-- "둥근 닫는 따옴표 뒤에 공백 없이 글자가 바로 붙어 있다면, 따옴표 뒤에 줄바꿈과 공백을 넣어 떨어뜨려라"
s/\([”’]\)\(\S\+\)/\1\r \2/g
-- "문장 부호(`.`, `!`, `?`) 뒤에 따옴표나 공백 없이 곧바로 다음 문장이 이어지면, 문장 부호 뒤에서 줄바꿈을 해라"
s/\([.!?]\)\([^”’\s]\)/\1\r \2/g
```

#### 🔍 패턴 매칭 부분 (`\([”’]\)\(\S\+\)`)

* **`\([”’]\)` (그룹 1):** 대괄호 안의 둥근 따옴표 `”` 또는 `’` 중 하나를 찾고, 이를 첫 번째 그룹으로 기억합니다.
* **`\(\S\+\)` (그룹 2):** 공백이 아닌 문자(`\S`)가 1회 이상 연속(`\+`)되는 덩어리를 찾고, 이를 두 번째 그룹으로 기억합니다.


#### 🔍 패턴 매칭 부분 (`\([.!?]\)\([^”’\s]\)`)

* **`\([.!?]\)` (그룹 1):** 온점(`.`), 느낌표(`!`), 물음표(`?`) 중 하나를 찾고, 이를 첫 번째 그룹으로 기억합니다.
* **`\([^”’\s]\)` (그룹 2):** 아까 본 **부정 문자 클래스**입니다. 둥근 따옴표(`”`, `’`)와 공백(`\s`)이 **아닌** 문자 딱 1글자를 찾아서 두 번째 그룹으로 기억합니다.
* *이유:* `.` 뒤에 바로 `”`가 오는 경우(예: `문장 끝.`”)는 정상적인 문장 마무char이므로 줄을 바꾸지 않기 위해 필터링하는 것입니다.

### 곧은 따옴표(Straight Quotes: `"`, `'`), 둥근 따옴표(Curly Quotes / Smart Quotes: `“`, `”`, `‘`, `’`)

문자 `“`와 `‘`는 일반적인 프로그래밍에서 사용하는 곧은 따옴표(Straight Quotes: `"`, `'`)가 아니라, 주로 문서 작성이나 출판에 사용되는 둥근 따옴표(Curly Quotes / Smart Quotes)입니다.

### 치환범위 지정 메타문자 (`\zs`, `\ze`)

Neovim(Vim)에서 특정 비공백 문자열(`\S+`)을 조건에 포함하되, 실제 치환은 그 앞부분만 수행하려면 **긍정형 전방 탐색(Positive Lookahead)** 또는 **치환 범위 지정 메타 문자(`\zs`)**를 사용합니다.

Vim 전용 메타 문자 `\zs`는 검색 패턴의 시작 지점을 강제로 재설정합니다. `\zs` 이전의 패턴은 매칭 조건에는 포함되지만, 실제 치환 대상에서는 제외됩니다.

```vim
:%s/찾을문자\ze\S+/바꿀문자/g
```

* **`찾을문자`**: 실제 바뀔 부분입니다.
* **`\ze`**: 이 기호 뒤에 오는 패턴은 매칭 여부만 확인하고 치환에서는 제외합니다 (Variable End).
* **`\S+`**: 공백이 아닌 문자가 하나 이상 붙어 있는 경우를 조건으로 겁니다.

**예시:** `apple` 뒤에 공백 없이 글자가 붙어 있을 때만 `apple`을 `orange`로 변경

```vim
:%s/apple\ze\S+/orange/g
```
> `applepie` -> `orangepie` (치환됨)
> `apple pie` -> `apple pie` (뒤에 공백이 있어 치환 안 됨)

#### 2. 캡처 그룹(Capture Group) 사용

표준적인 정규표현식 방식인 그룹화(`\(\)`)를 사용하여 뒷부분을 보존하는 방법입니다.

```vim
:%s/\(찾을문자\)\(\S\+\)/\1바꿀문자/g
```
* **`\(\S\+\)`**: 뒤에 오는 비공백 문자열을 그룹으로 묶습니다.
* **`\1`**: 첫 번째 그룹(찾을 문자)을 다시 쓰고 그 뒤에 내용을 덧붙이거나, 필요한 부분만 선택적으로 재조합합니다.
* 사실 위 케이스는 뒤를 보존해야 하므로 `:%s/찾을문자\(\S\+\)/바꿀문자\1/g` 형식이 더 적합합니다.

| 기호      | 설명                                      |
| :---      | :---                                      |
| **`\S+`** | 공백이나 줄바꿈이 아닌 하나 이상의 문자열 |
| **`\zs`** | 치환(Match) 시작 지점 설정 (Zero Start)   |
| **`\ze`** | 치환(Match) 종료 지점 설정 (Zero End)     |



# tmux

tmux (Terminal Multiplexer): 하나의 터미널 창에서 여러 세션·윈도우·패널을 동시에 운용할 수 있게 해주는 도구입니다.

**핵심 장점**

- SSH 접속이 끊겨도 세션이 유지됨 (백그라운드에서 계속 실행)
- 하나의 터미널을 여러 창으로 분할 가능
- 작업 세션을 저장하고 재접속 가능

구조 개념

```
Session           ← 최상위 단위 (프로젝트 단위로 구분)
 └── Window        ← 탭 개념 (작업 종류별 구분)
      └── Pane     ← 화면 분할 단위
```

**Prefix 키**

tmux의 모든 단축키는 Prefix 키 입력 후 명령어를 누릅니다.

* 기본 Prefix: **Ctrl + b**

## **세션 (Session)**

| 명령어 | 설명 |
| --- | --- |
| `tmux` | 새 세션을 시작합니다. |
| `tmux new -s 이름` | 이름을 지정해서 새 세션을 시작합니다. |
| `tmux ls` | 세션 목록을 확인합니다. |
| `tmux attach -t 이름` | 세션에 재접속합니다. |
| `tmux kill-session -t 이름` | 세션을 종료합니다. |
| `Prefix + d` | 세션에서 detach합니다. 세션은 유지됩니다. |
| `Prefix + $` | 세션 이름을 변경합니다. |
| `Prefix + s` | 세션 목록을 인터랙티브하게 봅니다. |

## **윈도우 (Window)**

| 단축키 | 설명 |
| --- | --- |
| `Prefix + c` | 새 윈도우를 생성합니다. |
| `Prefix + ,` | 윈도우 이름을 변경합니다. |
| `Prefix + w` | 윈도우 목록을 봅니다. |
| `Prefix + n` | 다음 윈도우로 이동합니다. |
| `Prefix + p` | 이전 윈도우로 이동합니다. |
| `Prefix + 숫자` | 해당 번호의 윈도우로 이동합니다. |
| `Prefix + &` | 현재 윈도우를 닫습니다. |

## **패널 (Pane)**

| 단축키 | 설명 |
| --- | --- |
| `Prefix + %` | 좌우로 분할합니다. |
| `Prefix + "` | 상하로 분할합니다. |
| `Prefix + 방향키` | 패널 간에 이동합니다. |
| `Prefix + z` | 현재 패널의 전체 화면을 켜고 끕니다. |
| `Prefix + x` | 현재 패널을 닫습니다. |
| `Prefix + {` / `}` | 패널 위치를 앞뒤로 이동합니다. |
| `Prefix + q` | 패널 번호를 표시합니다. |
| `Prefix + Alt + 방향키` | 패널 크기를 조절합니다. |

## **복사 모드 (스크롤)**

| 단축키 | 설명 |
| --- | --- |
| `Prefix + [` | 복사 모드로 들어갑니다. 이 모드에서 스크롤할 수 있습니다. |
| `방향키` / `PgUp` / `PgDn` | 스크롤합니다. |
| `q` | 복사 모드를 종료합니다. |

기본 설정 파일 예시 (~/.tmux.conf)

## Prefix를 Ctrl+a로 변경 (선호도에 따라)
unbind C-b
set -g prefix C-a
bind C-a send-prefix

## 마우스 활성화
set -g mouse on

## 윈도우 번호 1부터 시작
set -g base-index 1

## 256색 지원
set -g default-terminal "screen-256color"

## 상태바 색상
set -g status-bg colour235
set -g status-fg colour136

설정 변경 후 적용: Prefix + : → source-file ~/.tmux.conf


# kitty

kitty 0.50.0(macOS) 기준으로 정리했습니다. 설정 파일은 `~/.config/kitty/kitty.conf`입니다.

kitty에서 "window"는 탭 안의 분할 창을 뜻하고, macOS 창은 "OS window"라고 부릅니다.

## **내 설정 (kitty.conf)**

```conf
# mac: ~/.config/kitty/kitty.conf

allow_remote_control yes
macos_option_as_alt yes

enabled_layouts splits,stack

map cmd+d launch --location=vsplit --cwd=current
map cmd+e launch --location=hsplit --cwd=current

map cmd+alt+left  neighboring_window left
map cmd+alt+right neighboring_window right
map cmd+alt+up    neighboring_window up
map cmd+alt+down  neighboring_window down

map cmd+shift+z toggle_layout stack
map cmd+shift+p command_palette
```

| 단축키 | 기능 | 설명 |
| --- | --- | --- |
| `Cmd + d` | `launch --location=vsplit` | 현재 경로에서 좌우로 분할합니다. |
| `Cmd + e` | `launch --location=hsplit` | 현재 경로에서 상하로 분할합니다. |
| `Cmd + Alt + 방향키` | `neighboring_window` | 해당 방향의 분할 창으로 이동합니다. |
| `Cmd + Shift + z` | `toggle_layout stack` | 현재 창의 전체 화면 확대(stack 레이아웃)를 켜고 끕니다. |
| `Cmd + Shift + p` | `command_palette` | 명령 팔레트를 엽니다. |

| 옵션 | 설명 |
| --- | --- |
| `enabled_layouts splits,stack` | 두 레이아웃만 사용하며, 먼저 적은 splits가 기본 레이아웃이 됩니다. |
| `macos_option_as_alt yes` | Option 키를 Alt로 사용합니다. 이 옵션은 설정 다시 읽기로 반영되지 않으므로 kitty를 재시작해야 합니다. |
| `allow_remote_control yes` | 다른 프로그램이 창 내용 읽기와 텍스트 입력까지 포함해 kitty를 제어할 수 있습니다. SSH 연결을 통해서도 동작하므로 주의해야 합니다. |

## **기본 단축키 (macOS)**

**kitty_mod**

`kitty_mod`는 기본 단축키에 쓰이는 수정키의 별칭이며, 기본값은 `Ctrl + Shift`입니다. 공식 문서와 `kitty.conf`의 `kitty_mod+t`는 `Ctrl + Shift + t`를 뜻합니다. 아래 표의 `Ctrl + Shift` 조합도 대부분 이 별칭으로 정의되어 있습니다.

```conf
# 기본값입니다. 값을 바꾸면 kitty_mod를 사용하는 기본 단축키가 모두 함께 바뀝니다.
kitty_mod ctrl+shift

# 직접 정의하는 단축키에도 사용할 수 있습니다.
map kitty_mod+t new_tab
```

`Cmd` 조합은 `kitty_mod`와 별개로 정의된 macOS 전용 기본 단축키이므로, `kitty_mod` 값을 바꿔도 영향을 받지 않습니다.

**창 (분할)**

| 단축키 | 기능 | 설명 |
| --- | --- | --- |
| `Cmd + Enter` | `new_window` | 현재 레이아웃에 새 창을 엽니다. |
| `Cmd + Shift + d` | `close_window` | 현재 분할 창만 닫습니다. |
| `Cmd + 1~9` | `first_window` ~ `ninth_window` | N번째 창으로 이동합니다. 탭 이동이 아닙니다. |
| `Cmd + r` | `start_resizing_window` | 창 크기 조절 모드로 들어갑니다. |
| `Ctrl + Shift + F7` | `focus_visible_window` | 창 번호를 표시하고, 선택한 창으로 이동합니다. 창이 2개면 번호 없이 바로 이동합니다. |
| `Ctrl + Shift + F8` | `swap_with_window` | 창 번호를 표시하고, 선택한 창과 위치를 바꿉니다. |
| `Ctrl + Shift + l` | `next_layout` | 다음 레이아웃으로 전환합니다. |

**탭 / OS 창**

| 단축키 | 기능 | 설명 |
| --- | --- | --- |
| `Cmd + t` | `new_tab` | 새 탭을 엽니다. |
| `Cmd + w` | `close_tab` | 탭 전체를 닫습니다. 탭 안의 분할 창도 모두 닫힙니다. |
| `Cmd + Shift + ]` / `[` | `next_tab` / `previous_tab` | 다음 탭 / 이전 탭으로 이동합니다. |
| `Cmd + Shift + i` | `set_tab_title` | 탭 제목을 변경합니다. |
| `Cmd + n` | `new_os_window` | 새 OS 창을 엽니다. |
| `Cmd + Shift + w` | `close_os_window` | OS 창을 닫습니다. |
| `Ctrl + Cmd + f` | `toggle_fullscreen` | 전체 화면을 켜고 끕니다. |

**스크롤 / 검색**

| 단축키 | 기능 | 설명 |
| --- | --- | --- |
| `Cmd + 위/아래` | `scroll_line_up` / `scroll_line_down` | 한 줄씩 스크롤합니다. |
| `Cmd + PgUp/PgDn` | `scroll_page_up` / `scroll_page_down` | 한 페이지씩 스크롤합니다. |
| `Cmd + Home/End` | `scroll_home` / `scroll_end` | 스크롤백의 맨 위 / 맨 아래로 이동합니다. |
| `Cmd + f` | `search_scrollback` | 스크롤백을 검색합니다. |
| `Ctrl + Shift + h` | `show_scrollback` | 스크롤백을 페이저로 엽니다. |
| `Ctrl + Shift + g` | `show_last_command_output` | 마지막 명령의 출력을 페이저로 엽니다. |
| `Ctrl + Shift + z` / `x` | `scroll_to_prompt -1` / `scroll_to_prompt 1` | 이전 / 다음 프롬프트로 이동합니다. 셸 통합이 필요합니다. |

**화면 / 힌트 / 설정**

| 단축키 | 기능 | 설명 |
| --- | --- | --- |
| `Cmd + k` | `clear_terminal to_cursor active` | 커서까지의 화면을 지웁니다. |
| `Cmd + Option + k` | `clear_terminal scrollback active` | 스크롤백을 지웁니다. |
| `Cmd + Option + r` | `clear_terminal reset active` | 터미널을 초기화합니다. |
| `Cmd + +` / `-` / `0` | `change_font_size` | 글꼴 크기를 키우거나 줄이거나 원래대로 되돌립니다. |
| `Ctrl + Shift + e` | `open_url_with_hints` | 화면의 URL을 힌트로 선택해 엽니다. |
| `Ctrl + Shift + p` 후 `f` | `kitten hints --type path --program -` | 화면의 파일 경로를 힌트로 선택해 프롬프트에 입력합니다. |
| `Ctrl + Shift + u` | `kitten unicode_input` | 유니코드 문자를 입력합니다. |
| `Cmd + ,` | `edit_config_file` | 설정 파일을 편집합니다. |
| `Ctrl + Cmd + ,` | `load_config_file` | 설정 파일을 다시 읽습니다. |
| `Cmd + Option + ,` | `debug_config` | 현재 적용된 설정을 확인합니다. |

## **창 크기 조절 모드**

`Cmd + r`로 들어가며, 화면에 조작 안내가 표시됩니다. 실제로는 레이아웃의 행이나 열을 조절하므로, 같은 행이나 열에 있는 다른 창의 크기도 함께 바뀝니다. 창 경계를 마우스로 드래그해도 조절할 수 있습니다.

| 키 | 기능 | 설명 |
| --- | --- | --- |
| `W` / `N` | Wider / Narrower | 창을 넓히거나 좁힙니다. |
| `T` / `S` | Taller / Shorter | 창을 높이거나 낮춥니다. |
| `Alt` + 위 키 | Fractional resize | 남은 조절 단계의 일정 비율(기본 1/3)만큼 한 번에 움직입니다. |
| `Ctrl` + 위 키 | Double step | 조절 폭을 2배로 늘립니다. |
| `R` | Restore original sizes | 원래 크기로 되돌립니다. |
| `1` / `2` | Window strategy / Edge strategy | 창 단위 조절(Window)과 경계 단위 조절(Edge) 방식을 선택합니다. |
| `M` | Fractional modifier | 비율 조절에 쓰는 수정키를 Alt와 Shift 중에서 전환합니다. |
| `F` | Fraction presets | 비율 조절의 비율을 선택합니다. |

## **스크롤백 (Scrollback)**

스크롤백은 화면 위로 밀려난 출력을 터미널이 메모리에 보관해 두는 기록입니다. 긴 명령의 앞부분 출력을 다시 볼 수 있는 것도 이 기록 덕분입니다.

```conf
# 보관할 줄 수이며, 기본값은 2000입니다.
scrollback_lines 2000
```

값을 아주 크게 잡으면 성능이 떨어지고 RAM을 많이 사용합니다. 스크롤과 검색 단축키는 위의 **스크롤 / 검색** 표에 정리했습니다.

## **창 번호 표시**

`Ctrl + Shift + F7`을 누르면 각 창 위에 번호나 글자가 표시되고, 해당 키를 누르면 그 창으로 이동합니다. `Ctrl + Shift + F8`도 같은 방식으로 창 위치를 바꿉니다.

- 창이 2개면 번호를 표시하지 않고 바로 다른 창으로 이동합니다.
- 표시되는 문자는 `visual_window_select_characters` 옵션으로 바꿀 수 있습니다.
- `kitty @ ls`의 `id`는 내부 식별자이므로 `Cmd + 1~9`의 순번과 다릅니다.

## **주요 명령어**

| 명령어 | 설명 |
| --- | --- |
| `kitten themes` | 테마를 미리 보고 변경합니다. `kitty.conf`의 `BEGIN_KITTY_THEME` 블록과 `current-theme.conf`가 이 결과물입니다. |
| `kitten icat image.png` | 터미널에 이미지를 표시합니다. |
| `kitten diff a.txt b.txt` | 두 파일의 차이를 나란히 표시합니다. |
| `kitten ssh user@host` | 원격 서버에 셸 통합과 터미널 정보를 함께 전달해 접속합니다. |
| `kitty @ ls` | 원격 제어로 창과 탭 구조를 JSON으로 출력합니다. `allow_remote_control` 설정이 필요합니다. |
| `kitty @ set-font-size 14` | 원격 제어로 글꼴 크기를 변경합니다. |
