### $ cat makefile

<code>

    hw6: hw6.o list.o
            g++ -o hw6 hw6.o list.o
    hw6.o list.o: list.h

</code>

### $ cat hw6.cpp

<code>

    #include<iostream>
    #include"list.h"
    int main()
    {
            IntList il;                             //il이라는 이름의 IntList 클래스 선언
            il.Push_Back(5);                        //il클래스의 Back함수를 이용. il의 노드들이 이루는 링크드 리스트 맨 뒤에 5삽입
            il.Push_Back(7);                        //Push로 링크드 리스트 뒤에 노드 추가
            il.Push_Back(9);                        //Push로 링크드 리스트 뒤에 노드 추가
            cout<<il;                               //il 출력. << 재선언으로 클래스 내부의 링크드 리스트 data값을 이어서 모두 출력
            il.Push_Front(4);                       //il클래스의 링크드 리스트 앞에 추가
            il.Push_Front(3);                       //il클래스의 링크드 리스트 앞에 추가
            cout<<il;                               //il 출력.
            il.Insert(6);                           //il클래스의 Insert 함수로 정렬된 리스트에 적절한 위치로 삽입
            il.Insert(10);                          //위와 같음
            il.Insert(2);                           //
            il.Insert(5);                           //
            il.Insert(2);                           //
            il.Insert(10);                          //

            while(!il.IsEmpty())                    //il클래스의 IsEmpty 함수로 비어있을때까지 탐색
            {
                    cout<<il.Front()<<" ";          //il의 맨 앞 성분 출력
                    il.Pop_Front();                 //방금 출력한 맨 앞 성분 제거
            }
            cout<<endl;                             //개행
    }

</code>

### $ cat list.h

<code>

    using namespace std;

    struct Node{                                                            //구조체 Node 선언
            Node(int d=0, Node*l=0): data(d), link(l){}                     //구조체 Node의 원소는 d, l이 있음
            int data;                                                       //외부에서 d는  data를 가져다 쓸 것
            Node *link;                                                     //외부에서 l는 *link를 가져다 쓸 것
                                                                            //Node에 연결할 새로운 노드. 즉, Node->link는 Node안에 저장되어 있는
                                                                            //새로운 Node인  link라고 볼 수 있음
    };

    class IntList {                                                         //클래서 IntList 선언
            public:
                    IntList() {last = first = 0;}                           //생성자 선언. last, first를 0으로 초기화
                    bool IsEmpty() {return !first;}                         ///first가 있는 경우 0반환, 없는 경우 1반환
                    void Push_Back(int);                                    //

                    int Front();
                    void Pop_Front();
                    void Push_Front(int);
                    void Insert(int);

            private:
                    Node *first;                                            //first라는 이름의 노드 선언
                    Node *last;                                             //last라는 이름의 노드 선언
                    friend ostream& operator<<(ostream&, IntList&);         //출력 함수 선언
    };

    ostream& operator<<(ostream&, IntList&);                                //새로운 출력도구 선언

</code>

### $ cat list.cpp

<code>

    #include<iostream>
    #include"list.h"
    ostream& operator<<(ostream& os, IntList& il)   // 출력함수 << 재선언   il이라는 클래스가 인자인 경우
    {
            Node *ptr = il.first;                   //ptr이라는 이름의 Node 선언 il 클래스의 first 노드를 ptr에 넣는다.
            while(ptr!=0)                           //ptr이 존재하지 않을때까지 반복
            {
                    os<<ptr->data<<"__";            //ptr 노드의 데이터를 출력. 즉, 맨 처음에는 입력된 클래스의 최초 노드가 출력
                    ptr=ptr->link;                  //ptr에 연결되 있는 ptr->link를 ptr에 넣는다.
            }
            os << endl;                             //개행
            return os;
    }

    void IntList::Push_Back(int e)                  //링크드 리스트의 뒤쪽에 노드를 추가하는 함수
    {
            if(!first)                              //비어있는 링크드 리스트인 경우
                    first=last=new Node(e);         //링크드 리스트의 변수인 first, last에 입력한 Node 입력
            else                                    //노드가 들어있는 링크드 리스트인 경우
            {
                    last->link = new Node(e);       //last의 원소인 link에 입력할 노드 넣기.
                    last = last->link;              //last라는 타이틀을 last->link에 부여
            }
    }

    int IntList::Front()                            //링크드 리스트 맨 앞의 원소 출력
    {
            return first->data;                     //first의 data를 반환
    }

    void IntList::Pop_Front()                       //리링크드 리스트 맨 앞의 원소 삭제
    {
            first=first->link;                      //first에 연결된 노드를 first라는 타이틀 부여
    }

    void IntList::Push_Front(int e)                 //맨 앞에 노드 추가
    {
            Node *tmp=new Node(e);                  //tmp라는 이름의 노드 선언, 이 노드는 e를 값으로 갖는 Node
            tmp->link=first;                        //tmp에 연결된 링크 노드에 first라는 타이틀을 갖고 있던 노드 넣기
            first=tmp;                              //tmp라는 노드에 first라는 타이틀 부여
    }

    void IntList::Insert(int e)                     //정렬된 리스트에 e를 데이터로 갖는 노드를 정렬하여  삽입
    {
            Node *tmp=new Node(e);                  //e를 데이터로 갖는 Node와 같은 tmp를 새로 선언
            if(!first)                              //first가 존재하지 않는다면
                    first=last=tmp;                 //first, last 모두  tmp 넣기
            else if(first->data>e)                  //first의 데이터가 e보다 큰경우 -> first 앞에 입력
            {
                    tmp->link=first;                //tmp에 연결된 링크노드에 first 넣고
                    first=tmp;                      //first 타이틀은 tmp에게 부여
            }
            else if(first->data<e)                  //first의 데이터가 e보다 작은 경우->그들의 링크랑 비교
            {
                    Node *rear=first;               //중간에 삽입하는 경우 앞의 것, 뒤의 것을 잡아두고 가운데에 삽입해야함.
                    Node *front=first->link;        //이 때 앞뒤로 임시 저장하는게 rear, front
                                                    //첫번째 노드는 rear, 두번째 노드는 front로 front랑 비교하면서 비교
                    while(front&&front->data<e)     //front가 존재하고, front의 data가 e보다 작은 경우, 반복해서 e보다 큰거 찾을때까지 반복
                    {                               //e보다 작으면 rear, front를 하나씩 링크로 옮기고, e보다 큰경우 반복 탈주
                            rear=front;             //rear에 front를 넣고
                            front=front->link;      //front에는 front에 연결된 link를 넣는다.
                    }
                    if(!front)                      // 끝까지 갔는데도 e보다 큰 값이 없는 경우. 즉, e가 가장 큰 경우
                    {                               // front는 없으므로 신경쓸 필요 없고
                            rear->link=tmp;         // rear의 link에 새로운 입력할 노드 tmp를 연결한다.
                            last=tmp;               // tmp 노드에 last라는 타이틀을 준다
                    }
                    else if(front->data>e)          // 중간에 삽입하는 경우, rear, front 사이에 tmp 삽입
                    {
                            rear->link=tmp;         //rear에 tmp를 연결하고
                            tmp->link=front;        //tmp에 front를 연결
                    }
            }
    }

</code>

### $ cat hashtest.cpp

<code>

    #include<iostream>
    #include<list>
    #include<string.h>
    using namespace std;
    #define HTSIZE 137
    struct Node{                                                            //Node 선언. name과 val를 갖는다.
            Node(char *n, float v): name (n), val(v) {}
            char *name;                                                     //외부에서는 name이라는 이름으로 변수를 넣는다.
            float val;                                                      //외부에서는 val이라는 이름으로 변수를 넣는다.
    };

    list<Node> HT[HTSIZE];                                                  //Hassh Table 선언

    int hashfcn(char *name)                                                 //
    {
            return name[0] * name[strlen(name)-1]%HTSIZE;                   //name 배열의 첫번째*마지막 원소 곱해서 반환
    }

    bool WhereInHT(char *name, list<Node>::iterator & iter)                 //변수가 name, list타입의 생성자 iter일때
    {
            int hashval = hashfcn(name);                                    //hashval에 랜덤으로 섞인 hashfcn 넣기
            for(iter=HT[hashval].begin(); iter!=HT[hashval].end(); iter++)  //
                    if(!strcmp((*iter).name, name))
                            return true;
            return false;
    }

    bool GetFromHT(char *name, float& val)
    {
            list<Node>::iterator iter;
            if(WhereInHT(name, iter))
            {
                    val=(*iter).val;
                    return true;
            }
            return false;
    }

    void StoreIntoHT(char *name, float val)
    {                                                                       //변수가 name, val 일때
            list<Node>::iterator iter;
            if(WhereInHT(name, iter))                                       //list 타입의 생성자 iter 선언
                    (*iter).val = val;                                      //변수가 name, iter일때
            else
                    HT[hashfcn(name)].push_front(Node(name, val));
    }

    void PrintValue(char *name)
    {
            float val;
            if(!GetFromHT(name, val))
                    cout<<name<<" does not exist"<<endl;
            else
                    cout<<name<<" "<<val<<endl;
    }

    int main()
    {
            StoreIntoHT("abro", 23);                                        //name이 "abro", val이 23인 HT 저장
            StoreIntoHT("bb", 34.5);                                        ////
            StoreIntoHT("haha", 99);                                        ////
            StoreIntoHT("bb", 1234.5);                                      ////
            PrintValue("bb");                                               //
            PrintValue("haha");                                             //
            PrintValue("hoho");                                             //
    }

</code>
