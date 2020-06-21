using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 타입 매개변수에 대해 메서드 제약 조건을 설정하려면 델리게이트를 활용하라
    /// </summary>
    public static class ECSharp23
    {
        /* C#의 제네릭 클래스/메소드 등에 설정하는 타입 매개변수 제약은 한계를 가지고 있는 것으로 보여진다.
         * (특정 멤버변수를 포함하고 있는지에 대한 제약 조건은 추가할 수 없다)
         * 
         * 인터페이스를 활용하는 방법이 있지만, 제약조건으로 활용하기 위해 인터페이스를 추가하는 것은 해야 할 작업량을 늘리는 동시에 구조를 해칠 위험이 있다.
         * 
         * 델리게이트를 바탕으로 우회책을 활용해보자.
         */

        public delegate T CreateFromStream<T>(System.IO.TextReader reader);
        
        public static T Add<T>(T left, T right, Func<T, T, T> AddFunc) => AddFunc(left, right);
        
        public struct Point
        {
            public double X { get; }
            public double Y { get; }

            public Point(double X, double Y)
            {
                this.X = X;
                this.Y = Y;
            }
            public Point(System.IO.TextReader reader)
            {
                string line = reader.ReadLine();
                string[] fields = line.Split(',');

                if (fields.Length != 2)
                {
                    throw new InvalidOperationException("Input format incorrect");
                }

                if (double.TryParse(fields[0], out var xVal))
                {
                    X = xVal;
                }
                else
                {
                    throw new InvalidOperationException("Could not parse X value");
                }

                if (double.TryParse(fields[1], out var yVal))
                {
                    Y = yVal;
                }
                else
                {
                    throw new InvalidOperationException("Could not parse Y value");
                }
            }
        }

        public static IEnumerable<Tout> Zip<T1, T2, Tout>( IEnumerable<T1> left, IEnumerable<T2> right, Func<T1, T2, Tout> generator)
        {
            IEnumerator<T1> leftSequence = left.GetEnumerator();
            IEnumerator<T2> rightSequence = right.GetEnumerator();

            while(leftSequence.MoveNext() && rightSequence.MoveNext())
            {
                yield return generator(leftSequence.Current, rightSequence.Current);
            }

            leftSequence.Dispose();
            rightSequence.Dispose();
        }

        /// <summary>
        /// 예시코드로 보면 굳이 제네릭 타입으로 만들 필요가 없을 만큼 간단하지만 
        /// 사용한 기법을 통해서 일반적인 방법으로는 제약 조건을 설정할 수 없는 부분까지 지정할 수 있다.
        /// </summary>
        public class InputCollection<T>
        {
            private List<T> thingsRead = new List<T>();
            private readonly CreateFromStream<T> readFunc;

            public InputCollection(CreateFromStream<T> readFunc)
            {
                this.readFunc = readFunc;
            }

            public void ReadFromStream(System.IO.TextReader reader) => thingsRead.Add(readFunc(reader));
            public IEnumerable<T> values => thingsRead;
        }

        public static void RunSample()
        {
            double[] xValues = { 0, 1, 2, 3, 4, 5 };
            double[] yValues = { 0, 1, 2, 3, 4, 5 };

            List<Point> values = new List<Point>(Zip(xValues, yValues, (x, y) => new Point(x, y) ));

            var readValues = new InputCollection<Point>((inputStream) => new Point(inputStream));
        }

        
    }
}