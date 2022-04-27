### 특정 브랜치만 git Clone

클론 시에 해당 리포지토리에 브랜치가 많다면 시간이 오래 걸릴 수 있는데, 이런 경우에 아래처럼 단일 브랜치만 먼저 내려받을 수 있다.

```
git clone -b {branch_name} --single-branch {저장소 URL}
ex) git clone -b javajigi --single-branch https://github.com/javajigi/java-racingcar
```

위와 같이 실행하면 java-racingcar의 javajigi branch만 clone할 수 있다.

- [출처 : slipp](https://www.slipp.net/questions/577)

> git clone -b <branch name> --single-branch <github url> <target directory>
  
위와 같이 clone한 후 새로운 브랜치를 추가하고 싶은 경우가 있으면 다음과 같이 새로운 브랜치를 추가할 수 있다.

> git remote set-branches --add origin [remote-branch] <br/>
> git fetch origin [remote-branch]:[local-branch]

- [출처 : slipp](https://www.slipp.net/questions/605)
  
### 트랙킹 브랜치 생성
  
> git branch --track branch-name origin/branch-name <br/>
> git branch -t branch-name origin/branch-name <br/>
> ex: git branch -t SampleBranch origin/SampleBranch
  
### git Config
  
**설정 값 확인**
  
> git config --list <br/>
> git config --global --list

or look at your ~/.gitconfig file. The local configuration will be in your repository's .git/config file.

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


### List All Branches

To see local branches, run this command:

- git branch

To see remote branches, run this command:

- git branch -r

To see all local and remote branches, run this command:

- git branch -a

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
  
list stash entry

> git stash list
  
show stash entry diff
  
> git stash show 0
  
push stash
  
> git stash push -m "Some Stash" Sources/FileDir/File1.cs Sources/FileDir/File2.cs
  
apply stash(적용만)
  
> git apply stash 0
  
pop stash (적용과 동시에 스태시 엔트리 제거)
 
> git pop stash 0
  
stash drop(스태시 엔트리 제거)

stash branch (스태시 엔트리 변경사항을 브랜치로)
  
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
#  f, fixup = like "squash", but discard this commit's log message
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
