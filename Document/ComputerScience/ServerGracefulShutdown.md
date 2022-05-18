# Graceful Shutdown

## Graceful Shutdown

Graceful shutdown and hard shutdown are two opposing methods of turning off a computer. A graceful shutdown is when a computer is turned off by software function and the operating system (OS) is allowed to perform its tasks of safely shutting down processes and closing connections. A hard shutdown is when the computer is forcibly shut down by interruption of power.

Generally, a graceful shutdown is preferable in the case of any OS that saves its state. When the standard shutdown procedures are not done with these OSs, the result can be data corruption of program and operating system files. The result of the corruption can be instability, incorrect functioning or failure to boot.

- graceful shutdown 은 OS 가 프로그램의 상태를 기록할 필요가 있을 때 (혹은 그 외에 다양한 목적으로 기록해야 할 데이터가 있을 때) 사용되야 할 겁니다. 예컨대 데이터 기록 중에 hard shutdown 이 발생해서 데이터가 오염되기라도 한다면 큰 문제가 될 수 있습니다.

Many modern OSs and other software are fault tolerant and generally handle the odd power interruption without issue. Both Bare metal and virtualized systems can be affected by hard shutdowns, so they should be avoided when unnecessary. Virtual machines (VM) may need to be restored from backups, while bare metal systems may even require a full reinstall.

- 출처 [definition/graceful-shutdown-and-hard-shutdown](https://www.techtarget.com/whatis/definition/graceful-shutdown-and-hard-shutdown)

## Graceful Exit

프로그램이 실행 중에 치명적인 오류가 발생한다 하더라도, 해당 프로그램은 적합한 대처 절차를 수행하며 종료할 수 있어야 합니다. 발견된 오류는 적어도 로그 형식으로 남아 개발자들이 후속 조치를 취해야 할 수 있어야 하겠지요.

- 출처 [wiki : Graceful_exit](https://en.wikipedia.org/wiki/Graceful_exit)