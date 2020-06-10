using System;

//nameof() 연산자를 적극 활용하라

namespace EffectiveCSharp
{
    public class ECSharp06
    {
        private Action<object, PropertyChangedEventArgs> PropertyChanged;
        public class PropertyChangedEventArgs
        {
            public PropertyChangedEventArgs(string val) { }
        }

        private string m_Value;
        public string Name  //nameof 사용예시
        {
            get
            {
                return m_Value;
            }
            set
            {
                if (value != m_Value)
                {
                    m_Value = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Name)));
                    //Name 프로퍼티의 이름을 전달
                }
            }
        }
    }
}