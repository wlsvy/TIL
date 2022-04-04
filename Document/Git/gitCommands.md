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
