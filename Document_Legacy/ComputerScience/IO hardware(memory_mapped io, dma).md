# I/O Hardware

##### Reference
- [OperatingSystems CourseNotes](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/13_IOSystems.html)

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter13/13_01_TypicalBus.jpg)

- 컴퓨터 장치는 크게 저장 장치(디스크, 테이프), 전송 장치(네트워크 연결, 블루투스) 그리고 사용자 인터페이스 장치(키보드, 스크린, 마우스 등) 등으로 나눌 수 있습니다. 하드웨어 장치는 케이블을 통하거나 무선으로 신호를 보냄으로써 컴퓨터 시스템과 통신 합니다. 이들 장치는 포트(port)라 불리는 연결점을 통해 컴퓨터와 접속하며 만약 하나 이상의 장치들이 공동으로 여러 선들(wire)을 사용한다면, 이러한 선을 버스(bus)라고 부릅니다.
  - 버스의 정의는 회선의 집합으로써 이를 통해 어떻게 해야 메시지들을 주고받을 수 있는지를 정한 프로토콜(protocol)까지를 포함합니다.

## Programmed I/O
- Port I/O
  - Special processor instructions are used to transfer data.
    - in/out instructions in Intel architecture.
  - Each device uses a different I/O port. (port number)
- Memory-mapped I/O
  - The registers in device controller are mapped into physical address space.
    - Addresses are set by hardware jumpers or programming at boot time.
  - I/O is accomplished with load and store instructions.
  - Since I/O address space occupies a range in the system memory address space, it is not available for processes.

## Direct Memory Access

- Used to avoid programmed I/O for large data movement.
- Gives the access to memory bus to the DMA controller.
- Bypasses CPU to transfer data directly between I/O device and memory.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter13/13_05_DMA_Transfer.jpg)
- For devices that transfer large quantities of data ( such as disk controllers ), it is wasteful to tie up the CPU transferring data in and out of registers one byte at a time.
- Instead this work can be off-loaded to a special processor, known as the Direct Memory Access, DMA, Controller.
- The host issues a command to the DMA controller, indicating the location where the data is located, the location where the data is to be transferred to, and the number of bytes of data to transfer. The DMA controller handles the data transfer, and then interrupts the CPU when the transfer is complete.
- DMA can be done in terms of either physical addresses or virtual addresses that are mapped to physical addresses. The latter approach is known as Direct Virtual Memory Access, DVMA, and allows direct data transfer from one memory-mapped device to another without using the main memory chips.
