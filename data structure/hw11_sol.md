### $ cat makefile

<code>

    heapsort:       heapsort.o
            g++ -o heapsort heapsort.o
    bubblesort:     bubblesort.o
            g++ -o bubblesort bubblesort.o

</code>

### $ cat heapsort.cpp
 
<code>

    #include<iostream>
    using namespace std;

    template <class T>
    void PrintArray(T *a, const int n)      //변수가 n, 배열 a
    {
            for(int i=1; i<=n; i++)         //1~n까지 반복. 시작점이 1임.(arr[0]=0을 제외하고 실행하는 것)
                    cout<<a[i]<<" ";        //arr[1]~arr[n]의 arr 배열 원소 출력
            cout<<endl;                     //배열원소 출력이 끝났으면 종료
    }
    template <class T>
    void Adjust(T *a, const int root, const int n)
    {
            T e = a[root];                          //i노드의 값을 e에 넣고.

            int j;                                  //j는 2*root, 즉, i의 자식 노드를 의미함.
            for(j=2*root; j<=n; j*=2)               //j가 i의 자식노드, j가 배열길이보다는 작을 동안, j*=2하면서 반복
            {
                    if(j<n && a[j]<a[j+1])          //j가 배열길이보다 작고, j의 값이 j의 오른쪽 애 보다 작은 경우. 무조건 j의 형제
                            j++;                    //j의 형제가 더 크니까 j는 볼필요 없음. j의 형제를 비교해보자!
                                                    //j가 j+1보다 크면 j비교, 더 작으면 j+1비교!
                    if(e>=a[j])                     //e(i노드 값, 즉, j의 부모 값)가 a[j](혹은 a[j+1])보다 크거나 같으면
                            break;                  //반복 여기서 멈춤
                    a[j/2] = a[j];                  //e가 더 작다면, j의 부모, 즉, 배열i에 j값을 넣어라.
            }                                       //즉, 부모랑 자식 두개를 비교해서 그 밑의 손자까지 비교해서
                                                    //노드 i를 루트로 하는 부분트리를 맥스힙 구조로 재정렬해줌.
            a[j/2] = e;                             //중복 처리된 노드를 초기 값으로 선언해줌. (이부분 잘이해안감 다시 분석)
    }

    template <class T>
    void HeapSort(T *a, const int n)                //배열 a이고, 길이는 n임
    {
            for(int i=n/2; i>=1; i--)               //arr[5], arr[4], arr[3], arr[2], arr[1] 노드의 Adjust함수 실행
            {
                    Adjust(a, i, n);                //배열 a에서 i노드에 대해 Adjust하라. 배열 최대 길이는 n이다.
            }
            for(int i=n-1; i>=1; i--)               //전체 배열에서 heap구조로 다시 출력하는 과정
            {                                       //이미 여기서 전체 배열은 정렬 되어있음
                    swap(a[1], a[i+1]);             //크기 비교해서 재정렬하면서
                    Adjust(a,1,i);                  //출력하고 싶은 배열을 맞춰주고
                    PrintArray(a, i);               //진행상황 출력
            }
    }

    int main()
    {
            int a[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};    //a라는 배열의 원소 입력

            int n = sizeof(a)/sizeof(int)-1;                        //n=10, 배열 길이에서 1뺀값, 0은 안쓸거임
            cout<<"Before Sorting: ";
            PrintArray(a, n);                                       //배열 a를 그대로 출력!
            HeapSort(a, n);                                         //Heap 정렬 때리고
            cout<<"After Sorting: ";
            PrintArray(a, n);                                       //배열 a 다시 출력!
    }

</code>

### $ cat bubblesort.cpp
 
<code>

    #include<iostream>
    using namespace std;

    template <class T>
    void PrintArray(T *a, const int n)                              //배열 a에 길이 n일때
    {
            for(int i=1; i<=n; i++)
                    cout<<a[i]<<" ";
            cout<<endl;
    }

    template<class T>
    void BubbleSort1(T *a, int n)
    {
            for(int i=n-1; i>=1; i--)                               //n-1부터 시작해서 하나씩 줄여가면서
                    for(int j=1; j<=i; j++)                         //j는 1부터 i까지 올라가면서
                            if(a[j]>a[j+1])                         //j번째 원소와 i번째 원소 크기 비교
                                    swap(a[j], a[j+1]);             //swap
    }                                                               //말그대로 일일이 크기 비교해서 정렬

    template<class T>
    void BubbleSort2(T *a, int n)
    {
            int newn;                                               //newn은 정렬이 완료된 노드의 다음노드를 가르킴
            while(n>1)                                              //앞에서부터 해서 정렬이 완료된 부분은 탐색 안하고
            {                                                       //그 뒤부터 할수있도록 하는 반복구문
                    newn=1;
                    for(int i=1; i<n; i++)                          //i는 1부터 n(배열 길이)까지 반복
                            if(a[i]>a[i+1])                         //i번째 노드가 i+1보다 크다면
                            {
                                    swap(a[i], a[i+1]);             //i번째랑 i+1번째랑 바꾸고,
                                    newn = i+1;                     //i까지 정렬이 끝났으므로, newn에 i+1저장
                            }
                    n = newn;                                       //n에 newn을 저장
            }
    }

    int main()
    {
            int a[]={0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};      //배열 2개 입력
            int b[]={0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};      //소트 방법을 2개 사용

            int n=sizeof(a)/sizeof(int) - 1;                        //길이는 10
            cout<<"Before Sorting: ";                               //방법 1
            PrintArray(a, n);
            BubbleSort1(a, n);
            cout<<"After Sorting: ";
            PrintArray(a, n);

            cout<<"Before Sorting: ";                               //방법2
            PrintArray(b, n);
            BubbleSort2(b, n);
            cout<<"After Sorting: ";
            PrintArray(b, n);
    }
    
</code>
