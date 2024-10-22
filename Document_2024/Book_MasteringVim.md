# Mastering Vim, Ruslan Osipov, 2ND Edition

![](Book_MasteringVim.png)

# 1

## A brief history lesson

> Before personal computers and terminals, there were teleprinters. A teleprinter is a mechanical typewriter that can send and receive messages over a telecommunications channel.
>
> As technology progressed, teleprinters were replaced by terminals with screens, which enabled much more robust text editing. Vim’s direct predecessor, **vi**, started its life all the way back in 1976. Unlike its predecessors, **vi** (developed by Bill Joy, the author of ex) included many quality-of-life features and even allowed you to edit multiple lines of text at once – what a luxury!

---

> The first version of Vim was released in **1991** by **Bram Moolenaar**. Now, you’re all caught up!

## About Modal Interface

> Welcome to the modal interface, **where each trigger performs a different action based on context**. 
>
> The most common example of a modal interface that we encounter today is a smartphone. Each time we work in different applications or open different menus, a tap on the screen performs a different function.

![image_2024-10-22-14-59-36](img/image_2024-10-22-14-59-36.png)

- Vim is a modal editor
  - meaning that a single button press might result in different actions.

## A word about swap files

> By default, Vim keeps track of the changes you make to files in swap files. 

- The swap files are created as you edit the files, 
  - and are used to recover the contents of your files in case either Vim, your SSH session, or your machine crashes.
