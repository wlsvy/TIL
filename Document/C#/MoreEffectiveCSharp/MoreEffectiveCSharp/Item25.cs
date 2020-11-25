using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//배열 매개변수에는 params 배열만 사용해야 한다
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 매개변수로 배열을 사용하면 예측하기 어려운 다양한 문제에 노출됩니다. 컬렉션이나 가변 길이의 매개변수를 취하도록 메서드를 작성하는 것이 낫습니다.
    /// 
    /// 배열은 공변성covariant을 지원하는 특징 탓에 런타임에 타입 관련 오류가 발생할 수 있습니다.
    /// 배열은 요소를 간접적으로 참조할 수 있기 때문에 매개변수로 넘어간 배열이 메서드 내부에서 내용이 변경될 수 있습니다. 
    /// 
    /// 차라리 IEnumerable<T> 을 사용하는 것이 대안이 될 수도 있습니다. 해당 시퀀스에서는 내용을 변경하는 메서드를 제공하지 않습니다.
    /// 공변성을 활용해 매개변수로 베이스 클래스 배열을 전달하게 할 수도 있지만, 베이스 타입에서 컬렉션의 내용을 수정하는 API가 없어야 합니다.
    /// 
    /// 때로는 메서드에 가변 개수의 인수들을 전달해야 할 때가 있습니다. 이 때는 param 배열을 사용하는 것이 좋습니다.
    /// </summary>
    public static class MECSharp25
    {
        private static void ReplaceIndices(object[] arr)
        {
            for(int i = 0; i < arr.Length; i++)
            {
                arr[i] = i;
            }
        }

        private class B 
        {
            public static B Factory() => new B();
        }
        private class D1 : B 
        {
            public static new B Factory() => new D1();
        }
        private class D2 : B
        {
            public static new B Factory() => new D2();
        }

        private static void FillArray(B[] arr, Func<B> generator)
        {
            for(int i = 0; i < arr.Length; i++)
            {
                arr[i] = generator();
            }
        }

        //메서드에 가변 개수의 인수들을 전달해야 할 때가 있습니다. 이 때는 param 배열을 사용하는 것이 좋습니다.
        private static void WriteOutput1(object[] stuff)
        {
            foreach(var o in stuff)
            {
                Console.WriteLine(o.ToString());
            }
        }
        private static void WriteOutput2(params object[] stuff)
        {
            foreach (var o in stuff)
            {
                Console.WriteLine(o.ToString());
            }
        }

        public static void RunSample()
        {
            var labels = new string[] { "one", "two", "three", "four", "five" };
            try
            {
                //조금 극단적인 예. 예외를 던집니다.
                ReplaceIndices(labels);
            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());    //ArrayTypeMismatchException
            }

            //문제 없습니다.
            B[] storage = new B[10];
            FillArray(storage, () => B.Factory());
            FillArray(storage, () => D1.Factory());
            FillArray(storage, () => D2.Factory());

            try
            {
                //예외를 던집니다.
                storage = new D1[10];
                FillArray(storage, () => B.Factory());
                FillArray(storage, () => D1.Factory());
                FillArray(storage, () => D2.Factory());
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());    //ArrayTypeMismatchException
            }

            //가변 개수의 인수를 전달할 때
            WriteOutput1(new string[] { "one", "two", "three", "four", "five" });
            //WriteOutput1(); //컴파일 에러
            //WriteOutput1(null) //nullreferenceException
            WriteOutput1(new object[] { }); //빈 배열을 전달하고 싶으면 마음에 안들어도 이렇게 작성해야 합니다.

            WriteOutput2("one", "two", "three", "four", "five");
            WriteOutput2(); //문제 없습니다.
        }
    }
}
