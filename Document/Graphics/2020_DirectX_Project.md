# 2020_DirectX_Project

> [Direct X 11 개인 프로젝트](https://github.com/wlsvy/2020_DirectX_Project) 를 진행하면서 공부한 내용을 작성한 페이지입니다.

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
  - 숨겨진 기하geometry 물체들, 특히 절두체 바깥의 물체들은 연산 과정에서 제외합니다.
  - 샘플링sampling(여기서는 몇 개의 인접한 픽셀과 비교하는지) 에 따라 성능 차이가 발생합니다.
  - 결과가 지저분할 수(noisy) 있습니다. 가우시안 블러와 같은 추가적인 작업이 필요할 수 있습니다.

#### Reference
- [Game Dev](https://www.gamedev.net/tutorials/programming/graphics/a-simple-and-practical-approach-to-ssao-r2753/)

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

- HDR(high dynamic range) : 폭넓은 범위(색상으로 출력하는 0~1 범위를 넘어선)의 색상을 표현하는 방식입니다. 디지털 색상을 출력할 때, 색상의 최대 범위를 넘어선 값을 단순히 하얀색으로 표현하지 않으며(혹은 최소 범위 보다도 작은 값을 검은색으로 표현하는 등) 노출exposure 값을 통해  

- 톤 맵핑(Tone Mapping)은 HDR 색상을 제한된 범위의 색상(LDR low dynamic range)으로 변환시키는 방법입니다. HDR 이미지를 그대로 출력한다면 디스플레이 장치가 표현할 수 있는 색상 범위를 넘어선 값은 제대로 표현하지 못하는 문제를 해결합니다.
  - 톤 맵핑의 목적은 디스플레이 장치가 제한된 밝기만을 표현할 수 있을 때, 실제 장면이 자연스럽게 화면상에 표시될 수 있도록 하는 것입니다.
  - 카메라가 빛에 노출되는 정도exposure 값을 조정하여 hdr 색상 표현 범위를 ldr 범위에 맞게 조정할 수 있습니다.
    - 사람의 눈을 예시로 들면, 어두운 밤에는 exposure 를 높여 눈이 더 많은 빛을 받아들이게 합니다. 이를 통해 어두운 영역을 상대적으로 밝게 인식할 수 있습니다.
    - 반대로 밝은 낮에는 exposure를 높여 눈이 빛을 덜 받아들게 합니다. 결과적으로 밝은 영역을 상대적으로 어둡게 인식하게 됩니다.
  
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
