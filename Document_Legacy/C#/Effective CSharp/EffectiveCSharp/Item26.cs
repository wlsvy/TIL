using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 제네릭 인터페이스와 논 제네릭 인터페이스를 함께 구현하라
    /// </summary>
    public static class ECSharp26
    {
        /* 새로운 라이브러리를 개발할 때 제네릭 타입뿐 아니라 고전적인 방식도 함께 지원한다면 라이브러리 활용도를 좀 더 높일 수 있다.
         * 
         * 만약 nongeneric 타입을 지원하고자 한다면 아래 세 가지 요소에 대해서 nongeneric 방식을 지원해야 한다.
         * 1. 클래스와 인터페이스
         * 2. public 속성
         * 3. serialize 대상
         */

        public class Name : IComparable<Name>, IEquatable<Name>, IComparable
        {
            public string First;
            public string Last;
            public string Middle;

            /// <summary>
            /// IComparer<>
            /// </summary>
            public int CompareTo(Name other)
            {
                if(object.ReferenceEquals(this, other))
                {
                    return 0;
                }
                if(Object.ReferenceEquals(other, null))
                {
                    return 1;
                }

                int rVal = Comparer<string>.Default.Compare(Last, other.Last);

                if(rVal != 0)
                {
                    return rVal;
                }

                rVal = Comparer<string>.Default.Compare(First, other.First);
                if(rVal != 0)
                {
                    return rVal;
                }

                return Comparer<string>.Default.Compare(Middle, other.Middle);
            }

            /// <summary>
            /// IEquatable<>
            /// </summary>
            public bool Equals(Name other)
            {
                if (Object.ReferenceEquals(this, other))
                {
                    return true;
                }
                if (Object.ReferenceEquals(other, null))
                {
                    return false;
                }

                return Last == other.Last &&
                    First == other.First &&
                    Middle == other.Middle;
            }

            /// <summary>
            /// 만약 여기서 Name 객체를 비교한다면 IEquatable<Name>.Equals() 가 아닌 System.Object.Equals()를 호출하게 된다.
            /// 전자는 매개변수로 T 타입, 후자는 object 타입을 취하기 때문이다.
            /// </summary>
            public static bool CheckEquality(object left, object right)
            {
                if(left == null)
                {
                    return right == null;
                }
                return left.Equals(right);
            }

            /// <summary>
            /// 이렇게 코드를 작성한다면 Name 타입의 객체에 대해 동일성을 확인하는 작업을 올바르게 수행할 수 있다.
            /// </summary>
            public override bool Equals(object obj)
            {
                /* if 문 내부에서 as 를 통해 형변환 하는데 사전에 객체의 타입을 비교하는 이유
                 * 
                 * obj 객체가 Name을 상속한 파생클래스 타입인 경우, as 연산자는 객체에 대한 Name 타입의 참조를 반환한다.
                 * 이 경우 타입이 서로 다름에도 Name 타입 내에서 정의하고 있는 일부 값만 일치하다면 두 객체가 동일한 것으로 간주한다.
                 */
                if (obj.GetType() == typeof(Name))
                {
                    return this.Equals(obj as Name);
                }
                else
                {
                    return false;
                }
            }

            /// <summary>
            /// GetHashCode 역시 재정의
            /// </summary>
            public override int GetHashCode()
            {
                int hashCode = 0;

                if(Last != null)
                {
                    hashCode ^= Last.GetHashCode();
                }
                if (First != null)
                {
                    hashCode ^= First.GetHashCode();
                }
                if (Middle != null)
                {
                    hashCode ^= Middle.GetHashCode();
                }

                return hashCode;
            }

            public static bool operator ==(Name left, Name right)
            {
                if(left == null)
                {
                    return right == null;
                }
                return left.Equals(right);
            }
            public static bool operator !=(Name left, Name right)
            {
                if (left == null)
                {
                    return right != null;
                }
                return !left.Equals(right);
            }

            /// <summary>
            /// 명시적인 인터페이스 구현방식을 사용.
            /// 
            /// 이렇게 하면 실수로 제네릭 인터페이스 대신 논제네릭 인터페이스를 사용하는 것을 방지할 수 있다.
            /// 일반적인 방법으로 이 타입을 사용하면 제네릭 인터페이스를 구현한 메서드가 우선적으로 선택되기 때문이다.
            /// 
            /// nongeneric 인터페이스에 포함된 메서드를 호출하기 위해서는 명시적으로 IComparable 인터페이스 참조를 통해서 메서드를 호출해야 한다.
            /// </summary>
            int IComparable.CompareTo(object obj)
            {
                if(obj.GetType() != typeof(Name))
                {
                    throw new ArgumentException("Argument is not a Name object");
                }
                return this.CompareTo(obj as Name);
            }

            
            public static bool operator <(Name left, Name right)
            {
                if(left == null)
                {
                    return right != null;
                }
                return left.CompareTo(right) < 0;
            }
            public static bool operator >(Name left, Name right)
            {
                if (left == null)
                {
                    return false;
                }
                return left.CompareTo(right) > 0;
            }
            public static bool operator <=(Name left, Name right)
            {
                if (left == null)
                {
                    return true;
                }
                return left.CompareTo(right) <= 0;
            }
            public static bool operator >=(Name left, Name right)
            {
                if (left == null)
                {
                    return right == null;
                }
                return left.CompareTo(right) >= 0;
            }

            /* 위의 코드는 의미적으로는 Equatable<T> 와 Comparer<T> 의 구현 내용과 유사하다.
             * 
             * 클래스에 포함된 Default 특성(?)에는 타입 매개변수 T가 동일성과 선후 관계를 구현하고 있는지 확인하는 코드가 포함된다.
             * T타입이 이를 구현한다면 구현된 연산자가 사용되고, 그렇지 않다면 System.Object 타입을 매개변수로 취하는 메서드를 재정의한 코드가 사용된다.
             */
        }
    }
}