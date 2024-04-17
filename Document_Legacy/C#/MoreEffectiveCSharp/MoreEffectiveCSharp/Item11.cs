using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//API에는 변환 연산자를 작성하지 말라
namespace MoreEffectiveCSharp
{
    public static class MECSharp11
    {
        public class From
        {
            public int Value = 0;

            //암묵적 형변환 연산자
            public static implicit operator To(From from)
            {
                return new To();
            }
        }
        public class To
        {
            public int Value = 0;
        }

        public static void DoSomething(To to) => to.Value = 1;

        public static void RunSample()
        {
            From from = new From();
            DoSomething(from);  
            //암묵적 형변환을 수행합니다. -> To 타입의 임시객체가 생성된다는 사실에 주의합시다.
            //임시 객체는 즉시 가비지가 되며, 경우에 따라서 임시객체가 수행하는 동작은 의미가 없을 수도 있습니다.

        }
    }
}
