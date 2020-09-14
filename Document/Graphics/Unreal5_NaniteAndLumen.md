#### Reference
- [itmo](https://news.itmo.ru/en/startups_and_business/innovations/news/9473/)
- [unreal : mesh distance field](https://docs.unrealengine.com/en-US/Engine/Rendering/LightingAndShadows/MeshDistanceFields/index.html)
- [raymarchingdf](https://iquilezles.org/www/articles/raymarchingdf/raymarchingdf.htm)

# Nanaite
- 나나이트를 활용한다면 더 이상 메쉬를 렌더링 할때, 노말맵/LOD 기법이 필요하지 않습니다.
  - 테셀레이션 기반으로 특정 메쉬를 픽셀보다 작아질 때까지 쪼갭니다. displacement map이 있다면 메쉬를 최대 디테일로 표현할 수 있게 됩니다.
  - 노말 맵의 경우 복잡한 메쉬를 단순하게 표현하기 위한 최적화 기법의 일종이지만, 나나이트에서는 displacement map으로 대체 가능합니다.
  - LOD의 경우 카메라로 부터 멀리 떨어진 오브젝트를 낮은 디테일로 표현하는 방식입니다. 나나이트의 경우, 카메라 근처에 위치해 수만 개의 픽셀을 차지하는 메쉬의 경우, 테셀레이션 과정에 의해 수만 개의 삼각형으로 쪼개질 것이고 카메라로부터 멀리 떨어져 수백 개의 픽셀만을 차지하는 메쉬의 경우, 메쉬는 수백개의 삼각형으로 쪼개질 것입니다. 카메라와의 거리와 관계없이 테셀레이션 과정에 의해 메쉬는 모니터 상 표현될 수 있는 최대 디테일로 표현됩니다. 더 이상 LOD를 고려하지 않아도 된다는 것은 이런 맥락입니다.
  
- Unreal 5 시연 영상은 ps5 기반이며 ps5의 SSD는 5.5GB/s의 저장소 대역폭을 가지고 있습니다. (PC의 경우 저장소 대역폭이 보통 0.5 ~ 3GB/s입니다.) 나나이트를 구동하기 위해서 굉장히 빠른 속도로 고해상도 에셋을 다루는 하드웨어 성능이 필요하다고 말해집니다.

# Lumen
- 게임 구동 전 사전에 GI(Global Illumination) 정보를 굽는(bake) 것이 아닌 실시간으로 연산하여 조명을 표현하는 기술입니다.

- 크게 3 가지 단계로 나눠집니다.
1. voxelize : 씬 내의 오브젝트들을 복셀라이즈(voxelize : 마인크래프트 처럼 복잡한 메쉬들을 동일 크기의 정육면체들로 단순화 시킵니다)
2. SDF(Signed Distance Fields) : 복셀라이즈되어진 씬 정보를 바탕으로 Signed Distance Fields 이미지를 생성합니다. 
3. SSGI(Screen Space Global Illumination) : 주어진 정보를 바탕으로 SSGI를 수행합니다. 하지만 screen space 특성상 기하 구조가 화면 상에 온전히 나타나지 않는 부분도 있는 만큼 조명 연산 결과가 정확하지 않을 수 있다고 합니다.
