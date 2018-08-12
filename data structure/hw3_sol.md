### $ cat maze.dat

<code>

    12      15
    0 1 0 0 0 1 1 0 0 0 1 1 1 1 1
    1 0 0 0 1 1 0 1 1 1 0 0 1 1 1
    0 1 1 0 0 0 0 1 1 1 1 0 0 1 1
    1 1 0 1 1 1 1 0 1 1 0 1 1 0 0
    1 1 0 1 0 0 1 0 1 1 1 1 1 1 1
    0 0 1 1 0 1 1 1 0 1 0 0 1 0 1
    0 0 1 1 0 1 1 1 0 1 0 0 1 0 1
    0 1 1 1 1 0 0 1 1 1 1 1 1 1 1
    0 0 1 1 0 1 1 0 1 1 1 1 1 0 1
    1 1 0 0 0 1 1 0 1 1 0 0 0 0 0
    0 0 1 1 1 1 1 0 0 0 1 1 1 1 0
    0 1 0 0 1 1 1 1 1 0 1 1 1 1 0

</code>

### $ cat maze2.dat

<code>

    9       9
    0 0 0 0 0 0 0 0 1
    1 1 1 1 1 1 1 1 0
    1 0 0 0 0 0 0 0 1
    0 1 1 1 1 1 1 1 1
    1 0 0 0 0 0 0 0 1
    1 1 1 1 1 1 1 1 0
    1 0 0 0 0 0 0 0 1
    0 1 1 1 1 1 1 1 1
    1 0 0 0 0 0 0 0 0

</code>

### $ cat makefile

<code>

    hw3: hw3.o maze.o
            g++ -o hw3 hw3.o maze.o

</code>

### $ cat hw3.cpp

<code>

    #include<iostream>
    #include<fstream>
    using namespace std;
    void getdata(istream&, int&, int&);
    void Path(int, int);

    int main(int argc, char* argv[]){
            int m, p;       //m by p maze
            cout<<argc<<endl;
            if(argc==1)     // error 발생. 이미 호출한 미로인 경우
                    cerr<<"Usage: "<<argv[0]<<" maze_data_file\n";
            else{
                    cout<<argc<<endl;
                    ifstream is(argv[1]);   //is: 입력함수
                                            //ifstream: input file stream
                                            //즉, argv[1]파일은 입력하는 함수 is

                    cout<<argc<<endl;
                    if(!is){                // 파일 입력이 없다면.
                            cerr<<argv[1]<<" does not exist\n";
                            return 1;
                    }
                    cout<<"For maze datafile ["<<argv[1]<<"]\n\n";
                    getdata(is, m, p);
                    is.close();
                    Path(m, p);
            }
    }

</code>

### $ cat maze.cpp

<code>

    #include<iostream>
    #include<stack>
    using namespace std;
    const int MAXSIZE=100;
    bool maze[MAXSIZE+2][MAXSIZE+2]={0};
    bool mark[MAXSIZE+1][MAXSIZE+1]={0};

    enum directions{N, NE, E, SE, S, SW, W, NW};
    struct offsets{
            int a,b;
    } move[8]={-1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1};
    struct Items {
            Items(int xx=0, int yy=0, int dd=0) : x(xx), y(yy), dir(dd)
                    {}
            int x, y, dir;
    };

    template<class T>
    ostream& operator<< (ostream& os, stack<T>& s) {
            stack<T> tempstack;
            int i= s.size();
            for(int z=0; z<i;z++){
                    tempstack.push(s.top());
                    s.pop();
            }
            for(int z=0; z<i;z++){
                    os<< "-> "<< tempstack.top();
                    tempstack.pop();
                    }
            return os;
    }

    ostream& operator<< (ostream& os, Items& item)
    {
            static int count = 0;
            os << "(" << item.x<<", "<<item.y<<")";
            count++; if((count%5)==0)cout<<endl;
            return os;
    }

    void Path(const int m, const int p)
    {
            mark[1][1] = 1;
            stack<Items> stack;
            Items temp(1, 1, E);
            stack.push(temp);
            int count=0;

            while(!stack.empty())
            {
                    temp=stack.top();
                    stack.pop();
                    int i=temp.x; int j=temp.y; int d=temp.dir;
                    while(d<8)
                    {
                            int g=i+move[d].a;
                            int h=j+move[d].b;
                            if((g==m)&&(h==p))
                            {
                                    cout<<stack;
                                    temp.x=i; temp.y=j;
                                    cout<<" -> " <<temp;
                                    temp.x=m; temp.y = p;
                                    cout<< " -> " <<temp<<endl;
                                    cout<<"#nodes visited = "<<count+2<<" out of "<<m*p<<endl;
                                    return;
                            }
                            if((!maze[g][h])&&(!mark[g][h]))
                            {
                                    mark[g][h]=1;
                                    temp.x=i; temp.y=j; temp.dir=d+1;
                                    stack.push(temp);
                                    i=g; j=h; d=N;
                                    count++;
                            }
                            else d++;
                    }
            }
            cout<<"No path in maze"<<endl;
    }

    void getdata(istream& is, int& m, int& p)
    {
            is>>m>>p;
            for(int i=0;i<m+2;i++)
            {       maze[i][0]=1; maze[i][p+1]=1;}
            for(int j=1; j<=p; j++)
            {       maze[0][j]=1; maze[m+1][j]=1;}
            for(int i=1; i<=m; i++)
                    for(int j=1;j<=p;j++)
                            is>>maze[i][j];
    }
    
</code>
