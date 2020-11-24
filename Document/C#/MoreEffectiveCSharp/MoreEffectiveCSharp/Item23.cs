using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//생성자, 변경자, 이벤트 핸들러를 위해 partial 클래스와 메서드를 제공하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// partial 클래스와 partial 메서드는 단일 클래스를 작성할 때 자동 생성된 코드와 사용자 정의 코드를 완전하게 분리하는 매커니즘을 제공합니다.
    /// 
    /// partial 클래스의 목적은 코드 생성기가 만들어낸 코드를 개발자가 수정 없이 사용하도록 만드는 것입니다.
    /// 
    /// 코드 생성기를 작성할 때에는 확장 가능한 지점들을 partial 메서드로 정의해야 합니다. 
    /// partial 메서드는 동일 클래스를 구성하는 다른 partial 클래스 내에서 해당 메서드를 구현할 수 있도록 선언합니다.
    /// 
    /// partial 메서드는 클래스의 일부가 될 수도 있고 그렇지 않을 수도 있으므로, 그 원형을 정의할 때 몇 가지 제약사항을 가집니다. 
    /// 예를 들어 partial 메서드는 abstract나 virtual이 될 수 없습니다. 반환 타입은 반드시 void여야 하고, 인터페이스 메서드는 구현할 수 없습니다.
    /// 컴파일러는 out 매개변수를 초기화할 수 없으므로 out 매개변수를 사용할 수도 없습니다. 메서드 본문이 구현되지 않았으니 반환값을 생성할 수도 없습니다.
    /// 더불어 모든 partial 메서드는 암묵적으로 private 입니다.
    /// 
    /// </summary>
}
