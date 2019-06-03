## 시험 나올만한 것
* 템플릿 문법 (선언, 구현, 호출 등 모두!)
* vector 클래스의 주요 멤버 사용 방법 (P27, 28, 31, 36)
* map 클래스의 주요 멤버 사용 방법 (P34)
* #include<algorithm>해서 sort() 사용하는 문법
* 
* 람다 문법

## 10장
* 템플릿 : 함수나 클래스를 일반화시켜 매개 변수 타입을 지정하여 틀에서 찍어내듯이 클래스 코드를 생산하는 기법
  + 아래와 같이template 함수 myswap이 있을 때, 
  + 매개변수로 int, double, char 또는 그 외 무엇을 넣는지에 따라 T가 그것에 매칭되서 함수를 구체화하고 호출한다.
  + 물론 매개변수 a, b에 다른 타입의 변수를 넣으면 에러가 발생한다!
  + 이 때 매개 변수 타입은 배열도 가능!

<code>

    template <class T>
    void myswap(T & a, T & b){
      T tmp;
      tmp = a;
      a = b;
      b = tmp;
    }
    
    int main(){
      int a = 4, b = 5;
      myswap(a b); // T를 int로 설정
      
</code>

* 템플릿 장단점
  + 장점 : 재사용 가능
  + 단점 : 포팅에 취약. 디버깅이 어려움
  + 제네릭 프로그래밍 : 일반화 프로그래밍. 템플릿, 제네릭 클래스, STL을 활용한 프로그래밍
  
* 제네릭 클래스 만들기. 제네릭 클래스 선언, 구현, 호출

<code>

    // 선언
    template <class T>
    class MyStack{ // 제네릭 클래스로 만든 가짜 스택
      ...
      void push(T element);
      ...
    };
    
    // 구현
    template <class T>
    void MyStack<T>::push(T element){
      ...
    }
    
    // 호출
    int main(){
      ...
      MyStack<int> iStack;
      MyStack<double> dStack;
      iStack.push(3);
      dStack.push(3.5);
    }

</code>

* STL : 표준 템플릿 라이브러리. 많은 제네릭 클래스와 제네릭 함수 포함한다.
  + STL 구성
    - 컨테이너 : 템플릿 클래스
    - iterator : 반복자, 컨테이너 원소에 대한 포인터
    - 알고리즘 : 템플릿 함수

* STL 컨테이너 종류 : vector, deque, list, set, map, stack, queue
  + map, vector의 주요 멤버와 연산자 사용방법 정도는 예제 정도만큼만 알아두기

* vector : 가변길이 배열을 구현한 제네릭 클래스.
  + vector 함수 : P25
  
* map : 키 값 쌍을 원소로 저장하는 컨테이너
  + 키로 값을 검색 가능
  + map 함수 : (P33)
  
* STL 알고리즘
  + sort(소팅 시작한 원소의 주소, 소팅 범위의 마지막 원소 다음 주소) 함수
  
* 람다
  + [캡쳐 리스트](매개변수 리스트)->리턴타입{함수바디};
  ex)
  
<code>

    [](int x, int y)->int{return x+y;}(2, 3);

</code>
