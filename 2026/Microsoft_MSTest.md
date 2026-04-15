**MSTest**

[New dotnet test Experience with Microsoft.Testing.Platform - YouTube](https://www.youtube.com/watch?v=QWi_bvQc4fc)

- 2025년 11월 .NET 10.0 과 함께 소개된 MSTest 4.0
- 테스트 인터페이스 등 주로 섬세한 개선점이 주로 소개
- MS Learn 문서에서 테스트 프레임워크 버전 마이그레이션 가이드 제공
  - [MSTest migration from v3 to v4 - .NET  Microsoft Learn](https://learn.microsoft.com/en-us/dotnet/core/testing/unit-testing-mstest-migration-v3-v4)

공유해주신 영상 **"New dotnet test Experience with Microsoft.Testing.Platform"**은 .NET 10에서 새롭게 도입된 테스트 환경과 MS Test 버전 4의 주요 업데이트 내용을 다루고 있습니다.

주요 내용을 요약해 드립니다.

### 1. 새로운 `.NET test` 경험 (Microsoft.Testing.Platform) [[00:29](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=29)]
* **.NET 10의 새로운 뷰:** 테스트 결과를 더 직관적이고 시각적으로 보여주는 인터페이스가 도입되었습니다. 프로그레스 바를 통해 진행 상황을 실시간으로 확인할 수 있습니다. [[01:53](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=113)]
* **활성화 방법:** `global.json` 파일의 `test` 섹션에서 `runner` 옵션을 `Microsoft.Testing.Platform`으로 설정하면 새 모드를 사용할 수 있습니다. [[01:11](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=71)]
* **통합된 분석:** 여러 대상 프레임워크(TFM)나 아키텍처에서 발생한 오류를 한눈에 파악할 수 있는 요약 정보를 제공합니다. [[04:15](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=255)]

### 2. 강력한 확장 프로그램 및 CI 지원 [[05:05](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=305)]
* **Retry 확장:** 실패한 테스트를 자동으로 재시도하는 기능이 추가되었습니다. 최대 재시도 횟수나 실패 비율 제한 등을 설정할 수 있습니다. [[06:10](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=370)]
* **CI 환경 개선:** GitHub Actions 및 Azure DevOps의 로그 출력에 컬러 테마와 프로그레스 바가 적용되어 가독성이 높아졌습니다. [[08:44](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=524)]
* **Azure DevOps Report:** Azure DevOps에서 빌드하더라도 GitHub Pull Request에서 직접 오류 라인을 확인할 수 있는 기능이 제공됩니다. [[09:47](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=587)]

### 3. MS Test 버전 4 업데이트 [[11:06](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=666)]
* **메타 패키지 권장:** `MSTest` 메타 패키지 하나로 프레임워크, 어댑터, SDK를 모두 최신 버전으로 관리할 수 있습니다. [[11:59](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=719)]
* **새로운 분석기(Analyzers):** 중복된 `DataRow`를 감지하거나, `[TestClass]` 속성이 누락된 경우를 찾아내는 등 실수를 방지해 주는 분석기가 강화되었습니다. [[12:32](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=752)]
* **Analysis Mode:** 더 엄격한 규칙을 적용하는 'Recommended' 모드를 통해 코드 품질을 높이고 버전 업그레이드를 원활하게 할 수 있습니다. [[13:34](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=814)]

### 4. 새로운 단언문(Assertions) 및 속성 [[17:53](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1073)]
* **시각적 개선:** `Assert.AreEqual` 실패 시 문자열의 어느 부분이 다른지 화살표로 정확히 짚어줍니다. [[18:07](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1087)]
* **신규 단언문:** `IsInRange`, `IsGreaterThan`, 그리고 식(Expression)을 분석하여 변수 값을 함께 출력해 주는 `Assert.That`이 추가되었습니다. [[19:26](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1166)]
* **조건부 속성:** OS별(Windows, Linux 등) 테스트 실행 여부를 결정하는 속성과, 이를 확장하여 사용자 정의 조건(예: 특정 환경 변수 등)을 만들 수 있는 기능이 제공됩니다. [[20:40](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1240)]

### 5. 성능 최적화 [[23:37](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1417)]
* MSTest 3.11 및 버전 4에서는 대규모 테스트 세트(약 20만 개) 실행 속도가 획기적으로 개선되었으며, 메모리 할당을 줄여 GC 부담을 최소화했습니다. [[24:30](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1470)]

.NET 10과 MSTest v4를 통해 더 빠르고 정확한 테스트 환경을 구축할 수 있을 것으로 보입니다. 관련 블로그나 GitHub(microsoft/testfx)를 통해 더 자세한 피드백을 주고받을 수 있습니다. [[25:28](http://www.youtube.com/watch?v=QWi_bvQc4fc&t=1528)]

