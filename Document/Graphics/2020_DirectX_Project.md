# 2020_DirectX_Project

> ### [Direct X 11 개인 프로젝트](https://github.com/wlsvy/2020_DirectX_Project) 를 진행하면서 공부한 내용을 작성한 페이지입니다.

## GameObject - Component System

<details>
  <summary>접기/펼치기</summary>

Entity - Component System 으로 불리기도 합니다.
  - Unity 에서는 ECS가 다른 의미로 쓰이는데 DOTS(Data oriented tech stack)을 활용한 컴포넌트 설계를 말합니다.
  
- Entity - A container into which components can be added, usually hierarchical (any Entity can have sub-Entities).
- Component - Class of objects through which behaviors, looks and data can be added to an entity.
  
![](https://jlnr.de/images/game-object-inheritance/single-inheritance.svg)

- 2002 년 Scott Bilas 가 발표한 GDC 강연에 따르면 기존의 GameObject 설계는 위의 그림처럼 클래스를 상속하는 방식을 활용했습니다. 하지만 각각의 gameObject가 가지는 수많은 특징들은 얽히고 설키기 마련인데 이런 점은 단순히 클래스 상속으로 표현하기에는 한계점이 많았습니다. (그렇다고 다중 상속/가상 상속을 사용하자니 굉장히 위험했고요) Scott Bilas는 이 점을 지적하면서 새로운 component system 설계를 제안하게 됩니다.

![](https://answers.unity.com/storage/temp/119482-family.png)
> 유니티 엔진 활용 예시

그렇지만 component를 활용한 구조가 항상 좋은 것은 아닙니다. 장단점은 아래와 같습니다.


- #### 클래스 상속 구조 < component 활용 구조
  - 동적으로 gameObject의 특성을 정의할 수 있다는 것이 대표적입니다. 파생클래스를 작성한다는 것은 컴파일 되는 시점에 그 클래스의 특성이 결정되어 바뀌지 않는다고 볼 수 있습니다. 하지만 component의 경우, 런타임 중에 component 객체를 만들어 gameObject에 포함시키거나 제외시킬 수 있습니다. 
  - 공통되는 특성에 대해 하나의 component를 작성해 둔다면, 해당 component를 계속 재사용할 수 있는 이점이 있습니다.
  - No programmer required for designers to modify game logic
  - Circumvents the “impossible” problem of hard-coding all entity relationships at start of project
  - Allows for easy implementation of game-design ideas that cross-cut traditional OOP objects
  - Much faster compile/test/debug cycles
  - Much more agile way to develop code

- #### 클래스 상속 구조 > component 활용 구조
  - component는 동적으로 생성되어 gameObject에 할당될 수 있으므로 메모리를 동적으로 여러번 할당받아야 한다고 볼 수 있습니다. 이 경우, 특정 component의 할당 / 반환 작업이 여러번 이루어진다면 메모리 단편화 문제가 발생할 여지가 있습니다. 
  - 정적인 클래스의 경우, 해당 클래스가 어떤 멤버/메서드을 포함하고 있는지는 코드를 작성하는 그 순간에도 확인할 수 있습니다. 그렇지만 component를 활용하는 경우, 특정 gameObject가 어떤 기능을 가지고 있는지 확인하고 싶을 때 해당 기능을 포함하는 component가 존재하는지 런타임에 확인해야 합니다. 이 경우 gameObject의 component 배열을 한번 순회해야 하기 때문에 오버헤드 비용을 지불해야 할 수 있습니다. 
  - component 간의 통신을 할 때도 오류가 발생한다면 정적인 파생클래스의 경우보다 디버그 추적이 더 힘들 수 있습니다.



##### Reference 
- [entity-component system](http://entity-systems.wikidot.com/)
- [Scott Bilas 2002 GDC 강연 내용](https://www.gamedevs.org/uploads/data-driven-game-object-system.pdf)
- [wiki](https://en.wikipedia.org/wiki/Entity_component_system)
- [t-machine.org](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)

</details>

## DirectX 11 Rendering Pipeline

<details>
  <summary>접기/펼치기</summary>
  
![](https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-pipeline-stages.jpg)
- DirectX 11의 렌더링 파이프라인은 shader를 활용한 programmable pipeline 입니다.

- [Input-Assembler](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-input-assembler-stage) : 파이프라인 진입 단계입니다. 사용자가 입력한 버퍼의 기하 물체의 기초primitive 데이터를 전달 받아 이후 단계에서 사용하기 적합한 형태로 조합합니다. 또한 입력 정보에 system-generated values를 적용하여 쉐이더가 효율적으로 데이터를 활용할 수 있도록 합니다.
  - primitive topology에 정의된 primitive type에 따라 정점vertex 정보를 라인line 혹은 삼각형triangle 등의 형태로 조합할 수 있습니다.
  - system-generated values 를 통해 데이터에 primitive id, instance id, vertex id 등을 적용시켜 특정 쉐이더 단계마다 필요한 데이터만을 처리할 수 있도록 오버헤드를 줄일 수 있습니다.
- [Vertex Shader Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/vertex-shader-stage) : IA 단계에서 버텍스 정보를 전달받아 각 정점에 대해 처리작업을 수행합니다.
  - system generated values 중에서 VertexID, InstanceID 가 적용된 값을 처리합니다.
- [Tessellation Stages](https://docs.microsoft.com/en-us/windows/win32/direct3d11/direct3d-11-advanced-stages-tessellation) : low-detail의 primitive를 high-detail의 primitive로 분할시키는 단계입니다.
  - 테셀레이션의 경우, 디테일을 개선하는 작업을 렌더링 단계에서 수행하기 때문에, 애플리케이션은 높은 디테일의 모델 자원이 아닌 낮은 디테일의 자원을 활용할 수 있습니다. 이는 메모리 절약에 도움이 됩니다. 
  - Level of detail 즉 카메라로 부터 거리에 따른 디테일 수준을 조정할 수 있습니다. 
  - hull shader 단계 : programmable shader stage로서 입력받은 면(patch)의 제어점(patch constraint)을 tessellator 단계로 전달다.
  - tessellator 단계 : 프로그래밍이 불가능한 고정된 단계로서 hull shader로 부터 전달받은 정보를 활용해 입력 영역domain(line, triangle, quad 등)을 더 작은 영역으로 분할합니다.
  - domain shader 단계 : tessellator 단계에서 분할된 기하정보를 넘겨받습니다. 전달받은 정보를 다루고 다음 파이프라인 단계로 넘깁니다.
- [Geometry Shader Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/geometry-shader-stage) : 정점 쉐이더가 입력정보로 하나의 정점을 받는다면 기하 쉐이더는 하나의 primitive를 이루는 다수의 정점을 입력정보로 받습니다. 이를 기반으로 해당 primitive를 다룰 수 있으며, 새로운 primitive를 만들어내거나 기존의 것을 파괴할 수도 있습니다.
- [Stream-Output Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-output-stream-stage) : Rasterizer 단계 이전에 수행되며 현재 단계까지 처리되어진 정점 정보를 primitive topology에 맞게 묶어 메모리 버퍼로 출력합니다. SO 단계에서 메모리로 넘어간 데이터는 cpu혹은 이후 수행되는 렌더링 패스에서 읽어질 수 있습니다.
- [Rasterizer Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage) : 입력받은 벡터 정보(primitive로 이루어진) 2d 스크린 상에 출력하기 위한 픽셀 정보로 변환합니다. 절단 작업, 2d 뷰 포트에 맞춰 픽셀에 사상하는 작업, 원근감을 위해 z값을 나누는 작업(절단 좌표계의 정점을 정규화 장치 좌표계로 변환) 등이 이루어집니다.
- [Pixel Shader Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/pixel-shader-stage) : 현재까지의 단계를 거친 정점의 속성값들이 픽셀의 위치에 맞게 보간되어 픽셀 쉐이더로 전달됩니다. 픽셀 쉐이더는 입력값을 다루어 최종적으로 화면상에 출력할 색상값을 전달합니다.
- [Output-Merger Stage](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-output-merger-stage) : 픽셀 쉐이더의 결과 색상값, 기존 렌더 타겟의 데이터, 뎁스/스텐실 버퍼 데이터를 종합해서 최종 결과물을 만들어내는 단계입니다.
  - depth-stencil test, blending, multiple rendertarget 에 대한 처리가 이루어집니다.

###### Reference
- [MSDN reference](https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline)
  
</details>

## 조명

<details>
  <summary>접기/펼치기</summary>

#### [조명 연산 알고리즘Illumination models](https://en.wikipedia.org/wiki/Shading#Flat_shading) 과 조합해서 사용할 수 있는 밝기값 보간 방식

- `Flat shading` : 개별 삼각형에 대해 밝기값을 계산합니다.
  - 연산이 빠릅니다. 그러나 삼각형이 각진 부분 혹은 코너 부분에 있어서는 음양이 부드럽게 표현되지 않습니다.
  - specular light를 표현하는데 있어 좋지 못합니다. 직접적으로 반사되는 폴리곤은 면 전체가 똑같은 밝기로 빛나며 음영이 부드럽게 이어지지 않는 특징 때문에 자연스러운 연출이 되지 않습니다.
  - 또한 조명이 해당 폴리곤에 적당한 각도로 비추지 않는다면 specular lighting 요소는 아예 표현되지 않을 수도 있습니다.
- `Gouraud shading` : 삼각형의 각 정점에서 조명값을 정하고 계산된 색상을 삼각형 표면 전체로 보간합니다.
  - 정점의 조명값을 보간하는 특징 탓에 밝기가 부정확할 수 있습니다. (특히 specular lighting)
  - T 형태로 인접한 폴리곤의 경우 시각적으로 부자연스럽게 보일 수 있습니다.
  - 마하 밴드mach band 현상이 나타날 수 있습니다.
    - 두 개의 면이 만나는 경계선 부근에서 어두운 면은 더 어두워지고, 밝은 면은 더 밝게 보이는 일종의 착시 현상. 인간의 시각인식 체계 특징상 윤곽선을 추적하려는 경향에 의해 나타납니다.
- `Phong shading` : 각 정점에 저장된 법선을 이용하여 삼각형에 해당되는 각 픽셀의 법선 벡터를 보간합니다. 그 후 픽셀에 대해서 보간된 법선 벡터값을 활용해 밝기를 연산합니다.
  - 픽셀별 조명처리는 고러드gouraud 셰이딩 방식과 플랫flat 셰이딩 방식과 비교해서 연산이 복잡하고 비용이 많이 발생합니다.
  - 정반사광specular lighting을 가장 정확하게 표현할 수 있습니다.

#### 난반사Diffuse 관련
- 거친 표면의 성질 표현, 물리적 실제감 표현, 빛과 물체 표면과의 상호관계와 연관되어 있습니다.
- 광자가 난반사가 일어나는 표면에 도착하면 순간적으로 그 표면에 흡수됩니다.(주로 거친rough 표면에서 발생합니다) 광원으로부터 나온 광자의 색상과 물질의 색상에 따라서 광자가 완전히 흡수될 수도 있고, 임의의 방향으로 반사될 수도 있습니다. 난반사 성분은 시야 독립적입니다.(view - independent)

- [Lambert 법칙](https://en.wikipedia.org/wiki/Lambertian_reflectance) : 난반사만 일어날 수 있는 (완전히 거친) 표면에 반사된 빛을 계산하는 방법입니다.

#### 정반사specular 관련
- 하이라이트 생성함으로써 표면이 반짝거리도록 보이게 하고 굴곡을 보여주며 광원의 방향과 위치를 알게 해줍니다.
- 물리적 의미 : 광택 있는 표면에서 입사되는 광자가 반사 방향으로 튕겨져 나가는 원리입니다.

- [phong reflection](https://en.wikipedia.org/wiki/Phong_reflection_model) : 조명의 반사 벡터와 시야 벡터를 내적한 성분을 활용해 정반사 성분을 구합니다.
- [blinn - phong reflection](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model) : halfway vector(조명 방향 벡터와 시야 방향 벡터의 중간값 벡터)를 활용해 정반사 성분을 구합니다.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Blinn_phong_comparison.png/600px-Blinn_phong_comparison.png)
- phong 방식이 정반사광을 원형으로 나타낸다면, blinn phong 방식은 보다 타원형으로 나타냅니다. 강이나 바다에 반사되는 햇빛이 완벽한 원형의 모습을 유지하기보다는 수직방향으로 좀더 늘어져 보이는 것을 떠올리시면 됩니다.
- 조명이 굉장히 멀리 있는 경우(ex : Directional Light) 이면서 정사영orthographic/isometric 카메라를 활용하고 있을 때, halfway vector는 고정된 값으로 연산할 수 있기 때문에 phong 방식 보다 blinn-phong 방식이 더 빠를 수 있습니다.

</details>

## Texturing

<details>
  <summary>접기/펼치기</summary>

#### Texture Coordinates in DirectX 11

- UV-mapping 은 모델을 이루는 폴리곤 면의 특정 부분을 텍스쳐의 어느 지점에 대응시킬 것인지(sampling) 구하는 과정입니다. 
  - 보통 텍스쳐의 수평(horizontal) 성분을 U, 수직(vertical) 성분을 V 라고 부릅니다.
  - 정규화된 좌표 표현 방식(normalized texture space)을 통해 텍스쳐의 좌측 상단의 uv 성분을 (0, 0), 우측 하단의 uv 성분을 (1, 1)으로 지정합니다. 정규화된 방식을 통해서 우리는 vertex 정보에 uv 성분을 입력할 때 텍스쳐 크기(1024x1024, 512x512)를 고려할 필요가 없게 됩니다. 더불어서 이 특징은 mipmapping을 활용할 때도 유용합니다.
  
![](https://www.3dgep.com/wp-content/uploads/2014/04/DX11-Texture-Coordinates.png)
  
#### Mip Mapping

- mipmapping은 특정 이미지에 대한 연속된 이미지 리스트를 생성하는 것입니다. 그림에서 보시다시피 매번 이미지를 생성할 때 마다 사이즈를 반으로 줄여나가는 것이 특징입니다.
  - mipmapping 은 LOD (Level of Detail)에서 자주 활용되는 기법입니다. 물체가 카메라로부터 멀어질 때 점차 디테일한 표현은 눈에 띄지 않게 되므로, 먼 거리의 물체를 표현할 때는 최고 해상도의 텍스쳐를 활용할 필요까지는 없습니다. 이럴 때 mipmapping을 통해 생성한 낮은 해상도의 텍스쳐를 사용할 수 있습니다.
  - mipmapping 을 통해 생성한 이미지는 본래 해상도의 텍스쳐 메모리 용량의 1/3 정도 됩니다. (1/4 + 1/16 + 1/64 + ....)

![](https://www.3dgep.com/wp-content/uploads/2014/04/Mip-Mapping.png)

- mipmapping은 고해상도의 텍스쳐를 그대로 사용할 때, 텍스쳐 샘플링 품질과 관련해서 먼거리의 오브젝트에서 마치 쟈글거리는듯 보이는 부작용을 완화시키기도 합니다.

![](https://www.3dgep.com/wp-content/uploads/2014/04/mipmapping-egz.png)

#### Filter

- 텍스쳐 공간을 나타내는 기본 단위, 텍셀(texel)을 읽어올 때에도 다양한 방식이 있습니다.

**Point Filtering**  : 샘플링된 서브 텍셀과 가장 가까운 텍셀을 반환합니다.  
**Linear(Bilinear) filtering** : 샘플링된 서브 텍셀과 가장 가까운 텍셀들을 선형보간하여 중간값을 반환합니다.  
**Trilinear filtering** : 샘플링된 서브 텍셀과 가장 가까운 텍셀들을 선형보간하는 동시에 **인접한 mipmap level** 의 텍스쳐의 선형보간으로 구한 텍셀을 다시한번 보간해서 중간값을 반환합니다.  
**Anisotropic filtering** : 위의 명시한 샘플링 방식이 등방형(isotropic) 방식으로서 샘플링 영역이 사각형이었다면 비등방형(anisotropic)은 샘플링 영역을 설정할 때 카메라의 각도를 고려하며 해당 영역에 대해 보간된 텍셀을 반환합니다. 연산비용이 비싸면서도 가장 품질이 좋은 텍스쳐 샘플링 방식으로 알려져 있습니다.  

![](https://www.3dgep.com/wp-content/uploads/2014/04/Texture-Filtering1.png)

#### Mipmap Filtering

**Minification filtering** : 텍스쳐로부터 샘플링된 텍셀이 화면(screen)의 픽셀보다 작은 경우 발생합니다. 텍스쳐를 축소시킨 모습을 보게 됩니다.  
**Magnification filtering** : 텍스쳐로부터 샘플링된 텍셀이 화면(screen)의 픽셀보다 큰 경우 발생합니다. 텍스쳐를 확대시킨 모습을 보게 됩니다.  
- 두 경우에도 위의 명시한 적절한 샘플링 방식을 사용해 텍셀을 나타내게 됩니다.

![](http://what-when-how.com/wp-content/uploads/2012/05/tmp1cfe29_thumb_thumb.png)

#### ADDRESS MODE

- 텍스쳐 좌표값이 [0 ~ 1] 을 벗어났을 때 처리할 방식을 지정합니다.
  - 도대체 이 개념에 왜 Address 라는 이름이 붙는지 이해가 가지 않습니다.
- clamp, repeat, mirror, border, mirror once 등의 방식이 있습니다.

![](https://vulkan-tutorial.com/images/texture_addressing.png)

#### Reference 
- [3dgep : texturing-lighting-directx-11](https://www.3dgep.com/texturing-lighting-directx-11/#Texturing)
- [wikipedia : texture filtering](https://en.wikipedia.org/wiki/Texture_filtering)
- [vulkan-tutorial : Texture_mapping](https://vulkan-tutorial.com/Texture_mapping/Image_view_and_sampler)


</details>

## Deferred Rendering

<details>
  <summary>접기/펼치기</summary>
  
- 포워드 렌더링(forward rendering)과 지연 렌더링(deferred rendering)
  - 포워드 렌더링은 한 단계의 pass를 거쳐 입력 정보가 곧장 최종 결과물에 해당하는 픽셀(혹은 프래그먼트)로 렌더링 됩니다.
  - 지연 렌더링의 경우 렌더링하는 과정을 분리해 입력정보가 일반적으로 두 단계의 pass를 거치게 합니다. 먼저 첫 pass 에서는 입력된 기하정보(위치, 노말벡터 등)를 렌더타겟(G-buffer)에 저장하며 모든 렌더 대상에 대해 이 과정을 수행합니다. 그 후 통합된 물체들의 정보를 두 번째 pass를 통해 최종 결과물로 지연시켜(deferred) 렌더링합니다.
  
![](https://learnopengl.com/img/advanced-lighting/deferred_overview.png)

- 지연렌더링의 장점
  - `Deferred Lighting` 다수의 조명 연산을 효율적으로 수행할 수 있습니다. (`조명 개수 * 모델 개수` ==> `조명 개수 * 화면 픽셀 수`)
    - 그러나 shadow mapping을 활용하는 경우, 쉐도우 맵을 렌더링 할 때 `조명 개수 * 모델 개수` 만큼 연산해야 하는 사실은 변하지 않습니다.
- 지연렌더링의 단점
  - 투명한 물체를 그리기에 적합한 방법이 아닙니다. 그래도 우회책이 있긴 합니다. 
    - `투명성 알고리즘(Transparency Algorithm)` : Z-buffer 를 활성화한 상태에서 완전히 불투명한 물체를 먼저 그린다. 다음 깊이 버퍼를 비활성화하고 투명한 물체를 그린다. 이렇게 되면 깊이 비교 없이 반투명 물체의 컬러가 프레임 버퍼에 그대로 반영되므로 투명 효과를 줄 수 있다.
  - 다수의 렌더 타겟을 활용하기 때문에 그 만큼 추가적인 메모리를 사용합니다. 경우에 따라서 높은 메모리 대역폭을 지원하지 않는 gpu의 경우 지연렌더링을 사용하지 못할 수 있습니다.
  - 다수의 마테리얼material 정보를 활용할 때 지연렌더링은 한계점을 가집니다. gpu 내에 마테리얼 정보를 입력시키는 우회책이 있긴 하지만 추가적인 gpu 메모리를 사용하게 됩니다.
  - 안티 얼라이징anti - aliasing을 활용하기 어렵습니다. 그러나 edge detection을 통한 대안이 있습니다.


##### Reference
- [gamedevelopment](https://gamedevelopment.tutsplus.com/articles/forward-rendering-vs-deferred-rendering--gamedev-12342)
- [wiki](https://en.wikipedia.org/wiki/Deferred_shading)
  
</details>

## 주변광 차폐(SSAO Screen Space Ambient Occlusion)

<details>
  <summary>접기/펼치기</summary>
  
  
- `주변광 차폐(ambient occlusion)` 방식은 물체 표면의 특정한 부분이 노출되어 있다면 밝게, 둘러싸여져 있다면 그 부분은 주변광을 덜 받는 것으로 가정하고 보다 어둡게 표현하는 기법입니다.
  - 주름 혹은 방 가장자리의 모서리 부분을 예시로 생각하시면 됩니다.
  - SSAO는 screen space내의 정보를 활용해 정확하지는 않지만 보다 가벼운 연산으로 주변광 차폐값의 근사치를 구하는 방법입니다.

![](http://farm5.static.flickr.com/4026/4639752338_7a574740e9.jpg)

- 지연 렌더링 deferred rendering 환경에서는 쉽게 구현할 수 있습니다. screen space에 픽셀에는 렌더링 된 물체들의 위치/노말 벡터 정보가 저장되어 있다고 가정하겠습니다.
- `이웃한 픽셀의 위치 벡터 - 현재 연산하는 픽셀의 위치 벡터` 와 `현재 연산하는 픽셀의 노말 벡터`를 내적한 성분을 활용하면 됩니다. 내적값을 통해 두 벡터 사이의 각도를 알 수 있으며 해당값은 인접한 픽셀에 렌더링된 물체가 현재 픽셀을 얼마나 둘러싸는지(깊이 depth 차이가 얼마인지) 나타냅니다.

![](http://farm5.static.flickr.com/4054/4639143389_42b13c5ef6.jpg)
![](http://farm5.static.flickr.com/4030/4639143415_444cde1085.jpg)
- 벡터를 이용한 연산은 꽤 그럴듯한 결과를 보여줍니다. 하지만 이외에도 depth 버퍼를 활용하여 깊이값을 비교하는 방식을 떠올릴 수 있습니다.
  - 구현이 간편하고 더 빠른 연산이 가능해보이지만 문제점이 있는데 스스로를 가리는 현상self occlusion 과 모서리 주변 부분이 밝아지는 헤일로halo 현상이 나타난다는 것입니다.
  
- SSAO 방식은 빠르고 화면에 동적으로 움직이는 객체가 많을 때 효과적일 수 있습니다. 지연렌더링을 기반으로 하고 있다면 구현하기도 쉽습니다. 하지만 SSAO가 가지고 있는 단점도 역시 잘 고려해야 할 것이며 적절한 상황에 맞게 기법을 적용해야 할 것입니다.
  - False Occlusion(Halo) 현상 : 물체들이 거리를 두고 떨어져 있음에도, 카메라 상에서 겹쳐져 보인다면 주변광이 차폐되는 부분으로 잘못 인식하는 경우가 있습니다. 

![](https://answers.unrealengine.com/storage/temp/67883-haloartifact.jpg)

  - 숨겨진 기하geometry 물체들, 특히 절두체 바깥의 물체들은 연산 과정에서 제외합니다.
  - 샘플링sampling(여기서는 몇 개의 인접한 픽셀과 비교하는지) 에 따라 성능 차이가 발생합니다.
  - 결과가 지저분할 수(noisy) 있습니다. 가우시안 블러와 같은 추가적인 작업이 필요할 수 있습니다.

#### Reference
- [Game Dev](https://www.gamedev.net/tutorials/programming/graphics/a-simple-and-practical-approach-to-ssao-r2753/)
- [Advance Computer Graphic : SSAO](http://www.cse.chalmers.se/edu/year/2018/course/TDA361/Advanced%20Computer%20Graphics/SSAO.pdf)

</details>

## PostProcess 효과

<details>
  <summary>접기/펼치기</summary>
  
- 3D 렌더링에서 `후처리 효과(Post Processing)` 은 렌더링 결과물을 곧바로 화면에 출력하기 전 일종의 필터 역할을 하는 효과들을 적용하는 방식일 일컫습니다.

### Bloom

- `블룸(bloom)` 효과는 화면의 밝은 영역의 경계에서 빛이 발산되는 것 같은 효과를 주는 기법입니다.
  - 블룸 이펙트는 기존 이미지를 블러blurr 처리하여 구현할 수 있습니다. 블룸bloom 이펙트를 구현하기 이전에는 블러 처리가 먼저 이루어져야 합니다.
  
![bilinear downsampling](https://catlikecoding.com/unity/tutorials/advanced-rendering/bloom/blurring/bilinear-downsampling.png)

- 블러 효과를 적용할 때 다수의 픽셀들의 평균 색상값을 구하려 할 경우, 연산하는 픽셀의 수가 많다면 연산 비용이 증가합니다. 이를 피하기 위해 우선 다운 샘플링downsampling 을 활용하는 방법이 있습니다.
  - 이때 박스 샘플링(box sampling) 방식을 이용할 수 있습니다.

![](https://catlikecoding.com/unity/tutorials/advanced-rendering/bloom/creating-bloom/additive-blurring.png)

- 여러 단계의 다운 샘플링을 거친 이미지를 기존의 화면에 적용시켜야 할 것입니다. 단순히 다수의 다운 샘플링을 거친 이미지 하나 만을 적용한다면 예상보다 균등하게 흐릿해져 제대로 된 빛 발산 효과가 나타나지 않을 것입니다. 다운 샘플링을 거친 중간 단계의 이미지들 까지 중첩시켜서 적용해야 합니다. 

- 블러 이미지를 결과물에 적용할 때는 `Additive blending`을 적용해야 합니다. 블렌딩 방식이 혹시나 기존의 색상을 대체하는 방식이라면 역시 결과물의 빛 발산 효과가 제대로 나타나지 않을 것입니다.

### 감마 보정Gamma Correction

- 감마(gamma)라는 개념 사이에는 엔지니어 사이에도 개념 차이가 존재하며 이에 따른 혼란도 적지 않다고 한다. 적당히 '입력값에 대한 비선형적 출력 특성의 결정 요인' 정도로 이해하면 좋을 것 같다.

![](https://dthumb-phinf.pstatic.net/?src=%22http%3A%2F%2Fwww.monitor4u.co.kr%2Flesson%2FContentImg%2FGamma_Tour_01_sRGB-550.png%22&type=m10000_10000)

- 실제로 감마보정은 영상 처리 분야에서 생각보다 세분화된 단계로 적용된다.

감마보정의 주요 목적은
- 인간의 시야가 색상을 인식할 때 비선형적인 방식으로 인식합니다. 이때 밝은 색조보다는 어두운 색조의 대해서 더 민감하게 인식하는 경향이 있다. 일반적인 선형 색상으로 화면을 표시하려 한다면, 어두운 부분의 밝기가 변할 때 부드럽게 느껴지지 않고 단절되어 보이는 현상(posterization)이 발생합니다. 따라서 주어진 정보표현량의 한계 안에서 최적의 화질을 보여주기 위해선 비선형적으로 부호화하여 어두운 부분을 더 자세히 표현할 필요가 있습니다.
- CRT 음극선상의 특징상 비선형적으로 색상을 표현하기 때문에 원본의 색상을 정상적으로 나타내기 위해 소프트웨어 적으로 보정을 적용하는 이유도 있다고 하지만 주된 이유는 아니라고 합니다. 입력 전류를 조정함으로써 이 부분은 소프트웨어 측 보정 없이 해결할 수 있다고 합니다.
  - 하기야 디스플레이 장치 종류에 따라 보정값 수치가 바뀔 수 있는데 그 부분을 소프트웨어 측에서 책임지는 것은 올바른 해법이 아닌 것 같습니다.

[출처](https://ko.wikipedia.org/wiki/%EA%B0%90%EB%A7%88_%EB%B3%B4%EC%A0%95), [출처2](https://en.wikipedia.org/wiki/Gamma_correction)

```c++
void main()
{
    // do super fancy lighting in linear space
    [...]
    // apply gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
}
```
[감마 보정 예시 OpenGL](https://learnopengl.com/Advanced-Lighting/Gamma-Correction)

### Tone Mapping

- HDR(high dynamic range) : 폭넓은 범위(색상으로 출력하는 0~1 범위를 넘어선)의 색상을 표현하는 방식입니다. 디지털 색상을 출력할 때 색상의 최대 범위를 넘어선 값을 단순히 하얀색으로 표현하지 않습니다(혹은 최소 범위 보다 작은 값을 검은색으로 표현하는 등) 

- 톤 맵핑(Tone Mapping)은 HDR 색상을 제한된 범위의 색상(LDR low dynamic range)으로 변환시키는 방법입니다. HDR 이미지를 그대로 출력한다면 디스플레이 장치가 표현할 수 있는 색상 범위를 넘어선 값은 제대로 표현하지 못하는 문제를 해결합니다.
  - 톤 맵핑의 목적은 디스플레이 장치가 제한된 밝기만을 표현할 수 있을 때, 실제 장면이 자연스럽게 화면상에 표시될 수 있도록 하는 것입니다.
  - 카메라가 빛에 노출되는 정도exposure 값을 조정하여 hdr 색상 표현 범위를 ldr 범위에 맞게 조정할 수 있습니다.
    - 사람의 눈을 예시로 들면, 어두운 밤에는 exposure 를 높여 눈이 더 많은 빛을 받아들이게 합니다. 이를 통해 어두운 영역을 상대적으로 밝게 인식할 수 있습니다.
    - 반대로 밝은 낮에는 exposure를 낮춰 눈이 빛을 덜 받아들게 합니다. 결과적으로 밝은 영역을 상대적으로 어둡게 인식하게 됩니다.
  
![](https://learnopengl.com/img/advanced-lighting/hdr_exposure.png)
  
```c++
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
  
    // exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
}  
```
[코드 출처](https://learnopengl.com/Advanced-Lighting/HDR)

#### Reference
- [wiki](https://en.wikipedia.org/wiki/Video_post-processing)
- [bloom](https://catlikecoding.com/unity/tutorials/advanced-rendering/bloom/)
- [감마 보정](https://blog.naver.com/psy2993/90081371916)

</details>

## Cpu Side Frustum Culling

<details>
  <summary>접기/펼치기</summary>
  
- 카메라의 절두체의 바깥에 위치한 오브젝트는 렌더링 대상에서 제외하는 작업입니다. gpu의 작업량을 줄일 수 있습니다.

[절두체 선별 알고리즘 참고](http://www.lighthouse3d.com/tutorials/view-frustum-culling/)
  
</details>

## Shadow Mapping

<details>
  <summary>접기/펼치기</summary>
  
![](https://learnopengl.com/img/advanced-lighting/shadow_mapping_theory_spaces.png)

- 쉐도우 맵핑 방식은 특정 픽셀에 대해서, 조명의 관점에서 해당 픽셀이 보이는지를 확인하며 만약 보이지 않는다면 그림자가 지는 것으로 판단하는 방식입니다.
  - 카메라 관점과 조명 관점의 z-depth 값을 비교해서 결과를 구합니다. (조명 관점의 깊이값이 더 작다면 그림자가 지는 것)
  - 쉐도우 맵 텍스쳐 : 조명 관점의 시야에서 깊이값이 렌더링된 텍스쳐입니다.
  
![](https://learnopengl.com/img/advanced-lighting/shadow_mapping_zoom.png)
![](https://learnopengl.com/img/advanced-lighting/shadow_mapping_soft_shadows.png)

- 그림자의 계단현상을 해결하기 위한 방법으로는 대표적으로 PCF(Percentage Closer Filtering) 방식이 있습니다.
  - 연산하는 픽셀과 주변 픽셀의 그림자 결과값의 평균을 내서 가장자리의 그림자를 부드럽게 표현하는 방식입니다.
  
- 쉐도우 맵핑 방식의 가장 두드러지는 단점은 쉐도우 맵 텍스쳐의 해상도가 곧 그림자 표현의 퀄리티로 이어진다는 것입니다. 가장자리의 그림자를 확인하면 보통 계단현상이 나타나는 것을 확인할 수 있습니다. 메모리와 성능의 한계상 쉐도우 맵 텍스쳐의 크기를 무한정 늘릴 수도 없는 노릇입니다.
  - 텍스쳐 크기로 인한 한계점을 우회하는 방법으로는 casacade shadow map, Trapezoidal Shadow Map 방식이 존재합니다.
  - 쉐도우 맵 텍스쳐를 응용하여 퀄리티를 높이는 방법으로는 Percentage Closer Filtering, Variance Shadow maps 방식이 있습니다.

##### Reference
- [wiki](https://en.wikipedia.org/wiki/Shadow_mapping)
- [Learn OpenGL](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)

</details>

## Skeletal Animation

<details>
  <summary>접기/펼치기</summary>

![](https://upload.wikimedia.org/wikipedia/commons/thumb/a/aa/Sintel-hand_%28cropped%29.png/330px-Sintel-hand_%28cropped%29.png)

- Skeletal animation 과 rigging 방식에서는 3d 모델을 두 가지 방식으로 표현합니다.
  - 메쉬mesh : 3d 모델을 렌더링할 때 표현되는 모델의 표면 정보입니다.
  - 본bone : 모델의 각 부분들이 계층적으로 연결된 구조를 나타내는 정보입니다. (마치 사람의 골격구조 처럼)
  
![](http://ogldev.atspace.co.uk/www/tutorial38/vertex.jpg)
- 메쉬에 포함되는 각 정점vertex들은 본에 대해서 가중치를 가집니다. 이 가중치에 따라서 본이 움직일 때, 정점들 역시 가중치 만큼 영향을 받습니다.

- 각 본들은 독립적으로 움직일 수 있고, 애니메이션들은 각 정점들에 대해서 어떻게 움직여야 할지 하나하나 지정하는 대신 더 적은 수의 본들에 대해서만 작업하면 되는 장점이 있습니다.
- 대신 skeletal animation은 근육의 수축/팽창과 같은 움직임을 표현하는데는 한계점을 가집니다.

###### Reference
- [wiki](https://en.wikipedia.org/wiki/Skeletal_animation)
- [openGlDev](http://ogldev.atspace.co.uk/www/tutorial38/tutorial38.html)

</details>

## Volumetric Lighting

<details>
  <summary>접기/펼치기</summary>

![](https://fabiensanglard.net/lightScattering/LightScattering.jpg)

1. [Screen Space Occlusion 방식](https://developer.nvidia.com/gpugems/gpugems3/part-ii-light-and-shadows/chapter-13-volumetric-light-scattering-post-process)
  - 픽셀 상에 빛을 가리는 차폐막 (Occluder) 이 없으면 그 자리에는 빛이 지나가는 장소라고 가정, 해당 픽셀을 밝게 표현하는 방식입니다.
  - Directional Light 가 아닌 다른 종류(Spot 등) 의 조명을 쓰는 경우, 빛의 방향이 카메라를 정면으로 향하지 않는다면 볼륨이 제대로 표현되지 않게 됩니다.

2. [Ray march 방식](https://archive.org/details/GDC2016Hoobler)
  - 카메라에서 전방으로 나아가는 레이(Ray)가 있다고 가정합니다. 해당 레이를 샘플 개수 만큼 구간으로 나누어 특정 구간마다 조명이 기여하는 정도를 연산, 이후 모든 구간의 조명값을 더해 최종 결과값를 구합니다.
  - 비용이 비쌀 수 있지만 Screen Space Occlusion 방식보다 더 정확한 표현이 가능합니다.


##### Reference
- [Fast_Flexible_Physically-Based_Volumetric_Light_Scattering](https://developer.nvidia.com/sites/default/files/akamai/gameworks/downloads/papers/NVVL/Fast_Flexible_Physically-Based_Volumetric_Light_Scattering.pdf)
- [SlightlyMad/VolumetricLights](https://github.com/SlightlyMad/VolumetricLights)
- [ACskyline/VLD3D11](https://github.com/ACskyline/VLD3D11)

</details>
