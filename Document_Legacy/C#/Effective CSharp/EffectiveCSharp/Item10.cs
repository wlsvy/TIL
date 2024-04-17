using System;

//베이스 클래스가 업그레이드 된 경우에만 new 한정자를 사용하라

namespace EffectiveCSharp
{
    /// <summary>
    /// Virtual 로 선언되지 않은 비가상 메소드들은 new 한정자를 선언하고 상속 클래스에서 재정의할 수 있다.
    /// 하지만 new 한정자를 사용하면 굉장히 혼란스러워질 수 있는데, 동일한 객체에서도 객체를 참조하는 타입이 달라지면 호출 메소드가 변경되기 때문이다.
    /// </summary>
    public class ECSharp10
    {
        public class Base
        {
            public int DoSomething() { return 0; }
        }
        public class Derived : Base
        {
            public new int DoSomething() { return 1; }
        }

        private void Check()
        {
            Derived d = new Derived();
            Base b = d;

            //같은 객체지만 호출 메소드가 다르다.
            int val1 = b.DoSomething(); 
            int val2 = d.DoSomething();
        }

        /* New 한정자를 활용해도 좋은 경우는 베이스 클래스에서 이미 사용되고 있는 메소드를 재정의하여 완전히 새로운 베이스 클래스를 만들어야 하는 경우 정도다. 
         * 
         * 이미 널리 사용되고 있는 메소드가 있어서 이를 사용하는 코드를 일일이 찾아서 수정하기 어렵거나 혹은 
         * 외부 어셈블리에서 이 메서드를 사용하고 있어서 코드를 수정할 수 없는 경우라면 new 한정자를 사용해볼 만하다.
         */

        //BaseWidget 을 개발하는 개발사가 새로 NormalizeValues 라는 메소드를 추가했다고 가정하자
        public class BaseWidget 
        {
            public void NormalizeValues() { }
        }
        /// <summary>
        /// BaseWidget을 통해 MyWidget을 개발하는 개발자는 BaseWidget의 NormalizeValues가 추가되기 전에 이미 
        /// MyWidget 내에서 NormalizeValues 를 정의해서 사용하고 있었다. (BaseWidget의 클래스와 겹쳐버리는 상황 발생)
        /// 이미 많은 곳에서 사용되고 있어서 기존의 메소드를 수정하기가 어려운 상황이다!!!
        /// 
        /// 문제를 해결할 방법은 두 가지, MyWidget에서 사용하는 NormalizeValues 메소드를 전부 찾아서 고치거나
        /// 또 다른 방법으로는 메서드의 이름을 변경하는 대신 new 한정자를 사용하는 것.
        /// </summary>
        public class MyWidget : BaseWidget  
        {
            public new void NormalizeValues() { }
        }
    }
}
