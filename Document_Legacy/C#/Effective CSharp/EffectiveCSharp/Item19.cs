using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 런타임에 타입을 확인하여 최적의 알고리즘을 사용하라
    /// </summary>
    public static class ECSharp19
    {
        /// <summary>
        /// 잘 동작하는 편이지만 랜덤 액세스를 지원하는 컬렉션들에 대해서는 비효율적이다.
        /// 예를 들어 IList<T> 를 지원하는 인자가 생성자로 들어오면 따로 복제본을 만들 필요가 없다.
        /// </summary>
        public static class Before
        {
            public sealed class ReverseEnumerable<T> : IEnumerable<T>
        {
            private class ReverseEnumerator : IEnumerator<T>
            {
                int currentIndex;
                IList<T> collection;

                public ReverseEnumerator(IList<T> srcCollection)
                {
                    collection = srcCollection;
                    currentIndex = collection.Count;
                }

                public void Dispose()
                {
                    //예제에서는 구현하지 않았으나 실제로 사용할때는 반드시 필요
                    //IEnumerator<T>는 IDisposable을 상속하고 있기 때문
                    //이 클래스는 sealed class 이므로 따로 protected Dispose() 은 필요없다.
                }

                public T Current => collection[currentIndex];   //IEnumerator<T> 멤버
                object System.Collections.IEnumerator.Current => this.Current;  //IEnumerator 멤버
                public bool MoveNext() => --currentIndex >= 0;
                public void Reset() => currentIndex = collection.Count;
            }

            IEnumerable<T> sourceSequence;
            IList<T> originalSequence;

            public ReverseEnumerable(IEnumerable<T> sequence)
            {
                sourceSequence = sequence;
            }

            public IEnumerator<T> GetEnumerator()
            {
                if(originalSequence == null)
                {
                    originalSequence = new List<T>();
                    foreach(T item in sourceSequence)
                    {
                        originalSequence.Add(item);
                    }
                }

                return new ReverseEnumerator(originalSequence);
            }

            System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() => this.GetEnumerator();
        }
        }

        /// <summary>
        /// Before 의 코드를 런타임에 타입을 확인하는 방식으로 변환
        /// 
        /// 목표는 제네릭 클래스 내에 타입별로 별도로 구현해야 하는 부분을 잘 숨겨두는 것이다.
        /// </summary>
        public static class After
        {
            public sealed class ReverseEnumerable<T> : IEnumerable<T>
            {
                private class ReverseEnumerator : IEnumerator<T>
                {
                    int currentIndex;
                    IList<T> collection;

                    public ReverseEnumerator(IList<T> srcCollection)
                    {
                        collection = srcCollection;
                        currentIndex = collection.Count;
                    }

                    public void Dispose()
                    {
                        //예제에서는 구현하지 않았으나 실제로 사용할때는 반드시 필요
                        //IEnumerator<T>는 IDisposable을 상속하고 있기 때문
                        //이 클래스는 sealed class 이므로 따로 protected Dispose() 은 필요없다.
                    }

                    public T Current => collection[currentIndex];   //IEnumerator<T> 멤버
                    object System.Collections.IEnumerator.Current => this.Current;  //IEnumerator 멤버
                    public bool MoveNext() => --currentIndex >= 0;
                    public void Reset() => currentIndex = collection.Count;
                }
                private class ReverseStringEnumerator : IEnumerator<char>
                {
                    private string sourceSequence;
                    private int currentIndex;
                   
                    public ReverseStringEnumerator(string source)
                    {
                        sourceSequence = source;
                        currentIndex = source.Length;
                    }

                    public void Dispose()
                    {
                        //세부 구현 내용 생략
                    }
                   
                    public char Current => sourceSequence[currentIndex];  //IEnumerator<char> 멤버
                    object System.Collections.IEnumerator.Current => this.Current;  //IEnumerator 멤버
                    public bool MoveNext() => --currentIndex >= 0;
                    public void Reset() => currentIndex = sourceSequence.Length;
                }
                IEnumerable<T> sourceSequence;
                IList<T> originalSequence;

                public ReverseEnumerable(IEnumerable<T> sequence)
                {
                    sourceSequence = sequence;

                    // 만약 IList<T>를 구현하지 않았으면 null 이 할당되겠지만 문제되지 않는다.
                    originalSequence = sequence as IList<T>;
                }
                /// <summary>
                /// IList<T> 매개변수를 받는 오버로딩 생성자를 추가하면 되지 않을까 하지만, 이 경우 몇몇 상황에서 만족스럽게 동작하지 않는다.
                /// 예를 들어 런타임 시에는 IList<T> 타입의 객체라 하더라도 컴파일 타임에는 IEnumerable<T> 타입으로 간주될 수 있기 때문. => 이 경우에 대해서는 책에서 자세히 서술하지 않았다.
                /// 즉, 생성자 오버로딩 메서드 외에도 런타임 타입을 확인하도록 코드를 작성해야 한다.
                /// </summary>
                public ReverseEnumerable(IList<T> sequence)
                {
                    sourceSequence = sequence;
                    originalSequence = sequence;
                }

                /// <summary>
                /// 입력 시퀀스가 ICollection<T> 만을 구현한 경우 입력 시퀀스에 대한 복제본을 생성해야 하므로 매우 느리게 동작할 수 밖에 없다.
                /// Before의 코드를 아래와 같이 개선
                /// </summary>
                /// <returns></returns>
                public IEnumerator<T> GetEnumerator()
                {
                    //string 은 매우 특별한 케이스
                    if(sourceSequence is string)
                    {
                        //컴파일 타임에 T는 char가 아닐 수도 있으므로 캐스트에 주의해야 한다.
                        //런타임에 이 코드 블럭이 실행된다면 T 는 char 이므로 사실상 문제는 되지 않는다
                        return new ReverseStringEnumerator(sourceSequence as string) as IEnumerator<T>;
                    }

                    //역순으로 순회하기 위해서 원래 시퀀스를 복사
                    if (originalSequence == null)
                    {
                        if(sourceSequence is ICollection<T>)
                        {
                            ICollection<T> source = sourceSequence as ICollection<T>;
                            originalSequence = new List<T>(source.Count);
                        }
                        else
                        {
                            originalSequence = new List<T>();
                        }

                        foreach (T item in sourceSequence)
                        {
                            originalSequence.Add(item);
                        }
                    }

                    return new ReverseEnumerator(originalSequence);
                }

                System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() => this.GetEnumerator();
            }
        }
    }
}