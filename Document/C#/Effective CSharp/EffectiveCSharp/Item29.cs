using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 컬렉션을 반환하기보다 이터레이터를 반환하는 것이 낫다.
    /// </summary>
    public static class ECSharp29
    {
        /* 일련의 시퀀스를 반환해야 하는 경우, 컬렉션을 반환하기 보다 이터레이터를 반환하는 것이 좋다.
         * 
         * 이터레이터를 반환하면 이를 이용하여 다양한 작업을 좀 더 수월하게 수행할 수 있기 때문이다.
         */ 

        /// <summary>
        /// 이터레이터 메서드란 호출자가 요청한 시퀀스를 생성하기 위해서 yield return 문을 사용하는 메서드를 말한다. 
        /// 
        /// 아래는 알파벳 소문자에 대한 시퀀스를 생성하는 기본적인 이터레이터 메서드이다.
        /// </summary>
        public static IEnumerable<char> GenerateAlphabet()
        {
            var letter = 'a';
            while (letter <= 'z')
            {
                yield return letter;
                letter++;
            }
        }

        /// <summary>
        /// 이터레이터 메서드가 호출되면 앞에서와 같이 컴파일러가 생성한 객체가 인스턴스화 된다. 
        /// 이후 시퀀스 내에 포함된 항목을 요청하면 비로소 시퀀스가 생성된다.
        /// </summary>
        class EmbeddedIterator : IEnumerable<char>
        {
            private class LetterEnumerator : IEnumerator<char>
            {
                private char letter = (char)('a' - 1);

                public bool MoveNext()
                {
                    letter++;
                    return letter <= 'z';
                }

                public char Current => letter;
                object IEnumerator.Current => (object)letter;

                public void Reset() => letter = (char)('a' - 1);

                void IDisposable.Dispose() { }
            }

            public IEnumerator<char> GetEnumerator() => new LetterEnumerator();
            IEnumerator IEnumerable.GetEnumerator() => new LetterEnumerator();

            public static IEnumerable<char> GenerateAlphabet() => new EmbeddedIterator();
        }

        public static void RunSample()
        {
            /* int 시퀀스를 만들어내는 객체 생성. 
             * 호출 측에서는 이터레이터 메서드의 결과값을 추가적인 컬렉션에 저장하지 않는 이상 방대한 결과치를 저장하기 위한 공간이 필요하지 않다. 
             * 
             * 정확히 필요한 개수의 숫자만을 생성하는 것만큼 효율적이지는 않겠지만 음이 아닌 모든 정수를 생성하여 저장소에 저장하는 것보다는 낫다.
             * 
             * '필요할 때 생성' 이라는 전략은 이터레이터 메서드를 작성할 때 가장 중요한 전략 중 하나다.
             * 이터레이터 메서드는 시퀀스를 생성하는 방법을 알고 있는 객체를 생성한다. 그리고 이 객체는 실제 시퀀스에 대한 접근이 이루어지는 경우에만 사용된다.
             */
            var allNumbers = Enumerable.Range(0, int.MaxValue); 
        }

        public static IEnumerable<char> GenerateAlphabetSubset(char first, char last)
        {
            if (first < 'a')
            {
                throw new ArgumentException("first must be at least the letter a", nameof(first));
            }
            if(first > 'z')
            {
                throw new ArgumentException("first must be no greater than z", nameof(first));
            }
            if(last < first)
            {
                throw new ArgumentException("last must be at least as large as first", nameof(last));
            }
            if(last > 'z')
            {
                throw new ArgumentException("last must not be past z", nameof(last));
            }

            var letter = first;

            while(letter <= last)
            {
                yield return letter;
                letter++;
            }
        }

        /// <summary>
        /// 만약 컴파일러가 GenerateAlphabetSubset 와 같은 시퀀스 메서드를 확인하면
        /// 아래와 유사한 클래스를 새로 작성한다.
        /// 
        /// IEnumerable을 반환하는 함수는 사실 컴파일러가 임의로 작성한 클래스의 객체를 반환하는 것.
        /// 
        /// 유념해야 할 점은 시퀀스의 첫 번째 요소가 요청될 때까지 매개변수의 값이 유효한지를 확인하는 코드가 수행되지 않는다는 것이다.
        /// 즉, 메서드에 잘못된 인자를 넘겼을 때 문제를 확인하고 해결하기가 까다롭다. 
        /// 개발자가 잘못 작성한 코드에서 예외가 발생하는 것이 아니라 나중에 시퀀스를 사용하려 할 때 예외가 발생하기 때문이다.
        /// </summary>
        public class EmbeddedSubsetIterator : IEnumerable<char>
        {
            private readonly char first;
            private readonly char last;

            public EmbeddedSubsetIterator(char first, char last)
            {
                this.first = first;
                this.last = last;
            }

            public IEnumerator<char> GetEnumerator() => new LetterEnumerator(first, last);
            IEnumerator IEnumerable.GetEnumerator() => new LetterEnumerator(first, last);

            public static IEnumerable<char> GenerateAlphabetSubset(char first, char last) => new EmbeddedSubsetIterator(first, last);

            private class LetterEnumerator : IEnumerator<char>
            {
                private readonly char first;
                private readonly char last;

                private bool isInitialized = false;

                public LetterEnumerator(char first, char last)
                {
                    this.first = first;
                    this.last = last;
                }

                private char letter = (char)('a' - 1);

                public bool MoveNext()
                {
                    if (!isInitialized)
                    {
                        if (first < 'a')
                        {
                            throw new ArgumentException("first must be at least the letter a", nameof(first));
                        }
                        if (first > 'z')
                        {
                            throw new ArgumentException("first must be no greater than z", nameof(first));
                        }
                        if (last < first)
                        {
                            throw new ArgumentException("last must be at least as large as first", nameof(last));
                        }
                        if (last > 'z')
                        {
                            throw new ArgumentException("last must not be past z", nameof(last));
                        }
                        letter = (char)('a' - 1);
                        //이 부분에서 isInitialized = true;를 해줘야 할 것 같은데 책에는 따로 그 내용이 없다.
                    }

                    letter++;
                    return letter <= last;
                }

                public char Current => letter;
                object IEnumerator.Current => letter;

                public void Reset() => isInitialized = false;

                void IDisposable.Dispose() { }
            }
        }

        /// <summary>
        /// 컴파일러의 코드 생성 방식을 변경할 수는 없지만, 
        /// 코드를 약간 재구성하여 인자에 대한 유효성 검사를 수행하는 부분과 실제로 시퀀스를 생성하는 부분을 분리할 수는 있다.
        /// 
        /// 이전처럼 시퀀스에 접근하려 할 때 뒤늦게 예외가 발생하는 것을 막을 수 있다.
        /// </summary>
        public static IEnumerable<char> GenerateAlphabetSubset_Re(char first, char last)
        {
            if (first < 'a')
            {
                throw new ArgumentException("first must be at least the letter a", nameof(first));
            }
            if (first > 'z')
            {
                throw new ArgumentException("first must be no greater than z", nameof(first));
            }
            if (last < first)
            {
                throw new ArgumentException("last must be at least as large as first", nameof(last));
            }
            if (last > 'z')
            {
                throw new ArgumentException("last must not be past z", nameof(last));
            }

            return GenerateAlphabetSubsetImpl(first, last);
        }

        private static IEnumerable<char> GenerateAlphabetSubsetImpl(char first, char last)
        {
            var letter = first;
            while(letter <= last){
                yield return letter;
                letter++;
            }
        }

        /* 메서드는 필요에 따라 다른 반환 타입을 가질 수 있으며 이러한 반환 타입의 객체를 생성하는 데 드는 비용은 타입별로 각기 다르다.
         * 
         * 계산 시간과 저장소 공간을 모두 고려한다면 간혹은 시퀀스를 반환하는 메서드가 전체 시퀀스를 단번에 생성하여 반환하는 메서드보다 비용이 더 클 수도 있다.
         * 
         * 하지만 이에 대해서 과도하게 신경쓰기보다는 API를 좀 더 쉽게 사용할 수 있도록 배려하는 것에 집중하는 것이 좋다.
         * 이런 측면에서 IEnumerable<T>와 같은 인터페이스를 반환하도록 메서드를 작성하는 편이 좀 더 편리하다. 필요할 때마다 하나씩 항목을 생성할 수도 있고, 
         * ToList(), ToArray()를 이용하여 전체 시퀀스가 저장된 컬렉션을 생성할 수도 있기 때문이다.
         * 
         */ 
    }
}