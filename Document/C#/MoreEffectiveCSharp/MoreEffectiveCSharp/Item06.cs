using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


//속성을 데이터처럼 동작하게 만들어라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 대부분의 사용자는 속성이 데이터 멤버와 동일하게 동작할 것으로 기대하며, 그렇지 않을 경우 타입을 잘못 사용할 수 있습니다.
    /// 
    /// 속성을 사용하는 문법이 데이터 멤버를 직접 사용하는 것과 같기 때문에, 동작 방식 또한 같으리라고 생각하게 됩니다.
    /// 
    /// 더하여, 사용자들은 속성 접근자가 많은 작업을 수행할 것으로 생각하지 않습니다. 
    /// get 접근자가 내부적으로 많은 작업을 수행하지 않도록 하고, set 접근자에서도 값의 유효성 검증 정도의 작업만 처리하도록 작성하는 것이 좋습니다.
    /// </summary>
    public static class MECSharp06
    {
        //아래의 코드는 속성에 대한 기본적인 가정을 지키고 있습니다. 빠르게 실행되며 객체의 유효성을 지켜줍니다.
        public class Widget
        {
            private string m_StrValue;
            public string StrValue
            {
                get => m_StrValue;
                set
                {
                    if (string.IsNullOrEmpty(value))
                    {
                        throw new ArgumentException("This Value can't be null or blank");
                    }
                    m_StrValue = value;
                }
            }
        }

        //point 구조체에서 속성을 활용한 예
        public struct Point
        {
            public int X, Y;
            public double Distance => Math.Sqrt(X * X + Y * Y);
        }

        //Distance를 자주 호출해야 하는 경우, 성능을 위해 거리값을 캐싱해 놓은 예
        public struct Point_New
        {
            private int m_Xvalue;
            private int m_Yvalue;
            private double? m_Distance;
            public int X
            {
                get => m_Xvalue;
                set
                {
                    m_Xvalue = value;
                    m_Distance = default(double?);
                }
            }
            public int Y
            {
                get => m_Yvalue;
                set
                {
                    m_Yvalue = value;
                    m_Distance = default(double?);
                }
            }
            public double Distance
            {
                get
                {
                    if (!m_Distance.HasValue)
                    {
                        m_Distance = Math.Sqrt(X * X + Y * Y);
                    }
                    return m_Distance.Value;
                }
            }
        }

        //속성 안에서 원격 데이터베이스에 접근하는 등 시간이 오래걸리는 기능을 넣지 맙시다.
        //만약 그런 경우, 사용자들은 set 접근자 내에서 데이터베이스에 접근할 것으로 기대하지는 않으니 그로 인한 오해로 속성을 잘못 사용할 수 있습니다.
        //디버그 중 디버거는 속성의 값을 출력하기 위해 get 접근자를 호출합니다. 
        //이때 get접근자에서 예외가 발생하거나 시간이 오래걸리거나 혹은 내부 상태를 변경하는 경우, 디버깅이 더 어려워질 것입니다.
    }
}
