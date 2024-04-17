using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//상속보다는 인터페이스를 정의하고 구현하는 것이 낫다
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 기반 클래스는 관련성이 있는 타입들의 공통 동작(처리)을 기술하고 구현합니다. 반면 인터페이스는 연관성 없는 타입이라 하더라도 공통적인 기능을 기술할 수 있습니다.
    /// 
    /// 클래스는 사용자가 만들 타입을 정의하지만, 인터페이스는 해당 타입의 동작을 기술합니다. 
    /// 관련성 있는 타입들을 정의할 때에는 클래스의 상속구조를 활용하고, 연관성이 적은 여러 타입의 걸쳐 공통으로 구현할 기능은 인터페이스를 활용합시다.
    /// </summary>
    public static class MECSharp14
    {
        //인터페이스를 통해 할 수 없는 것은 멤버의 구현부를 작성하는 것입니다.(C# 8.0 부터는 인터페이스의 default method를 작성하는 것이 가능합니다.)
        //
        //기반 클래스는 기능을 확장하는데 있어 부작용이 작지만, 인터페이스의 경우 동작을 변경한다면 연관된 모든 타입이 영향을 받게 됩니다. 
        //만약에 동작을 추가하는 경우, 새로운 인터페이스를 만들고 기존의 인터페이스 타입을 상속하면 됩니다.
        //인터페이스는 계약과 같으니 한번 배포되고 나면 그 내용은 이후에 변경하지 않는 것이 좋습니다.
        //
        //기반 클래스를 상속할 때 추상 메서드만을 구현하면 될 때 인터페이스를 상속하면 반드시 모든 동작을 구현해야 하는 것이 인터페이스의 단점이라고 보는 것은 잘못된 것 같습니다.
        //인터페이스는 어떤 동작을 할지에 대한 계약과 같으니 그에 따른 용도가 있습니다. 방금 예시의 경우, 기반 클래스가 인터페이스를 상속받는 것이 적합한 설계일 것입니다.



        //인터페이스를 매개변수 혹은 반환값으로 활용하는 경우로 봅시다.
        //첫 번째 메서드가 재사용성이 좋습니다. IEnumerable을 지원하는 모든 타입에 대해 동작하기 때문입니다.
        private static void PrintSequence<T>(IEnumerable<T> sequence) { }
        private static void PrintSequence(Widget sequence) { }



        //아래 경우는 유연한 디자인이라고 볼 수 없습니다. 외부에서 List 객체에 직접 접근할 수 있게 됩니다.
        private class Widget
        {
            private List<int> m_List;
            public List<int> Sequence => m_List;
        }

        //사용자에게 허용할 동작만을 정의한 인터페이스를 반환합니다. 외부에서는 인터페이스가 정의한 동작만을 호출할 수 있습니다.
        private class Widget_New
        {
            private List<int> m_List;
            public IEnumerable<int> Sequence => m_List;
        }

        //인터페이스를 활용하는 경우의 또 다른 장점입니다. 코드를 작성하다가 시퀀스 전체가 아닌 일부만을 반환해야 하는 경우가 생겼다고 합시다.
        //위의 예시처럼 List<int> 타입을 그대로 반환하는 경우, 구현 내용을 수정하는 과정에 외부 코드에 영향이 미치겠지만
        //인터페이스를 활용하는 경우라면 언제든지 손쉽게 세부 내용을 변경할 수 있습니다.
        private class Widget_New2
        {
            private List<int> m_List;
            public IEnumerable<int> Sequence => m_List.Where((i) => i % 2 == 0);
        }
    }
}
