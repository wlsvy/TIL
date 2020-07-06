# 운영체제

저자 : Abraham Silberschatz, Peter B. Galvin, Greg Gagne
9판 요약 정리

##### Reference
- [parksb 블로그](https://parksb.github.io/article/5.html)

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
- OS executes the applications.
- OS makes the computer system convenient to use.
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

- 이러한 이중 모드(Dual-mode) 방식을 사용하면 잘못된 사용으로부터 시스템과 사용자를 보호할 수 있다. 하드웨어는 커널 모드일 때만 특권 명령(Privileged instructions)를 실행한다. 만약 유저 모드에서 특권 명령을 실행하려 한다면 하드웨어는 이 동작을 막고 운영체제에게 트랩을 보낼 것이다. 유저 모드에서 커널 모드의 기능을 호출하고 싶다면 시스템 콜(System call)을 활용합니다.

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
`시스템 호출 system call`은 운영체제의 의해 사용 가능하게 된 서비스에 대한 인터페이스를 제공합니다.

- interface provided by the OS.
- how a program requests a service from an operating system.
	- E.g. accessing the hard disk
	- E.g. creating and executing new processes
- provide an essential interface between a process and operating system.
- typically written in a high-level language (C or C++)

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
6.	Protection
	- set/get permission, allow/deny user
	- E.g. chmod()...

### Application Program Interface (API)
- A set of functions available to application programmer.
- Three most common APIs
	- Win32 API for Windows.
	- POSIX API for POSIX-based systems (UNIX/Linux).
	- Java API for the Java virtual machine.
- Why use APIs rather than system calls?
	- Portability
	- Easy to use
	- api를 활용한다면 응용 프로그래머는 자신의 프로그램이 같은 api를 지원하는 어느 시스템에서건 컴파일 되고 실행되는 것을 기대할 수 있습니다.
	- 또한 실제 시스템 콜은 종종 좀 더 자세한 명세가 필요하고 프로그램 상에서 작업하기가 응용 프로그래머에게 가용한 api 보다 어렵습니다.
- Programmer dose not need to know system call implementation.
	- Just needs to obey API and understand what OS will do.
	- Details of OS are hidden from programmer by API.
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
