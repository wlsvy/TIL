using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 함수를 매개변수로 사용하여 결합도를 낮춰라
    /// </summary>
    public static class ECSharp34
    {
        /* 컴포넌트 간의 계약 관계를 기술할 때 베이스 클래스 혹은 인터페이스를 활용하곤 한다.
         * 
         * 베이스 클래스를 활용하는 방식이라면 최종 사용자는 우리가 개발한 컴포넌트를 매우 쉽게 활용할 수 있다.
         * 이 경우 계약 사항은 매우 명확하며 특정 베이스 클래스를 상속하여 새로운 클래스를 작성하고 추상(혹은 가상) 메서드를 구현해 주기만 하면 된다.
         * 사용자는 동일한 기능을 재구현해야 하는 부담을 덜 수 있다.
         * 1. 컴포넌트의 관점에서 보더라도 특정 동작이 반드시 구현되었을 것이라 가정할 수 있다.(구현 내용과는 관계없이)
         * 2. 베이스 클래스에서 파생 클래스가 반드시 작성해야 하는 작업을 강제하는 것은 제약이 많다. 사용자 입장에서는 매우 제한적으로 느껴질 수 있다.
         * 
         * 
         * 인터페이스를 작성하고 이를 구현하도록 구조를 가져가면 베이스 클래스에 의존하는 방식보다는 조금 더 느슨한 결합을 만들 수 있다.
         * 1. 인터페이스를 사용하면 사용자에게 클래스의 계층 구조를 강제하지 않을 수 있다는 장점이 있다.
         * 2. 인터페이스만을 제공하기 때문에 클라이언트 코드에서 활용할 수 있는 재사용 기능 코드를 제공하기가 어렵다는 단점이 있다.
         * 
         * 함수를 매개변수로 전달하는 방식. 즉, 델리게이트를 활용한다면
         * 1. 개발자가 더 이상 구상 타입concrete type을 작성할 필요가 없으며, 오히려 추상화된 정의를 통해서 종속성을 다루는 것을 의미한다.
         * 2. 하지만 함께 사용하던 코드들을 분리하려면 추가 작업을 할 수밖에 없고 코드의 명확성도 떨어진다.
         * 3. 별도로 델리게이트나 여타의 통신 매커니즘을 사용하여 코드상의 결합도를 낮추면 낮출수록 컴파일러가 제공하는 다양한 검사 기능을 활용하기가 어려워진다.
         */

        /// <summary>
        /// 항목 31에서 Zip 구현 예
        /// </summary>
        public static IEnumerable<string> Zip<T>(IEnumerable<string> first, IEnumerable<string> second)
        {
            using (var firstSequence = first.GetEnumerator())
            {
                using (var secondSequence = second.GetEnumerator())
                {
                    while (firstSequence.MoveNext() && secondSequence.MoveNext())
                    {
                        yield return $"{firstSequence.Current} {secondSequence.Current}";
                    }
                }
            }
        }

        /// <summary>
        /// 델리게이트를 활용하는 방식으로 수정한 모습
        /// 
        /// 이처럼 코드를 작성하면 Zip 메서드와 호출자의 결합도가 훨씬 느슨해진다.
        /// </summary>
        public static IEnumerable<TResult> Zip<T1, T2, TResult>(
            IEnumerable<T1> first, 
            IEnumerable<T2> second,
            Func<T1, T2, TResult> zipper)
        {
            using (var firstSequence = first.GetEnumerator())
            {
                using (var secondSequence = second.GetEnumerator())
                {
                    while (firstSequence.MoveNext() && secondSequence.MoveNext())
                    {
                        yield return zipper(firstSequence.Current, secondSequence.Current);
                    }
                }
            }
        }

        /// <summary>
        /// 항목 33의 CreateSequence 예
        /// </summary>
        public static IEnumerable<int> CreateSequence(int numberOfElements, int startAt, int stepBy)
        {
            for (var i = 0; i < numberOfElements; i++)
            {
                yield return startAt + i * stepBy;
            }
        }

        public static IEnumerable<T> CreateSequence<T>(
            uint numberOfElements, 
            Func<T> generator)
        {
            for (var i = 0; i < numberOfElements; i++)
            {
                yield return generator();
            }
        }

        /// <summary>
        /// 시퀀스의 합을 구하는 코드를 분리한 예시
        /// </summary>
        public static TResult Fold<T, TResult>(IEnumerable<T> sequence, TResult total, Func<T, TResult, TResult> accumulator)
        {
            foreach(T item in sequence)
            {
                total = accumulator(item, total);
            }
            return total;
        }

        public static void RunSample()
        {
            var zipResult = Zip(
                Enumerable.Range(0, 10), 
                Enumerable.Repeat<char>('f', 30),
                (i, c) => $"{i.ToString()} {c}");

            var startAt = 0;
            var nextVal = 5;
            var sequence = CreateSequence(1000, () => startAt += nextVal);
        }

        /* 함수를 매개변수로 사용하면 알고리즘 자체와 알고리즘을 적용할 타입을 분리하는 데 도움이 된다.
         * 
         * 하지만 이렇게 결합도를 느슨하게 구성하려면 분리된 컴포넌트를 사용할 때 발생할 수 있는 오류를 처리하기 위해 추가적인 작업을 해야 한다.
         * 예를 들어 이벤트를 정의하는 코드를 작성했다고 생각해보자. 
         * 
         * 사용자가 이벤트 핸들러를 구성하지 않았을 수도 있으므로 이벤트를 발생시킬 때마다 해당 이벤트가 null인지 확인해야 한다.
         * 델리게이트를 사용할 때도 마찬가지이다.
         * 
         * 클라이언트가 델리게이트로 null을 전달하면
         * 1. 예외적인 상황인지
         * 2. 이 경우를 위한 기본동작이 있는지
         * 3. 만약 델리게이트가 예외를 일으키면 어떻게 되는지 이를 복구할 수 있는지. 만일 그렇다면 어떻게 복구할 것인지.
         * 
         * 사용자에게 요구하는 계약 사항을 상속 기법을 이용하여 엄밀하게 정의하지 않고 델리게이트를 사용한다 하더라도, 
         * 델리게이트에 대한 참조가 필요하므로 런타임에 결합 관계는 여전히 발생한다는 사실을 알아두자.
         * 
         * 만약 어떤 객체가 특정 델리게이트를 나중에 다시 사용하기 위해서 그 복사본을 저장해둔다면 이 객체는 델리게이트의 생명주기에 영향을 미치게 된다.
         * 즉 참조하는 델리게이트가 이전보다 더 오래 살아있게 된다. 이는 나중에 사용할 목적으로 객체에 대한 참조를 저장해두는 것과 다를 바 없다.
         * 
         * 
         * 
         * 
         * 컴포넌트와 이를 사용하는 클라이언트 코드 간에 계약 관계를 정의하는 가장 핵심적인 방법은 여전히 인터페이스를 활용하는 것이다.
         * 
         * 추상 베이스 클래스를 사용하면 클라이언트 측에서 자주 사용할 법한 코드를 미리 구현해서 제공할 수도 있고
         * 델리게이트를 잘 활용하면 유연성을 매우 높일 수 있지만
         * 
         * 도구의 지원을 많은 부분 포기해야 할 수도 있다.
         */
    }
}