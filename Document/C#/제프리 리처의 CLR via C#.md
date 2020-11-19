# 제프리 리처의 CLR via C# 4판

## 1장. CLR의 실행 모델

<details>
  <summary>fold/unfold</summary>

### 공용 언어 런타임(CLR, Common Language Runtime)
- 서로 다른 프로그래밍 언어들 사이에서 공동으로 사용할 수 있는 실행환경(Runtime)을 말합니다.
- CLR을 지원하는 언어라면 CLR의 기능(메모리 관리, 어셈블리 로딩, 스레드 동기화 등)을 자유롭게 사용할 수 있습니다.

<img src="https://1.bp.blogspot.com/-g9AYNMBpG1s/U7Qii8mJm_I/AAAAAAAAAqg/bTFteXucTQA/s1600/2014-07-02_111719.png" width="40%" height="40%">

- CLR은 관리모듈을 실행시킵니다. 관리 모듈(managed module)이란 CLR을 지원하는 프로그래밍 언어를 컴파일한 결과물로 크게 IL과 메타데이터로 이루어집니다.

### 메타데이터(metadata)
- 메타데이터는 모듈 내의 타입과 그들의 구성 멤버 등의 대한 데이터 테이블입니다.
  - 테이블은 크게 두 종류로 나누어집니다. 하나는 소스 코드에 포함된 타입들과 그 멤버들의 정보, 다른 하나는 소스 코드가 참조하는 타입들과 멤버들에 대한 정보입니다.
- 프로그램 실행 파일이 생성될 시 메타데이터는 해당 파일 안에 포함됩니다.
- visual studio의 인텔리센스는 메타데이터를 활용합니다.
- 메타데이터는 각각의 객체(object)들이 메모리 블록 안에 serialization 할 수 있도록 합니다. 이후 deserialization을 거쳐서 객체가 원래 상태로 복원될 수 있습니다.
- 가비지 컬렉터(garbage collector)가 객체의 생명주기를 추적할 때 메타데이터를 활용합니다.

### 어셈블리(assembly)
CLR은 실제로 모듈들을 다루지는 않으며, 어셈블리를 다루게 됩니다. 어셈블리는 명확하게 정의하기엔 추상적인 개념이며 아래와 같습니다.

- 하나의 어셈블리는 하나 이상의 모듈이나 리소스 파일들에 대한 논리적 그룹입니다.
- 하나의 어셈블리는 재사용, 보안, 버전 관리의 가장 작은 단위입니다.

<img src="https://i.stack.imgur.com/s6gSO.png" width="60%" height="60%">

위의 그림에서 다수의 모듈과 리소스 파일이 결합되어 하나의 어셈블리로 만들어집니다.
- 매니페스트 : 어셈블리 안의 모듈 및 리소스 파일들의 집합을 설명합니다.

### 어셈블리 실행

<img src="https://i.stack.imgur.com/LXVmH.png" width="60%" height="60%">

위의 그림에서 JIT(just in time) 컴파일러가 IL 명령어를 실행하는 과정은 대략 아래와 같습니다.

1. Main 메서드가 실행되기 바로 직전에, CLR은 main 메서드 안에서 참조된 모든 타입들을 파악합니다. 이때 CLR은 내부적으로 자료구조를 생성해 참조된 타입을 관리하는 용도로 사용합니다.
2. Main 메서드가 WriteLine 메서드를 호출할 때 JIT 컴파일러가 호출됩니다. 컴파일러는 메서드의 IL 코드를 네이티브 CPU 명령어로 컴파일합니다. 
3. CLR은 메모리를 동적할당한 뒤 해당 공간에 네이티브 cpu 명령어를 저장합니다.
4. CLR은 새로 생성된 네이티브 cpu 명령어의 메모리 주소를 저장합니다.
5. 실제 코드를 실행합니다.
6. 두번째로 WriteLine 메서드를 호출할 때 CLR은 이미 WriteLine 메서드에 대한 코드를 이미 검사하였고 컴파일이 완료했다는 사실을 확인합니다. 곧바로 네이티브 cpu 명령어가 저장된 메모리로 이동해 코드를 실행합니다. 추가적인 jit 컴파일러 호출은 없습니다.


- 성능 저하는 메서드가 최초로 호출될 때에만 발생합니다.
- JIT 컴파일러는 생성한 네이티브 cpu 명령어를 동적 메모리상에 저장하며 응용프로그램이 종료될 때 자동으로 반환합니다.

### IL과 검증, 안전하지 않은 코드
- IL은 스택 기반의 언어로 모든 IL 명령어들과 연산자가 실행 스택 위에 쌓이고 꺼내어가는 방식으로 실행됩니다.
- IL의 가장 큰 장점은 cpu 내부로부터 추상화된 동작들에 대한 것이 아닙니다. 응용프로그램의 견고함과 보안을 책임진다는 것에 더 의의가 있습니다.
  - IL을 네이티브 CPU 명령어로 컴파일하는 동안, CLR은 확인(verification) 과정을 통해 코드를 검사하고 안전성을 점검합니다.
  - 확인 과정을 통하여 메모리를 잘못된 방향으로 접근하거나 사용하지 않으며, 다른 응용프로그램 코드에 역으로 영향을 주는 일이 없게 합니다. 대표적인 예로 응용프로그램의 물리 메모리와 가상 메모리 주소가 달라 잘못 접근하는 경우를 방지하는 경우가 있습니다.
- C# 컴파일러는 기본적으로 안전한 코드를 만듭니다. 안전한 코드는 확인 과정을 안전하게 통과할 수 있습니다. 반면에 안전하지 않은 코드를 사용하는 경우도 있는데 unsafe 키워드를 추가해서 작성할 수 있습니다. 직접 메모리에 접근하거나 비관리 코드와의 상호운용을 할때 유용합니다.

### 공용 언어 사양
- 공용 타입 시스템(CTS, Common Type System) : 마이크로소프트는 공용 타입 시스템(CTS) 표준을 정의하여 CLR 에서 타입이 어떻게 정의되어야 하고 동작되어야 하는지 명시하고 있습니다.
  - 모든 타입은 미리 정의된 타입인 System.Object 를 상속받습니다.

- CLR은 서로 다른 언어 사이에서 통신할 수 있게 해주는 것 이상으로 모든 언어들을 연계하고 어떤 언어로 쓰인 객체가 다른 언어에서도 완전히 동일한 의미와 사용법을 가지는 동등한 객체로 인지할 수 있게 해줍니다.
  - 이러한 통합이 가능한 이유는 CLR의 표준 타입 집합들과 메타데이터 그리고 공용 실행 환경(Common Execution Environment) 덕분입니다.
- 공용 언어 사양(CLS, Common Language Specification) : 마이크로소프트는 공용 언어사양을 정의하여 컴파일러를 제조할 때 준수해야 할 최소한의 사항들을 정의합니다. 여기에는 다른 CLR 위에서 동작하는 언어들 사이에서 반드시 지원해야할 내용들을 포함합니다.
  - 공용 언어 사양을 통해 언어 사이의 공통적인 규칙이 필수적으로 포함될 수 있게 되었으며 CLR은 이를 통해서 다양한 언어간의 상호 연계를 가능하게 합니다.

<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcRLR0g7k3JcNHoagiCnQjDYZEEjiDnLTYpKkQ&usqp=CAU" width="40%" height="40%">

</details>

## 4장. 타입의 기초

<details>
<summary>fold/unfold</summary>

### 모든 타입은 System.Object를 상속한다.

#### Reference
- [Microsoft : Object Class](https://docs.microsoft.com/en-us/dotnet/api/system.object?view=net-5.0)
---

- 모든 타입들은 궁극적으로 System.Object 타입으로부터 파생됩니다.
- 따라서 C#의 모든 객체는 System.Object의 public/protected 메서드(GetHashCode, ToString 등)를 사용할 수 있습니다.

```cs
//아래 두 클래스 선언은 동일합니다.

class Widget 
{

}

class Widget : System.Object
{

}


```

- CLR은 모든 객체들을 반드시 new 연산자에 의하여 만들어지도록 하고 있습니다. 
```cs
Widget widget = new Widget("Construct Param");
```

- new 연산자는 아래의 일을 합니다.
  - 할당하려는 타입과 System.Object 타입, 그리고 System.Object를 상속받은 모든 기본 타입들에서 정의된 모든 인스턴스 필드들을 메모리에 할당하기 위한 바이트 수를 계산합니다.
     - 힙상의 모든 객체에는 타입 객체 포인터(Type Object Pointer)와 동기화 블록 인덱스(Sync Block Index)가 추가됩니다. CLR은 두 멤버를 통해 객체를 관리합니다.
     - 추가 멤버들을 위한 바이트는 객체의 실제 크기에 포함됩니다.
  - 필요한 만큼 메모리를 할당합니다. 처음 할당할 때 모든 바이트를 0으로 초기화합니다.
  - 객체의 타입 객체 포인터와 동기화 블록 인덱스 멤버를 초기화합니다.
  - 생성자를 호출하고 new 연산자에 서술된 매개변수가 전달됩니다. 파생클래스의 생성자 부터 호출되며 System.Object의 생성자가 가장 마지막에 호출됩니다.


### 타입 간 캐스팅하기

- CLR의 중요한 기능들 중 하나는 타입 안전성입니다. 실행 시점에서 CLR은 객체의 정확한 타입이 무엇인지 항상 파악하고 있습니다.

```cs

    //암시적으로 System.Object를 상속합니다.
    internal class Widget { }
    
    public sealed class Program
    {
        public static void Main()
        {
            Object o = new Widget(); //암시적 변환이며, 안전합니다.

            //Object 타입으로부터 Widget 클래스를 타입이 파생되었기 때문에 명시적 형 변환 연산자가 필요합니다.
            //경우에 따라 런타임 오류가 발생할 수 있습니다.
            Widget w = (Widget)o;
        }
    }

```
### C#의 is와 as 연산자로 캐스팅하기
- C#에서 캐스팅 연산을 다룰 때 is/as 를 활용할 수 있습니다.

```cs
    Object o = new Object();
    Boolean result1 = o is Object;  //true
    Boolean result2 = o is Widget;  //false
```
- 아래와 같이 활용할 수 있으나, 아래의 경우는 CLR 이 타입을 두 번 점검합니다.

```cs
    //if 문에서 한번 검사합니다.
    if(o is Widget)
    {
        //명시적 형변환을 수행하면서 또 한번 검사합니다.
        Widget w = (Widget)o;
    }
```

- 위와 같은 상황을 방지하기 위해 as 연산자를 사용할 수 있습니다.
```cs
    //여기서 한번 타입을 점검합니다.
    Widget w = o as Widget;
    if(w != null)
    {
        //여기서 w를 사용합니다.
    }
```

### 실행 시점과의 연관성

- 아래는 M1 메서드가 호출되기 직전의 스레드 스택의 상태입니다. 할당된 스레드에서 M1 메서드를 호출할 것입니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-2.jpg" width="40%" height="40%">

- 대게 메서드들은 프롤로그 코드(Prologue Code)를 포함하며 메서드 안의 코드가 동작하도록 초기화를 거치게 합니다.
- 여기에 대응되는 에필로그 코드(Epilogue Code)도 있어서 메서드 실행 후의 정리 작업을 수행하게 합니다. 그리고 원래 호출자에게 돌아갈 수 있게 준비합니다.


- 아래에서 프롤로그 코드는 스레드 스택에 지역변수를 위한 메모리 공간을 할당합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-3.jpg" width="40%" height="40%">

- 아래에서 M2 메서드를 호출합니다. 메서드로 넘길 매개변수와 호출이 끝나고 되돌아갈 위치를 나타내는 주소값이 스택에 올라갑니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-4.png" width="40%" height="40%">

- M2 메서드의 지역변수가 스택에 올라갑니다. M2 메서드가 종료되면 리턴 주소를 확인해 다시 M1 메서드를 수행하던 위치로 되돌아갈 것입니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-5.jpg" width="40%" height="40%">



- 이제 아래의 두 클래스가 정의되어 있다고 가정합시다.

```cs

    public internal class Employee
    {
        public Int32 GetYearsEmployed() { ... }
        public virtual string GetProgressReport() { ... }
        public static Employee Lookup(string name) { ... }
    }

    public internal class Manager : Employee
    {
        public override string GetProgressReport() { ... }
    }
```

- 처음에 Windows 프로세스가 실행되고, CLR이 로드되고, managed heap이 초기화되고, 스택공간과 스레드가 할당될 것입니다. 이 스레드는 초기 코드를 실행한 상태고 이제 M3 메서드를 호출하려고 합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-6.png" width="40%" height="40%">

- JIT 컴파일러가 M3 메서드의 IL 코드를 컴파일하면서 M3 메서드 안의 타입들과 변수 정보에 대해서 파악합니다.
  - 이 시점에서 CLR은 이러한 타입들을 포함하는 어셈블리들을 로드할 것이며, 어셈블리의 메타데이터를 통해 타입 정보를 추출하여 타입에 대한 정보를 서술하는 또다른 자료 구조를 생성합니다.
  - 아래 그림에서 Int32와 string 과 같은 기본적인 타입 정보는 이미 올라와 있다고 가정하며 나타내지 않습니다.

- 아래 그림처럼 힙 위에 만들어지는 모든 객체는 타입 객체 포인터와 동기화 블록 인덱스 멤버를 추가적으로 가집니다.
- 타입을 선언할 때 정의된 정적 데이터는 타입 객체 안에 포함됩니다. 그리고 타입 객체가 생성되는 시점에 초기화됩니다.
- 마지막으로 타입 내의 메서드 하나당 한 개의 항목이 포함된 메서드 테이블도 만들어지게 됩니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-7.png" width="40%" height="40%">

- 스레드의 스택상에 지역 변수를 위한 메모리를 할당합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-8.png" width="40%" height="40%">

- 매니저 객체가 생성됩니다. 역시 타입객체 포인터와 동기화 블록 인덱스를 가지며, 타입 객체 포인터는 Manager의 정확한 타입 객체를 가리키도록 초기화됩니다.
- CLR은 객체를 생성하면서 객체의 모든 인스턴스 필드를 0 또는 NULL 값으로 초기화합니다.
- 그 다음 객체의 생성자를 호출하면서 인스턴스의 데이터를 수정합니다.
- 이후 new 연산자는 만들어진 Manager 객체의 메모리 주소를 반환하여 스레드 스택상에 할당된 변수 e에 저장합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-9.png" width="40%" height="40%">

- Lookup 메서드를 호출할 때 JIT 컴파일러는 IL 코드를 컴파일하고 컴파일된 코드를 동적할당된 메모리에 저장합니다.
- joe가 관리직에 해당한다면 새로운 Mananger 객체가 생성되고 지역변수 e에 저장합니다. 
- 이때 처음 만들어진 Manager 객체는 아무도 참조하지 않으므로 가비지 수거 대상이 됩니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-10.png" width="40%" height="40%">

- GetYearsEmployed 메서드를 호출합니다. 마찬가지로 JIT 컴파일을 거친 뒤 코드를 수행합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-11.png" width="40%" height="40%">

- 가상 메서드 GetProgressReport를 호출합니다.
  - 가상 메서드를 호출할 때에는 JIT 컴파일러가 호출에 앞서 추가적인 코드를 메서드를 호출할 때마다 그 안에 추가하게 됩니다.
  - e의 타입은 Employee 이지만 실제 가리키는 객체는 Manager 타입입니다. 코드를 수행할 때 객체 타입 포인터 멤버가 가리키고 있는 타입 객체 정보를 확인하여 실제 어떤 객체를 가리키고 있는지 파악합니다.
  - 이후 실제 객체 타입의 메서드 테이블에서 호출하려는 메서드를 찾아냅니다. 역시 필요하면 JIT 컴파일을 수행합니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-12.png" width="40%" height="40%">

- 아래 그림에서 타입 객체 역시 객체에 해당하므로, 타입 객체 포인터를 멤버를 가진다는 것을 확인할 수 있습니다.
  - 해당 타입 객체 포인터의 경우 System.Type 이라는 MSCORLIB.DLL 안의 선언되어 있는 타입 객체를 가리키게 됩니다.
  - System.Type 타입 객체의 경우 타입 객체 포인터 멤버가 자기 자신을 가리킵니다. System.Type 타입 자체가 그 자체로 객체의 타입 객체이기 때문입니다.

<img src="https://github.com/wlsvy/TIL/blob/master/Document/C%23/CLRviaC%23_Image/4-13.png" width="40%" height="40%">

</details>

## 5장. 기본, 참조, 값 타입

<details>
<summary>fold/unfold</summary>

### 프로그래밍 언어 기본 타입

#### Reference
- [Microsoft : c# 내장 타입](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/builtin-types/built-in-types)

- 컴파일러가 직접 지원하는 데이터 타입들을 기본 타입(Primitive Type)이라고 부릅니다.
  - 대표적인 예로 int 타입이 있으며 아래 코드 4줄은 전부 같은 IL코드를 생성합니다.

```cs
    int a = 0;
    System.Int32 a = 0;
    int a = new int();
    System.Int32 a = new System.Int32();
```

- C#의 기본 타입들은 조금 독특한 특징을 가지고 있습니다. 다른 프로그래밍 언어에서 int는 32비트 운영체제에서는 32비트 정수로 64비트 운영체제에서는 64비트 정수로 취급되는 경우가 있지만, C#에서 int는 System.Int32의 별칭이기 때문에 반드시 32비트 정수로 취급됩니다. 64비트 정수는 System.Int64의 별칭인 long을 사용해야 합니다.

- C# 컴파일러는 기본 타입들을 다루는 작업들에 대해서 몇 가지 기능을 제공해줍니다.

1. 컴파일러는 아래의 타입들에 대해서 암묵적/명시적 형 변환을 지원합니다.
  - 암묵적 변환에 경우 변환 과정에서 데이터 손실이 없는 '안전한' 경우에만 지원합니다.
```cs
Int32 i = 5;        //Int32 -> Int32
Int64 l = i;        //Int32 -> Int64
Single s = i;       //Int32 -> Single
Byte b = (Byte)i;   //Int32 -> Byte(명시적)
Int16 v = (Int16)s; //Single -> Int16(명시적)
```

- 특히 부동 소수점 데이터를 다룰 때 주의해야 하는데 값을 정수형으로 변환할 때 컴파일러에 따라 버림/반올림 연산 중 어떤 것을 적용할지는 컴파일러마다 다릅니다. C#의 경우는 버림 연산이 적용됩니다.

2. 기본 타입은 변수가 아닌 리터럴 상수로 기재할 수 있습니다.
```cs
Console.WriteLine($"{123.ToString()}, {456.ToString()}");
```

3. 리터럴 상수로 구성되는 표현식이 있다면, 컴파일러가 해당되는 표현식을 컴파일 타임에 평가하여 응용프로그램의 성능을 향상시키도록 할 수도 있습니다.
4. 컴파일러는 +, -, *, /, &, ^ 등의  연산자가 사용되었을 때, 자동으로 연산자 처리 우선순위를 결정합니다.

### 기본 타입 연산의 오버플로우 여부 검사
- 언어마다 오버플로우를 처리하는 방식이 다릅니다. 오버플로우를 허용하는 C/C++ 과 다르게 Visual Baisc .NET에서는 오버플로우를 명백한 오류로 취급하고 발견될 경우 이 사실을 알립니다.
  - C#은 오버플로우를 어떻게 처리할지 개발자가 선택할 수 있게 합니다. 컴파일러 옵션을 바꾸거나, checked/unchecked 키워드를 활용합니다.

```cs
UInt32 valid = unchecked((UInt32)(-1)); 

int i = -1;
UInt32 invalid = checked((UInt32)(i));  //overflow exception

//블록 지정도 가능
checked
{
    Byte b = 100;
    b = (Byte)(b + 200);    //overflow exception
}

checked
{
    DoSomething(100);   //오버플로우 검사가 이루어지지 않을 수도 있습니다.
}

```

- checked 블록 안에서 메서드를 호출한다고 가정했을 때, 메서드가 어떻게 컴파일 되는지에 따라 오버플로우 검사가 이루어질 수도, 이루어지지 않을 수도 있습니다. 
  - checked 코드 블록은 단순히 컴파일 시점에 IL 코드의 오버플로우 검사여부를 결정하는 것에 불과하기 때문입니다.
- checked/unchecked 연산자와 코드 블록, 그리고 컴파일러 스위치는 Decimal 타입에 대해서 검사를 지원하지 않습니다. Decimal 타입은 CLR이 다루지 않는 특수한 타입이며, c# 내부적으로 Decimal 에 대해서는 특별히 다르게 취급하기 때문입니다.(Decimal을 연산하기 위한 정적메서드와 연산자 오버로딩이 추가적으로 존재합니다.)
  - System.Numerics.BigInteger 타입도 마찬가지입니다.

### 참조 타입과 값 타입
</details>
