using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// Action, Predicate, Function 과 순회 방식을 분리하라
    /// </summary>
    public static class ECSharp32
    {
        /* 익명 델리게이트를 사용할 때는 action 과 function 이라는 두 가지 패턴이 있다.
         * function 의 특별한 용례인 predicate도 있는데 이는 시퀀스 내의 항목이 조건에 부합하는지를 boolean 로 반환하는 function을 말한다.
         * 
         * action 델리게이트는 컬렉션 내의 개별 요소에 대하여 실제 수행할 작업을 전달하기 위해 주로 사용된다.
         */ 

        /// <summary>
        /// Where의 구현. 각 원소는 Predicate를 통해 평가된다. 여기서 Predicate는 일종의 필터 역할을 맡은 셈
        /// </summary>
        public static IEnumerable<T> Where<T>(IEnumerable<T> sequence, Predicate<T> filterFunc)
        {
            if(sequence == null)
            {
                throw new ArgumentException(nameof(sequence), "sequence must not be null");
            }
            if(filterFunc == null)
            {
                throw new ArgumentNullException("Predicate must not be null");
            }

            foreach(T item in sequence)
            {
                if (filterFunc(item))
                {
                    yield return item;
                }
            }
        }

        /// <summary>
        /// 시퀀스에서 N번째 원소를 반환하는 메서드
        /// </summary>
        public static IEnumerable<T> EveryNthItem<T>(IEnumerable<T> sequence, int period)
        {
            var count = 0;

            foreach(T item in sequence)
            {
                if(++count % period == 0)
                {
                    yield return item;
                }
            }
        }

        /// <summary>
        /// Select의 구현. 시퀀스로부터 새로운 시퀀스를 생성하는 변환 메서드이다.
        /// </summary>
        public static IEnumerable<T> Select<T>(IEnumerable<T> sequence, Func<T, T> method)
        {
            foreach(T element in sequence)
            {
                yield return method(element);
            }
        }
        public static IEnumerable<Tout> Select<Tin, Tout>(IEnumerable<Tin> sequence, Func<Tin, Tout> method)
        {
            foreach(Tin element in sequence)
            {
                yield return method(element);
            }
        }

        /* 이러한 메서드를 작성하고 사용하는 것은 어렵지 않지만,
         * 1. 시퀀스를 순회하는 것과
         * 2. 시퀀스의 개별 요소에 대해 작업을 수행하는 것을 구분해야 하는 것을 기억하자.
         * 
         * 익명 델리게이트나 람다 표현식을 이용하여 코드를 작성해두면 다양한 방법으로 이를 재사용할 수 있다.
         */ 
    }
}