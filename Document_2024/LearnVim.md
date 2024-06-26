# Learn Vim

**Modes in Vim**

![](img/2024-05-29-21-54-51.png)

![](img/2024-05-29-21-55-46.png)

**Word(W)**

- w (word) : jump to the beginning of the next word
- b (back) : jump to the beginning of a word backwards
- e (end) : jump to the end of a word
- ge : jump to the end of a word backwards

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

**파일 열면서 명령 실행**

파일을 열면서 set number 명령 실행

`vim +':set number' 파일이름`\
or
`vim +set\ number path/to/file`

**Cheat Sheet**

![](img.2024-06-01-03-59-07.png)

- [Vim Cheat Sheet](https://vim.rtorr.com/)

- Global

    **:h[elp] keyword - open help for keyword**
    :sav[eas] file - save file as
    :clo[se] - close current pane
    **:ter[minal] - open a terminal window**
    K - open man page for word under the cursor

- Cursor Movement

   h - move cursor left
   j - move cursor down
   k - move cursor up
   l - move cursor right
   gj - move cursor down (multi-line text)
   gk - move cursor up (multi-line text)
   H - move to top of screen
   M - move to middle of screen
   L - move to bottom of screen
   **w - jump forwards to the start of a word**
   W - jump forwards to the start of a word (words can contain punctuation)
   **e - jump forwards to the end of a word**
   E - jump forwards to the end of a word (words can contain punctuation)
   b - jump backwards to the start of a word
   B - jump backwards to the start of a word (words can contain punctuation)
   ge - jump backwards to the end of a word
   gE - jump backwards to the end of a word (words can contain punctuation)
   % - move cursor to matching character (default supported pairs: '()', '{}', '[]' - use :h matchpairs in vim for more info)
   **0 - jump to the start of the line**
   **^ - jump to the first non-blank character of the line**
   **$ - jump to the end of the line**
   g_ - jump to the last non-blank character of the line
   **gg - go to the first line of the document**
   **G - go to the last line of the document**
   5gg or 5G - go to line 5
   gd - move to local declaration
   gD - move to global declaration
   **fx - jump to next occurrence of character x**
   **tx - jump to before next occurrence of character x**
   Fx - jump to the previous occurrence of character x
   Tx - jump to after previous occurrence of character x
   **; - repeat previous f, t, F or T movement**
   , - repeat previous f, t, F or T movement, backwards
   } - jump to next paragraph (or function/block, when editing code)
   { - jump to previous paragraph (or function/block, when editing code)
   zz - center cursor on screen
   zt - position cursor on top of the screen
   zb - position cursor on bottom of the screen
   Ctrl + e - move screen down one line (without moving cursor)
   Ctrl + y - move screen up one line (without moving cursor)
   Ctrl + b - move screen up one page (cursor to last line)
   Ctrl + f - move screen down one page (cursor to first line)
   Ctrl + d - move cursor and screen down 1/2 page
   Ctrl + u - move cursor and screen up 1/2 page
   Tip Prefix a cursor movement command with a number to repeat it. For example, 4j moves down 4 lines.
   Insert mode - inserting/appending text
   **i - insert before the cursor**
   **I - insert at the beginning of the line**
   **a - insert (append) after the cursor**
   **A - insert (append) at the end of the line**
   **o - append (open) a new line below the current line**
   **O - append (open) a new line above the current line**
   **ea - insert (append) at the end of the word**
   Ctrl + h - delete the character before the cursor during insert mode
   Ctrl + w - delete word before the cursor during insert mode
   Ctrl + j - add a line break at the cursor poisition during insert mode
   Ctrl + t - indent (move right) line one shiftwidth during insert mode
   Ctrl + d - de-indent (move left) line one shiftwidth during insert mode
   Ctrl + n - insert (auto-complete) next match before the cursor during insert mode
   Ctrl + p - insert (auto-complete) previous match before the cursor during insert mode
   Ctrl + rx - insert the contents of register x
   Ctrl + ox - Temporarily enter normal mode to issue one normal-mode command x.
   Esc or Ctrl + c - exit insert mode

- Editing

    r - replace a single character.
    R - replace more than one character, until ESC is pressed.
    J - join line below to the current one with one space in between
    gJ - join line below to the current one without space in between
    gwip - reflow paragraph
    g~ - switch case up to motion
    gu - change to lowercase up to motion
    gU - change to uppercase up to motion
    cc - change (replace) entire line
    c$ or C - change (replace) to the end of the line
    ciw - change (replace) entire word
    cw or ce - change (replace) to the end of the word
    **s - delete character and substitute text (same as cl)**
    **S - delete line and substitute text (same as cc)**
    xp - transpose two letters (delete and paste)
    **u - undo**
    U - restore (undo) last changed line
    **Ctrl + r - redo**
    **. - repeat last command**
    Marking text (visual mode)
    v - start visual mode, mark lines, then do a command (like y-yank)
    V - start linewise visual mode
    o - move to other end of marked area
    Ctrl + v - start visual block mode
    O - move to other corner of block
    aw - mark a word
    ab - a block with ()
    aB - a block with {}
    at - a block with <> tags
    ib - inner block with ()
    iB - inner block with {}
    it - inner block with <> tags
    Esc or Ctrl + c - exit visual mode

- Visual Commands

	> - shift text right
	< - shift text left
	y - yank (copy) marked text
	d - delete marked text
	~ - switch case
	u - change marked text to lowercase
	U - change marked text to *uppercase*

- Cut and Paste

	**yy - yank (copy) a line**
	2yy - yank (copy) 2 lines
	yw - yank (copy) the characters of the word from the cursor position to the start of the next word
	yiw - yank (copy) word under the cursor
	yaw - yank (copy) word under the cursor and the space after or before it
	y$ or Y - yank (copy) to end of line
	**p - put (paste) the clipboard after cursor**
	P - put (paste) before cursor
	gp - put (paste) the clipboard after cursor and leave cursor after the new text
	gP - put (paste) before cursor and leave cursor after the new text
	**dd - delete (cut) a line**
	2dd - delete (cut) 2 lines
	dw - delete (cut) the characters of the word from the cursor position to the start of the next word
	diw - delete (cut) word under the cursor
	daw - delete (cut) word under the cursor and the space after or before it
	**:3,5d - delete lines starting from 3 to 5**
	**:g/{pattern}/d - delete all lines containing pattern**
	**:g!/{pattern}/d - delete all lines not containing pattern**
	**d$ or D - delete (cut) to the end of the line**
	**x - delete (cut) character**

- Search And Replace

	**/pattern - search for pattern**
	**?pattern - search backward for pattern**
	\vpattern - 'very magic' pattern: non-alphanumeric characters are interpreted as special regex symbols (no escaping needed)
	**n - repeat search in same direction**
	N - repeat search in opposite direction
	**:%s/old/new/g - replace all old with new throughout file**
	**:%s/old/new/gc - replace all old with new throughout file with confirmations**
	:noh[lsearch] - remove highlighting of search matches
