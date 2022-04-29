# WindowCommand 명령어

## Basics

- call : calls a batch file from another one
- **cd** :change directory
- **cls** : clear screen
- cmd : start command prompt
- color : change console color
- date : show/set date
- dir : list directory content
- echo : text output
- exit : exits the command prompt or a batch file
- find : find files
- hostname : display host name
- pause : pauses the execution of a batch file and shows a - message
- runas : start a program as another user
- shutdown : shutdown the computer
- sort : sort the screen output
- start : start an own window to execute a program or command
- **taskkill** : terminate a process or a application
  - `taskkill /pid 21500` : 21500 pid를 가지는 프로세스 종료
  - `taskkill /IM java*` -> java로 시작하는 이름을 가진 프로세스 종료
  - `taskkill /T /PID 21303` -> PID가 21303인 프로세스와 그 자식 프로세스 종료
  - `taskkill /f` : 강제 종료 옵션
- **tasklist** : display applications and related tasks
  - `tasklist /v` : 상세 정보 표시 옵션
  - `tasklist /fi` : 필터 옵션
    - `tasklist /fi "PID gt 1000"` : pid 가 1000 이상인 프로세스 리스트 나열
    - `tasklist /fi "windowtitle eq someWindow"` : 창 이름이 someWindow 인 프로세스 나열
- time : display/edit the system time
- timeout : wait any time
- title : set title for prompt
- ver : display operating system version
- w32tm : setting time synchronisation/time server/time zone

## Network

- ftp : transfer files to a FTP server
- ftype : display file type and mapping
- getmac : display MAC address
- ipconfig : display IP network settings
- netsh : configure/control/display network components
- netstat : display TCP/IP connections and status
- nslookup : query the DNS
- pathping : test the connection to a specific IP address
- ping : pings the network
- route : display network routing table, add static routes
- systeminfo : displays computer-specific properties and - configurations
- telnet : establish Telnet connection
- tftp : transfer files to a TFTP server
- tracert : trace routes similar to patchping

## Files

- attrib : display file attributes
- comp : compare file contents
- compact : display/change file compression
- copy / xcopy : copy files
- diskcomp : compare content of two floppy disks
- diskcopy : copy floppy disc to another one
- erase / del : delete one or more files
- expand : extract files
- fc : copare files and display the differences
- mkdir : create a new directory
- move : move/rename files
- rename : rename files
- replace : replace files
- rmdir / rd : delete directory
- tree : display folder structure graphically
- type : display content of text files

## Media

- chkdsk : check volumes
- chkntfs : display/change volume check at startup
- defrag : defragment media
- diskpart : volume management
- driverquery : display installed devices and their properties
- format : format volumes
- label : change volume name
- mode : configure interfaces/devices
- mountvol : assign/delete drive mountpoints
- verify : monitoring whether volumes are written correctly
- vol : show volume description and serial numbers of the HDDs

## Miscellaneous

- for : for loop
- gpresult : display group policies
- gpupdate : update group policies
- perfmon : start performance monitor
- prompt : change command prompt
- reg : add/read/import/export registry entries

> [출처- thomas-krenn](https://www.thomas-krenn.com/en/wiki/Cmd_commands_under_Windows)