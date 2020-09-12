# PBR(Physics Based Rendering)

#### Reference
- [wikipedia : Physically_based_rendering](https://en.wikipedia.org/wiki/Physically_based_rendering)
- [slide share : 물리 기반 셰이더의 허와 실:물리기반 셰이더를 가르쳐 봤습니다 공개용](https://www.slideshare.net/jpcorp/ss-60782086)
- [slide share : PBR 기초 이론과 사용되는 맵들 Vol.2](https://www.slideshare.net/MRESC/pbr-vol2-131205432)

 ---
 
 - PBR 이전 기존의 렌더링이 diffuse, ambient, specular 라이팅 성분을 단순하게 사용했다면 PBR 에서는 빛을 다룰 때 좀더 정확한 라이팅 표현 방법을 사용합니다.
 
 ![](https://image.slidesharecdn.com/random-160412001945/95/-16-638.jpg?cb=1547270662)
 
 
 1. energy conversion : 물체 표면에 닿은 빛의 양은 보존됩니다. 들어온 빛의 양은 물체 표면으로 흡수된 양과 반사된(정반사 난반사) 양의 합입니다. 이때 정반사 난반사 비율은 표면 거칠기(Roughness) 에 의해 결정됩니다.

입사광 = 흡수된 빛 에너지 + 정반사 광 + 난반사 광

2. specular - pbr에서는 물체의 금속성분을 중요하게 다룹니다. 금속은 고유의 specular 색상을 가지고, 비금속은 단순히 흰색의 specular 색상을 가지기 때문입니다. 표면의 금속 성질을 고려해서 specular 색상을 결정합니다.

3. fresnel - 표면에서 반사된 빛의 양이 관찰 각도에 따라 달라지는 현상입니다. 쉽게 말했을 때 멀찍이 수평선에 있는 표면이 정반사 성분이 더 강하게 나타납니다.
