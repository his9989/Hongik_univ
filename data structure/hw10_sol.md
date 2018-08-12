### $ cat makefile

<code>

    kruskal:        mstree.o kruskal.o
            g++ -o kruskal mstree.o kruskal.o
    prim:   mstree.o prim.o
            g++ -o prim mstree.o prim.o
    sollin: mstree.o sollin.o
            g++ -o sollin mstree.o sollin.o
    kruskal.o prim.o sollin.o mstree.o : mstree.h

</code>

### $ cat kruskal.cpp

<code>

    #include<fstream>
    #include<queue>                                                 //queue 사용
    #include "mstree.h"                                             //"mstree.h"헤더 사용
    int NNODES;                                                     //NNODES 선언. 전체 Node 개수를 아려주는 변수

    priority_queue <Edge, vector<Edge>, Compare> PQ;                //인자로 Edge, vector, Compare를 받는 PQ 임. PQ에는 Edge가 쌓임
    void kruskal()                                                  //PQ에 kruskal()이라는 함수를 쓸거임
    {
            Sets sets(NNODES);                                      //Sets 형식의 sets라는 이름의 클래스 생성.
            int nedges = 0;                                         //nedges 초기화. 모든  edge까지  현재 몇번째 edge 탐색인지 알려주는 num
            while (nedges<NNODES - 1)                               //노드가 n개면 엣지는 n-1개 이므로, nedges가 0부터 시작이므로 nedges<NNODES-1
            {
                    if(PQ.empty())                                  //PQ가 비어있는 경우
                            throw "No Spanning Tree Exists.";       //"파일이 없다~" 출력
                    Edge e = PQ.top();                              //PQ가 있는 경우에는 PQ의 가장 작은 값을 Edge 타입의 변수 e에 저장
                    PQ.pop();                                       //PQ의 탑을 삭제

                    int v1root = sets.Find(e.v1);                   //e라는 모서리에  2개의 정점이 있다. 이 정점에 연결된 모서리가 싸이클인지 확인
                    int v2root = sets.Find(e.v2);                   //그래프 노드 숫자를 적은 배열에서 v1, v2의 넘버를 가져옴
                    if(v1root != v2root)                            //둘이 다르다면
                    {
                            sets.Union(v1root, v2root);             //둘을 이어랏!! 만들고 싶은 그림 하나 그렸다!!
                            nedges++;                               //엣지 하나 추가하엿느니라~~~
                            cout<<e;                                //e를 출력해라~ 즉, 여기서 출력화면이 나온다~
                    }
            }
    }                                                               //parent 배열: -1, -1, -1, -1, -1, -1, -1
                                                                    //(0, 5) 탐색:  5, -1, -1, -1, -1, -1, -1
                                                                    //(2, 3) 탐색:  5, -1,  3, -1, -1, -1, -1
                                                                    //(1, 6) 탐색:  5,  6,  3, -1, -1, -1, -1
                                                                    //(1, 2) 탐색:  5,  6,  3, -1, -1, -1,  3
                                                                    //(3, 6) 탐색:  5,  6,  3, -1, -1, -1,  3
                                                                    //             -> parent(3)=3, parent(6)=parent(3)=3 으로 같아서 넘어감
                                                                    //(3, 4) 탐색:  5,  6,  3,  4, -1, -1,  3
                                                                    //(4, 6) 탐색:  5,  6,  3,  4, -1, -1,  3
                                                                    //             -> parent(4)=4, parent(6)=parent(3)=parent(4)=4
                                                                    //(4, 5) 탐색:  5,  6,  3,  4,  5, -1,  3
                                                                    //(0, 1) 탐색:  5,  6,  3,  4,  5, -1,  3
                                                                    //             -> parent(0)=parent(5)=5
                                                                    //                parent(1)=parent(6)=parent(3)=parent(4)=parent(5)=5

    void ReadEdges4kruskal (istream& is)                            //입력받는 함수
    {
            Edge e;                                                 //Edge 타입의 e 선언~
            while(GetEdge(is, NNODES, e))                           //입력을 제대로 받았으면~
                    PQ.push(e);                                     //PQ에 입력받은 노드 정보를 입력~
    }                                                               //PQ에서 자동 정렬

    int main(int argc, char *argv[])
    {
            ifstream is;                                            //
            if(argc==1)                                             //
                    is.open("mstree.dat");                          //
            else                                                    //
                    is.open(argv[1]);                               //
            if(!is)                                                 //입력이 안된다면
            {                                                       //
                    cerr<<"No such input file\n";                   //에러어ㅓ
                    return 1;                                       //종료
            }                                                       //
            is>>NNODES;                                             //dat파일 첫줄의 node 개수 정보 입력
            if(NNODES<2)                                            //node 개수가 2보다 적으면
            {                                                       //
                    cerr<<"#nodes must be 2.."<<endl;               //빠구
                    return 1;                                       //종료
            }                                                       //

            try                                                     //
            {                                                       //
                    ReadEdges4kruskal(is);                          //입력받자이제~
                    kruskal();                                      //입력 모두 받았으면 kruskal하자~
            }                                                       //
            catch (char const *str)                                 //
            {
                    cerr<<"Exception: "<<str<<endl;                 //
                    return 1;                                       //
            }
    }

</code>

### $ cat prim.cpp

<code>

    #include<fstream>
    #include<queue>
    #include"mstree.h"
    int NNODES;

    priority_queue<Edge, vector<Edge>, Compare> PQ;                 //우선순위 큐 PQ 선언

    queue<Edge> *Q;                                                 //queue Q를 선언, Q는 맨처음에 입력된 엣지들의 집합

    void MoveIntoPQ_EdgesOfNode(int v)                              //PQ에 queue의 값을 넣는 함수, PQ는 edge를 넣어서 정렬하는 용도
    {                                                               //여기서 queue는 임의의 정점 v에 연결된 모든 edge가 저장된 queue
            while(!Q[v].empty())                                    //Q가 비어있지 않다면!
            {
                    Edge e = Q[v].front();                          //Edge 타입의 e에 Q[v]의 front를 넣고
                    Q[v].pop();                                     //Q[v]를 pop하고
                    PQ.push(e);                                     //PQ에 e를 넣어랏. 그럼 자동으로 입력된 엣지들이 정렬됨
            }                                                       //즉, 0의 경우 0에 연결된 edge가 우선순위로 정렬됨
    }
    void prim()                                                     //prim 알고리즘 호출 함수
    {
            Sets sets(NNODES);                                      //NNODES는 처음 입력받은 엣지의 개수
            int nedges = 0;                                         //nedges는 몇 번째 엣지를 탐방중인지 세는 카운트 변수
            while(nedges<NNODES - 1)                                //엣지=노드-1, 엣지는 0부터 시작하므로
            {
                    if(PQ.empty())                                  //0에 저장된 엣지가 하나도 없는 경우
                            throw "No Spanning Tree Exits.";        //노드에 엣지가 하나도 없음 안되지~
                    Edge e = PQ.top();                              //노드0에 붙은 엣지 중 가장 가중치 작은 엣지를 e에 저장
                    PQ.pop();                                       //입력한 엣지는 지워버려~
                                                                    //즉 일단 PQ에 노드 0의 엣지들이 정렬되있음. 그 Edge 중 최소값이 e에 들어감
                    int root0 = sets.Find(0);                       //0의 parent값을 찾아라. -1로 초기화 되있으므로 root0는 0이 된다.
                    if(root0!=sets.Find(e.v1))                      //e에는 2개의 노드가 붙어있다. 하나는 0, 나머지는 그외, 그외를 찾는 if문
                    {
                            sets.Union(root0, e.v1);                //싸이클을 막기 위해 배열 상에 입력 내용 표시
                            nedges++;                               //엣지 하나 찾았다~
                            cout<<e;                                //찾은 엣지 출력
                            MoveIntoPQ_EdgesOfNode(e.v1);           //e.v1부터 시작
                    }
                    else if(root0!=sets.Find(e.v2))                 //edge e에 붙어있는 0이 아닌 노드를 찾는 if문
                    {
                            sets.Union(root0, e.v2);                //싸이클을 막기 위해 배열 상에 입력 내용 표시
                            nedges++;                               //엣지 하나 찾았다~
                            cout<<e;                                //찾은 엣지 출력
                            MoveIntoPQ_EdgesOfNode(e.v2);           //e.v2부터 시작
                    }
            }
    }

    void ReadEdges4prim(istream& is)                                //Node를 입력하는 함수, PQ에 노드0의 정점을 먼저 넣어주는 함수
    {
            Q=new queue<Edge> [NNODES];                             //어떤 node에 대해 거기에 붙어 있는 모든 edge를 Q에 넣음
            Edge e;                                                 //Edge 타입의 e 선언

            while (GetEdge(is, NNODES, e))                          //e가 입력가능한 정점일때
            {
                    Q[e.v1].push(e);                                //e,v1노드의 queue에 e를 넣어라
                    Q[e.v2].push(e);                                //e.v2노드의 queue에 e를 넣어라
            }
            MoveIntoPQ_EdgesOfNode(0);                              //정점 0의 모든 edge를 PQ로 이동. 즉, 시작점을 노드 0으로 하겠다는 뜻!!
    }

    int main(int argc, char *argv[])                                //main 함수
    {
            ifstream is;
            if(argc==1)
                    is.open("mstree.dat");
            else
                    is.open(argv[1]);
            is>>NNODES;                                             //Node의 개수를 NNODES로 입력
            if(NNODES<2)                                            //Node의 개수가 2개 미만이면
            {
                    cerr<<"No sych input file\n";                   //알고리즘 할게 업음~
                    return 1;                                       //끗
            }
            try                                                     //try 구문에 예외 발생하면 catch, 안하면 그냥 끗!
                    {ReadEdges4prim(is); prim(); }                  //입력 값에 대해 ReadEdges4prim 함수 실행, prim() 실행
            catch (char const *str)
                    {cerr<<"Exception: "<<str<< endl; return 1;}    //예외 발생! 끗
    }

</code>

### $ cat sollin.cpp

<code>

    #include<fstream>                                               //
    #include<queue>                                                 //
    #include<algorithm>                                             //알고리즘 헤더 사용ㅑ ->
    #include"mstree.h"                                              //mstree.h 헤더 사용
    int NNODES;                                                     //전체 노드의 개수

    priority_queue<Edge, vector<Edge>, Compare> *PQ;                //Edge, vector, Compare 타입의 PQ 선언

    void MoveIntoPQ_EdgesOfNodes(int v1, int v2)                    //
    {
            while(!PQ[v2].empty())                                  //v2의 PQ가 존재한다면
            {
                    Edge e = PQ[v2].top();                          //v2의 PQ의 min값을 e에 넣고
                    PQ[v2].pop();                                   //v2의PQ의 min값을 지우고
                    PQ[v1].push(e);                                 //v1의PQ에 e를 넣음
            }
    }

    void sollin()                                                   //sollin 알고리즘 내용
    {
            Sets sets(NNODES);                                      //최종 Node 개수의 sets 선언
            int nedges = 0;                                         //현재 몇번쨰 엣지를 탐색하는지 횟수 변수 선언
            while (nedges<NNODES-1)                                 //엣지 개수는 노드-1(0부터 시작)
            {
                    Edge *e = new Edge[NNODES];                     //e는 Edge 배열, 즉, 배열 e는 전체 노드만큼의 크기
                                                                    // -> 이 배열 e는 edge의 가중치가 임시 저장되는 배열
                    for(int i=0; i<NNODES; i++)                     //엣지  배열 e의 원소에 기존 edge에서 PQ로 얻은 최소값을 넣어줌
                    {                                               // -> 즉, e[i]란 i정점에서 갈수있는 가장 작은 가중치를 의미함
                            if(!PQ[i].empty())                      //i 정점의 PQ가 비어있지 않다면
                            {
                                    e[i] = PQ[i].top();             //i 정점의 PQ의 최소값을 e배열의 i번째에 입력, 노드까지 값이 입력
                                                                    //즉, 이때 임시 배열 e안에 i노드의 가중치는 PQ에 저장된 최소값의 edge의
                                                                    //가중치와 도착 노드까지 저장됨. (시작노드는 i본인)
                                    PQ[i].pop();                    //PQ에 pop해줌.
                                                                    //if문 결론: 정점i의 PQ에서 min값의 구조체를 임시 가중치 배열 e에 넣음
                            }
                    }

                    for(int i=0; i<NNODES; i++)                     //사이클 여부를 확인하고 신장트리 완성하는 구문
                    {
                            int root1 = sets.Find(e[i].v1);         //앞의 kruskal, prim과 마찬가지로 사이클 여부 찾는 구문
                            int root2 = sets.Find(e[i].v2);         //
                            if(root1 != root2)                      //한 엣지의 양 옆 정점이 다른 경우
                            {
                                    sets.Union(root1, root2);       //root1의 parent에 root2값을 넣어라. 싸이클 방지 구문
                                    nedges++;                       //엣지 하나 찾았다~~~
                                    cout<<e[i];                     //e배열의 i번째 엣지 출력
                            }
                            MoveIntoPQ_EdgesOfNodes(root1, root2);  //여기서 i로 초기화 되있던 엣지 e[i]의 가중치가 제대로 들어가게됨(맞나..?)
                    }
            }
    }       //이 과정으로 노드 하나당 edge하나만 연결 가능->        //----------------------round 1, 모든 node가 edge 하나씩 연결-------
            //즉, 0에 edge 하나만 연결 하도록 함                    //1round는 입력 받은 대로 첫번째 for문에 의해
                                                                    //e={10, 14, 12, 12, 22, 10, 14} 이렇게 배열 초기화
                                                                    //PQ[0]=28  /  PQ[1]=16, 28  /  PQ[2]=16  / PQ[3]=18, 22
                                                                    //PQ[4]=24, 25  / PQ[5]=25  /  PQ[6]=18, 24 1round는 이렇게 초기화됨
                                                                    //
                                                                    //두번째 for문에 의해                   parent={-1,-1,-1,-1,-1,-1,-1}
                                                                    //e={10, 14, 12, 12, 22, 10, 14}
                                                                    //i=0] root1=0, root2=5                 parent={ 5,-1,-1,-1,-1,-1,-1}
                                                                    //0의 부모를 5로 바꿈, <10출력>
                                                                    //      ->PQ[0]=25, 28 / PQ[5]={}
                                                                    //i=1] root1=1, root2=6                 parent={ 5, 6,-1,-1,-1,-1,-1}
                                                                    //1의 부모를 6으로 바꿈, <14출력>
                                                                    //      ->PQ[1]=16,18,28 / PQ[6]=24
                                                                    //i=2] root1=2, root2=3                 parent={ 5, 6, 3,-1,-1,-1,-1}
                                                                    //2의 부모를 3으로 바꿈, <12출력>
                                                                    //      ->PQ[2]=16,18 / PQ[3]=22
                                                                    //i=3] root1=2->3, root2=3              parent={ 5, 6, 3,-1,-1,-1,-1}
                                                                    //부모 변경 없음, 출력 없음, PQ 이동 없음
                                                                    //
                                                                    //i=4] root1=3, root2=4                 parent={ 5, 6, 3, 4,-1,-1,-1}
                                                                    //3의 부모를 4로 바꿈, <22출력>
                                                                    //      ->PQ[3]=22, 24 / PQ[4]=25
                                                                    //i=5] root1=0->5 / root2=5             parent={ 5, 6, 3, 4,-1,-1,-1}
                                                                    //부모 변경 없음, 출력 없음, PQ이동 없음
                                                                    //
                                                                    //i=6] root1=1->6 / root2=6             parent={ 5, 6, 3, 4,-1,-1,-1}
                                                                    //부모 변경 없음, 출력 없음, PQ이동 없음
                                                                    //
                                                                    //------------------------------------------------------------------
                                                                    //-----------------------round 2, 최종 간선 트리 형성--------------
                                                                    //2round는 위의 과정으로 첫번째 for문에 의해
                                                                    //e={25, 16, 16, 22, 25,  , 24}
                                                                    //PQ[0]=28  /  PQ[1]=18, 28  /  PQ[2]=18  /  PQ[3]=24
                                                                    //PQ[4]={}  /  PQ[5]={}  /  PQ[6]={}
                                                                    //
                                                                    //두번쨰 for문에 의헤                   parent={ 5, 6, 3, 4,-1,-1,-1}
                                                                    //e={25, 16, 16, 22, 25,  , 24}
                                                                    //i=0] root1=4, root2=5                 parent={ 5, 6, 3, 4, 5,-1,-1}
                                                                    //4의 부모를 5로 바꿈, <25출력>
                                                                    //      ->PQ[4]={} / PQ[5]={}
                                                                    //i=1] root1=1->6, root2=2->3->4->5     parent={ 5, 6, 3, 4, 5,-1, 5}
                                                                    //6의 부모를 5로 바꿈, <16출력> (여기서 nnedges=6되서 이 for문만 끝나면 됨)
                                                                    //      ->PQ[6]={} / PQ[5]={}
                                                                    //i=2] root1=1->6->5, root2=2->3->4->5  parent={ 5, 6, 3, 4, 5,-1, 5}
                                                                    //부모 변경 없음, 출력 없음, PQ이동 없음
                                                                    //
                                                                    //i=3] root1=3->4->5, root2=4->5        parent={ 5, 6, 3, 4, 5,-1, 5}
                                                                    //부모 변경 없음, 출력 없음, PQ이동 없음
                                                                    //
                                                                    //i=4] root1=4->5, root2=5              parent={ 5, 6, 3, 4, 5,-1, 5}
                                                                    //부모 변경 없음, 출력 없음, PQ이동 없음
                                                                    //
                                                                    //i=5] --
                                                                    //
                                                                    //
                                                                    //i=6] root1=4->5, root2=6->5           parent={ 5, 6, 3, 4, 5,-1, 5}
                                                                    //
                                                                    //끝!! -> 즉, 10, 14, 12, 22, 25, 16 출력하고 sollin 종료!!

    void ReadEdges4sollin(istream& is)                              //데이터를 입력받는 함수
    {
            PQ=new priority_queue<Edge, vector<Edge>, Compare> [NNODES];    //Node 크기의 PQ를 선언
            Edge e;                                                 //Edge 타입의 e 선언

            while (GetEdge(is, NNODES, e))                          //엣지 정보를 한줄씩 받음(시작주소, 도착주소, 가중치)
            {
                    PQ[e.v1].push(e);                               //e.v1의 PQ에 가중치 e를 우선순위로 입력
                    PQ[e.v2].push(e);                               //e.v2의 PQ에 가중치 e를 우선순위로 입력
            }                                                       //각 정점에는 그 정점에 붙은 edge를 저장하는 PQ가 각각 있음.
    }
                                                                    //PQ[0]=10, 28  /  PQ[1]=14, 16, 28  /  PQ[2]=12, 16  / PQ[3]=12, 18, 22
                                                                    //PQ[4]=22, 24, 25  / PQ[5]=10, 25  /  PQ[6]=14, 18, 24
                                                                    //이렇게 각 노드에 연결된 가중치를 각 노드의 PQ에 각각 저장

                                                                    //main 함수
    int main(int argc, char *argv[])
    {
            ifstream is;
            if(argc==1)
                    is.open("mstree.dat");
            else
                    is.open(argv[1]);
            if(!is)
            {
                    cerr<<"No such input file\n";
                    return 1;
            }
            is>>NNODES;                                             //전체 Node 개수 입력 받기
            if(NNODES<2)                                            //전체 Node 개수가 2개 미만이면 실행못함
            {
                    cerr<<"#nodes must be 2.."<<endl;
                    return 1;                                       //끗!!
            }
            try                                                     //다음 구문을 시도하고 에러 있으면 catch에서 잡아!
            {
                    ReadEdges4sollin(is);                           //데이터를 입력받겟따
                    sollin();                                       //sollin으로 정렬하라.
            }
            catch(char const *str)                                  //예외 발생시
            {
                    cerr<<"Exception: "<<str<<endl;
                    return 1;
            }
    }

</code>

### $ cat mstree.cpp

<code>

    #include "mstree.h"
    Sets::Sets(int numberOfElements)
    {                                               //parent는 순환을 막는 용도
            if(numberOfElements < 2)                //그래프에 노드가 2개 미만이면
                    throw "2개 이상이어야 함.";     //좀 더 넣어라
            n = numberOfElements;                   //전체 노드의 개수를 n에 저장
            parent = new int[n];                    //parent = new int [n], 즉parent는 n개의 배열
            fill(parent, parent + n, -1);           //parent 배열의 빈부분에 -1을 입력
    }                                               //parent 배열은 i번째 원소(노드)는 값이 i고, 범위 외는 -1이다.

    void Sets::Union(int i, int j)
            {parent[i] = j;}                        //parent 배열의 i번째 원소로 j를 넣어라.

    int Sets::Find(int i)
    {
            while (parent[i]>=0)                    //parent 배열의 i번째 원소가 0보다 큰, 즉, 무언가 값이 있다면
                    i=parent[i];                    //parent 배열의 i번째 원소를 i에 넣고,
            return i;                               //i값을 반환. 즉, parent 배열의 i번째 원소를 반환
    }                                               //이때 while에 의해, 이 노드에 연결된 모든 노드를 탐방하게됨.

    bool Edge::operator==(Edge& e2)
            {return (v1==e2.v1 && v2==e2.v2);}      //e2의 v1과 e1의 v1이 같고, e2의 v2와 e1의 v2가 같은 경우 true 반환
    bool Edge::operator!=(Edge& e2)
            {return (v1!=e2.v1 || v2!=e2.v2);}      // ~~ 위와 마찬가지
    ostream& operator<<(ostream& os, Edge& e)
    {
            os<<"("<<e.v1<<", "<<e.v2<<") : "<<e.weight<<endl;      //출력!!>_<
            return os;
    }

    bool GetEdge(istream& is, const int numnodes, Edge& e)
    {
            is>>e.v1>>e.v2>>e.weight;               //e 엣지의 v1, v2, weight를 입력
            if(!is.good())                          //입출력 가능한 상태가 아니라면
                    return false;                   //여기서 관둬!
            if(e.v1<0||e.v1>numnodes||e.v2<0||e.v2>=numnodes||e.v1==e.v2)   //e의 v1, v2가 음수거나, e.v1, v2가 numnodes보다 큰경우
                    throw "Incorrect Edge";         //부정확한 엣지
            if(e.v2<e.v1)
                    swap(e.v1, e.v2);               //v1, v2의 순서를 일관되게 정렬해줌
            return true;
    }

</code>

### $ cat mstree.h

<code>

    #ifndef MSTREE_H
    #define MSTREE_H
    #include<iostream>
    using namespace std;

    class Sets
    {
            public:
                    Sets(int);
                    void Union(int i, int j);
                    int Find(int i);
            private:
                    int *parent;
                    int n;
    };

    struct Edge
    {
            int v1, v2;
            double weight;
            bool operator == (Edge& e2);
            bool operator != (Edge& e2);
    };

    struct Compare
    {
            bool operator() (Edge e1, Edge e2)
                    {return e1.weight > e2.weight;}                 //e1의 가중치가 더 크면 true, e2의 가중치가 더 크면 false
    };

    ostream& operator << (ostream& os, Edge& e);
    bool GetEdge(istream& is, const int numnodes, Edge& e);

    #endif

</code>

### $ cat mstree.dat

<code>

    7
    0       1       28
    0       5       10
    1       2       16
    1       6       14
    2       3       12
    3       4       22
    3       6       18
    4       5       25
    4       6       24
    
</code>
