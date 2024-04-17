using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//값 타입은 변경 불가능한 것이 낫다
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 멀티 스레드 환경에서 불변 타입은 스레드 안전성을 가지는 것이 큰 장점입니다.
    /// 
    /// Immutable 관련 타입을 활용합시다.
    /// </summary>
    public static class MECSharp03
    {
        public class Phone
        {
            public int Value = 0;
        }

        //아래의 PhonesList는 내부 멤버 변수가 readonly 이지만 배열의 원소를 변경하는 것이 가능합니다. 
        public struct PhoneList
        {
            private readonly Phone[] m_Phones;
            public IEnumerable<Phone> Phones => m_Phones; 

            public PhoneList(Phone[] ph)
            {
                m_Phones = ph;
            }
        }

        private static void Case0()
        {
            Phone[] phones = new Phone[10];
            for(int i = 0; i < 10; i++)
            {
                phones[i] = new Phone();
            }
            PhoneList plist = new PhoneList(phones);

            //수정 가능. 외부 참조를 통해 phones 내부 객체의 값 변경
            phones[5] = new Phone();
        }

        public struct PhoneList_Immutable
        {
            private readonly ImmutableList<Phone> m_Phones;
            public IEnumerable<Phone> Phones => m_Phones;

            public PhoneList_Immutable(IEnumerable<Phone> ph)
            {
                m_Phones = ph.ToImmutableList();
            }
        }

        private static void Case1()
        {
            Phone[] phones = new Phone[10];
            for (int i = 0; i < 10; i++)
            {
                phones[i] = new Phone();
            }
            PhoneList_Immutable plist = new PhoneList_Immutable(phones);


            //phones의 원소를 바꿔도 plist의 내부 객체는 바뀌지 않습니다.
            phones[5] = new Phone();
        }

        public static void RunSample()
        {
            Case0();
            Case1();
        }
    }
}
