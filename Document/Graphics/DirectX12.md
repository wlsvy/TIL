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


## Anti aliasing

#### Reference
- [slide share : anti-aliasing](https://www.slideshare.net/JinWooLee2/anti-aliasing)
- [mynameismjp : msaa-overview](https://mynameismjp.wordpress.com/2012/10/24/msaa-overview/)

- 안티 앨리어싱은 기하 구조를 픽셀로 표현할 때 나타나는 계단 현상을 처리하는 기법입니다.

### SSAA(Super-Sampling Anti-Aliasing = FSAA(Full-Scene AA))
![](https://www.sapphirenation.net/-/media/sites/sapphirenation/articles/2016/11/1.jpg)
- 모든 픽셀에 대하여 픽셀당 한 개 이상의 샘플을 추출해 평균값을 구합니다.
- 표시하는 해상도 보다도 고해상도로 렌더링 한 뒤 원래 해상도로 축소시킵니다.
- 고해상도로 렌더링하기 때문에 부하가 굉장히 큽니다.

### MSAA(Multi-Sampling Anti-Aliasing)

- Super-Sampling을 효율과 성능면에서 최적화한 방식입니다.

![](https://mynameismjp.files.wordpress.com/2012/10/msaa_rasterization.png0)

- MSAA (N)x : 하나의 픽셀은 N 개의 서브 샘플(subsample)을 가지게 됩니다.
  - SSAA의 경우 목표로 하는 기존의 렌더타겟보다 고해상도의 렌더 타겟의 모든 픽셀에 대해서 픽셀 쉐이더 연산을 수행합니다. 하지만 MSAA의 경우, 기존의 렌더 타겟에 대응하는 픽셀에 대해서만 픽셀 쉐이더 연산을 수행합니다.(SSAA가 기존보다 4배 고해상도 렌더링을 한다고 하면 픽셀 쉐이더 연산량도 4배가 되지만, MSAA 는 2x, 4x 의 경우 상관없이 픽셀 쉐이더 연산량은 변하지 않습니다.)
  - 아래의 사진에서 알 수 있듯이 특정 픽셀이 삼각형 내부에 완전히 포함된다면, 해당 픽셀 쉐이더의 결과값은 온전히 반영될 것입니다. 하지만 픽셀의 서브 샘플을 반정도 걸치는 경우에는 픽셀 쉐이더의 결과값이 삼각형이 걸치는 서브 샘플의 비율 만큼(2/4 => 50%) 결과값이 반영됩니다. 
  - 각 픽셀의 서브 샘플마다 깊이 테스트가 수행되어야 합니다. 이 말은 즉 MSAA 를 수행하기 위해서는 기존의 z-buffer가 N 사이즈 만큼 커야 합니다.( MSAA 2x 의 경우 z-buffer는 기존보다 2배 커야 합니다.)
  - 픽셀 쉐이더 연산은 특정 삼각형이 픽셀의 서브 샘플에 하나라도 걸치는 경우 수행됩니다. 즉 아래 사진에서 삼각형이 걸쳤다고 판정되지 않는 왼쪽 사진의 경우, 해당 픽셀에 대해서는 픽셀 쉐이더 연산이 수행되지 않습니다.

![](https://mynameismjp.files.wordpress.com/2012/10/msaa_partial_coverage2.png?w=1024&h=234)

### FXAA
### TXAA
