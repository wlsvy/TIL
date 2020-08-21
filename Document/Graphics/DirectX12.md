> ## DirectX 12 프로젝트 [Ladybug3D](https://github.com/wlsvy/Ladybug3D)를 진행하면서 공부한 내용을 작성한 페이지입니다.
> - ### cmake에 대해 정리한 내용은 [여기](https://github.com/wlsvy/CMake_Study)에 있습니다.

#### Reference 
- [Microsoft : important-changes-from-directx-11-to-directx-12](https://docs.microsoft.com/en-us/windows/win32/direct3d12/important-changes-from-directx-11-to-directx-12)
- [Microsoft : user-mode-heap-synchronization](https://docs.microsoft.com/ko-kr/windows/win32/direct3d12/user-mode-heap-synchronization?redirectedfrom=MSDN)
- [3dgep : directx12 tutorial](https://www.3dgep.com/learning-directx-12-1/)

## 공부하면서 체감한 DirectX 12 과 DirectX 11의 차이점 
- Dx12의 경우 gpu의 병렬처리를 좀더 적극적으로 활용하기 위해 api가 설계되었다고 느끼고 있습니다. (보다 쉬운 설명을 위해 cpu는 싱글 스레드 환경이라고 가정하겠습니다.)
- Dx11를 활용하는 경우 cpu 측에서 gpu 인터페이스를 통해 명령을 내릴 경우, 각 명령마다 cpu는 gpu가 명령을 수행할 때까지 대기하게 됩니다. 
- Dx12의 경우, Dx11과 렌더링 파이프라인은 동일하지만 `commandQueue`, `fence` 개념이 등장합니다. Dx11 에서는 gpu에 명령을 내릴때마다 gpu가 명령을 수행 완료될 때까지 cpu가 기다려야 한다면 Dx12 환경에서는 cpu가 렌더링 명령을 곧장 gpu측에 전달하는 것이 아니라, 먼저 commandQueue 담아두게 됩니다. 
  - commandQueue에 입력된 명령들을 gpu가 일괄처리 할 수 있도록, cpu에서 명령을 입력받는 과정과 gpu에서 명령을 처리하는 과정을 분리한 것입니다.

> 렌더링 기법 중에서 forward rendering 과 deferred rendering 의 차이를 보는 것 같았습니다.

![](https://docs.microsoft.com/en-us/windows/win32/direct3d12/images/gpu-engines.png)
> 위의 그림에서 처럼 gpu에서 처리될 일련의 명령들이 commandList가 됩니다. commandList는 종류별로(copy : 자원 복사, compute : gpu 연산(compute shader), 3d : 렌더링) 구분되어 commandQueue 담겨집니다.

- 즉 요약하면 이렇습니다. 매 프레임마다 cpu는 gpu에 전달한 명령들을 큐에 입력시키며 gpu는 프레임이 업데이트 되기 전 commandQueue의 명령들을 병렬처리를 통해 일괄적으로 하는 것입니다. 
  - 지금은 추측이지만, dx12가 drawcall 의 오버헤드를 줄었다는 특징은 이런 맥락에서 나타나는 것이 아닐까 생각합니다.

- '병렬 처리'에 주목합시다. gpu에 전달되는 명령들은 종류별로 분류될 수 있지만 각 명령들이 서로에게 의존성을 가지고 있는 경우가 존재합니다. 특정 명령을 수행하기에 앞서 선행되어야 할 명령이 존재한다면 이러한 정보 역시 gpu에게 전달되어야 할 것입니다. `fence`가 이 역할을 맡습니다.

![](https://www.3dgep.com/wp-content/uploads/2017/11/GPU-Synchronization.png)
> 개인적으로 fence의 개념 이해를 돕는 이미지를 찾아봤습니다만.... 어렵긴 해도 괜찮은 자료가 위 그림 밖에 없습니다.

- fence는 멀티스레딩의 semaphore와 닮아있습니다. fence 에는 64비트 unsigned 정수값을 포함합니다. 멀티스레딩에서 semaphore의 값을 확인해 프로세서가 임계 구역(critical section)에 접근하는 것을 제한하듯, gpu는 commandList의 signal 값과 fence 값을 확인하며 해당 명령이 지금 수행가능 여부를 판별하는 것입니다.
