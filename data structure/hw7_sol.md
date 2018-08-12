### $ cat makefile

<code>

    hw7a: hw7a.o
            g++ -o hw7a hw7a.o
    hw7a.o: bt0.h

    hw7b: hw7b.o
            g++ -o hw7b hw7b.o
    hw7b.o: bt.h

</code>

### $ cat hw7a.cpp
 
<code>

    #include<iostream>
    #include "bt0.h"
    using namespace std;

    int main()
    {
            Tree<double> tree;                              //double을 인자로 하는 Tree타입의 tree 클래스 선언
            double dval;                                    //double 자료형의 dval 선언

            cout<<"Enter values:\n";
            while(cin>>dval)                                //dval값을 입력받을 수 있을때까지 입력받아서
                    tree.Insert(dval);                      //tree 클래스의 Insert함수(dval) 호출
            cout<<endl<<"Preorder traversal:        ";
            tree.Preorder();                                //tree클래스의 Preorder 실행
            cout<<endl<<"Inorder traversal: ";
            tree.Inorder();                                 //tree클래스의 Inorder 실행
            cout<<endl<<"Postorder traversal:       ";
            tree.Postorder();                               //tree클래스의 Postorder 실행
            cout<<endl<<"Levelorder traversal:      ";
            tree.Levelorder();                              //tree클래스의 Levelorder 실행
            cout<<endl;
    }

</code>

### $ cat bt0.h
 
<code>

    #ifndef BT0_H
    #define BT0_H
    #include<iostream>
    #include<queue>
    using namespace std;

    template<class T>
    struct Node
    {
            Node(T d, Node<T> *left=0, Node<T> *right=0)                    //data d, leftChild, rightChild
                    : data(d), leftChild(left), rightChild(right) {}

            Node <T> *leftChild;
            T data;
            Node <T> *rightChild;
    };

    template <class T>
    class Tree
    {
            public:
                    Tree()                                                  //root=0인 Tree 생성자 선언
                            {root = 0;}
                    void Insert(T &value)
                            {Insert(root, value);}
                    void Preorder()
                            {Preorder(root);}
                    void Inorder()
                            {Inorder(root);}
                    void Postorder()
                            {Postorder(root);}

                    void Levelorder();

            private:
                    void Visit(Node<T> *);
                    void Insert(Node<T>* &, T &);
                    void Preorder(Node<T> *);
                    void Inorder(Node<T> *);
                    void Postorder(Node<T> *);

                    Node<T> *root;
    };

    template <class T>
    void Tree<T>::Visit(Node<T> *ptr)                                       //해당 노드의 data를 출력하는 함수
            {cout<<ptr->data<<" ";}

    template <class T>
    void Tree<T>::Insert(Node<T>* &ptr, T &value)                           //입력할 노드와 입력할 값
    {
            if(ptr==0)                                                      //입력한 노드에 노드가 존재하지 않는 경우
                    ptr=new Node<T>(value);                                 //value를data로 갖는 새로운 노드를 ptr에 넣음
            else if(value<ptr->data)                                        //value가 ptr의 data보다 작은 경우
                    Insert(ptr->leftChild, value);                          //ptr->leftChild에 입력
            else if(value>ptr->data)                                        //value가 ptr의 data보다 큰 경우
                    Insert(ptr->rightChild, value);                         //ptr->rightChild에 입력
            else
                    cout<<endl<<"Duplicate value "<<value<<" ignored\n";    //같은 값의 경우 중복!
    }

    template <class T>
    void Tree<T>::Preorder(Node<T> *currentNode)                            //전위 탐방. 루트부터 최좌측 리프까지 이후 우측 노드 탐색
    {
            if(currentNode)                                                 //자식 탐색하기 전에 부모가 존재하는지 확인
            {
                    Visit(currentNode);                                     //부모를 먼저 출력하고
                    Preorder(currentNode->leftChild);                       //좌측 출력하고, 좌측에 자식이 있으면 그에대해 다시 preorder
                    Preorder(currentNode->rightChild);                      //우측 출력하고, 우측을 루트로하는 부트리가 있으면 preorder
            }
    }

    template <class T>
    void Tree<T>::Inorder (Node<T> *currentNode)                            //중위 탐방. 최좌측 리프에서 부모찍고 우측 찍고 부트리의 부모로 반복
    {
            if(currentNode)
            {
                    Inorder(currentNode->leftChild);
                    Visit(currentNode);
                    Inorder(currentNode->rightChild);
            }
    }

    template <class T>
    void Tree<T>::Postorder (Node<T> *currentNode)
    {
            if(currentNode)
            {
                    Postorder(currentNode->leftChild);
                    Postorder(currentNode->rightChild);
                    Visit(currentNode);
            }
    }

    template <class T>
    void Tree<T>::Levelorder ()                                             //Level의 모든 것을 탐색하고 다음 level로 내려감
    {
            queue <Node <T>*> queue;                                        //queue 선언. level에 해당하는 모든 노드의 값을 쌓는 용도
            Node<T> *currentNode=root;                                      //T 클래스의 currentNode라는 Node 선언하여 root 입력
            while(currentNode)                                              //currentNode, 즉, 처음에는 root에 대해
            {
                    Visit(currentNode);                                     //현재 노드 출력
                    if(currentNode->leftChild)                              //currentNode의 leftChild가 존재하는 경우
                            queue.push(currentNode->leftChild);             //leftChild를 queue에 삽입
                    if(currentNode->rightChild)                             //currentNode의 rightChild가 존재하는 경우
                            queue.push(currentNode->rightChild);            //rightChild를 queue에 삽입
                    if(queue.empty())                                       //queue가 비어있는 경우
                            return;                                         //그냥 여기서 끝내자~ 입력할게 1도 없다~
                    currentNode=queue.front();                              //currentNode에 queue의  front를 삽입
                                                                            //즉, currentNode의 자식을 currentNode에 삽입
                    queue.pop();                                            //입력한 자식은 지워버림
            }
    }
    #endif

</code>

### $ cat hw7b.cpp
 
<code>

    #include "bt.h"
    #include<string>
    using namespace std;

    int main()
    {
            BST<string, double> bst;
            string str;
            double dval;

            cout<<"Enter string & value pairs:\n";
            while(cin>>str>>dval)
                    bst.Insert(str, dval);
            cout<<endl<<"Preorder traversal:        ";
            bst.Preorder();
            cout<<endl<<"Inorder traversal: ";
            bst.Inorder();
            cout<<endl<<"Postorder traversal:       ";
            bst.Postorder();
            cout<<endl<<"Levelorder traversal:      ";
            bst.Levelorder();
            cout<<endl;
    }

</code>

### $ cat bt.h
 
<code>

    #ifndef BT0_H
    #define BT0_H
    #include<iostream>
    #include<queue>
    using namespace std;

    template<class K, class E>                                                     //변수가 K, E
    struct Node
    {
            Node(K ky, E el, Node<K, E> *left=0, Node<K, E> *right=0)              //변수로 key, ele, left, right 갖는다
                    : key(ky), element(el), leftChild(left), rightChild(right) {}

            Node <K, E> *leftChild;
            K key;
            E element;
            Node <K, E> *rightChild;
    };

    template <class K, class E>
    class BST                                                                      //data만 갖고 있던 것을 key와 element를 갖게함
    {
            public:
                    BST()                                                          //BST 생성자
                            {root = 0;}
                    void Insert(K &newkey, E &el)
                            {Insert(root, newkey, el);}
                    void Preorder()
                            {Preorder(root);}
                    void Inorder()
                            {Inorder(root);}
                    void Postorder()
                            {Postorder(root);}

                    void Levelorder();

            private:
                    void Visit(Node<K, E> *);
                    void Insert(Node<K, E>* &, K &, E &);
                    void Preorder(Node<K, E> *);
                    void Inorder(Node<K, E> *);
                    void Postorder(Node<K, E> *);

                    Node<K, E> *root;
    };

    template <class K, class E>
    void BST<K, E>::Visit(Node<K, E> *ptr)
            {cout<<ptr->key<<" "<<ptr->element<<" ";}

    template <class K, class E>
    void BST<K, E>::Insert(Node<K, E>* &ptr, K &newkey, E &el)
    {
            if(ptr==0)
                    ptr=new Node<K, E>(newkey, el);
            else if(newkey<ptr->key)
                    Insert(ptr->leftChild, newkey, el);
            else if(newkey>ptr->key)
                    Insert(ptr->rightChild, newkey, el);
            else
                    ptr->element = el;
    }

    template <class K, class E>
    void BST<K, E>::Preorder(Node<K, E> *currentNode)
    {
            if(currentNode)
            {
                    Visit(currentNode);
                    Preorder(currentNode->leftChild);
                    Preorder(currentNode->rightChild);
            }
    }

    template <class K, class E>
    void BST<K, E>::Inorder (Node<K, E> *currentNode)
    {
            if(currentNode)
            {
                    Inorder(currentNode->leftChild);
                    Visit(currentNode);
                    Inorder(currentNode->rightChild);
            }
    }

    template <class K, class E>
    void BST<K, E>::Postorder (Node<K, E> *currentNode)
    {
            if(currentNode)
            {
                    Postorder(currentNode->leftChild);
                    Postorder(currentNode->rightChild);
                    Visit(currentNode);
            }
    }

    template <class K, class E>
    void BST<K, E>::Levelorder ()   //Levelorder은 P266 참고
    {
            queue <Node <K, E>*> queue;
            Node<K, E> *currentNode=root;
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
    #endif

</code>
