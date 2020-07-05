# Value Category In C++

-  C++11이 나오기 전, C와 C++의 value category는 lvalue와 rvalue만으로 이루어진 단순한 분류체계를 가지고 있었습니다. 하지만 C++11에 move semantic이 소개된 뒤로 좀더 복잡한 분류체계를 가지게 됩니다.

- has identity: it's possible to determine whether the expression refers to the same entity as another expression, such as by comparing addresses of the objects or the functions they identify (obtained directly or indirectly);
  - 표현식(expression) entity가 다른 표현식의 entity와 같은 것인지 확인할 수 있다면 해당 표현식은 identity를 가진다라고 말할 수 있습니다.
      - 예를 들어 객체나 함수의 주소값은 비교할 수 있으므로 그들은 identity를 가집니다.
      - [entity](https://en.cppreference.com/w/cpp/language/basic_concepts)란 c++ 내 다양한 것을 지칭합니다.(함수, 객체, 참조값, 템플릿, 타입, 열거형.... 등등)
- can be moved from: move constructor, move assignment operator, or another function overload that implements move semantics can bind to the expression.
  - 이동 생성자/이동 할당 연산자, 혹은 무브 시맨틱을 구현한 함수에 대해 적용될 수 있는 표현식이라면 '이동 가능하다' 라고 표현합니다. 


![](https://miro.medium.com/max/1400/1*G9HLBwBJFho9TNzE0J9__w.png)


- a glvalue (“generalized” lvalue) is an expression whose evaluation determines the identity of an object, bit-field, or function;
- a prvalue (“pure” rvalue) is an expression whose evaluation either 
  - c++ 17 이전
  - computes a value that is not associated with an object
  - creates a temporary object and denotes it
  - c++ 17 이후
  - computes the value of the operand of an operator or is a void expression (such prvalue has no result object), or
  - initializes an object or a bit-field (such prvalue is said to have a result object). With the exception of decltype, all class and array prvalues have a result object even if it is discarded. The result object may be a variable, an object created by new-expression, a temporary created by temporary materialization, or a member thereof;
- an xvalue (an “eXpiring” value) is a glvalue that denotes an object or bit-field whose resources can be reused;

- an lvalue (so-called, historically, because lvalues could appear on the left-hand side of an assignment expression) is a glvalue that is not an xvalue;
- an rvalue (so-called, historically, because rvalues could appear on the right-hand side of an assignment expression) is a prvalue or an xvalue.



![](https://miro.medium.com/max/1400/1*j-uvWhoJEfAoCwkWoUErRQ.png)

단순히 C++ 11 에서는 value category를 아래처럼 표현할 수 있습니다.
- have identity and cannot be moved from are called lvalue expressions; 
  - lvalue : identity를 가지며 이동 불가능
- have identity and can be moved from are called xvalue expressions;
  - xvalue : identity를 가지며 이동 가능
- do not have identity and can be moved from are called prvalue ("pure rvalue") expressions;
  - prvalue : identity를 가지지 않으며 이동 가능
- do not have identity and cannot be moved from are not used[6].
  - identity를 가지지 않으며 이동 가능하지 않은 값은 사용되지 않음
  
- The expressions that have identity are called "glvalue expressions" (glvalue stands for "generalized lvalue"). Both lvalues and xvalues are glvalue expressions.
  - identity를 가진다면 glvalue 표현식이라 할 수 있습니다. xvalue와 lvalue를 포함합니다.
- The expressions that can be moved from are called "rvalue expressions". Both prvalues and xvalues are rvalue expressions.
  - 이동이 가능하면 rvalue 표현식이라 할 수 있습니다. xvalue와 ravlue를 포함합니다.
  
## C++ 17 이후
- copy elision 이 일부 조건에서 필수적인 기능으로 자리잡게 되면서, prvalue 표현식과 그 표현식으로 부터 생성된 임시 객체를 분리해야 했습니다. 결과적으로 prvalue 표현식은 더 이상 이동되지 않게 됩니다. 

##### Reference
- [cpp Reference](https://en.cppreference.com/w/cpp/language/value_category)
- [medium.com](https://medium.com/@barryrevzin/value-categories-in-c-17-f56ae54bccbe)
- [blog.seulgi.kim](https://blog.seulgi.kim/2017/06/cpp11-value-category.html)
- [c++ draft](http://eel.is/c++draft/basic.lval#1.4)
