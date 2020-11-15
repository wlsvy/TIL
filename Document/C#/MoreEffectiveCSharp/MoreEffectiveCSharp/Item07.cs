using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//튜플을 사용해서 타입의 사용 범위를 제한하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// C#에서 객체나 자료구조를 표현하는 사용자 정의 타입을 만드는 방법으로서 클래스, 구조체, 튜플tuple, 익명anonymous 타입을 예로 들 수 있습니다.
    /// 여기서 클래스와 구조체는 설계를 구현하기 위해 다양한 표현 방식을 제공하다보니 과도하게 이 둘만 사용하는 경향이 있습니다.
    /// 
    /// 경우에 따라서 간단한 기능을 구현하려는 경우에는 튜플과 익명 타입을 고려하는 것도 좋은 방법입니다.
    /// </summary>
    public static class MECSharp07
    {
        //익명 타입은 컴파일러가 생성하는 변경 불가능한 참조 타입입니다.

        private static void RunAnonymousTypeSample()
        {
            //아래 문장을 컴파일러에게 다음과 같은 사실을 알려줍니다.
            //1. 내부적으로 활용할 새로운 sealed 클래스가 필요하다.
            //2. 이 타입은 변경이 불가능하고, 2개의 읽기 전용 public 속성인 X, Y를 가집니다.
            var aPoint = new { X = 5, Y = 67 };
        }

        /// <summary>
        /// 위의 문장은 AnonymousMumbleMumble 클래스로 변환된다고 볼 수 있습니다.
        /// 익명 타입의 장점으로
        /// 1. 컴파일러를 이용하는 편이 훨씬 수월합니다. 직접 코드를 입력하는 것에 비해 더 빨리 작성할 수 있습니다.
        /// 2. 개발자는 간혹 무언가를 실수할 수 있지만, 컴파일러는 그렇지 않습니다.
        /// 3. 컴파일러에 코드 생성을 위임하면 우리가 직접 관리해야할 코드를 최소화할 수 있습니다.
        /// 4. 익명 타입은 객체 초기화 구문을 지원하는 변경 불가능한 타입을 만드는 유일한 방법입니다.
        /// 5. 익명 타입의 런타임 비용은 생각보다 크지 않습니다. 익명 타입을 만들 때마다 컴파일러가 새로운 익명 타입을 정의할 것 같지만 충분히 최적화되어 있습니다.
        ///   똑같은 익명 타입을 요청하면 이전에 만든 익명 타입을 재사용합니다. 
        /// 
        /// 단점으로는
        /// 1. 익명 타입의 이름은 알 수 없으므로 이 타입으로 매개변수를 전달할 수도, 반환값의 타입으로 사용할 수도 없습니다.
        /// 2. 데이터는 포함하지만 동작은 포함하지 않습니다. 즉 익명 타입에서 사용자 정의 메소드를 작성할 수 없습니다.
        /// 
        /// </summary>
        internal sealed class AnonymousMumbleMumble
        {
            private readonly int x;
            public int X => x;

            private readonly int y;
            public int Y => y;

            public AnonymousMumbleMumble(int xParam, int yParam)
            {
                x = xParam;
                y = yParam;
            }
        }

        private static T Transform<T>(T element, Func<T, T> transformFunc)
        {
            return transformFunc(element);
        }

        /// <summary>
        /// 자동으로 생성된 익명 타입과는 달리, 이 타입으로 생성한 객체나 시퀀스는 여전히 사용 가능한데, 
        /// 해당 객체를 사용하는 메서드나 표현식을 익명 타입을 정의하고 있는 메서드 내의 정의하면 됩니다.
        /// 
        /// 복잡한 알고리즘을 구현하다 보면 람다 표현식도 복잡해지고, 여러 번에 걸쳐 제네릭 메서드를 호출해야 하는 수 밖에 없습니다.
        /// 다행히 이 경우에 익명 타입은 중간 결과를 저장하기에 안성맞춤입니다.
        /// 
        /// 익명 타입은 여러 단계를 거쳐야 하는 알고리즘을 수행할 때 각 단계의 결과를 임시 저장할 때 사용할 수 있고, 이를 다음 단계의 입력으로 전달할 수도 있습니다.
        /// 
        /// 익명 타입의 범위는 그것을 정의한 메서드 내로 제한되기 때문에 
        /// 개발자가 애플리케이션을 이해하기 위해 봐야 할 타입의 개수가 줄어들며 해당 익명 타입이 메서드 내에서만 쓰인다는 것을 명확하게 해줍니다.
        /// </summary>
        private static void RunAnonymousTypeSample2()
        {
            //익명 타입을 변환 메서드에 적용할 수 있습니다.
            var aPoint = new { X = 5, Y = 67 };
            var anotherPoint = Transform(aPoint, (p) => new { X = p.X * 2, Y = p.Y * 2 });
        }

        public class Widget
        {
            public long ID;
            public string Name;
            public long Value;
        }

        /// <summary>
        /// 서로 다른 위치에서 사용되는 익명 타입들을 컴파일러가 '동일한 타입'으로 간주하는 조건
        /// 1. 익명 타입들이 동일한 어셈블리 안에 선언되어야 합니다.
        /// 2. 속성 이름과 타입이 일치해야 하며, 같은 순서로 선언되어야 합니다.
        /// </summary>
        private static void RunAnonymousTypeSample3()
        {
            //아래는 서로 다른 익명 타입입니다.
            var aPoint = new { X = 5, Y = 67 };
            var anotherPoint = new { Y = 12, X = 16 };

            //익명 타입은 동일성equality를 검사할 때 값의 내용을 기반으로 하기 때문에 복합키로 사용할 수 있습니다.
            var arr = new Widget[100];
            var query = from c in arr
                        group c by new { c.ID, c.Value };
        }

        /// <summary>
        /// 튜플tuple은 인스턴스를 생성할 때 경량의 타입을 정의한다는 면에서 익명타입과 비슷합니다. 하지만 public 필드를 포함하는 변경 가능한 값 타입이라는 점에서 큰 차이가 있습니다.
        /// 
        /// 컴파일러는 제네릭 타입인 ValueTuple을 활용하며, 각 속성의 이름은 사용자가 지정한 속성 이름을 그대로 사용합니다.
        /// 익명 타입과는 달리 튜플을 인스턴스화하면, 완전히 새로운 타입을 생성하는 것이 아니라 ValueTuple 제네릭 구조체를 이용하여 닫히closed 제네릭 타입을 생성합니다.
        /// (이미 필드의 개수별로 여러 개의 ValueTuple 제네릭 타입이 정의되어 있습니다.)
        /// 
        /// C#에서는 기본적으로 객체간의 타입 호환성을 확인하기 위해 타입의 이름을 사용합니다. 이러한 방식을 기반 타이핑(nominative typing)이라고 합니다.
        /// 그런데, 튜플에서는 객체들이 같은 타입인지를 결정할 때 이름 기반 타이핑이 아니라 구조적 타이핑(structural typing)을 사용합니다.
        /// 즉, 튜플은 이름대신 형태shape를 확인하여 타입이 같은지 확인합니다. 
        /// 
        /// 이런 이유로, 두 개의 정수를 가지는 모든 튜플은 앞의 예제에서 살펴본 Point 튜플과 같은 타입으로 간주되며 두 객체 모두 System.ValueTuple <int, int> 의 인스턴스입니다.
        /// </summary>
        private static void RunTupleSample()
        {
            //튜플은 아래와 같이 정의합니다.
            //두 갱의 정수필드를 가진 튜플을 만듭니다. 컴파일러는 각 필드들에 부여한 X, Y 라는 이름을 유지하므로, 이를 통해 해당 필드에 접근할 수 있습니다.
            var aPoint = ( X: 5, Y: 67);
            var anotherPoint = aPoint;

            //pointThree 에서는 필드 이름으로 Rise와 Run을 사용합니다. aPoint를 문제없이 pointThree에 대입할 수 있는데 사실 이 둘은 같은 튜플 타입이기 때문입니다.
            (int Rise, int Run) pointThree = aPoint;

            (int A, int B) val = (A: 7, B: 5);
            Console.WriteLine($"Sample Tuple : {val.ToString()}");
        }


        /// <summary>
        /// 익명 타입과 튜플 중 하나를 선택할 때는 두 타입간 차이를 고려해야 할 것입니다. 
        /// 
        /// 튜플은 구조적 타이핑을 따르므로 메서드의 반환 타입이나 매개변수의 타입으로 사용하기에 적합합니다.
        /// 익면 타입은 변경 불가능한 타입을 정의할 때나, 중간 결과를 저장할 때, 혹은 컬렉션의 복합키로 사용하기 좋습니다.
        /// 
        /// 튜플은 값 타입이 가지는 장점을 포함하는 반면, 익명 타입은 참조 타입이 가지는 장점을 포함합니다.
        /// </summary>
        public static void RunSample()
        {
            RunAnonymousTypeSample();
            RunAnonymousTypeSample2();
            RunAnonymousTypeSample3();

            RunTupleSample();
        }
    }
}
