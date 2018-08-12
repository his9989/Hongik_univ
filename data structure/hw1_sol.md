### $ cat makefile

<code>

    hw1a : hw1a.o recta.o
            g++ -o hw1a hw1a.o recta.o
    hw1a.o recta.o : recta.h
    hw1b : hw1b.o rectb.o
            g++ -o hw1b hw1b.o rectb.o
    hw1b.o rectb.o : rectb.h

</code>

### $ cat hw1a.cpp

<code>

    #include <iostream>
    #include "recta.h"                              //만들어둔 헤더 불러옴
    using namespace std;

    int main()
    {
            Rectangle r(2, 3, 6, 6), s(1, 2, 5, 9); //

            cout << "<rectangle r> "; r.Print();
            cout << "<rectangle s> "; s.Print();
            if(r.SmallerThan(s))
                    cout <<"s is bigger";
            else if (r.EqualTo(s))
                    cout <<"Same Size";
            else cout << "r is bigger";
            cout << endl;
    }

</code>

### $ cat recta.h

<code>

    #ifndef RECTANGLE_H
    #define RECTANGLE_H
    class Rectangle{
    public:
            Rectangle(int, int, int, int);  //생성자
            void Print();                   //print 함수 선언
            bool SmallerThan(Rectangle&);   //ST 함수 선언
            bool EqualTo(Rectangle&);       //ET 함수 선언
            int GetHeight();
            int GetWidth();
    private:
            int xLow, yLow, height, width;
    };
    #endif

</code>

### $ cat recta.cpp

<code>

    #include <iostream>
    #include "recta.h"
    using namespace std;

    Rectangle::Rectangle(int x=0, int y=0, int h=0, int w=0)
    : xLow(x), yLow(y), height(h), width(w) {}
    void Rectangle::Print()                 //Rec 클래스의 Print함수 선언
    {
            cout <<"position: "<<xLow<<", "<<yLow;
            cout <<" Height = "<<height<<" Width = "<<width<<endl;
    }
    bool Rectangle::SmallerThan(Rectangle& s)       //REC 클래스의 ST함수 선언
    {
            if(height*width < s.height*s.width)
                    return true;
            else
                    return false;
    }
    bool Rectangle::EqualTo(Rectangle& s)
    {
            if(height*width == s.height*s.width)
                    return true;
            else
                    return false;
    }
    /*int Rectangle::GetHeight()
    {return height;}
    int Rectangle::GetWidth()
    {return width;}*/
    
</code>

### $ cat hw1b.cpp

<code>

    #include <iostream>
    #include "rectb.h"
    using namespace std;

    int main()
    {
            Rectangle r(2, 3, 6, 6), s(1, 2, 5, 9);

            cout << "<rectangle r> "<< r;
            cout << "<rectangle s> "<< s;
            if(r<s)
                    cout <<"s is bigger";
            else if (r==s)
                    cout <<"Same Size";
            else cout << "r is bigger";
            cout << endl;
    }
    
</code>

### $ cat rectb.h

<code>

    #ifndef RECTANGLE_H
    #define RECTANGLE_H
    using namespace std;
    class Rectangle{
    public:
            Rectangle(int, int, int, int);  //생성자
            bool operator<(Rectangle&);
            bool operator==(Rectangle&);
            int GetHeight();
            int GetWidth();
    friend ostream& operator<<(ostream&, Rectangle&);
    private:
            int xLow, yLow, height, width;
    };
    #endif

</code>

### $ cat rectb.cpp

<code>

    #include <iostream>
    #include "rectb.h"
    using namespace std;

    Rectangle::Rectangle(int x=0, int y=0, int h=0, int w=0)
    : xLow(x), yLow(y), height(h), width(w) {}
    ostream& operator<<(ostream& os, Rectangle& s)
    {
            os<<"Position: "<<s.xLow<<", "<<s.yLow;
            os<<" Height: "<<s.height<<" Width: "<<s.width<<endl;
            return os;
    }
    bool Rectangle::operator<(Rectangle& s)
    {
            if (height*width < s.height*s.width) return true;
            else return false;
    }
    bool Rectangle::operator==(Rectangle& s)
    {
            if (height*width == s.height*s.width) return true;
            else return false;
    }
    int Rectangle::GetHeight()
    {return height;}
    int Rectangle::GetWidth()
    {return width;}

</code>
