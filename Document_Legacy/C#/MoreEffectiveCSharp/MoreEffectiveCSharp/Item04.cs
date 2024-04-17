using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//값 타입과 참조 타입을 구분하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// C#에서 값 타입은 다형성이 없습니다. 일반적으로는 애플리케이션이 사용하는 저수준low-level 데이터를 저장하는 데 적합합니다.
    /// 참조 타입은 다형성을 지니므로 애플리케이션의 동작을 정의할 때 사용해야 합니다.
    /// 
    /// 아래의 질문에 모두 Yes 라고 답할 수 있다면 값 타입을 고려합시다.
    /// 1. 주요 용도가 데이터 저장인가
    /// 2. 변경 불가능하게 만들 수 있는가
    /// 3. 크기가 작을 것으로 기대하는가
    /// 4. public 인터페이스가 데이터 멤버 접근용 속성뿐이가
    /// 5. 자식 클래스를 절대 갖지 않는다고 확신하는가
    /// 6. 다형성이 필요한 일은 없을 것으로 확신하는가
    /// </summary>
}
