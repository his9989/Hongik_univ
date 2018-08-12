### $ cat makefile

<code>

    hw8a: hw8a.o
            g++ -o hw8a hw8a.o
    hw8a.o: maxheap.h
    hw8b: hw8b.o
            g++ -o hw8b hw8b.o
    hw8c: hw8c.o
            g++ -o hw8c hw8c.o

</code>

### $ cat hw8a.cpp

<code>

    #include"maxheap.h"

    int main(){
            MaxHeap<int> H; //여기서 HeapSize는 0으로 초기화됨
            H.Push(15);     //여기서 HeapSize는 1으로 초기화
            H.Push(14);     //여기서 HeapSize는 2으로 초기화
            H.Push(21);     //여기서 HeapSize는 3으로 초기화
            H.Push(2);      //여기서 HeapSize는 4로 초기화
            H.Push(10);     //여기서 HeapSize는 5로 초기화
            H.Push(20);     //여기서 HeapSize는 6으로 초기화

            cout<<H;

            while(!H.IsEmpty())
            {
                    cout<<H.Top()<<" ";     // 첫번째 노드 출력
                    H.Pop();                // 여기서 HeapSize는 하나씩 줄어든다
            }
            cout<<endl;
    }

</code>

### $ cat maxheap.h

<code>

    #include<iostream>
    using namespace std;

    template <class T>
    void ChangeSize1D(T* &a, const int oldSize, const int newSize);         //size 확장하는 함수

    template<class T>
    class MaxHeap {                                                         //MaxHeap라는 클래스 선언
            public:
                    MaxHeap(int);
                    void Push(const T& e);
                    void Pop();
                    bool IsEmpty()
                            {return heapSize==0;}
                    T Top()
                                    {return heap[1];}
            private:
                    int heapSize;
                    int capacity;
                    T *heap;
                    template <class T2>
                    friend ostream& operator<<(ostream&, MaxHeap<T2>&);
    };

    template <class T>
    void ChangeSize1D(T *&a, const int oldSize, const int newSize)          //heap의 oldSize를 newSize로 바꾸는 과정
    {
            T *temp = new T[newSize];                                       //새로운 heap인 temp를 선언한다. 크기는 newSize
            copy(a, a+oldSize, temp);                                       //배열 a부터 a+oldSize에 있는 값을 temp로 복사
            delete[] a;                                                     //a를 지워버리고
            a = temp;                                                       //a의 내용이 들어가고, 길이는 확장된 temp를 a로 다시 넣음.
    }

    template <class T>
    ostream& operator<<(ostream& os, MaxHeap<T>& H) {                       //변수로 heap이 들어온 경우 출력하는 연산자
            os<<"<Heap Contents> ";
            for(int i=1; i<H.heapSize+1; i++)                               //heap에 heapSize 길이 만큼 반복
                    os<<i<<":"<<H.heap[i]<<" ";                             //입력받은 heap H의 원소를 하나씩 출력
            os<<endl;
    }

    template <class T>
    MaxHeap<T>::MaxHeap (int theCapacity = 10): heapSize(0) {               //사용할 수 있는 노드에 대해 n번쨰 배열은 n+1번쨰 원소로 표현
            if(theCapacity<1)                                               //heapSize는 0으로 초기화
                    throw "Must be +ve";                                    //
            capacity = theCapacity;                                         //
            heap=new T[capacity+1];                                         //heap은 1부터 시작할 것,
    }

    template <class T>
    void MaxHeap<T>::Push(const T& e)
    {
            if(heapSize==capacity)          // heapSize가 capacity인 경우 확장
            {
                    ChangeSize1D(heap, capacity+1, 2*capacity+1);
                    capacity*=2;
            }
            int currentNode = ++heapSize;   // heapSize가 Push 명령어 하나 마다 하나씩 증가함. 생성자에 의해 heapSize 초기값은 0임
                                            // currentNode = ++heapSize에 의해 currentNode는 명령어 호출마다 루트부터 하나씩 내려간다
            while(currentNode!=1&&heap[currentNode/2]<e)    // 입력하고자 하는 값이 부모보다 큰 경우 맥스힙이므로 서로 바꿔
            {
                    heap[currentNode] = heap[currentNode/2];        //부모와 자식 자리 바꾸는 과정
                    currentNode/=2;
            }
            heap[currentNode]=e;            // currentNode 자리에 Push 변수 e 넣기
    }

    template <class T>
    void MaxHeap<T>::Pop()
    {
            if(IsEmpty())
                    throw "Heap is empty. Cannot delete.";
            heap[1].~T();                   //1번째 노드 즉, 루트 제거
            T lastE=heap[heapSize--];       //Push에 의해 max까지 올랐던 heapsize가 하나씩 줄어듬
            int currentNode = 1;            //루트 노드 자리를 currentNode로 명명
            int child =2;                   //루트 노드의 자식
            while (child <= heapSize)       //child를 끝까지 탐색
            {
                    if(child<heapSize&&heap[child]<heap[child+1])   //child가 끝은 아니고, child의 값이 child+1의 값보다 작은경우
                            child++;                                //다음 자식을 살펴보자
                    if(lastE>=heap[child])                          //child의 값보다 lastE가 크거나 같을때
                            break;                                  //야야 멈춰봐
                    heap[currentNode]=heap[child];                  //루트에다가 이거 넣자!
                    currentNode=child;                              //
                    child*=2;
            }
            heap[currentNode]=lastE;
    }

</code>

### $ cat hw8b.cpp

<code>

    #include<iostream>
    #include<queue>
    using namespace std;

    int main()
    {
            priority_queue<int> maxPQ;
            maxPQ.push(15);
            maxPQ.push(14);
            maxPQ.push(21);
            maxPQ.push(2);
            maxPQ.push(10);
            maxPQ.push(20);

            while(!maxPQ.empty())
            {
                    cout<<maxPQ.top()<<" ";
                    maxPQ.pop();
            }
            cout<<endl;
    }

</code>

### $ cat hw8c.cpp

<code>

    #include<iostream>
    #include<queue>
    #include<vector>
    using namespace std;

    struct Student
    {
            Student(string n, int m, int e)
                    : name(n), math(m), english(e) {}
            string name;
            int math, english;
    };

    struct cmp      // 새로운 정렬 기준
    {
            bool operator() (const Student s1, const Student s2)
            {
                    return s1.math + s1.english > s2.math + s2.english;
            }
    };

    int main()
    {
            priority_queue<Student, vector<Student>, cmp> minPQ;
                    //priority_queue<[데이터 타입, [컨테이너 타입], [정렬기준]> [변수 이름];
                    //[데이터 타입]: 실제로 정렬되는 내용물의 타입. 여기서는 Student 구조체 자체가 정렬됨
                    //[컨테이너 타입]: vector을 이용해서 정렬할 것임. 정렬 데이터는 Student 구조체임
                    //vector 내에서 정렬 기준은 cmp임
            minPQ.push(Student("Kim", 70, 85));
            minPQ.push(Student("Lee", 70, 40));
            minPQ.push(Student("Byun", 90, 90));
            minPQ.push(Student("wu", 40, 40));
            minPQ.push(Student("jung", 59, 59));
            minPQ.push(Student("hong", 45, 49));

            while(!minPQ.empty())
            {
                    cout<<minPQ.top().name<<" ";
                    minPQ.pop();
            }
            cout<<endl;
    }
 
</code>
