using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EffectiveCSharp;

namespace EffectiveCSharp
{
    class MainProgram
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("Hello ECS");

            //ECSharp02.RunSample();
            //ECSharp15.Case0.RunSample0();
            //ECSharp15.Case0.RunSample1();
            //ECSharp16.Case0.RunSample();
        }
    }
}

/*
 * 1 : 지역변수를 선언할 때는 var 를 사용하는 것이 낫다
 * 2 : const 보다는 readonly 가 좋다.
 * 3 : 캐스트보다는 is, as 가 좋다.
 * 
 * 6 : nameof() 연산자를 적극 활용하라
 * 7 : 델리게이트를 이용하여 콜백을 표현하라
 * 8 : 이벤트 호출 시에는 null 조건 연산자를 사용하라
 * 9 : 박싱과 언박싱을 최소화하라
 * 10 : 베이스 클래스가 업그레이드 된 경우에만 new 한정자를 사용하라
 * 11 : .NET 리소스 관리에 대한 이해
 * 12 : 할당 구무보다 멤버 초기화 구문이 좋다.
 * 13 : 정적 생성자 구문을 올바르게 초기화하라
 * 14 : 초기화 코드가 중복되는 것을 최소화하라
 * 15 : 불필요한 객체를 만들지 말라.
 * 16 : 생성자 내에서는 절대로 가상 함수를 호출하지 말라
 * 17 : 표준 dispose 패턴을 구현하라
 */

/*
 * 항목 Template
 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 
    /// </summary>
    public static class ECSharp00
    {
        public static void RunSample()
        {

        }
    }
}

*/

/*
 * 클래스 템플릿

public class Widget
{
    Widget() { }
}

public struct MyValueType
{
    public int value;

    public MyValueType(int val)
    {
        value = val;
    }
}

public class MyRefType : IDisposable
{
    public void Dispose()
    {
        System.Console.WriteLine("On Dispose");
    }
}

*/
