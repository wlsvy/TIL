using System;
using System.Collections;
using System.Linq;
using System.Collections.Generic;

namespace EffectiveCSharp
{
    public class ECSharp07
    {
        public void DoSomething()
        {
            List<int> numbers = Enumerable.Range(1, 200).ToList();

            var oddNmbers = numbers.Find(n => n % 2 == 1);
            var test = numbers.TrueForAll(n => n < 50);

            numbers.RemoveAll(n => n % 2 == 0);

            numbers.ForEach(item => Console.WriteLine(item));
        }

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