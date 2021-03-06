# 운영체제

운영체제 요약 정리

##### Reference
- Abraham Silberschatz, Greg Gagne, and Peter Baer Galvin, "Operating System Concepts, Ninth Edition "
- [parksb 블로그](https://parksb.github.io/article/5.html)
- [Operating System Course Note](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/)
- [Thread Course Note](http://lass.cs.umass.edu/~shenoy/courses/fall12/lectures/notes/Lec06_notes.pdf)

# 1장 서론
<details>
	<summary>접기/펼치기</summary>

## Operating System Definition

Operating system
**acts as an intermediary between applications and the computer hardware.**
- manages computer hardware resources.
- provides some services for applications.
- os는 애플리케이션과 하드웨어의 중간다리 역할을 합니다.
- os에 대해 정확한 정의를 내리기는 어렵습니다.
- 일반적인 정의로 os는 컴퓨터에서 항상 수행되는 프로그램으로 커널kernel 이라고 불립니다.
	- 시스템 프로그램은 운영체제와 연관되어 있으며 커널의 일부분은 아니고, 응용프로그램은 시스템의 운영과 관계없는 모든 프로그램을 포함합니다.

#### 사용자 관점
- os는 컴퓨터 시스템을 사용하기 편리하게 만들며 사용자 프로그램을 실행시킵니다.

#### 시스템 관점
- OS is a **resource allocator**. os는 자원 할당자입니다. 
	- H/W resources: CPU, memory, and I/O devices.
	- SW resources: files, sockets, semaphores, etc.
- OS is a **control program**. 
	- controls the execution of applications and operations of I/O devices.
- os는 자원할당자로서 하드웨어 자원을 다루거나, 제어 프로그램으로서 적절한 사용을 위해 사용자 프로그램의 수행을 제어합니다.


## Computer System Operation
- 현대의 범용 컴퓨터 시스템은 공유 메모리에 대한 접근을 제공하는 공통 버스에 의해 연결된 여러 개의 장치 제어기와 하나 이상의 cpu로 구성되어 있습니다.
- 컴퓨터가 구동(부팅)을 시작하기 위해서는, 수행할 초기 프로그램`부트스트랩 프로그램 bootstrap program`은 보통 펌웨어로 알려진 컴퓨터 내의 Rom 메모리나 EEPROM에 저장됩니다.
	- 부트스트랩 프로그램은 cpu 레지스터를 포함 시스템의 모든 면을 초기화하며 운영체제의 커널을 찾아 메인 메모리에 적재합니다.
	- 커널이 메인 메모리에 적재되면 본격적으로 os는 시스템과 사용자에게 서비스를 제공할 수 있습니다.
- 사건이 발생하면 하드웨어나 소프트웨어에서 발생한 `인터럽트 interrupt`에 의해 신호가 보내집니다.
	- SW는 시스템 호출(system call)을 통해서 인터럽트를 발생시킬 수 있습니다.
	- When interrupt occurs,
		- CPU stops what it is doing and invokes the interrupt service routine (ISR).

## Storage Structure
- cpu는 명령어를 단지 메모리로부터 가져올 수 있으므로 프로그램을 수행하려면 프로그램이 반드시 메모리에 있어야 합니다.
	- 범용 컴퓨터는 대부분의 프로그램을 `RAM random accescc memeory`에 적재합니다.
	- 폰 노이만 구조 시스템에서 실행되는 전형적인 명령-실행 사이클은 먼저 메모리로부터 명령을 인출해, 그 명령을 명령 레지스터instruction register에 저장합니다. 이어서 명령을 해독한 뒤 필요한 피연산자를 메모리로부터 인출하여 내부 레지스터에 저장합니다. 연산 결과값은 다시 메모리에 저장될 수 있습니다.

	- 이상적으로 프로그램과 데이터가 주 메모리에 영구히 존재했으면 하지만 두 가지 이유로 불가능합니다.
		- 주 메모리는 모든 필요한 프로그램과 데이터를 영구히 저장히기에는 크기가 작다.
		- 주 메모리는 전원이 공급되지 않으면 그 내용을 잃어버리는 휘발성 장치이다.
	- 그러므로 대부분 컴퓨터 시스템은 주 메모리의 확장으로 보조 저장 장치를 제공합니다. 보조 저장장치는 대량의 데이터를 영구적으로 저장할 수 있습니다.

## I/O structure
- 통상적으로 운영체제는 각 장치제어기마다 디바이스 드라이버를 가지고 있습니다. 이는 장치 제어기의 동작을 이해하고 운영체제의 다른 부분들에게 장치에 대한 인터페이스를 제공합니다.

- 인터럽트 구동 방식
	- 적은 양의 데이터를 전송하는 데에는 큰 문제가 없습니다.
	- 디바이스 드라이버가 장치 제어기에게 명령을 내리면 제어기는 데이터를 전송한 뒤 인터럽트를 통해 드라이버에게 전송 작업이 끝났음을 통보하는 방식입니다.

- `직접 메모리 접근 방식 DMA direct memory access`
	- 인터럽트 구동 방식이 대량의 데이터를 전송할 때 가지는 높은 오버헤드를 해결하기 위한 방법입니다.
	- cpu의 개입 없이 메모리로부터 자신의 버퍼로 혹은 그 반대 방향으로 데이터 블록 전체를 전송합니다.
	- 속도가 느린 장치처럼 한 바이트마다 인터럽트가 발생하는 것이 아니라 블록 전송이 완료될 때마다 인터럽트가 발생합니다.
	- 장치 제어기가 DMA 작업을 수행하는 동안 cpu는 다른 작업을 수행할 수 있습니다.

## Computer-System Architecture

- Single-Processor Systems

	- 과거 대부분의 컴퓨터는 싱글 프로세서를 사용했다. 싱글 프로세서 컴퓨터에는 하나의 메인 CPU만 탑재되며, 장치에 따라 특별한 목적을 가진 프로세서가 들어갔다. 가령 디스크 프로세서는 디스크 연산만 수행하고, 키보드 프로세서는 키보드 연산만 수행하는 식이다.

- Multiprocessor Systems
	- 멀티 프로세서 시스템은 이젠 일반적인 컴퓨터 시스템이 되었다. 멀티 프로세서 컴퓨터는 2개 이상의 프로세서를 가지며 몇가지 장점을 가지고 있다.
		1. 처리량(Throughput)의 증가: 당연하겠지만 프로세서가 늘어나면 더 빠른 시간 안에 연산을 수행할 수 있다. 물론 프로세서를 계속 늘린다고 성능이 한없이 좋아지는 것은 아니며, 증가 비율이 1:1인 것도 아니다.
		2. 규모의 경제: 멀티 프로세서 시스템은 여러 대의 싱글 프로세서 시스템을 구축하는 것보다 돈이 적게 든다. 멀티 프로세서 시스템은 주변장치(Peripherals)를 공유할 수 있기 때문이다.
		3. 신뢰성의 증가: 만약 기능이 여러 프로세서에 분산될 수 있다면, 하나의 프로세서가 작동을 멈춰도 전체 시스템은 느려질 뿐 멈추지 않는다. 이런 식으로 성능이 나빠지지만 작동은 가능하도록 하는 것을 우아한 성능저하(Graceful degradation)라고 부른다. 그리고 이렇게 성능을 저하함으로써 작업을 계속 유지하는 시스템을 장애 허용 시스템(Fault tolerant)이라고 부른다.

	- 멀티 프로세서 시스템은 비대칭 멀티프로세싱(Asymmetric multiprocessing)과 대칭 멀티프로세싱(Symmetric multiprocessing) 두 가지로 나뉜다.
		- 비대칭 멀티프로세싱은 관료주의적인 회사다. 보스 프로세서(Boss processor)가 시스템을 제어하고, 다른 프로세서들은 보스의 지시를 받게 된다. 이렇게 하면 부하 분산(Loadbalancing)을 효율적으로 할 수 있다. 대신 보스 프로세서가 작동을 멈추면 일꾼 프로세서들도 멈추게 된다. 
		- 대칭 멀티프로세싱은 보스가 없는 자유로운 회사다. 모든 프로세서들은 하나의 메모리를 공유하고, 동일한 작업을 병렬적으로 수행한다. 만약 프로세서에 이상이 생겨 작동을 멈춰야 한다면 자신이 수행하던 작업을 다른 프로세서들에게 나눠주고 자신만 재부팅한다.
		- 대부분의 컴퓨터 시스템은 대칭 멀티프로세싱을 사용한다.

- 추가적으로 클러스터형 시스템clustered system 이 있습니다.

## Operating System Structure

운영체제의 가장 중요한 부분 중 하나는 멀티프로그램(Multiprogram) 능력이다. 멀티프로그래밍(Multiprogramming)은 여러 프로그램을 메모리에 로드해 두고 한 프로세스가 대기 상태가 되면 다른 프로세스의 작업을 수행하는 시스템이다. 이렇게 하면 CPU의 사용 효율을 높일 수 있다. (디스크에 있는 것은 프로그램, 메인 메모리에 있는 것은 프로세스다.)
- 시분할(혹은 멀티 태스킹multi tasking) 다중 프로그래밍의 논리적 확장입니다. 시분할 시스템에서는 cpu가 다수의 작업들을 교대로 수행하지만 매우 빈번하게 교대가 일어나기 때문에 프로그램이 실해오디는 동안에 사용자들은 각자 자기의 프로그램과 상호작용할 수 있습니다.
- 시분할 시스템과 멀티프로그래밍 시스템은 여러 작업들을 동시에 메모리에 올리는 방식이다. 때문에 운영체제는 메모리에 자리가 없는 경우를 고려해 어떤 작업을 먼저 처리할지 정해야한다. 이러한 과정을 작업 스케줄링(Job scheduling), CPU 스케줄링(CPU Scheduling)이라고 한다.
- 만약 메모리를 너무 많이 사용하게 되는 경우, 반응 시간을 줄이기 위해 가상 메모리(Virtual memory)를 사용한다. 가상 메모리는 보조기억장치의 일부를 메인 메모리처럼 사용하는 기술로, 실제 물리 메모리(Physical memory)보다 더 큰 프로그램을 구동할 수 있도록 해준다.

## Operating-System Operations
- 운영체제는 인터럽트 주도적(interrupt driven). 인터럽트가 없다면 시스템은 조용히 인터럽트를 기다립니다.
- 운영체제와 사용자는 컴퓨터 시스템의 하드웨어와 소프트웨어 자원을 공유하기 때문에 사용자 프로글매의 오류가 현재 수행 중인 프로그램에만 문제를 일으키도록 보장해야 합니다. 한 프로그램의 오류에 의해 현재 수행 중인 다른 프로그램에 악영향을 받을 수 있습니다.
- 트랩(또는 예외)은 오류, 혹은 사용자 프로그램의 운영체제 서비스 수행 요청에 의해 유발되는 SW 덕분에 생긴 인터럽트 입니다.

## Dual-Mode and Multimode Operation
- 운영체제는 사용자 프로그램이 함부로 시스템에 접근하지 못하도록 연산 모드(Modes)를 분리합니다. 유저 모드(User mode)와 커널 모드(Kernel mode 슈퍼바이저 모드, 시스템 모드, 특권 모드privileged mode)가 그것이며, 하드웨어의 모드 비트(Mode bit)가 0이면 커널 모드, 1이면 유저 모드임을 가리킵니다.

- 모드 비트를 사용하면 os를 위하여 실행되는 작업과 사용자를 위하여 실행되는 작업을 구분할 수 있습니다. 운영체제의 서비스가 필요하다면 사용자 모드에서 커널모드로 전환합니다.
- 시스템 부트 시, 하드웨어는 커널 모드에서 시작합니다. 이어 운영체제가 적재되고 사용자 모드에서 사용자 프로세스가 시작됩니다.
	- 인터럽트가 발생할 때마다 하드웨어는 사용자 모드에서 커널 모드로 전환합니다.

- 이러한 이중 모드(Dual-mode) 방식을 사용하면 잘못된 사용으로부터 시스템과 사용자를 보호할 수 있습니다. 하드웨어는 커널 모드일 때만 특권 명령(Privileged instructions)를 실행합니다. 만약 유저 모드에서 특권 명령을 실행하려 한다면 하드웨어는 이 동작을 막고 운영체제에게 트랩을 보낼 것입니다. 유저 모드에서 커널 모드의 기능을 호출하고 싶다면 시스템 콜(System call)을 활용합니다.

## Timer
운영체제는 사용자의 프로그램이 제어권을 운영체제에게 넘겨주지 않는 상황을 방지하기 위해 타이머(Timer)를 사용한다. 타이머는 운영체제에게 제어권을 보장하기 위해 특정 주기에 인터럽트를 발생시킨다. 운영체제는 카운터를 설정하고, 타이머의 시간은 매 틱(Ticks)마다 감소한다. 그렇게 카운터가 0에 도달하면 인터럽트가 발생한다.

## Caching
캐시는 굉장히 빠르고 작은 저장장치이며, 캐싱은 캐시 메모리를 사용해 컴퓨터의 속도를 높이는 기술이다. 데이터를 디스크에서 직접 가져오는 것은 너무 느리기 때문에 캐시에 자주 사용될 것 같은 데이터를 미리 담아두고, CPU나 디스크가 캐시의 데이터를 참조할 수 있도록 한다. 파일의 중복성이 증가하지만, 속도 역시 증가한다. 캐싱은 지역성(Locality) 원리를 사용한다. 

- Caching is performed at many levels in a system or in many environments.
- CPU cache, operating system’s buffer cache, disk cache, etc.
- Web cache, streaming cache, etc.

Cache is first checked to determine if the requested data are there.
- If it is, data are used directly from the cache.
- If not, data are copied to cache and used there.

Generally, cache size is limited.
- replacement policy is required
- E.g. LRU, LFU, clock, …

Cached data should be carefully handled.
- Several copies of a datum can exist.
- Data inconsistency

In multiprocessor environment
- Cache coherency 
- All CPUs have the most recent value in their cache.
- 캐시 일관성은 중요한 요소이다. 각각의 cpu마다 다른 캐시를 가지고 있으며 여기서 각 cpu마다 가장 최근에 갱신된 값을 저장해 활용할 시 나타날 수 있는 데이터 불일치를 조심해야 한다.
- Distributed environment’s situation is more complicated.

## Process Management	
- A process is a program in execution.
	- 프로세스는 실행중인 프로그램으로서 메인 메모리에 적재된 프로그램을 말하기도 합니다.

Process management activities
- Scheduling processes on the CPUs
- Creating and deleting processes
- Process synchronization mechanisms
- Inter-process communication mechanisms
- Deadlock handling

</details>

# 2장 시스템 구조
<details>
	<summary>접기/펼치기</summary>

## System Call
`시스템 호출 system call`은 운영체제가 제공하는 서비스에 대한 인터페이스를 제공합니다.
- 프로그램이 운영체제에 대해 서비스를 요청하는 방법이기도 합니다.
	- E.g. 하드 디스크 접근
	- E.g. 새로운 프로세스 생성 및 실행
- 프로세스와 OS 간에 필수적인 인터페이스를 제공합니다.
- 일반적으로 high-level language (C or C++) 로 작성되었습니다.

Three methods for passing parameters to the OS
1. pass the parameters in registers. 값 전달
2. store parameters in a table on memory, and then pass the address of table in a register. 참조 전달
	- e.g. Linux and Solaris
3. push parameters onto the stack by program, and pop off the stack by OS. 스택 활용

시스템 콜은 크게 6가지로 분류할 수 있습니다.

1.Process control
  - create/terminate, load/execute, wait/signal event
  - E.g. fork(), execve(), getpid(), signal(), …
2. File management
  - create/delete, open/close, read/write
  - E.g. open(), read(), write() close(), …
3. Memory management
  - allocate memory
  - E.g. brk(), …
4. Information maintenance
  - get/set timer or date, get/set process, file, or device attributes
  - E.g. time()
5. Communications
  - create/delete connection, send/receive message
  - E.g. socket(), bind(), connect(), 
6. Protection
  - set/get permission, allow/deny user
  - E.g. chmod()...

### Application Program Interface (API)
- API는 애플리케이션 프로그래머가 활용할 수 있는 기능의 집합입니다.
- 세 가지 가장 보편적인 API 
	- Win32 API for Windows.
	- POSIX API for POSIX-based systems (UNIX/Linux).
	- Java API for the Java virtual machine.
- 시스템 콜 대신 API를 활용하는 이유
	- 호환성 Portability
	- 사용하기 쉬움 Easy to use
	- api를 활용한다면 응용 프로그래머는 자신의 프로그램이 같은 api를 지원하는 어느 시스템에서건 컴파일 되고 실행되는 것을 기대할 수 있습니다.
	- 또한 실제 시스템 콜은 종종 좀 더 자세한 명세가 필요하고 프로그램 상에서 작업하기가 응용 프로그래머에게 가용한 api 보다 어렵습니다.
    - 프로그래머는 시스템 콜의 구현상태에 대해 알아야 할 필요가 없습니다.
	  - Just needs to obey API and understand what OS will do. 
	  - 프로그래머 입장에서 OS를 활용하는 구체적인 부분은 API 내부에 감춰지게 됩니다.
- API는 각 함수에 전달되어야 할 매개변수들과 프로그래머가 기대할 수 있는 반환 값을 포함하여 응용 프로그래머가 사용 가능한 함수의 집합을 명시합니다.

## Operating system structures
1. Simple structure
2. Layered structure
3. Microkernel structure
4. Module structure
5. Hybrid Systems

## System Boot
How to load kernel?
- Bootloader
	- run diagnostics, initialize system.
	- locates the kernel, loads it into memory, and starts it.
- 작은 시스템의 경우
	- Store bootloder and OS in ROM.
- 큰 시스템의 경우 (e.g. PC)
	- Store bootloader in ROM and OS in disk, respectively.
	- Simple bootloader in boot block -> complicated bootloader -> kernel

</details>

# 3장 프로세스

<details>
	<summary>접기/펼치기</summary>

## 프로세스 개념
- OS는 다양한 프로그램을 실행시킵니다.
- `일괄처리 시스템Batch system` – 잡job 을 실행합니다.
- `시분할 시스템Time-shared systems` – 사용자 프로그램 혹은 태스크task 들을 가집니다.
- Textbook uses the terms job and process almost interchangeably


##### Process
- 실행되는 프로그램(a program in execution)
- 단순히 텍스트 섹션으로 알려진 프로그램 코드 이상의 무엇

##### A process includes
- text section 이라 불리는 프로그램 코드(program code)
- 전역 혹은 정적 변수(global/static variables)를 포함하는 Data sections
- 임시 데이터(temporary data)를 포함하는 스택(stack)
  - Function parameters, return addresses, local variables
- 동적 할당된 메모리를 포함하는 힙(Heap)
- program counter, processor registers 값 등. 이 정보들은 특정 프로세스들 사이에서 문맥 교환이 이루어질 때 현재 진행 상황을 저장합니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_01_Process_Memory.jpg)

> 메모리에서 stack 영역은 메모리 최대 주소값에서 0으로, heap 영역은 data section 영역 주솟값 이후 부터 메모리 최대 주소값으로, 즉 두 영역을 서로 향하는 방향으로 메모리를 할당합니다. 만약 이 둘이 만나게 된다면 stack overflow 및 동적 할당 시 메모리 오류가 발생할 것입니다. 
> stack : 높은 주솟값 -> 낮은 주솟값, heap : 낮은 주솟값 -> 높은 주솟값

### Process State
- 프로세스는 실행이 될때 자신의 상태를 변경합니다.
- New : 프로세스가 새로 생성된 상태입니다.
- Running : 프로세스의 명령어가 실행되는 상태입니다.
- Waiting (blocked, sleep) : 프로세스가 특정 이벤트를 대기하고 있는 상태입니다.
- Ready : 프로세스가 프로세서(CPU)에게 할당되기를 기다리는 상태입니다.
- Terminated : 프로세스가 실행을 종료한 상태입니다.

### Process Control Block
- 프로세스를 관리하는 메타데이터(Metadata)
  - Process Control Block : process 관리
  - Task Control Block : Task 관리
    - E.g. task_struct in Linux
  - File Control Block : file 관리
    - E.g. vnode in Unix file system

> [메타데이터](https://en.wikipedia.org/wiki/Metadata)는 다른 데이터에 대한 정보를 포함하는 데이터, 즉 데이터의 데이터입니다.

- 프로세스 제어 블록은 특정 프로세스와 연관된 여러 정보를 수록하며 다음과 같은 것들을 포함합니다.
  - Process ID
  - Process state
    - New, ready, running, waiting, terminated
  - Program counter
    - Address of the next instruction
  - CPU registers
    - Stack pointer, general-purpose registers, …
  - CPU scheduling information
    - Priority, …
  - Memory-management information
    - Page table, segment table, …
  - Accounting information
    - Amount of CPU used, …
  - I/O status information
    - Open files, allocated I/O devices, …

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_03_PCB.jpg)

## Process Scheduliing

### Process Scheduling Queues
- Ready queue
  - 메인 메모리에 적재되어 있으며 실행을 기다리고 있는 프로세스들의 집합입니다.
- Device queues
  - I/O device 를 기다리고 있는 프로세스들의 집합입니다.
  - 각 장치는 자신의 디바이스 큐를 가집니다.
- 프로세스들은 다양한 큐(queues) 사이를 옮겨다닙니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_05_Queues.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_06_QueueingDiagram.jpg)

### Schedulers
- CPU scheduler
  - selects which process should be executed next and allocates CPU.
  - Processes can be classified into
    - I/O-bound process
      - spends more time doing I/O than computations.
      - many short CPU bursts
    - CPU-bound process
      - spends more time doing computations. 
      - a few very long CPU bursts

### Context Switch

문맥 교환 Context Switch 가 발생할 때 시스템은 아래의 작업을 수행합니다.
- 기존 프로세스의 상태(registers, memory maps)를 저장합니다. 각종 정보를 저장하는 테이블과 리스트를 업데이트 합니다.(updating various tables and lists)
- 새 프로세스의 상태(registers, memory maps)를 불러옵니다. 각종 정보를 저장하는 테이블과 리스트를 업데이트 합니다.(updating various tables and lists)

Context switch time is pure overhead. 
  - 문맥교환이 발생할 때 시스템은 다른 작업을 수행하지 못합니다.
  - Context switch time depends on hardware.
    - The register set is different.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_04_ProcessSwitch.jpg)

## Operation on Process

### Process Creation
- 부모 프로세스는 자식 프로세스를 생성합니다. 
- which, in turn creates other processes. 
- Finally, it forms a tree of processes.
- Unix, Linux, Windows와 같은 대부분의 현대 운영체제들은 유일한 프로세스 식별자(pid)를 사용하여 프로세스를 구분합니다. 보통 정수형을 사용합니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_08_ProcessTree.jpg)

- 자식 프로세스는 자원을 필요로 하며 운영체제로부터 할당받거나 부모 프로세스의 자원을 공유합니다.
Resource sharing
- Parent and children share all resources,
- Children share subset of parent’s resources, or
- Parent and child share no resources.
Execution
- Parent and child execute concurrently, or
- Parent waits until child terminate.
Address space
- Child duplicates parent, or
- Child has a new program loaded into it. 자식 프로세스가 자신에게 적재될 새로운 프로그램을 갖고 있다.

### Process Termination
Process executes last statement and asks operating system to delete itself (exit).
- Child process returns a status value to its parent (wait). 
- Child process’ resources are deallocated by operating system

Parent may terminate execution of child processes (abort).
- If child has exceeded the allocated resources.
- If task assigned to child is no longer required.

연쇄식 종료cascading termination : 부모 프로세스가 종료되면 그 자식 프로세스들 역시 전부 종료 시킵니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_10_ProcessCreation.jpg)

## Interprocess Communication

- Independent process
  - cannot affect or be affected by the execution of another process.
- Cooperating process
  - can affect or be affected by the execution of another process

- 협력적인 프로세스의 장점
  - Information sharing
    - E.g. shared files, …
  - Computation speed-up
    - Parallel execution via subtasks
  - Modularity
    - Division the system function into separate tasks

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_12_CommunicationsModels.jpg)

- Communication Model
  - Message passing 
  - Shard memory
    - Producer-Consumer 모델 활용
  - 메시지 전달 방식이 공유 메모리보다 더 나은 성능을 보인다는 연구가 있습니다. 공유 메모리를 활용시 공유 데이터가 여러 캐시 사이에서 이주하기 때문에 캐시 일관성 문제가 발생하여 성능 저하가 발생하기 때문입니다.

</details>

# 4장 스레드

<details>
	<summary>접기/펼치기</summary>

## Overview
- 스레드는 cpu 이용의 기본 단위이며, 프로그램 내부의 흐름이라고 볼 수 있습니다. 프로그램 카운터(program Counter), 스택, 레지스터, 스레드ID 로 구성되어 있습니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_01_ThreadDiagram.jpg)

- 모든 스레드는 아래 자원을 공유합니다.
  - 코드, 데이터, 힙 영역
  - open files
  - signal handlers
  - working environment (current directory, user ID, etc.)

- 각 스레드는 아래의 자원을 각자 개별적으로 소유합니다.
  - 스택
  - 레지스터
  - 프로그램 카운터(program count)
  - 스레드 ID

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_02_MultithreadedArchitecture.jpg)
- Motivation
  - 두 프로세스가 하나의 데이터를 공유하려면 메시지 패싱이나 공유 메모리 또는 파이프를 활용해야 합니다. 이는 효율도 떨어지고 개발자가 구현, 관리하기도 번거롭습니다.
  - 프로세스 사이에 문맥 교환이 일어나면 큰 오버헤드가 발생합니다. 스레드 전환에도 컨텍스트 스위치가 일어나지만 오버헤드가 상대적으로 작습니다.
  - 예를 들어 워드 프로세스에서는 background thread 가 작성된 문단의 맞춤법을 검사하는 사이 foreground thread 는 사용자의 입력을 받아 처리합니다. 그러면서 또 다른 세번째 스레드는 하드 드라이브에서 파일(이미지 등)을 메인 메모리로 올리고, 네번째 스레드는 주기적으로 수정사항을 자동저장합니다.
  - 또 다른 예는 웹 서버입니다. 다수의 스레드가 각각의 요청을 동시에 처리합니다. 다수의 자식 프로세스를 만들어내거나 (스레드 개념이 등장하기 전에 사용된 방법입니다.) 다수의 요청을 일련의 시퀀스로 나열해서 차례차례 처리하지 않아도 됩니다.

- Benefits
  - 응답성 Responsiveness - 스레드들이 정지(block) 상태이거나 혹은 값비싼 연산을 수행하는 중일 때 특정 명령이 요청된다면 또 다른 스레드가 여기에 즉각적으로 응답할 수 있습니다.
  - 자원 공유 Resource sharing - 기본적으로 스레드들은 코드, 데이터 등의 메모리 영역을 공유하기 때문에 하나의 메모리 공간에 대해서 다수의 스레드가 동작할 수 있습니다.
  - 효율성 Economy - 스레드를 생성하고 관리하는 작업(문맥 교환context switch 역시 마찬가지입니다)은 프로세스에 대해 동일한 작업을 수행할 때 보다 빠릅니다.
    - fork() 등의 명령어로 프로세스를 생성하는 작업은 비용이 비싼 편입니다.
  - 규모 적응성Scalability, i.e. Utilization of multiprocessor architectures - A single threaded process can only run on one CPU, no matter how many may be available, whereas the execution of a multi-threaded application may be split amongst available processors.

## Context Switch in Thread

- 프로세스간 문맥 교환 context switch 이 발생할 때는 내부적으로 시스템 캐시를 초기화합니다. (리눅스의 경우 TLB(translation lookaside buffer))
- 스레드간 문맥 교환이 발생하는 경우에는 시스템 캐시가 유지되며, 스레드들이 동일한 주소 공간을 활용하고 있으므로 문맥 교환 비용이 훨씬 경제적입니다.

## Multithreading Models
- 사용자 스레드는 사용자 수준에서 지원되며 커널의 자원 없이 관리됩니다. 반면에 커널 스레드는 운영체제에 의해 직접 지원되고 관리됩니다. 현재 대부분의 os는 커널 스레드를 지원합니다.

- 현대 시스템에서 스레드는 사용자 스레드와, 커널 스레드로 분류됩니다.
- 사용자 스레드는 사용자 수준에서 지원되며 커널의 자원 없이 관리됩니다. 애플리케이션 프로그래머과 활용할 수 있는 스레드입니다.
- 커널 스레드는 OS 커널 내에서 관리되는 스레드입니다. 모든 현대 OS 들은 커널 스레드를 지원합니다. 이는 커널이 다수의 시스템 콜을 동시에 처리할 수 있게 합니다.
- 특정 경우에서는 사용자 스레드가 커널 스레드와 반드시 매칭되어야 합니다. 아래 제시된 전략들 중 한 가지를 사용합니다.
- 커널 스레드보다 사용자 스레드의 문맥 교환 비용이 적습니다. 커널 스레드의 경우 문맥 교환 시 system call overhead 가 존재하기 때문입니다.

1. Many-To-One Model
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_05_ManyToOne.jpg)

2. One-To-One Model
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_06_OneToOne.jpg)

3. Many-To-Many Model
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_07_ManyToMany.jpg)

## Implicit Threading
### Thread Pools
- Creating new threads every time one is needed and then deleting it when it is done can be inefficient, and can also lead to a very large ( unlimited ) number of threads being created.
- An alternative solution is to create a number of threads when the process first starts, and put those threads into a thread pool.
  - Threads are allocated from the pool as needed, and returned to the pool when no longer needed.
  - When no threads are available in the pool, the process may have to wait until one becomes available.
- The ( maximum ) number of threads available in a thread pool may be determined by adjustable parameters, possibly dynamically in response to changing system loads.
- Win32 provides thread pools through the "PoolFunction" function. Java also provides support for thread pools through the java.util.concurrent package, and Apple supports thread pools under the Grand Central Dispatch architecture..

</details>

# 5장 CPU 스케쥴링

<details>
	<summary>접기/펼치기</summary>

운영체제가 프로세스를 프로세서에 할당하는 것을 디스패치(Dispatch)라고 한다. (이때 프로세스 상태가 ready에서 running으로 바뀐다.) 그리고 운영체제가 레디 큐(Ready queue)에 있는 프로세스들 중에서 어떤 프로세스를 디스패치할 것인가 정하는 것이 프로세스 스케줄링(Process scheduling)이다.

스케줄링 알고리즘에는 대표적으로 FCFS, SJF, SRF, RR 네 가지 방식이 있고, 알고리즘을 평가할 때는 수행 시간(Burst time)과 CPU 사용량(CPU utilization), 단위 시간 당 끝마친 프로세스의 수(Throughput), 하나의 프로세스가 레디 큐에서 대기한 시간부터 작업을 마칠 때까지 걸리는 시간(Turnaround time), 프로세스가 레디 큐에서 대기한 시간(Wating time), 프로세스가 처음으로 CPU를 할당받기까지 걸린 시간(Response time)을 기준으로 한다.

선점(Preemptive) 방식과 비선점(Non-Preemptive) 방식으로 나뉜다. 선점 스케줄링은 운영체제가 강제로 프로세스의 사용권을 통제하는 방식이고, 비선점 스케줄링은 프로세스가 스스로 다음 프로세스에게 자리를 넘겨주는 방식이다. 즉, 선점 스케줄링 방식에서는 CPU에 프로세스가 할당되어 있을 때도 운영체제가 개입해 다른 프로세스에게 CPU를 할당할 수 있다.

## Basic Concepts

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter6/6_01_CPU_BurstCycle.jpg)

- A CPU burst of performing calculations, and
- An I/O burst, waiting for data transfer in or out of the system.

### CPU Scheduler
- CPU가 명령을 처리하지 않는(Idle) 상태일 때 ready queue 에서 다음에 수행될 프로세스를 결정하는 것이 CPU scheduler의 역할입니다.
- ready queue 를 구성하는 자료구조와 알고리즘은 반드시 FIFO 형식의 queue 일 필요가 없습니다. 여기에는 다양한 방식이 존재합니다.


CPU 스케쥴링(CPU scheduling decisions)은 아래 상황에서 발생합니다.
  1. a process switches from running to waiting state (e.g. I/O request),
  2. a process switches from running to ready state (e.g. time slice expiration),
  3. a process switches from waiting to ready (e.g. I/O completion), or
  4. a process terminates.
- (1) 과 (4) 에서 발생하는 스케쥴링은 비선점형 입니다.
- (2) 과 (3) 에서 발생하는 스케쥴링은 선점형 입니다.

### Dispatcher
Dispatcher는 스케쥴러에 의해 선택된 프로세스에게 CPU 통제권을 제공하는 모듈입니다. Dispatcher는 아래의 기능을 포함합니다.
  - Switching context.
  - Switching to user mode.
  - Jumping to the proper location in the newly loaded program.
Dispatcher 는 모든 문맥 교환 context switch 동작마다 작동하며 가능한한 빨라야 합니다. Dispathcer에 의해 소모되는 시간을 dispatch latency 라 합니다.

## Scheduling Criteria
- CPU utilization
  - keeps the CPU as busy as possible. (0% ~ 100%)
- Throughput
  - 특정 시간(per time unit)마다 수행 완료되는 프로세스 갯수입니다.
- Turnaround time
  - 요청이 처음 발생했을 때(Time from the submission of a request) 부터 완료될 때까지 걸린 시간입니다.
- Waiting time
  - ready queue 에서 프로세스가 대기한 시간의 총합입니다.
- Response time
  - 요청이 처음 발생했을 때(Time from the submission of a request) 부터 첫 처리 작업(응답response)이 시작될 때까지 걸린 시간입니다.

 ## Scheduling Algorithm
- FCFS (First-Come First-Served)
  - 선입 선처리(비선점형)
- SJF (Shortest-Job-First)
  - 최단 작업 우선(선점형)
- SRTF (Shortest-Remaining-Time-First)
  - 최소 잔여 시간 우선(선점형)
- Priority Scheduling
  - 우선 순위(비선점형 & 선점형)
- RR (Round Robin)
  - 시간 분할(선점형)
- Multilevel Queue
- Multilevel Feedback Queue

 - 선입 선처리 스케쥴링(FCFS)은 가장 단순한 스케쥴링 알고리즘이지만, 짧은 프로세스들이 매우 긴 프로세스들이 끝날 때까지 기다려야 하는 경우를 유발시킵니다. 
 - 최단 작업 우선 스케쥴링(SJF)은 최적임이 증명 가능하며, 가장 짧은 대기 시간을 제공합니다. 
   - SJF 스케쥴링을 구현하는 것은 어려운데, 이는 다음 CPU 버스트의 길이를 예측하기 어렵기 때문입니다.
- SJF 알고리즘은 일반적인 우선순위 스케쥴링 알고리즘의 특별한 경우로 후자는 CPU를 단순히 최고 우선순위의 프로세스에게 할당합니다. 우선순위와 SJF 스케쥴링은 모두 기아 상태를 겪을 수 있습니다. 노화(aging)는 기아 상태를 예방하는 기법입니다.
- 라운드 로빈(RR) 스케쥴링은 시분할(대화형) 시스템에 더 적합합니다. 라운드 로빈 스케쥴링은 준비 완료 큐에 있는 첫 번재 프로세스에게 q시간 단위(time slice) 동안 CPU를 할당합니다. 여기서 q는 시간 할당량이며, q시간 이후에, 프로세스가 CPU를 양도하지 않았다면, OS는 CPU를 선점하고 프로세스는 준비 완료 큐의 꼬리로 이동합니다.
  - 주요 문제는 시간 할당량을 선택하는 것입니다. 시간 할당량이 너무 크면 라운드 로빈 스케쥴링은 선입 선처리 스케쥴링으로 격하되고, 만약 시간 할당량이 너무 적으면, 문맥 교환으로 나타나는 스케쥴링 오버헤드가 지나치게 커집니다.
- 다단계 큐 알고리즘(multilevel queue)들은 준비완료 큐(ready queue)를 다수의 별도의 큐로 분류하며 다양한 클래스의 프로세스들에 대해 상이한 알고리즘을 사용하도록 허용합니다. 가장 보편적인 모델은 라운드 로빈 스케쥴링을 사용하는 전위 대화형 큐와 선입 선처리 스케쥴링을 사용하는 후위 일괄처리 큐입니다.
  - 추가로 큐와 큐 사이의 스케쥴링도 반드시 있어야 하며, 일반적으로 고정 우선순위의 선점형 스케쥴링으로 구현됩니다. 예를 들어 포그라운드 큐는 백그라운드 큐보다 절대적으로 높은 우선순위를 가질 수 있습니다.
  - 일반 다단계 큐에서는 프로세스가 큐에서 다른 큐로 이동할 수 없습니다.
- 다단계 피드백 큐(multilevel feedback queue)는 프로세스들이 한 큐에서 다른 큐로 이동하는 것을 허용합니다.
  - 프로세스들을 CPU 버스트 성격에 따라서 구분하며 어떤 프로세스가 CPU 시간을 너무 많이 사용하면, 낮은 우선순위의 큐로 이동시킵니다. 반대로 낮은 우선순위의 큐에서 너무 오래 대기하는 프로세스들은 높은 우선순위의 큐로 이동할 수 있습니다. 이러한 노화(againg) 방식은 기아 상태를 예방합니다.
 

</details>

# 6장 프로세스 동기화

<details>
	<summary>접기/펼치기</summary>


## Background

동시에 여러 개의 프로세스가 동일한 자료를 접근하여 조작하고, **그 실행 결과가 접근이 발생한 특정 순서에 의존하는 상황을 경쟁상황(race condition)** 이라고 합니다. 경쟁상황으로부터 보호하기 위해, 우리는 한 순간에 하나의 프로세스만이 공유 메모리에 접근할 수 있도록 보장해야 합니다.

## 임계 구역 문제 critical sectioin problem

- 각 프로세스는 임계구역(critical section)이라고 부르는 코드 부분을 포함하고 있고, 그 안에서는 다른 프로세스와 공유하는 변수를 변경하거나, 테이블을 갱신하거나 파일을 쓰거나 하는 등의 작업을 수행합니다.
  - 이 시스템의 중요한 특징은 한 프로세스가 자신의 임계구역에서 수행하는 동안에는 다른 프로세스들은 그들의 임계구역에 들어갈 수 없다는 사실입니다.

- 임계구역의 문제를 해결하기 위한 조건은 아래 세 가지 입니다.
  1. Mutual exclution (상호 배제): 이미 한 프로세스가 critical section에서 작업중일 때 다른 프로세스는 critical section에 진입해서는 안됩니다.
  2. Progress (진행): critical section에서 작업중인 프로세스가 없다면 다른 프로세스가 critical section에 진입할 수 있어야 합니다.
  3. Bounded waiting (한정된 대기): critical section에 진입하려는 프로세스가 무한하게 대기해서는 안됩니다.

## Peterson’s Solution

피터슨의 솔루션은 임계구역과 나머지 구역을 번갈아 가며 실행하는 두 개의 프로세스로 한정됩니다.
- turn은 임계구역으로 진입할 순번, flag 배열은 프로세스가 임계구역으로 진입할 준비가 되었다는 것을 나타냅니다.

```c++

do {
  flag[i] = true;
  turn = j;
  while (flag[j] && turn == j);

  // Critical section

  flag[i] = false;

  // Remainder section

} while(true);

```
## 동기화 하드웨어 Synchronization Hardware

Modern machines provide special atomic hardware instructions.
- Atomic = non-interruptable
- Either test memory word and set value, or
- swap contents of two memory words.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_0304_TestAndSet.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_0506_CompareAndSwap.jpg)


## Mutex Locks
- mutex locks은 여러 스레드가 공통 리소스에 접근하는 것을 제어하는 기법으로, critical section을 보호하고 race condition을 방지하기 위해 mutex 락을 사용합니다. 프로세스는 임계구역에 들어가기 전에 반드시 락을 획득해야 하고 빠져나올 때 락을 반환해야 합니다. ('mutex’는 'MUTual EXclusion’의 축약어) 

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_08_Locks.jpg)

- One problem with the implementation shown here, ( and in the hardware solutions presented earlier ), is the busy loop used to block processes in the acquire phase. These types of locks are referred to as spinlocks, because the CPU just sits and spins while blocking the process.
- Spinlocks are wasteful of cpu cycles, and are a really bad idea on single-cpu single-threaded machines, because the spinlock blocks the entire computer, and doesn't allow any other process to release the lock. ( Until the scheduler kicks the spinning process off of the cpu. )
- On the other hand, spinlocks do not incur the overhead of a context switch, so they are effectively used on multi-threaded machines when it is expected that the lock will be released after a short time.

## Semaphores

- mutex가 일반적으로 동기화 도구의 가장 간단한 형태라면 semaphore는 프로세스들이 자신들의 행동을 더 정교하게 동기화 할 수 있는 방법을 제공합니다.
- semaphore는 정수 변수로서 초기화를 제외하고는 단지 두 개의 표준 원자적 연산 wait()와 signal()로만 접근이 가능합니다. 

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_Semaphores.jpg)

In practice, semaphores can take on one of two forms:
- Binary semaphores can take on one of two values, 0 or 1. They can be used to solve the critical section problem as described above, and can be used as mutexes on systems that do not provide a separate mutex mechanism.
- Counting semaphores can take on any integer value, and are usually used to count the number remaining of some limited resource. The counter is initialized to the number of such resources available in the system, and whenever the counting semaphore is greater than zero, then a process can enter a critical section and use one of the resources. When the counter gets to zero ( or negative in some implementations ), then the process blocks until another process frees up a resource and increments the counting semaphore with a signal call.

### Semaphore Implementation
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_Semaphore2.jpg)

- The big problem with semaphores as described above is the busy loop in the wait call, which consumes CPU cycles without doing any useful work. This type of lock is known as a spinlock
- An alternative approach is to block a process when it is forced to wait for an available semaphore, and swap it out of the CPU. In this implementation each semaphore needs to maintain a list of processes that are blocked waiting for it, so that one of the processes can be woken up and swapped back in when the semaphore becomes available.
  - 대안은 block and wakeup 이 있습니다. semaphore 안에 기다리는 프로세스들의 리스트를 만들어서, 접근하려는 프로세스들을 중지시키되(block) 순서가 되면 해당되는 프로세스를 다시 깨우는(wake up) 방식입니다.

- 세마포어(Semaphore)는 여러 개의 프로세스나 스레드가 critical section에 진입할 수 있는 locking 매커니즘이다. 세마포어는 카운터를 이용해 동시에 리소스에 접근할 수 있는 프로세스를 제한한다. 물론 한 프로세스가 값을 변경할 때 다른 프로세스가 동시에 값을 변경하지는 못한다. 세마포어는 P와 V라는 명령으로 접근할 수 있다. (P, V는 try와 increment를 뜻하는 네덜란드어 Proberen과 Verhogen의 머릿글자다.)

Which is better?
- Busy-waiting
  - No context switching is required.
  - It is good when the length of critical section is short.
- Block-wakeup
  - Context switching is required.
  - It is good when the length of critical section is long


- Deadlocks and Starvation  
두 프로세스가 서로 종료될 때까지 대기하는 프로그램을 실행한다고 생각해보자. 프로세스 A는 B가 종료될 때까지, 프로세스 B는 A가 종료될 때까지 작업을 하지 않기 때문에 프로그램은 어떤 동작도 하지 못할 것이다. 이처럼 두 프로세스가 리소스를 점유하고 놓아주지 않거나, 어떠한 프로세스도 리소스를 점유하지 못하는 상태가 되어 프로그램이 멈추는 현상을 데드락(Deadlock)이라고 한다. 운영체제도 결국 소프트웨어이기 때문에 데드락에 빠질 수 있다.

## Classic Problems of Synchronization
- 유한 버퍼 문제 the bounded-buffer problem
- reader-writer 문제
- 식사하는 철학자들 문제 the dinning-philosophers problem : 교착 상태

</details>

# 7장 교착 상태

<details>
	<summary>접기/펼치기</summary>

다중 프로그래밍 환경에서는 여러 프로세스들이 한정된 자원을 사용하려고 서로 경쟁할 수 있습니다. 한 프로세스가 자원을 요청했을 때, 자원을 사용할 수 없는 상황이 발생할 수 있고, 그 경우 프로세스는 대기 상태로 들어갑니다. 이처럼 대기 중인 프로세스들이(필요한 나머지 자원이 다른 프로세스에 의해 점유되어 있고 그들도 다 대기중인 상황) 결코 그 상태를 다시 변경할 수 없으면 이런 상황을 교착 상태라고 부릅니다.

## System model

 프로세스는 자원을 사용하기 전에 반드시 요청해야 하고 사용 후에는 반드시 방출해야 합니다. 정상적인 작동 모드에서는 프로세스는 다음 순서로만 자원을 사용할 수 있습니다.
 1. 요청Request : 리소스를 요청합니다. 만약 다른 프로세스가 리소스를 사용중이라서 리소스를 받을 수 없다면 대기합니다.
 2. 사용Use : 프로세스는 자원에 대해 작업을 수행할 수 있습니다.
 3. 방출Release : 프로세스가 자원을 반환합니다.



- For all kernel-managed resources, the kernel keeps track of what resources are free and which are allocated, to which process they are allocated, and a queue of processes waiting for this resource to become available. Application-managed resources can be controlled using mutexes or wait( ) and signal( ) calls, ( i.e. binary or counting semaphores. )
- A set of processes is deadlocked when every process in the set is waiting for a resource that is currently allocated to another process in the set ( and which can only be released when that other waiting process makes progress. )

## Deadlock Characterization

#### 데드락은 다음 4가지 조건이 성립할 때 발생합니다.
- 상호배제 Mutual exclusion: 여러 프로세스 중 하나만 critical section에 진입할 수 있을 때.
- 점유하며 대기 Hold and wait: 프로세스 하나가 리소스를 잡고 있고, 다른 것은 대기중일 때.
- 비선점 No preemption: OS가 작동중인 프로세스를 임의로 중단시킬 수 없을 때.
- 순환 대기 Circular wait: 프로세스가 순환적으로 서로를 기다릴 때.

### Resource-Allocation Graph

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter7/7_02_Deadlock.jpg)
deadlock

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter7/7_03_CycleNoDeadlock.jpg)
graph with cycle but no deadlock

## Methods for Handling Deadlocks

데드락을 다루는 방법은 크게 세 가지로 나눌 수 있습니다.
1. 시스템이 결코 교착상태가 되지 않도록 보장하기 위하여 교착상태를 예방하거나 회피하는 프로토콜을 사용합니다.
2. 시스템이 교착상태가 되도록 허용한 다음에 회복시키는 방법이 있습니다.
3. 문제를 무시하고 교착상태가 시스템에서 결코 발생하지 않는 척 합니다.
  - If deadlocks only occur once a year or so, it may be better to simply let them happen and reboot as necessary than to incur the constant overhead and system performance penalties associated with deadlock prevention or detection. This is the approach that both Windows and UNIX take.

## Deadlock Prevention

데드락이 발생하기 위한 네 가지 조건 중 한 가지를 만족시키지 않도록 보장함으로써 데드락을 방지할 수 있습니다.

1. Mutual Exclusion: 적어도 하나의 자원은 공유가 불가능한 자원이어야 합니다. 공유 자원은 배타적인 접근을 보장하지 않으며 데드락의 원인이 될 수 있습니다.
2. Hold and wait: 프로세스가 자원을 요청할 때는, 다른 자원들을 점유하지 않을 것을 반드시 보장해야 합니다. 하나의 프로토콜은 각 프로세스가 실행되기 전에 자신의 모든 자원을 요청하고 할당받을 것을 요구해야 합니다.
3. No preemption: 자원을 점유하고 있는 프로세스가 즉시 할당할 수 없는 자원을 요청하면 os측에서 프로세스의 자원들을 선점해 버립니다. 즉 이들 자원을 암묵적으로 방출해 버립니다.
4. Circular wait: 순환 대기를 막는 한 가지 방법으로는 모든 자원 타입들에게 전체적인 순서를 부여하여, 각 프로세스가 열거된 순서대로 자원을 요청하도록 지정하는 것입니다.

데드락을 방지하는 대안책은 성능상의 오버헤드를 유발하는 단점이 있습니다.

## Deadlock Avoidance

프로세스에게 할당해야 할 자원을 할당하더라도 교착상태를 야기하지 않을 수 있다면 상태가 안전하다고 말합니다.(safe state) 
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter7/7_06_StateSpaces.jpg)

- 자원 할당 그래프 알고리즘 Resource - Allocation Graph Algorithm
  - 다음 자원을 할당할 때 자원 할당 그래프상에서 순환이 발생하지 않다는 것을 확인한 뒤 자원을 할당하는 알고리즘을 통해 데드락을 피할 수 있습니다.
- 은행원 알고리즘 Banker's Algorithm
  - When a process starts up, it must state in advance the maximum allocation of resources it may request, up to the amount available on the system.
  - When a request is made, the scheduler determines whether granting the request would leave the system in a safe state. If not, then the process must wait until the request can be granted safely.

## Deadlock Detection & Recovery

- Allow system to enter deadlock state.

**Detection algorithm.**
- Periodically invoke an algorithm that searches for a cycle in the graph.
  - If there is a cycle, there exists a deadlock.
- [Note] When multiple instances of a resource type, use more complicated algorithm.

**Recovery scheme.**
- Process termination
  - Abort all deadlocked processes.
  - Abort one process at a time until the deadlock cycle is eliminated.
- Resource preemption
  - Preempt some resources from processes and give these resources to other processes until the dedlock cycle is broken.


</details>

# 8장 메모리 관리 전략

<details>
	<summary>접기/펼치기</summary>

## Background
 메모리는 각각 주소가 할당된 일련의 바이트들로 구성됩니다. cpu는 pc(program counter)가 지시하는대로 메모리로부터 다음 수행할 명령어를 가져오는데 그 명령어는 필요한 경우 추가적인 데이터를 더 가져올 수 있으며 반대로 데이터를 메모리로 내보낼 수 있습니다.

 전형적인 명령어 실행은 먼저 메모리로부터 한 명령어를 가져오는 데서부터 시작됩니다. 그 다음 명령어를 해독하고, 메모리에서 피연산자(operand)를 가져와 피연산자에 대해 명령어를 실행한 후에 계산 결과를 메모리에 다시 저장합니다. 메모리는 주소에 지시한 대로 읽기 쓰기만 할 뿐 이 주소들이 어떻게 생성되었는지(명령어 계수기pc, 인덱싱, 간접 및 문자 주소 등) 혹은 그 주소가 가리키는 내용이 무엇인지(데이터 혹은 명령어)를 모릅니다. 

## Basic Hardware

주 메모리와 프로세서 자체에 내장되어 있는 레지스터들은 cpu가 직접 잡근할 수 있는 유일한 범용 저장장치입니다. 기계 명령어들은 메모리 주소를 인수로 취할 수 있지만, 디스크의 주소를 취하지는 못합니다. 즉 모든 실행된느 명령어와 데이터들은 cpu가 직접적으로 접근할 수 있는 주 메모리와 레지스터에 있어야 합니다. 만약 데이터가 메모리에 없다면 cpu 처리 작업 전에 디스크에서 메모리로 적재시켜야 할 것입니다.

- cpu에 내장되어 있는 레지스터들은 일반적으로 cpu 클록(clock) 1 사이클(cycle)내에 접근이 가능하지만, 메모리 버스를 통해 전송되는 주 메모리의 경우는 많은 cpu 클록 사이클이 소요됩니다. 이 경우 cpu가 필요한 데이터가 아직 적재되지 않아 작업을 수행하지 못하는 지연(stall) 현상이 발생하게 됩니다.
  - 이에 대한 해결 방법은 cpu와 주 메모리 사이에 (통상 빠르게 접근할 수 있도록 cpu안에) 빠른 속도의 메모리 캐시(cache)를 추가하는 것입니다.

### Address Binding

일반적으로 프로그램은 디스크에 binary executable 파일로 저장되어 있다. 프로그램을 실행하기 위해서는 메모리에 로드해 프로세스로 만들어야 한다. 이때 디스크에서 메인 메모리로 로드되기를 대기하는 곳이 input queue다. 운영체제는 input queue에서 프로세스를 선택해 메모리에 로드한다.

명령과 데이터를 메모리 주소로 binding하는 시점에 binding이 구분된다.

- Compile time: 만약 compile time에 프로세스가 메모리의 어느 위치에 들어갈지 미리 알고 있다면 absolute codel를 생성할 수 있다. 위치가 변경된다면 코드를 다시 컴파일해야 한다. MS-DOS .COM 형식 프로그램이 예시다.
- Load time: 프로세스가 메모리의 어느 위치에 들어갈지 미리 알 수 없다면 컴파일러는 relocatable code를 만들어야 한다. 이 경우 최종 바인딩은 로드의 소요 시간만큼 지연될 수 있다.
- Execution time: 프로세스가 실행 중 메모리의 한 세그먼트에서 다른 세그먼트로 이동할 수 있다면 바인딩은 runtime까지 지연되어야 한다.
  - 대다수의 os 가 사용하고 있는 방식이며 address mapping을 위한 MMU(Memory Management Unit)가 필요합니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_03_MultistepProcessing.jpg)

### Logical Versus Physical Address Space

- cpu가 생성하는 주소를 일반적으로 논리 주소(logical address)라고 하며, 반면에 메모리가 취급하게 되는 주소(즉 메모리 주소 레지스터(MAR)에 주어지는 주소)는 일반적으로 물리주소(physical address)라 합니다.
  - 이 경우 논리 주소는 가상 주소로도 알려져 있습니다. 
  - 실행시간에 논리 주소를 물리 주소로 변환하는 작업은 memory-management unit, MMU 에 의해 수행됩니다.

- The MMU can take on many forms. One of the simplest is a modification of the base-register scheme described earlier.
- The base register is now termed a relocation register, whose value is added to every memory request at the hardware level.
- Note that user programs never see physical addresses. User programs work entirely in logical address space, and any memory references or manipulations are done using purely logical addresses. Only when the address gets sent to the physical memory chips is the physical memory address generated.


![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_04_DynamicRelocation.jpg)

### Dynamic Loading

- 전체 프로그램을 한번에 메모리에 적재하는 것이 아닌 각 루틴이 실제 호출되기 전까지는 메모에 올라오지 않고 재배치 가능한 상태로 디스크에서 대기하게 하는 방식입니다.
  - 필요한 루틴이 메모리에 적재된다는 것이 장점입니다. 
  - 특정 루틴이 이미 적재되어 있는지 확인하는 과정이 추가되어야 하기 때문에 시스템 복잡성을 증가시킬 수 있습니다.

### Dynamic Linking and Shared Libraries

- With static linking library modules get fully included in executable modules, wasting both disk space and main memory usage, because every program that included a certain routine from the library would have to have their own copy of that routine linked into their executable code.
- With dynamic linking, however, only a stub is linked into the executable module, containing references to the actual library module linked in at run time.
  - This method saves disk space, because the library routines do not need to be fully included in the executable modules, only the stubs.
  - We will also learn that if the code section of the library routines is reentrant, ( meaning it does not modify the code while it runs, making it safe to re-enter it ), then main memory can be saved by loading only one copy of dynamically linked routines into memory and sharing the code amongst all processes that are concurrently using it. ( Each process would have their own copy of the data section of the routines, but that may be small relative to the code segments. ) Obviously the OS must manage shared routines in memory.
  - An added benefit of dynamically linked libraries ( DLLs, also known as shared libraries or shared objects on UNIX systems ) involves easy upgrades and updates. When a program uses a routine from a standard library and the routine changes, then the program must be re-built ( re-linked ) in order to incorporate the changes. However if DLLs are used, then as long as the stub doesn't change, the program can be updated merely by loading new versions of the DLLs onto the system. Version information is maintained in both the program and the DLLs, so that a program can specify a particular version of the DLL if necessary.
  - In practice, the first time a program calls a DLL routine, the stub will recognize the fact and will replace itself with the actual routine from the DLL library. Further calls to the same routine will access the routine directly and not incur the overhead of the stub access. ( Following the UML Proxy Pattern. )

## swapping

 프로세스가 실행되기 위해서는 메모리에 있어야 하지만 프로세스는 실행 중에 임시로 예비 저장장치(backup store)로 내보내어졌다가 실행을 계속하기 위해 다시 메모리로 되돌아 올 수 있습니다. 모든 프로세스의 물리 주소 공간 크기의 총합이 시스템의 실제 물리 메모리 크기보다 큰 경우에도 스와핑을 이용하면 동시에 실행하는 것이 가능하게 합니다.
  - ready queue에서 대기중인 프로세스를 cpu가 고르고 dispatcher를 호출하면 dispatcher는 다음 프로세스가 메모리에 올라와 있는지 확인하며 올라와 있지 않다면 디스크에서 불러옵니다.(swap in)
  - 만약 이 프로세스를 위한 공간이 없다면 공간을 만들기 위해 현재 메모리에 올라와 있는 프로세스를 내보내고(swap out) 원하는 프로세스를 불러옵니다.


 ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_05_ProcessSwapping.jpg)


## Contiguous Memory Allocation

- One approach to memory management is to load each process into a contiguous space. The operating system is allocated space first, usually at either low or high memory locations, and then the remaining available memory is allocated to processes as needed. ( The OS is usually loaded low, because that is where the interrupt vectors are located, but on older systems part of the OS was loaded high to make more room in low memory ( within the 640K barrier ) for user processes. )

### Memory Protection

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_06_HardwareSupport.jpg)

- 사용자 프로그램이 유효하지 못한 메모리 주소에 접근하는 것을 막는 방법입니다. 
  - limit 레지스터가 논리 주소의 범위를 제한합니다. 만약 범위를 넘어선다면 trap을 발생시킵니다.

### Memory Allocation
- One method of allocating contiguous memory is to divide all available memory into equal sized partitions, and to assign each process to their own partition. This restricts both the number of simultaneous processes and the maximum size of each process, and is no longer used.
- An alternate approach is to keep a list of unused ( free ) memory blocks ( holes ), and to find a hole of a suitable size whenever a process needs to be loaded into memory. There are many different strategies for finding the "best" allocation of memory to processes, including the three most commonly discussed:
  - first fit
  - best fit
  - worst fit

### Fragmentation
- 내부단편화internal fragmentation은 실제 프로세스 공간보다 큰 메모리를 할당하게 되는 경우를 말한다. 일반적으로 메모리가 시스템 효율을 위해 고정 크기의 정수 배로 할당되기 때문에 생기는 현상이다.
- 외부단편화external fragmentation은 특정 프로세스를 적재하기에 전체 메모리의 빈 공간은 충분하지만, 각 메모리 공간이 흩어져 있어서 프로세스를 메모리에 올릴 수 없는 현상.

## Segmentation
segmentation은 하나의 프로세스를 여러 개로 나누는 것을 말한다. segment는 main, function, method, object 등의 논리적 단위로, 인간의 관점으로 프로세스를 나눈 것이다. 각 segment의 base와 limit은 segment table에 저장된다.
  - 프로그래머가 생각하는 논리 구조대로 프로세스를 나눕니다. 
  - 세그멘테이션은 프로세스가 적재되는 물리 주소 공간이 연속적이지 않아도 적재를 허용하지만 외부 단편화를 유발할 수 있으며 메모리 압축(compact)작업이 필요할 수 있습니다.
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_08_SegmentationHardware.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_09_Segmentation.jpg)

## paging
- 페이징은 또 다른 메모리 관리 기법으로 프로세스를 동일한 크기로 (page) 나눔으로써 외부 단편화를 방지하고 단편화에 따른 압축 작업이 필요하지 않습니다. 

- Entire program image resides on disk.
- When the program starts, just load the first page only.
- The rest of pages are loaded in memory on-demand.
- A particular page X of the program can be either
  - already loaded in memory page frame Y, or
  - never been loaded before, it is in disk.
- Pages can be placed anywhere in memory.
- Whenever CPU presents an address, MMU looks up page table.
  - For translating logical address to physical address.

- paging에서는 physical memory의 각 block을 frame이라고 하고, logical memory의 각 block을 page라고 부른다. frame을 작게 나눌수록 fragment가 적게 생기며, 실제로 external fragmentation은 거의 생기지 않는다. logical address를 physical address로 변환하는 page table이 필요하다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_10_PagingHardware.jpg)

- page table은 메모리에 저장되어 있다. PTBR(Page-Table Base Register)가 page table을 가리키고, PTLR(Page-Table Length Register)가 page table의 크기를 가지고 있다. 따라서 매번 데이터에 접근할 때마다 한 번은 데이터에, 한 번은 page table에 접근해야 한다. 물론 이는 비효율적인 일이기 때문에 캐시같은 것을 사용해 해결했다.

- TLB(Translation Look-aside Buffer)는 참조했던 페이지를 담아주는 캐시 역할을 한다. TLB는 key-value pair로 데이터를 관리하는 acssociative memory이며, CPU는 page table보다 TLB을 우선적으로 참조한다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_11_PagingModel.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_11A_PageNumberOffset.jpg)

- CPU에 의해 만들어진 주소는 page number(p)와 page offset(d) 두 부분으로 나뉜다. page number는 page table의 index로써 page table에 접근할 때 사용된다. page offset은 physical address를 얻을 때 쓰이며, page table의 base address에 page offset을 더하면 physical address를 구할 수 있다.

### Protection
메모리 할당이 contiguous한 경우 limit만 비교해도 메모리를 보호할 수 있었다. 하지만 paging은 contiguous하지 않기 때문에 다른 방법을 쓴다. page table의 각 항목에는 valid-invalid bit가 붙어있어 그 값이 valid라면 해당 페이지에 접근이 가능하고, invalid라면 해당 페이지가 logical address space에 속하지 않아 접근할 수 없다는 것을 의미한다.

### Shared Pages
paging의 또 다른 장점은 코드를 쉽게 공유할 수 있다는 것이다. 만약 코드가 reentrant code(또는 pure code)라면 공유가 가능하다. reentrant code는 runtime 동안 절대로 변하지 않는 코드이며, 따라서 여러 프로세스들이 동시에 같은 코드를 수행할 수 있다. 이런 식으로 공통 page를 공유하면 12개 로드해야 할 것을 6개만 로드해도 된다.

</details>


# 9장 가상 메모리

<details>
	<summary>접기/펼치기</summary>

가상 메모리(virtual memory)라는 것은 프로세스 전체가 메모리 내에 올라오지 않더라도 실행이 가능하도록 하는 기법입니다. 가상 메모리는 물리 메모리로부터 사용자 관점의 논리 메모리를 분리시켜 메인 메모리를 추상화시켜 사용자는 매우 큰 가상 주소 공간을 가정하고 프로그램을 만들 수 있게 됩니다.
- 이 기법의 주요 장점 중 하나는 사용자 프로그램이 물리 메모리(physical memory)보다 커져도 된다는 점입니다.
- 또한 파일의 공유를 쉽게 해주고 공유 메모리 구현을 가능하게 합니다.
- 추가적으로 프로세스 생성을 효율적으로 처리할 수 있는 기법을 제공합니다.
- 보통 프로그램이 실행될 때 프로그램 전체가 필요한 것이 아닌 일부분만이 필요한 점을 바탕으로 필요한 부분만을 디스크에서 메모리로 가져옵니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_01_VirtualMemoryLarger.jpg)

논리 메모리를 물리 메모리로부터 분리시켜주는 것 외에 가상 메모리는 페이지 공유를 통해 파일이나 메모리가 둘 또는 그 이상의 프로세스들에 의해 고융되는 것을 가능하게 합니다.
- 시스템 라이브러리가 여러 프로세스들에게 공유될 수 있습니다.
- 마찬가지로 프로세스들이 메모리를 공유할 수 있습니다.

## Demanding Page

- 프로그램의 전체가 메모리에 있어야 할 필요는 없습니다.(보편적인 경우) 요구 페이징은 실제 프로그램 실행 시에 페이지들이 실행과정에서 실제로 필요해 질 때 적재됩니다. 메모리에 접근하기 전 페이지 테이블을 참조하며, 필요한 페이지가 현재 메모리에 적재되어 있는 상태인지 valid-invalid bit를 통해 확인합니다.
  - 페이지 테이블을 참조할 때 valid-invalid bit가 유효하지 않은 경우 해당 페이지가 메모리에 적재되지 않은 상태이므로 page fault trap을 발생시킵니다. 이 트랩은 운영체제에게 페이지 부재를 처리해야함을 알립니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_05_PageTable.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_06_PageFaultSteps.jpg)

## Copy-on-Write

- fork() 명령어를 통해 자식 프로세스를 생성할 때 자식 프로세스가 부모의 페이지를 당분간 함께 사용하도록 합니다. 이때 공유되는 페이지를 쓰기 시 복사(copy on write) 페이지라고 표시합니다.
  - "둘 중 한 프로세스가 공유 중인 페이지를 쓸 때 그 페이지의 복사본이 만들어진다" 라는 의미입니다.
  - 즉 공유 페이지 중 수정되지 않는 페이지는 부모와 자식 프로세스가 복사과정 없이 그대로 공유하지만, 만약에 어떤 페이지에 대해서 수정 작업이(write) 발생한다면 해당 페이지에 대해서만 복사본을 생성합니다.(copy)

## Page Replacement

- 메인메모리의 많은 페이지를 할당하여 용량이 가득 찼다면(비어있는 프레임이 없다면) swap out 을 통해 기존의 페이지를 frame을 해제하여 메모리 공간을 확보할 수 있습니다. 이때 해제할 프레임을 선택하는 페이지 교체 알고리즘을 활용합니다.

### 페이지 교체 알고리즘
- FIFO : 메모리에 가장 먼저 적재된 페이지를 선택합니다.
  - Belady's anomaly : 프로세스에게 프레임을 더 주었는데 페이지 증가율이 오히려 더 증가하는 현상입니다. 추후에 필요한 프레임을 해제해 버리는 것이 원인입니다.
- Optimal Page Replacement 최적 페이지 교체 : 앞으로 가장 오랫동안 사용되지 않을 페이지를 선택합니다. 실제 구현이 어렵습니다.
- LRU Least Recently Used : 가장 오랜 기간 사용되지 않았던 페이지를 선택합니다.
  - FIFO 방식보다 우수하고 Belady's anomaly가 발생하지 않습니다. 하지만 참조 시간을 기록하기 위한 하드웨어의 지원이 필요합니다.
  - LRU 근사 페이지 교체(LRU Approximation Page Replacement) 알고리즘으로 부가적 참조 비트 알고리즘 등이 있습니다.
- LFU Least Frequently Used : 참조 회수가 가장 작은 페이지를 선택합니다. 각 페이지를 참조할 때 마다 참조 횟수를 기록합니다.

## Allocation of Frames

- 여러 개의 프로세스가 있을 때 이들에게 프레임을 어떻게 할당할 것인지 결정하는 알고리즘입니다.
  - 예를 들어 가용 프레임이 90개 이고 실행하는 프로세스가 5개 일 때 각 프로세스에게 몇 개의 가용 프레임을 할당할 것인지 결정합니다.

- 균등할당equal allocation 알고리즘
- 비례할당proportional allocation 알고리즘
- 전역 대 지역 할당 global versus local allocation : 페이지를 할당할 때 페이지 교체 알고리즘을 크게 전역교체 global replacement와 지역 교체 local replacement 두 가지로 나눕니다.
  - 지역 교체의 경우 프로세스가 교체할 프레임을 선택할 때, 자기에게 할당된 프레임들 중에서만 교체 대상을 고릅니다.
  - 전역 교체의 경우 프로세스가 교체할 프레임을 선택할 때, 자기에게 할당된 프레임 외에도 다른 프로세스에 속한 프레임을 포함해 전역 범위에서 결정합니다.

## Thrashing

- 어떤 프로세스에 대해서 활발하게 사용되는 페이지 집합을 지원해 줄 만큼 프레임을 충분히 할당받지 못했다면 해당 프로세스가 동작할 때 페이지 부재가 바로 발생할 것입니다. 프레임들은 이미 활발하게 사용되는 페이지들로 이루어져 있으므로 어떤 프레임을 교체하건 곧 다시 페이지 부재가 발생하며 또 다시 읽어와야 할 것입니다. 이런 과도한 페이징 작업을 스레싱(thrashing)이라고 부릅니다. 어떤 프로세스가 실제 실행보다 페이징에 더 많은 시간을 사용하고 있을 경우 스레싱이 발생했다고 합니다.
  - 스레싱은 심각한 성능 저하를 초래합니다.
  - 스레싱이 발생하면 페이징 장치에 대한 큐잉이 진행되면서 ready 큐는 비게 됩니다. 프로세스들이 페이징 장치를 기다리는 동안 cpu 이용률은 현저하게 떨어집니다.
    - 이때 cpu 스케쥴러는 이용률이 떨어지는 것을 보고 이용률을 다시 높이기 위해서 새로운 프로세스를 추가합니다.
	- 새로 추가된 프로세스에는 기존의 프로세스가 가진 frame을 가져와서 할당합니다. 기존의 프로세스는 안 그래도 부족한 프레임 중에서 일부를 반환합니다. 페이지 부재율은 더욱 높아지며 cpu 이용률은 급격히 감소합니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_18_Thrashing.jpg)

- 스레싱을 해결하기 위한 방법은 프로세스 실행의 지역성 모델(locality model)을 기반으로 합니다.
- 작업 집합 모델(working set model)의 기본 아이디어는 최근 특정 기준 시간 만큼의 페이지 참조를 관찰하는 것입니다. 한 프로세스가 최근 페이지를 참조했다면 그 안에 들어있는 서로 다른 페이지들의 집합을 작업 집합이라고 부릅니다.
  - 페이지가 활발하게 사용되면 작업 집합에 포함되지만, 기준 시간 이상으로 사용되지 않으면 작업 집합에서 제외되게 될 것입니다.
  - 작업 집합 모델을 결정한 뒤에 os는 프로세스의 작업 집합을 감시하면서 집합 크기에 맞는 충분한 프레임을 할당합니다. 이 방법은 가능한 최대의 다중 프로그래밍의 정도를 유지하면서도 스레싱을 방지할 수 있게 해줍니다. 따라서 CPU의 이용률도 최적화됩니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_20_WorkingSetModel.jpg)

</details>
