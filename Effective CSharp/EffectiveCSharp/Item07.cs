using System;
using System.Collections;
using System.Linq;
using System.Collections.Generic;

//델리게이트를 이용하여 콜백을 표현하라

namespace EffectiveCSharp
{
    public class ECSharp07
    {
        /*
         * 콜백은 서버가 클라이언트에게 비동기적으로 피드백을 주기 위해서 주로 사용하는 방법이다. C# 에서는 델리게이트를 활용해서 콜백을 표현한다.
         */

        /// <summary>
        /// Linq의 List<T> 로 콜백을 사용하는 예
        /// </summary>
        public void DoSomething()
        {
            List<int> numbers = Enumerable.Range(1, 200).ToList();

            var oddNmbers = numbers.Find(n => n % 2 == 1);
            var test = numbers.TrueForAll(n => n < 50);

            numbers.RemoveAll(n => n % 2 == 0);

            numbers.ForEach(item => Console.WriteLine(item));
        }
        /// <summary>
        /// 모든 델리게이트는 기본적으로 멀티캐스트multicast 가 가능하다. 
        /// 멀티개스트 델리게이트는 한 번만 호출하면 델리게이트 객체에 추가된 모든 대상함수가 호출된다. 
        /// 하지만 이러한 구조에는 두 가지 두의해야할 부분이 있는데,
        /// 
        /// 1. 먼저 예외에 안전하지 않으며, 마지막으로 호출된 대상 함수의 반환값이 델리게이트의 반환값으로 간주된다
        /// 2. 델리게이트의 내부동작은 대상 함수들을 연속적으로 호출하는 형태로 구현된다.
        /// 델리게이트는 어떤 예외도 잡지 않으며(catch), 따라서 예외가 발생하면 함수 호출 과정이 중단된다.
        /// </summary>

        public class ComplicatedClass
        {
            public void LengthyOperation() { }
        }

        IEnumerable<ComplicatedClass> container;

        public void LengthyOperation(Func<bool> pred)
        {
            foreach (ComplicatedClass cl in container)
            {
                cl.LengthyOperation();
                //사용자가 임의로 중단을 요청했는지 확인

                if (pred() == false) //pred가 멀티캐스트 델리게이트 일 때, 
                                     //마지막으로 호출된 대상 함수의 반환값이 최종으로 반환된다.
                {
                    return;
                }
            }
        }

        /// <summary>
        /// 멀티캐스트가 부적절할 시, 델리게이트를 개별적으로 호출
        /// </summary>
        public void LengthyOperation2(Func<bool> pred)
        {
            bool bContinue = true;
            foreach (ComplicatedClass cl in container)
            {
                cl.LengthyOperation();
                foreach (Func<bool> pr in pred.GetInvocationList())
                //델리게이트에 등록된 모든 메소드를 개별적으로 호출
                {
                    bContinue &= pr();
                }

                if (bContinue == false)
                {
                    return;
                }
            }
        }
    }
    
}