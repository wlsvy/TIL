# Direct X, Open GL 차이점

## Platform

Direct3D는 Microsoft Window 플렛폼에서만 작동합니다.

이에 반해 OpenGL API는 Open Standard를 따르며 대부분의 플렛폼에서 OpenGL을 지원합니다.

## Coordinate System

![](https://image.slidesharecdn.com/gtc2009openglkilgard-091008215235-phpapp01/95/opengl-32-and-more-26-728.jpg?cb=1255392697)
> [출처](https://www.slideshare.net/Mark_Kilgard/opengl-32-and-more/26-Direct3D_vs_OpenGL_Coordinate_System)

- 윈도우 원점 위치
  - DirectX : 우측 상단
  - OpenGL : 우측 하단
  
- 절단 좌표계 좌표 범위
  - DirectX : X/Y 성분은 [-1, 1], Z 성분은 [0, 1]
  - OpenGL : X/Y/Z 성분 전부 [-1, 1]
  
- 좌표 시스템
  - DirectX : 우측 좌표계(left handed coordinate system)
  - OpenGL : 좌측 좌표계(right handed coordinate system)
  - 행렬 연산 방식이 다릅니다.


* 추가적으로도 다양한 차이점이 있는데, 렌더링 파이프라인, hardware resource 활용방식에서 나타난다.

##### Reference
- [gpututorial](https://gpututorial.blogspot.com/2018/01/opengl-vs-direct3d.html)
