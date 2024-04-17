using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//선택적 매개변수를 사용하여 메서드 오버로드를 최소화하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// C#에서는 메서드의 인수를 위치나 이름으로 지정할 수 있습니다. 이를 위해 형식 매개변수의 이름도 public 인터페이스에 포함됩니다.
    /// 
    /// 그러므로 매개변수의 이름을 변경하면 호출 측의 코드를 손상시킬 수도 있는 것입니다.
    /// </summary>
    public static class MECSharp12
    {
        private static void DoSomething(int a = 1, int b = 2, int c = 3, int d = 4, int e = 5)
        {
            Console.WriteLine($"A : {a}, B : {b}, C : {c}, D : {d}, E : {e}");
        }

        public static void RunSample()
        {
            //마지막 매개변수에만 값을 적용하고 싶은 경우라고 가정합시다. 
            //C++ 과 달리 앞의 a, b, c, d 매개변수는 명시적으로 지정할 필요가 없습니다.
            //선택적 매개변수로 e 값만 지정할 수 있습니다.
            DoSomething(e: 7);

            //매개변수 순서도 바꿀 수 있습니다.
            DoSomething(e: 7, a: 3);

            //메서드의 매개변수 이름도 public 인터페이스에 해당된다는 말도 이런 맥락입니다. 선택적 매개변수를 사용한다면 매개변수의 이름도 외부에서 중요한 역할을 맡게됩니다.
            //그러니 메서드의 매개변수를 변경하는 일은 최소화하되 매개변수를 추가하는 경우, 해당 매개변수가 기본값을 가지는지 확인하고 메서드를 오버로딩해야 할지 판단합시다.
        }
    }
}
