## 나올만한 것
* Up castinf, Down casting
* 상속받은 코드에서 에러 발생 위치 파악 및 이유 

## 8장
* inhertance : 기본 클래스 (부모 클래스)의 속성, 기능을 파생 클래스(자식 클래스)에게 물려주는 것.
  + 상속받은 파생 클래스 객체의 멤버 중, 재정의한 멤버가 아닌 상속받은 기존의 멤버는 "기본 클래스 멤버"라고 칭한다.
  + 그에 비해 새로 생긴 멤버는 "파생 클래스 멤버"라고 칭한다.

* Up Casting : 파생클래스의 포인터가 기본 클래스 포인터에 치환되는것. 
  + 포인터에 대한 포인터라고 할 수 있다.
  + 부모 클래스의 포인터로 자식 클래스 중 기본 클래스 멤버만 접근하는 경우
  + 즉, 기본 클래스 멤버만 가능하다.
  + ex) 생물(부모)을 가리키는 손가락으로 포유류, 어류, 사람 등 생물을 상속받은 객체(자녀)를 가리키는 것 = Up Casting
  
<code>
    
    // ColorPoint는 Point의 파생 클래스
    ColorPoint cp; 
    ColorPoint *pDer = &cp; // pDer 포인터로 객체 cp의 모든 public 멤버 접근 가능
    Point* pBase = pDer; // 업캐스팅. pBase로는 cp의 기본 클래스의 public 멤버만 접근할 수 있다.
  
</code>
  
* Down Casting : 기본 클래스의 포인터가 파생 클래스의 포인터에 치환되는 것.
  + 강제 타입 변환이 필요하다.

<code>

    ColorPoint cp;
    ColorPoint *pDer;
    Point* pBase = &cp; // 업캐스팅
    pDer = (ColorPoint *)pBase; // 다운캐스팅, 강제 형변환 필요

</code>

* ★ 상속관계에 있는 생성자 호출 관계
  + 기본 클래스의 생성자가 먼저 실행된 후 파생 클래스의 생성자가 실행된다.
  + ex) C가 B를 상속받고, B가 A를 상속받는 경우 A, B, C 순서로 생성자가 호출된다.
  + 소멸자는 반대의 순서로 호출된다.
  + 컴파일러는 묵시적으로 기본 클래스의 기본 생성자를 호출하도록 한다.
  + 생성자가 명시적으로 기본 클래스의 생성자를 선택호출 할 수 있다.
  
<code>
  
    // P27
    class B : public A{
    public:
      B(){ cout<<"B"<<endl; }
      B(int x): A(x+3) { cout<<"B"<<endl; } // A(int x) 생성자를 명시적으로 호출하게 된다.
      // 즉, 명시적으로 부모클래스 중 생성하고 싶은 생성자가 기본 생성자 말고 따로 있는 경우, 위처럼 명시해줘야된다.

</code>

* 상속 지정
  + public : 기본 클래스의 접근제한자 속성을 그대로 계승
  + private : 기본 클래스의 접근제한자 속성을 private로 계승
  + protected : 기본 클래스의 접근제한자 속성을 protected로 계승

* P30 예제 8-4
  + 1번 : Base의 private이므로
  + 2번 : Base를 상속하면서 private로 모든 접근제한자를 바꾸었기 때문
  + 3번 : Base를 상속하면서 private로 모든 접근제한자를 바꾸었기 때문
  + 4번 : Derived의 Private이므로
  + 5번 : Derived의 protected이므로

* 다중 상속은 참고로만 알고 있기
  + 상속받는 Basic class가 여러 개 있는 경우
  + 중복 상속의 문제가 발생할 수 있다. 즉, 아래의 경우 MP3, MobilePhone class가 Machine라는 class를 상속받는 경우 Machine를 2번 상속된다
  + 가상 상속으로 해결할 수 있다.
  + 자바에서는 이를 아예 허용하지 않는다.
  
<code>

    class MusicPhone : public MP3, public MobilePhone {
      public:
        void dial();
    };

</code>
