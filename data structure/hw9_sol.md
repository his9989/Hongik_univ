### $ cat makefile

<code>

    hw9a:   hw9a.o
            g++ -o hw9a hw9a.o
    hw9b:   hw9b.o
            g++ -o hw9b hw9b.o
    hw9a.o hw9b.o:  bst.h

</code>

### $ cat hw9a.cpp

<code>

    #include<iostream>
    #include <fstream>
    #include "bst.h"
    using namespace std;

    void File2Tree(istream& fin, BST<string, int>& tree)
    {
            string command, key;
            int elt;
            int r;
            int num;

            while (fin>>command)    //command가 입력되면 while문을 반복!
            {
                    if(command=="print")
                            tree.Print();
                    else if(command=="insert")
                    {
                            fin>>key>>elt;
                            tree.Insert(key, elt);
                    }
                    else if(command=="get")
                    {
                            fin>>key;
                            if(tree.Get(key, elt))
                                    cout<<"The value of "<<key<<" is "<<elt<<endl;
                            else
                                    cout<<"No such key: "<<key<<endl;
                    }
                    else if (command == "rankget")
                    {
                            fin>>r;
                            if(tree.RankGet(r, key, elt))
                                    cout<<"The "<<r<<"-th element is "<<key<<" : "<<elt<<endl;
                            else
                                    cout<<"No such ranking : "<<r<<endl;
                    }
                    else if(command == "delete")
                    {
                            fin>>key;
                            tree.Delete(key);
                    }
                    else
                            cout<<"Invalid command : "<<command<<endl;
            }
    }

    int main(int argc, char * argv[])               // argc: 메인에 전달되는 인자의 개수
    {
            if(argc<2)
            {
                    cerr << "Usage : "<<argv[0]<<" infile\n";       //argv[0] : 실행하는 파일 이름. 여기서는 hw9a bst1.dat 중 앞의 hw9a
                    return 1;
            }
            ifstream fin(argv[1]);                  // 실행할 때 hw9a bst1.dat할 때 bst1.dat를 지칭함
            if(!fin)
            {
                    cerr<<argv[1]<<" open failed\n";        // 파일이 없는 경우는 이런게 출력됨.
                    return 1;
            }
            BST<string, int> tree;
            File2Tree(fin, tree);           // 입력된 데이터 파일을 위에서 정의한 함수대로 출력해냄
            fin.close();                    // fstream 헤더의 함수. bst1.dat를 닫는 명령어
    }

</code>

### $ cat hw9b.cpp

<code>

    #include<iostream>
    #include <fstream>
    #include "bst.h"
    using namespace std;

    void File2Tree(istream& fin, BST<string, int>& tree)
    {
            string command, key;
            int elt;
            int r;
            int num;

            while (fin>>command)
            {
                    if(command=="print")
                            tree.Print();
                    else if(command=="insert")
                    {
                            fin>>key>>elt;
                            tree.Insert(key, elt);
                    }
                    else if(command=="get")
                    {
                            fin>>key;
                            if(tree.Get(key, elt))
                                    cout<<"The value of "<<key<<" is "<<elt<<endl;
                            else
                                    cout<<"No such key: "<<key<<endl;
                    }
                    else if (command == "rankget")
                    {
                            fin>>r;
                            if(tree.RankGet(r, key, elt))
                                    cout<<"The "<<r<<"-th element is "<<key<<" : "<<elt<<endl;
                            else
                                    cout<<"No such ranking : "<<r<<endl;
                    }
                    else if(command == "delete")
                    {
                            fin>>key;
                            tree.Delete(key);
                    }
                    else
                            cout<<"Invalid command : "<<command<<endl;
            }
    }

    int main(int argc, char * argv[])
    {
            if(argc<2)
            {
                    cerr << "Usage : "<<argv[0]<<" infile [infile2]\n";
                    return 1;
            }
            ifstream fin(argv[1]);
            if(!fin)
            {
                    cerr<<argv[1]<<" open failed\n";
                    return 1;
            }
            BST<string, int> small;
            File2Tree(fin, small);
            fin.close();

            if(argc==2)
                    return 0;
            ifstream fin2(argv[2]);
            if(!fin2)
            {       cerr<<argv[2]<<" open failed\n";
                    return 1; }

            BST<string, int> big;

            cout<<"\n2nd tree follows\n";
            File2Tree(fin2, big);
            fin2.close();

            BST<string, int> finaltree;
            finaltree.TwoWayJoin(small, big);
            cout<<"\n<two way joined tree final print>";
            finaltree.Print();
    }

</code>

### $ cat bst.h

<code>

    #ifndef TREE_H
    #define TREE_H
    #include<iostream>
    #include<queue>
    using namespace std;

    template <class K, class E>
    struct Node
    {
            Node(K ky, E el, Node<K, E> *left=0, Node<K, E> *right=0)              //key, element, leftChild, rightChild를 갖는 노드 선언
                    : key(ky), element(el), leftChild(left), rightChild(right) {leftSize=0;}

            Node<K, E> *leftChild;
            K key;
            E element;
            Node<K, E> *rightChild;
            int leftSize;
    };

    template <class K, class E>
    class BST
    {
            public:
                    BST()                           //BST: 부모 기준 작은 건 왼쪽, 큰 건 오른쪽으로 솔팅된 이진 트리
                            {root = 0; }            //root는 당연히 0부터 시작할 것임
                    void Insert(K &newkey, E &el)   // Insert가 호출되는 경우의 명령어
                    {
                            Insert(root, newkey, el);       //root, newkey, el 정보를 이용하여 입력하고
                            left=0;
                            Releft(root);                   //
                    }
                    void Preorder()                 // Preorder 정렬
                            {Preorder(root);}
                    void Inorder()                  // Inorder 정렬
                            {Inorder(root);}
                    void Postorder()                // Postorder 정렬
                            {Postorder(root);}
                    void Levelorder();              // Levelorder 정렬
                    bool Get(const K&, E&);         // key, element를 변수로 하는 Get함수 선언
                    bool Print();                   // Print는 기니까 저기서 선언하자~
                    bool RankGet(int r, K& k, E& e);//Rankget도 길다야 ㅋㅋ 저기서 정의할게~~
                    void Delete(K &oldkey)          // delete는 delete 호출 후 Releft 호출
                    {
                            Delete(root, oldkey);
                            left=0;
                            Releft(root);
                    }
                    void ThreeWayJoin(BST<K, E>& small, K midkey, E midel, BST<K, E>& big);
                    void TwoWayJoin(BST<K, E>& small, BST<K, E>&big);


            private:
                    void Visit(Node<K, E> *);
                    void Insert(Node<K, E>* &, K &, E &);
                    void Left(Node<K, E> *);
    //              void Leftcounter(Node<K, E> *);
    //              void Rightcounter(Node<K, E> *);
                    void Releft(Node<K, E> *);
                    void Preorder(Node<K, E> *);
                    void Inorder(Node<K, E> *);
                    void Postorder(Node<K, E> *);
                    void Delete(Node<K, E>* &, K &);
                    Node<K, E> *root;
                    int left;
    };

    template<class K, class E>
    void BST<K, E>::Visit(Node<K, E> *ptr)
    {
            cout<<ptr->key<<" "<<ptr->element<<" "; //sorting할때 출력하는 명령어.
    }

    template <class K, class E>
    void BST<K, E>::Insert(Node<K, E>* &ptr, K &newkey, E &el)
    {
            if(ptr==0)              // 지금 노드가 찾고자하는 노드다!!
                    ptr=new Node<K, E>(newkey, el); //그냥 바로 추가!!
            else if(newkey<ptr->key)                // 넣고자 하는 값이 ptr->key보다 작은 경우
                    Insert(ptr->leftChild, newkey, el);     //왼쪽으로 가거라아ㅏㅏ
            else if(newkey>ptr->key)                // 넣고자 하는 값이 ptr->key보다 큰 경우
                    Insert(ptr->rightChild, newkey, el);    // 오른쪽으로 가거라아ㅏㅏ
            else
                    ptr->element = el;              // 같은 값이 있는 경우 갱신!
    }

    template <class K, class E>
    void BST<K, E>::ThreeWayJoin(BST<K, E>& small, K midkey, E midel, BST<K, E>& big)
    {
            root = new Node<K, E>(midkey, midel, small.root, big.root);     //midkey, midel, small.root, big.root를 인자로 하는 새 노드 선언해서 root에 넣음
            small.root = big.root=0;
    }

    template <class K, class E>
    void BST<K, E>::TwoWayJoin(BST<K, E>& small, BST<K, E>& big)            //small 트리와 big 트리가 있다
    {
            if(!small.root)                                                 //small트리의 루트가 죽은 경우
            {       root = big.root;                                        //root에 big.root 넣고
                    big.root=0;                                             //빅루트 죽여
                    return;                                                 //끗
            }
            if(!big.root)                                                   //big트리의 루트가 죽은 경우
            {       root = small.root;                                      //루트에 스몰루트 넣고
                    small.root=0;                                           //스몰 루트 죽여
                    return;                                                 //끗
            }
                                                                            //두개 트리 모두 있는 경우. 여기서는 스몰트리에서 가장 큰값을
                                                                            //루트로 해서 좌측에 스몰, 우측에 빅 연결할 것
            BST small2=small;                                               //BST 타입의 small2를 선언해서 small를 small2에 복사
            Node<K, E>*ptr=small2.root;                                     //ptr노드에 small2의 루트 넣기 (즉, small의 루트)
            while(ptr->rightChild)                                          //small2의 루트에 우측 자식 있는 경우
                    ptr=ptr->rightChild;                                    //우측자식이 ptr이 되도록 -> 최우측까지 반복
            K midkey = ptr->key;                                            //K 타입의 midkey에 최우측의 key넣고
            E midel = ptr->element;                                         //E 타입의 midel에 최우측의 element 넣고
            Delete(small2.root,midkey);                                     //small2의 루트를 갖는 트리에서 midkey 노드를 삭제. 즉, small2의 최우측 노드 삭제
            ThreeWayJoin(small2, midkey, midel, big);                       //small2 트리와 small2의 삭제된 최우측 노드와 big트리 합성
            small.root = 0;                                                 //합쳐졌으니까 스몰루트 삭제
            big.root=0;                                                     //합쳐졌으니까 빅루트 삭제
    }

    template<class K, class E>
    void BST<K, E>::Left(Node<K, E> *currentNode)
    {
            left++;
            currentNode->leftSize=left;
    }

    template<class K, class E>
    void BST<K, E>::Releft(Node<K, E> *currentNode)
    {
            if(currentNode)
            {
                    Releft(currentNode->leftChild);
                    Left(currentNode);
                    Releft(currentNode->rightChild);
            }
    }

    template <class K, class E>
    void BST<K, E>::Preorder(Node<K, E> *currentNode)       //Preorder sorting 전위
    {                                                       // 부모 탐색 후 좌측 찍고, 우측 찍고
            if(currentNode)
            {
                    Visit(currentNode);
                    Preorder(currentNode->leftChild);
                    Preorder(currentNode->rightChild);
            }
    }

    template <class K, class E>
    void BST<K, E>::Inorder(Node<K, E> *currentNode)        //Inorder sorting 중위
    {                                                       // 좌측 찍고, 부모 찍고, 우측 찍고
            if(currentNode)
            {
                    Inorder(currentNode->leftChild);
                    Visit(currentNode);
                    Inorder(currentNode->rightChild);
    //              Left(currentNode);
            }
    }

    template <class K, class E>
    void BST<K, E>::Postorder(Node<K, E> *currentNode)      //Postorder sorting 후위
    {                                                       // 좌측 찍고, 우측 찍고, 부모 찍고
            if(currentNode)
            {
                    Postorder(currentNode->leftChild);
                    Postorder(currentNode->rightChild);
                    Visit(currentNode);
            }
    }

    template<class K, class E>
    void BST<K, E>::Levelorder()                            //Level sorting 레벨 탐방
    {                                                       // 부모들 먼저 쭈욱 찍고, 다 찍으면 그다음 레벨로 내려감
            queue <Node<K, E>*> queue;
            Node<K, E> *currentNode = root;
            while(currentNode)
            {
                    Visit(currentNode);
                    if(currentNode->leftChild)
                            queue.push(currentNode->leftChild);
                    if(currentNode->rightChild)
                            queue.push(currentNode->rightChild);
                    if(queue.empty())
                            return;
                    currentNode=queue.front();
                    queue.pop();
            }
    }

    template <class K, class E>
    bool BST<K, E>::Get(const K& k, E& e)           //key, element가 있을때 node 입력하는 함수
    {
            Node<K, E> *ptr = root;                 // root를 가르키는 새로운 노드 ptr 선언
            while(ptr)                              // ptr이 존재하는 동안 반복
            {
                    if(k<ptr->key)                  // 찾고자 하는 key값이 부모의key보다 작은 경우
                            ptr=ptr->leftChild;     // 왼쪽으로 가라아아ㅏ
                    else if(k>ptr->key)             // 찾고자 하는 key값이 부모의 key보다 큰 경우
                            ptr=ptr->rightChild;    // 오른쪽으로 가라아ㅏㅏㅏ
                    else                            // 찾고자하는 key값을 찾은경우
                    {
                            e=ptr->element;         // 출력할 e에다가 찾고자 하는 key의 element를 넣기
                            return true;            // 여기서 true 반환하고 끝내라!
                    }
            }
            return false;                           // 찾고자 하는 ket가 없는 경우 false 반환
    }

    template <class K, class E>
    bool BST<K, E>::Print() //inorder과 postorder로 traversal 함
    {
            cout<<endl<<"inorder traversal : ";
            Inorder();
            cout<<endl<<"Postorder traversal : ";
            Postorder();
            cout<<endl;
    }

    template <class K, class E>
    bool BST<K, E>::RankGet(int r, K & k, E & e)    //중위 탐방으로 r번째의 key와 element를 말해라
    {
            Node<K, E> *currentNode = root;                         //root를 가리키는 node 선언, 이후 하나씩 옮김
            while(currentNode)                                      //current가 목표에 도달할때까지 찾아가기
            {
                    if(r<currentNode->leftSize)                     //r이 current의 leftSize보다 작은 경우
                            currentNode = currentNode->leftChild;   //current를 좌측 자식으로 옮기기
                    else if(r>currentNode->leftSize)                //r이 current의 leftSize보다 큰 경우
                    {
                            currentNode = currentNode->rightChild;  //current를 우측 자식으로 옮기기
                    }
                    else                                            //r이 current의 leftSize와 같은 경우
                    {
                            k=currentNode->key;                     //k에 current의 key를 k에 넣고
                            e=currentNode->element;                 //k에 current의 element를 e에 넣고
                            return true;                            //여기서 RankGet 함수 종료, true 반환
                    }
            }
            return false;                                           //찾는 값이 없음. false 반환
    }
                                                                    //r이 1인 경우 계속 왼쪽으로 내려가면 inorder의 시작 점 즉, rank1
                                                                    //계속 왼쪽으로 내려가서 밑에서 2번째가 rank2
                                                                    //3을 찾고자 한다면 2에서 오른쪽으로 내려가서 거기서 맨 왼쪽으로
                                                                    //4는 rank3의 부모노드
                                                                    //5는 rank4의 부모노드거나 rank4의 우측 노드 등 이런식으로 rank 찾음

    template <class K, class E>
    void BST<K, E>::Delete(Node<K, E>* &ptr, K &oldkey)             //ptr을 노드로 하는 트리에서  oldkey를 인자로 받았을때 함수 실행
    {
            Node<K, E> *tmpptr;                                     //임시 ptr
            Node<K, E> *tmpdaddyptr;                                //임시 ptr의 부모
            if(ptr==0)                                              //ptr이 비어있으면 그냥 넘어갓
                    return;
            else if(oldkey<ptr->key)                                        //삭제하고자 하는 key가 ptr보다 작으면
                    Delete(ptr->leftChild, oldkey);                 //좌측으로 넘어가서 재귀
            else if(oldkey>ptr->key)                                //삭제하고자 하는 key가 ptr보다 크면
                    Delete(ptr->rightChild, oldkey);                //우측으로 넘어가서 재귀
            else                                                    //삭제하고자 하는 노드를 찾은 경우. ptr을 삭제할 것 입니다!
            {
                    if(!ptr->leftChild && !ptr->rightChild)         //노드에 좌, 우측 노드가 없는 경우. 즉 리프인 경우
                    {
                            delete ptr;                             //그냥 oldkey갖는 노드 삭제
                            ptr = 0;                                //ptr이 루트를 가르키게
                            return;                                 //끗
                    }
                    else if(ptr->leftChild && !ptr->rightChild)     //좌측 자식만 있는 경우
                    {
                            tmpptr=ptr;                             //tmpptr에 ptr 넣고
                            ptr = ptr->leftChild;                   //ptr은 ptr의 좌측 자식을 가르키게 하고
                                                                    //ptr은 계속 이어져온 변수로, 이렇게 이어져있으면 자식노드가 자연스럽게
                                                                    //부모노드를 대신한다.
                            delete tmpptr;                          //tmpptr을 삭제하고
                            return;                                 //끗
                    }
                    else if(!ptr->leftChild && ptr->rightChild)     //우측 자식만 있는 경우
                    {
                            tmpptr=ptr;                             //tmpptr에 ptr 넣고
                            ptr=ptr->rightChild;                    //재귀로 이어온 ptr자리에 ptr->right자식 넣고
                            delete tmpptr;                          //tmpptr 즉, ptr ㄱ밧 삭제
                            return;                                 //끗
                    }
                    else                                            //좌, 우측 모두 있는 경우
                    {                                               //BST이므로 우측에서 제일 작은거 or 좌측에서 제일 큰거 대체.
                                                                    //여기서는 우측에서 가장 작은 거 대체함. 삭제되는 것은 ptr. ptr자리에 대체할 것을 찾아야함
                            Node<K, E> *rc = ptr->rightChild;       //ptr의 우측 자식을 루트로 하는 rc 생성
                            if(!rc->leftChild)                      //rc의 좌측 노드가 없는 경우. 즉, rc의 루트가  가장 작은 노드인 경우
                            {
                                    ptr->key = rc->key;             //rc의 모든 값, 심지어 rc의 우측 자식트리까지 ptr에 연결하고
                                    ptr->element = rc->element;
                                    ptr->rightChild = rc->rightChild;
                                    delete rc;                      //rc 삭제
                                    return;
                            }
                            else                                    //rc의 좌측 노드가 있는 경우. 가장 좌측 즉, 가장 작은 노드 찾아야됨
                            {
                                    tmpdaddyptr=rc;                 //rc를 임시 저장
                                    tmpptr=tmpdaddyptr->leftChild;  //rc의 좌측 자식을 임시 저장
                                    while(tmpptr->leftChild)        //rc의 좌측자식의 좌측 자식이 있는 경우. 가장 좌측의 노드를 찾는 과정
                                    {
                                            tmpdaddyptr=tmpptr;     //부모 임시를 아들 임시로 바꾸고
                                            tmpptr=tmpdaddyptr->leftChild; //아들임시를 그 아들의 아들 임시로 바꿔. 즉, daddyptr, ptr 둘다 한칸씩 내려
                                    }
                                    ptr->key=tmpptr->key;           //tmpptr의 좌측 노드가 없는 경우
                                    ptr->element=tmpptr->element;   //tmpptr의 key, element를 모두 ptr로 넣어. 만약 이때 우측 자식만 없다면 여기서 끝!.
                                    if(tmpptr->rightChild)          //가장 작은 노드에 우측 자식이 있는 경우
                                    {                               //우측 자식이 부모 자리로 올라가야함.
                                            rc=tmpptr->rightChild;  //
                                            tmpdaddyptr->leftChild=rc;
                                    }
                                    delete tmpptr;                  //ptr로 올라간 우측 서브트리에서 가장 작은 값을 갖고있던 tmpptr자리를 삭제해줌
                                    return;                         //끗
                            }
                    }
            }
    }
    #endif

</code>

### $ cat bst1.dat

<code>

    insert  boy 23
    insert  emerald 70
    insert  cola 30
    insert  dog 40
    insert  ace 10
    insert  bug 27
    insert  boy 90
    print
    get boy
    get emerald
    get dog
    get hohoho

</code>

### $ cat bst2.dat

<code>

    insert  xboy 23
    insert  xemerald 70
    insert  xcola 30
    insert  xdog 40
    insert  xace 10
    insert  xboy 90
    print
    rankget 4
    delete xcola
    delete xemerald
    print
    get xboy
    get xemerald
    get xdog
    get xhohoho

</code>
