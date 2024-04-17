using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//값 타입에서는 0이 유효한 상태가 되도록 설계하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 주로 enum 값을 명시할 때, 0에 해당하는 값이 무효하다는 것(None)을 의미하도록 표현하는 것을 고려합시다.
    /// 
    /// 비트 연산 (!=, &&, || 등)에서 0 은 중요한 의미를 가지며, .NET에서 기본적으로 모든 객체를 0으로 초기화하기 때문입니다.
    /// enum에서 첫번째 값을 명시적으로 0이 아닌 값으로 표현한다면, 처음 값을 초기화할때 무효한 값을 가진 상태가 되는 것입니다.
    /// </summary>
    public static class MECSharp05
    {
        //명시적으로 0에 해당하는 enum값을 넣지 않은 경우
        public enum Planet
        {
            Mercury = 1,
            Venus = 2,
            Count
        }

        public static void RunSample()
        {
            //0을 출력합니다. 즉 default(Planet) 값은 유효하지 않은 상태인 것입니다.
            Console.WriteLine($"Intialized Planet Value : {default(Planet)}");
        }

        //아래처럼 0에 해당하는 값을 포함시킵시다. 보통의 경우, None 처럼 임의의 상태가 아닌 값을 0에 대응시킵시다.
        public enum Widget
        {
            None = 0,
            Type1 = 1,
            Type2 = 2,
            Type3 = 3,
            Type4 = 4,
            Count
        }
    }
}
