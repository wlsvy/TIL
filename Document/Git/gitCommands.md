### 특정 브랜치만 git Clone

클론 시에 해당 리포지토리에 브랜치가 많다면 시간이 오래 걸릴 수 있는데, 이런 경우에 아래처럼 단일 브랜치만 먼저 내려받을 수 있다.

```
git clone -b {branch_name} --single-branch {저장소 URL}
ex) git clone -b javajigi --single-branch https://github.com/javajigi/java-racingcar
```

혹은 depth 옵션 사용. 축약된 히스토리를 먼저 받아온다. clone 중에 네트워크가 끊기거나 하면 clone 과정이 전부 리셋되기 때문에 저장소 사이즈가 클 경우 축약 버전을 먼저 받는 방법이 유효할 수 있다.

> git clone --branch javajigi --depth 1 https://github.com/javajigi/java-racingcar


위와 같이 실행하면 java-racingcar의 javajigi branch만 clone할 수 있다.

- [출처 : slipp](https://www.slipp.net/questions/577)

> git clone -b <branch name> --single-branch <github url> <target directory>
  
위와 같이 clone한 후 새로운 브랜치를 추가하고 싶은 경우가 있으면 다음과 같이 새로운 브랜치를 추가할 수 있다.

> git remote set-branches --add origin [remote-branch] <br/>
> git fetch origin [remote-branch]:[local-branch]

- [출처 : slipp](https://www.slipp.net/questions/605)

- git clone/fetch 시에 --depth 옵션 : 원격 저장소에서 브랜치 헤드 커밋 지점으로부터 몇 개의 커밋을 불러올 것인지 지정합니다.(중간에 머지 커밋이 있는 경우, 정확히 지정한 N 개의 커밋만 불러온다고 보장하진 않습니다.)
  - 대신 이 경우에 압축된 히스토리를 받아오기 때문에(shallow repository라 합니다), 이 상태에서 커밋을 푸시하거나 추가 pull 을 받을 때 시스템 거부를 당할 수 있습니다.
  - 이 때는 `git fetch --unshallow` 혹은 `git pull --allow-unrelated-histories` 로 완전한 히스토리를 다시 받아올 수 있다.
  - [참고: 티스토리](https://bitlog.tistory.com/66), [stackoverflow: git-refusing-to-merge-unrelated-histories-on-rebase](https://stackoverflow.com/questions/37937984/git-refusing-to-merge-unrelated-histories-on-rebase)

### git partial clone

The "Partial Clone" feature is a performance optimization for Git that allows Git to function without having a complete copy of the repository. The goal of this work is to allow Git better handle extremely large repositories.

During clone and fetch operations, Git downloads the complete contents and history of the repository. This includes all commits, trees, and blobs for the complete life of the repository. For extremely large repositories, clones can take hours (or days) and consume 100+GiB of disk space.

Often in these repositories there are many blobs and trees that the user does not need such as:

- files outside of the user’s work area in the tree. For example, in a repository with 500K directories and 3.5M files in every commit, we can avoid downloading many objects if the user only needs a narrow "cone" of the source tree.
- large binary assets. For example, in a repository where large build artifacts are checked into the tree, we can avoid downloading all previous versions of these non-mergeable binary assets and only download versions that are actually referenced.
- 즉 과거에 덩치 큰 파일이 추가되었다가 삭제된 경우, 이런 과거 파일을 반드시 받아야 할 필요가 있는 것은 아닐 텐데 해당 파일을 제외하고 clone을 수행하겠다는 것

Partial clone allows us to avoid downloading such unneeded objects in advance during clone and fetch operations and thereby reduce download times and disk usage. Missing objects can later be "demand fetched" if/when needed.

--filter=<filter-spec>

- Use the partial clone feature and request that the server sends a subset of reachable objects according to a given object filter. When using `--filter`, the supplied `<filter-spec>` is used for the partial clone filter. For example, --filter=blob:none will filter out all blobs (file contents) until needed by Git. Also, `--filter=blob:limit=<size>` will filter out all blobs of size at least `<size>`.

> git clone --filter=blob:none https://github.com/wlsvy/TIL.git

- 출처 : [git : partial clone](https://git-scm.com/docs/partial-clone), [git clone](https://git-scm.com/docs/git-clone)

### 트랙킹 브랜치 생성
  
> git branch --track branch-name origin/branch-name <br/>
> git branch -t branch-name origin/branch-name <br/>
> ex: git branch -t SampleBranch origin/SampleBranch
  
### git Config
  
**설정 값 확인**
  
> git config --list <br/>
> git config --global --list

or look at your ~/.gitconfig file. The local configuration will be in your repository`s .git/config file.

Use:
  
> git config --list --show-origin

- [출처 : stackoverflow](https://stackoverflow.com/questions/12254076/how-do-i-show-my-global-git-configuration)

**자동 gc 꺼버리기**
  
> git config --global gc.auto 0
  
  
### Git Clear Unstaged Change

For all unstaged files iFor all unstaged files in current working directory use:

> git checkout -- .

For a specific file use:

> git checkout -- path/to/file/to/revertn current working directory use:

- [stackOverflow](https://stackoverflow.com/questions/52704/how-do-i-discard-unstaged-changes-in-git)


### List All Branches, Delete Branch

- To see local branches, run this command: `git branch`
- To see remote branches, run this command: `git branch -r`
- To see all local and remote branches, run this command: `git branch -a`
- Delete Branch: `git branch -d <branch-name>`

출처 : [Git Branches: List, Create, Switch to, Merge, Push, & Delete](https://www.nobledesktop.com/learn/git/git-branches)

### Alias MultipleCommand

This targets Windows batch / msysgit bash; might not work on other environments.

As Olivier Verdier and Lily Ballard have said

> [alias] chs = !git checkout $1 && git status

almost works, but gives a spurious extra insertion of the argument ...

> git chs demo -> git checkout demo && git status demo

But if you add `&& :` to the end of your alias, then the spurious argument is consumed into a location tag.

So

> [alias] chs = !git checkout $1 && git status && :

gives the correct output ... `git chs demo -> git checkout demo && git status`

- 출처 : [stackoverflow](https://stackoverflow.com/questions/7534184/git-alias-multiple-commands-and-parameters)

### log / diff / Grep / ls-files

log

- 기본 커맨드 포맷 : `git log [<options>] [<revision-range>] [[--] <path>…​]`
- By CommitRange :  `git log <revision-range>`
  - > ex) git log --oneline aad924a34e3~2...aad924a34e3
- By Message : `ex) git log --grep="JRA-224:"`
- By File : `ex) git log -- foo.py bar.py`
- By Content : `ex) git log -S"Hello, World!"`
- `ex) git log --oneline --graph --perl-regexp --author='(kim|oh)'`
- 옵션 몇가지
  - `--oneline`
  - `--graph`
  - `--stat` : Generate a diffstat.
    - These parameters can also be set individually with `--stat-width=<width>, --stat-name-width=<name-width> and --stat-count=<count>.`
  - `--shortstat`
  - `--merges` : Print only merge commits. This is exactly the same as --min-parents=2.
  - `--no-merges` : Do not print commits with more than one parent. This is exactly the same  as --max-parents=1.
  - `--first-parent` : When finding commits to include, follow only the first parent commit upon seeing a merge commit.
  - `--author=<pattern>`
  - `--committer=<pattern>`
  - `--grep=<pattern> / --invert-grep`
  - `--full-diff`
  
diff

- 특정 커밋 범위 내 diff 표시 : `git diff <revision-range>`
  - 기본적으로 `git diff <commit>` 은 현재 커밋 위치 부터 `<commit>` 까지 diff를 표시한다.
  - > ex) git diff --name-status aad924a34e3~2...aad924a34e3
- 옵션 몇 가지
  - `--name-status` : Show only names and status of changed files. See the description of the --diff-filter option on what the status letters mean
  
shortlog

- 기본 커맨드 포맷 : `git shortlog [<options>] [<revision-range>] [[--] <path>…​]`
- 옵션 몇가지
  - `-n / --numbered` : Sort output according to the number of commits per author instead of author alphabetic order.
  - `-s / --summary` : Suppress commit description and provide a commit count summary only.
  - `-e / --email` : show email
  - `--group=<type>` : Group commits based on `<type>`. If no --group option is specified, the default is author. `<type>` is one of: `author`, `committer`, `trailer`
  - `-c / --committer` : This is an alias for --group=committer.
  - `--author=<pattern>`

grep

- `git-grep` : Print lines matching a pattern. Look for specified patterns in the tracked files in the work tree, blobs registered in the index file, or blobs in given tree objects. 
- `ex) git grep 'time_t' -- '*.[ch]'` : Looks for time_t in all tracked .c and .h files in the working directory and its subdirectories.
- `ex) $ git grep -i 'boo*' $(git rev-list --all)` : 
- `ex) git grep -f 'booktype.php.'` : The following output shows that the booktype.php file exists in the current repository, and the file contains a single line.
- `ex) git grep -e 'Book'` : The following output shows that both booklist.php and booktype.php files contain the word ‘Book’ at line number 1.
- 옵션 몇 가지
  - `-f <file>` : Read patterns from `<file>`, one per line.
  - `-e` : The next parameter is the pattern. 
  - `-i / --ignore-case` : Ignore case differences between the patterns and the files.
  - `-F / --fixed-strings` : Use fixed strings for patterns (don’t interpret pattern as a regex).
  - `-l / --files-with-matches / --name-only` : Instead of showing every matched line, show only the names of files that contain (or do not contain) matches.
  - `-L / --files-without-match`

ls-files

- git-ls-files - Show information about files in the index and the working tree
- `ex) git ls-files "*item*"`

- [git-log](https://git-scm.com/docs/git-log)
- [git-diff](https://git-scm.com/docs/git-diff)
- [git-shortlog](https://git-scm.com/docs/git-shortlog)
- [git-Grep](https://git-scm.com/docs/git-grep)
- [git-ls-files](https://git-scm.com/docs/git-ls-files)
  
### Find deleted file in history

If you do not know the exact path you may use

> git log --all --full-history -- "**/thefile.*"

If you know the path the file was at, you can do this:

> git log --all --full-history -- <path-to-file>
  
ex : `git log --all --full-history -- "Sources/Something.cs"`

- 출처 : [stackoverflow](https://stackoverflow.com/questions/7203515/how-to-find-a-deleted-file-in-the-project-commit-history)
  
Show Head Commit Id/history
  
> git show-ref --heads <br/>
> git rev-parse HEAD <br/>
> git rev-parse remotename/branchname <br/>
> git log branchname -n 5 <br/>
> git log remotename/branchname <br/>
  
- 출처 : [stackoverflow](https://stackoverflow.com/questions/1967967/git-command-to-display-head-commit-id)

### Stash
  
- list stash entry : `git stash list`
- show stash entry diff: `git stash show <number>`, `ex) git stash show 0`
- push stash: `ex) git stash push -m "Some Stash" Sources/FileDir/File1.cs Sources/FileDir/File2.cs`
- apply stash `ex) git apply stash 0`
- pop stash (적용과 동시에 스태시 엔트리 제거) : `ex) git pop stash 0`
- stash drop(스태시 엔트리 제거)
- stash branch (스태시 엔트리 변경사항을 브랜치로)
  
- 출처 : [git](https://git-scm.com/docs/git-stash)

### git Reorder Commit By Interactive rebase
  
먼저 interactive rebase를 시작
  
> git rebase -i HEAD~3
  
git bash 의 경우 vi 에디터를 통해 메시지를 수정하게 된다. 수정을 마치고 난 뒤에 종료
  
```
pick 7c65355 Task 1/3
pick 2639543 Task 2/3
pick d442427 Task 3/3

# Rebase 2260a88..d442427 onto 2260a88
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit`s log message
#  x, exec = run command (the rest of the line) using shell
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out  
```

예를 들어 순서 변경 및 Squash 수행하도록 메세지를 변경하고 싶다면 아래처럼 수정한다.
  
```
pick d442427 Task 3/3
s 7c65355 Task 1/3
s 2639543 Task 2/3
```
  
- 출처 : [git ready](https://gitready.com/advanced/2009/03/20/reorder-commits-with-rebase.html)
  
### rev-list
  
조건에 맞는 커밋 오브젝트를 시간 역순으로 나열합니다.
  
> git rev-list HEAD..origin/main <br/>
> git rev-list --count HEAD..origin/main <br/>
  
### Tilde / Caret Notation
 
Tilde : The [“Specifying Revisions” section of the git rev-parse documentation](https://git-scm.com/docs/git-rev-parse#Documentation/git-rev-parse.txt-emltrevgtltngtemegemmaster3em) defines `~` as

> A suffix `~<n>` to a revision parameter means the commit object that is the nth generation ancestor of the named commit object, following only the first parents. For example, `<rev>~3` is equivalent to `<rev>^^^` which is equivalent to `<rev>^1^1^1` …
  
Caret : Git history is nonlinear: a directed acyclic graph (DAG) or tree. For a commit with only one parent, `rev~` and `rev^` mean the same thing. The caret selector becomes useful with merge commits because each one is the child of two or more parents — and strains language borrowed from biology.
  
> A suffix `^` to a revision parameter means the first parent of that commit object. `^<n>` means the nth parent ([e.g.] `<rev>^` is equivalent to `<rev>^1`). As a special rule, `<rev>^0` means the commit itself and is used when `<rev>` is the object name of a tag object that refers to a commit object.

 ```
  G   H   I   J
 \ /     \ /
  D   E   F
   \  |  / \
    \ | /   |
     \|/    |
      B     C
       \   /
        \ /
         A

A =      = A^0
B = A^   = A^1     = A~1
C = A^2
D = A^^  = A^1^1   = A~2
E = B^2  = A^^2
F = B^3  = A^^3
G = A^^^ = A^1^1^1 = A~3
H = D^2  = B^^2    = A^^^2  = A~2^2
I = F^   = B^3^    = A^^3^
J = F^2  = B^3^2   = A^^3^2
```

### Detached HEAD

It is sometimes useful to be able to checkout a commit that is not at the tip of any named branch, or even to create a new commit that is not referenced by a named branch.

브랜치의 끝점이 아닌 과거의 특정 커밋으로 체크아웃해야할 때가 있습니다. 이때에는 어떤 브랜치와도 연관되지 않은 `Detached Head` 상태에 진입해서 목표하는 커밋으로 체크아웃 할 수 있게 됩니다.
- `Detached Head` 상태에서는 기본 깃 동작들을 수행할 수 있습니다만, 참조하는 브랜치가 없는 상태이므로 주의할 점이 있습니다. 이 상태에서 다시 다른 브랜치로 checkout 한다면 `Detached Head` 상태에서 작업한 내역들을 잃어버리게 됩니다. (깃의 GC가 수거해갑니다.)
- 아래처럼 새로운 브랜치를 만들어 기존작업 내역에 대해 `Detached Head`에 참조상태를 새로 갱신할 수 있습니다.

```bash
$ git checkout -b foo   (1)
$ git branch foo        (2)
$ git tag foo           (3)
```
1. creates a new branch foo, which refers to commit f, and then updates HEAD to refer to branch foo. In other words, we’ll no longer be in detached HEAD state after this command.
2. similarly creates a new branch foo, which refers to commit f, but leaves HEAD detached.
3. creates a new tag foo, which refers to commit f, leaving HEAD detached.

- 출처 [git : detached Head](https://git-scm.com/docs/git-checkout#_detached_head)

### Ref Log

Reference logs란 로컬 저장소에서 브랜치의 끝점 혹은 레퍼런스가 갱신될 때마다 히스토리를 기록합니다. 로컬 저장소에서 과거 정보를 확인할 때 유용합니다.

```bash
git reflog 
git reflog expire 
git reflog delete 
git reflog exists <ref>
```

- 작업하다가 실수로 이전 커밋을 잃거나, 의도치 않게 변형된 경우에 reflog 를 활용할 수 있습니다. 단순히 reflog 의 커밋 번호로 reset 하면 이전 내역으로 복구 할 수 있습니다.

- 출처 [git : Reflog](https://git-scm.com/docs/git-reflog)
