## 시험에 나올만한 것
* 파생클래스에서 함수 재정의 한 뒤 업캐스팅하여 어떤 함수가 호출되는지 고르기
* 함수 재정의와 오버라이딩, 오버로딩 용어 구분 (P18)
* 동적 바인딩 구현, 가상 소멸자
* 추상 클래스 & 순수 

## 9장
* 범위지정 연산자 (:)
  + 범위 지정 연산자는 원래 정적 바인딩을 지시한다. 
  
* 파생클래스에서 함수 재정의
  + Upcasting 활용
  + ★ 코드 암기 필요, 중요! - 업캐스팅에 대한 이해 반영
  + 함수 재정의와 오버라이딩 용어 정리

<code>

    class Base{ public: void f(){..}};
    class Derived:public Base{ public: void f(){..}};
    
    void main(){
      Derived d, *pDer;
      pDer = &d;
      pDer->f(); // Derived:f()호출
      
      Base* pBase;
      pBase = pDer; // Up casting
      pBase->f(); // Base:f() 호출

</code>

* Virtual Function : 동적 바인딩 지시어. 
  + 컴파일러에게 함수에 대한 호출 바인딩을 실행 시간까지 미루도록 지시
  + 오버라이딩하면 업캐스팅해줘도 자녀 함수만 호출할 수 있다.
  
* ★ 함수 재정의와 오버라이딩 용어 정리
  + virtual(동적 바인딩) 사용하는 경우 : 오버라이딩
  + 정적 바인딩의 경우 : 함수 재정의
  + 자바는 무조건 동적 바인딩이 일어난다.
  + 오버라이딩 : Virtual을 사용. 동적 바인딩

* 즉, 동적 바인딩이란 : 
  + 부모 클래스에 대한 포인터로 가상함수를 호출하는 경우, 
  + 객체 내에 오버라이딩한 자녀 클래스의 함수를 찾아서 자녀 클래스의 함수를 실행한다.

<code>

    class Base{public: virtual void f(){...}}; // 가상함수 선언
    class Derived:public Base{public: virtual void f(){...}}; // 가상함수 구현
    // 오버라이딩한 Derived의 f()에서는 virtual 생략 가능
    
    int main(){
      Derived d, *pDer;
      pDer = &d;
      pDer->f(); // Derived::f() 호출
      
      Base* pBase;
      pBase = pDer; // 업캐스팅
      pBase->f(); // 동적바인딩 발생, Derived::f()호출

</code>

* 가상 소멸자

<code>

    class Base{public: virtual ~Base();};
    class Derived:public Base{public: virtual ~Derived();};
    // 동작 순서 : ~Base() 소멸자 호출, ~Derived() 실행, ~Base() 실행

</code>

* 순수 가상 함수 : 함수의 코드가 없고, 선언만 있는 가상 멤버 함수
  + P29 Shape.h의 draw()가 순수 가상 함수이므로 Shape.cpp의 Shape.draw() 구현부는 존재하면 안된다.
  + 추상 클래스 : 최소 하나의 순수 가상 함수를 가진 클래스
  + 추상 클래스 특징 : 객체 생성 불가능, 포인터 선언은 가능
  + 추상 클래스의 목적 : 상속에서 기본 클래스 역할 수행. 인스턴스 생성 목적은 아님
  + 추상 클래스를 상속 받았을 때, 순수 가상 함수를 오버라이딩 하지 않으면 파생 클래스도 추상 클래스가 된다.
  
<code>

    class Shape{
    public:
      virtual void draw()=0; // 순수 가상 함수 선언
    };

</code>
