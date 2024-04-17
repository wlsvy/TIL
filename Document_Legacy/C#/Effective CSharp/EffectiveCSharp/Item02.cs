using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EffectiveCSharp;

//const 보다는 readonly 가 좋다.

namespace EffectiveCSharp
{
    public static class ECSharp02
    {
        public class Widget
        {
            Widget() { }
            Widget(int a) { }
        }

        public const int Millennium = 2000;         //컴파일 타임 상수
        public static readonly int ThisYear = 2004; //런타임 상수

        //private const DateTime classCreation = new Widget();    //컴파일 오류, 내장 자료형이 아니면 컴파일 타임에 상수로 바꿀 수 없다.

        /// <summary>
        /// const : 컴파일 상수, readonly : 런타임 상수
        /// readonly 로 선언된 값에는 객체의 생성자가 호출되는 시기에 값이 결정될 수 있어서 훨씬 유연하다.
        /// 
        /// 프로젝트 내에서 특정 어셈블리만 수정했을 경우, 일부 파일만 리빌드했을 때, const의 값이 바뀌지 않는 경우가 있다. 
        /// 컴파일을 하는 시간에 IL 코드에서 값이 고정되어 버리기 때문. -> 값이 변경되지 않아 원하지 않는 동작을 할 가능성이 있다.
        /// 
        /// readonly 보다 const가 빠르다는 것은 분명하나 readonly 가 가지는 유연성을 생각하면 충분히 readonly를 고려하는 것이 좋다.
        /// 
        /// 컴파일할 때 사용되는 상숫값을 정의할 때에는 반드시 const를 사용해야 한다. 
        /// 특성attribute 의 매개변수, switch/case 문의 레이블, enum의 정의 시 
        /// 사용하는 상수 등은 컴파일 시에 사용돼야 하므로 반드시 const를 통해서 초기화되어야 한다.
        /// 
        /// 몇가지 예외사항을 제외하면, const 보다는 readonly를 사용하는 것이 좋다.
        /// </summary>
        public static void RunSample()
        {
            int myTimeYear = Millennium; //IL 코드에서 Millennium은 2000 으로 대체된다.
            if(myTimeYear == 2020)
            {

            }
            /*
             * 컴파일타임 상수는 내장된 숫자형, enum, 문자열, null에 대해서만 사용될 수 있다.
             * 내장 자료형이어야만 컴파일타임에 상수를 리터럴로 대체할 수 있기 때문이다.
             */
        }
    }
}