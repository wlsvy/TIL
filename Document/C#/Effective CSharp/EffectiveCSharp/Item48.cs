using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 강력한 예외 보증을 준수하는 것이 좋다
    /// </summary>
    public static class ECSharp48
    {
        /* 강력한 보증이란 예외로 인해 요청됐던 작업이 중단되는 경우에도 응용프로그램을 변경 이전의 상태로 유지해야 함을 의미합니다.
         * 즉, 작업이 온전히 완료되거나 혹은 응용프로그램의 상태가 그대로 유지되거나 둘 중 하나의 경우만 가능해야 하며, 그 중간이 존재해서는 안됩니다.
         * 
         * 강력한 보증을 준수하면 예외를 catch한 경우에도 응용프로그램을 이어서 수행하기가 수월합니다.
         * 
         * 강력한 보증을 위해서는 앞에 항목에서 살펴봤던 권고 사항과 더불어서 프로그램이 사용하는 데이터 요소는 변경 불가능한 값 타입에 저장하는 것도 좋습니다.
         * LINQ 쿼리를 이용하는 함수형 프로그래밍 스타일을 사용하는 것도 도움이 됩니다. 
         * LINQ 쿼리를 사용하면 기본적으로 강력한 예외 보증 요건을 준수하게 됩니다.
         * 
         * 때로는 함수형 프로그래밍 스타일을 사용할 수 없는 경우도 있는데, 
         * 이 경우 기존 데이터에 대한 복사본을 유지하고 예외를 유발할 가능성이 있는 작업을 온전히 완료한 후 값을 교환하는 방법을 사용하면 됩니다.
         * 1. 방어적인 프로그램을 위해 수정할 데이터에 대한 복사본을 마련합니다.
         * 2. 복사해둔 데이터를 수정합니다. 수정 과정에서 예외가 발생할 수 있습니다.
         * 3. 수정된 복사본과 원본 데이터를 교환합니다. 이 교환 작업은 예외를 일으켜선 안됩니다. 
         */ 

        public class Widget
        {
            public List<int> Data;

            public List<int> UnreliableOperation()
            {
                //여기서 예외를 던질 수 있는 작업을 수행한다고 가정합시다.
                return Enumerable.Range(10, 20).ToList();
            }

            /// <summary>
            /// 아래 코드는 copy and swap 방식의 일종으로
            /// 임시 데이터 객체를 만들어 필요한 작업을 수행하고, 예외 없이 성공적으로 동작을 마치면 원본 데이터와 교체합니다.
            /// 
            /// 아래 코드는 제대로 동작하지 않습니다. ICollection 데이터는 참조형식이고, 아래 코드는 데이터의 레퍼런스만 교체합니다.
            /// 만약 외부에서 Data 레퍼런스를 사용하고 있다면 해당 부분까지 레퍼런스가 변경되는 것은 아닙니다.
            /// </summary>
            public void UpdateData()
            {
                var temp = UnreliableOperation();

                Data = temp;
            }
        }

        /// <summary>
        /// Evelop - Letter 봉투 편지 패턴을 활용해 안전하게 동작을 수행하도록 고쳐봅시다.
        /// </summary>
        public class Envelope : IList<int>
        {
            private List<int> m_Data = new List<int>();

            /// <summary>
            /// SafeUpdate를 통해 안전하게 값을 변경합니다.
            /// </summary>
            public void SafeUpdate(IEnumerable<int> sourceList)
            {
                List<int> updates = new List<int>(sourceList.ToList());
                m_Data = updates;
            }

            public int this[int index]
            {
                get => m_Data[index];
                set => m_Data[index] = value;
            }

            public int Count => m_Data.Count;
            public bool IsReadOnly => ((IList<int>)m_Data).IsReadOnly;
            public void Add(int item) => m_Data.Add(item);
            public void Clear() => m_Data.Clear();
            public bool Contains(int item) => m_Data.Contains(item);
            public void CopyTo(int[] array, int arrayIndex) => m_Data.CopyTo(array, arrayIndex);
            public IEnumerator<int> GetEnumerator() => m_Data.GetEnumerator();
            public int IndexOf(int item) => m_Data.IndexOf(item);
            public void Insert(int index, int item) => m_Data.Insert(index, item);
            public bool Remove(int item) => m_Data.Remove(item);
            public void RemoveAt(int index) => m_Data.RemoveAt(index);
            IEnumerator IEnumerable.GetEnumerator() => m_Data.GetEnumerator();
        }

        public class SafeWidget
        {
            private Envelope data;
            public IList<int> MyCollection => data;

            public List<int> UnreliableOperation()
            {
                //여기서 예외를 던질 수 있는 작업을 수행한다고 가정합시다.
                return Enumerable.Range(10, 20).ToList();
            }

            public void UpdateData()
            {
                data.SafeUpdate(UnreliableOperation());
            }
        }

        /* 일부 루틴이나 메서드에서는 가장 엄격한 보증 방식인 '예외 없음' 이 적용되어야 합니다.
         * 
         * dispose/ finalizer 는 예외 없음을 보장해야 합니다.
         * 이런 메서드가 예외를 일으키면 자원이 제대로 정리되지 않은 상태로 프로그램이 종료되게 됩니다.
         * 
         * 예외 필터의 when 절 내에서도 절대 예외가 발생하면 안 됩니다.
         * 이 경우에는 기존 예외가 사라지고 새로운 예외가 생성됩니다.
         * 
         * 델리게이트 대상이 되는 메서드 안에서도 예외 없음이 보장되어야 합니다.
         * 멀티캐스트 델리게이트의 경우 대상이 되는 메서드 중 하나가 예외를 일으키면 다른 대상 메서드가 호출되지 않는 문제가 있습니다.
         */
    }
}