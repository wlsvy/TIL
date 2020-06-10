using System;

namespace EffectiveCSharp
{
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

            int val1 = b.DoSomething(); //같은 객체지만 호출 메소드가 다르다.
            int val2 = d.DoSomething();
        }

        public class BaseWidget //BaseWidget 을 개발하는 개발사가 새로 NormalizeValues 라는 메소드를 추가했다고 치자
        {
            public void NormalizeValues() { }
        }
        public class MyWidget : BaseWidget  //BaseWidget을 통해 MyWidget을 개발하는 개발자는 BaseWidget의 NormalizeValues가 추가되기 전에 이미 
                                            //MyWidget 내에서 NormalizeValues 를 정의해서 사용하고 있었다. (BaseWidget의 클래스와 겹쳐버리는 상황 발생)
                                            //이미 많은 곳에서 사용되고 있어서 기존의 메소드를 수정하기가 어려운 상황이다!!!
        {
            public new void NormalizeValues() { }
            //문제를 해결할 방법은 두 가지, MyWidget에서 사용하는 NormalizeValues 메소드를 전부 찾아서 고치거나
            //또 다른 방법으로는 메서드의 이름을 변경하는 대신 new 한정자를 사용하는 것.
        }
    }
}
