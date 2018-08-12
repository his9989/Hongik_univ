### $ cat hw2a.cpp

<code>

    #include <iostream>
    using namespace std;
    #include "polya.h"
    int main()
    {
            Polynomial p1, p2, p3;

            cin >> p1 >> p2;
            p3 = p1 + p2;
            cout << p1 << p2 << p3;
    }

</code>

### $ cat polya.h
 
<code>

    #ifndef POLYNOMIAL_H
    #define POLYNOMIAL_H
    using namespace std;

    struct Term
    {
            float coef;
            int exp;
    };
    class Polynomial
    {
            public:
                    Polynomial();
                    Polynomial operator+(Polynomial&);
                    void NewTerm(const float, const int);
            friend ostream& operator<<(ostream&, Polynomial&);
            friend istream& operator>>(istream&, Polynomial&);
            private:
                    Term *termArray;
                    int capacity;
                    int terms;
    };
    #endif

</code>

### $ cat polya.cpp
 
<code>

    #include <iostream>
    #include "polya.h"
    using namespace std;

    istream& operator>> (istream& is, Polynomial& p)
    {
            int noofterms; float coef; int exp;
            is >> noofterms;
            for(int i=0; i<noofterms; i++)
            {
                    is >> coef >> exp;
                    p.NewTerm(coef, exp);
            }
            return is;
    }
    ostream& operator<< (ostream& os, Polynomial& p)
    {
            for(int i=0; i<p.terms; i++)
            {
                    if(i==0)
                    {
                            if(p.termArray[i].exp==0)
                                    os<<p.termArray[i].coef;
                            else if(p.termArray[i].exp!=0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef==-1)
                                            os<<"-x^"<<p.termArray[i].exp;
                                    else
                                            os<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                            }
                    }
                    else
                    {
                            if(p.termArray[i].exp!=0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"+x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef==-1)
                                            os<<"-x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef>1)
                                            os<<"+"<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef<0)
                                            os<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                            }
                            else if(p.termArray[i].exp==0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"+1";
                                    else if(p.termArray[i].coef==0)
                                            os<<"-1";
                                    else if(p.termArray[i].coef>1)
                                            os<<"+"<<p.termArray[i].coef;
                                    else if(p.termArray[i].coef<0)
                                            os<<p.termArray[i].coef;
                            }
                    }
            }
            os<<endl;
            return os;
    }
    Polynomial::Polynomial():capacity(4), terms(0)
    {
            termArray = new Term[capacity];
    }
    void Polynomial::NewTerm(const float theCoeff, const int theExp)
    {
            if(terms==capacity)
            {
                    capacity *= 2;
                    Term *temp = new Term[capacity];
                    copy(termArray, termArray+terms, temp);
                    delete [] termArray;
                    termArray = temp;
            }
            termArray[terms].coef = theCoeff;
            termArray[terms++].exp = theExp;
    }
    Polynomial Polynomial::operator+(Polynomial& b)
    {
            Polynomial c;
            int aPos = 0, bPos = 0;
            while((aPos<terms)&&(bPos<b.terms))
            {
                    if(termArray[aPos].exp==b.termArray[bPos].exp)
                    {
                            float t = termArray[aPos].coef+b.termArray[bPos].coef;
                            if(t) c.NewTerm(t, termArray[aPos].exp);
                            aPos++; bPos++;
                    }
                    else if(termArray[aPos].exp<b.termArray[bPos].exp)
                    {
                            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                            bPos++;
                    }
                    else
                    {
                            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                            aPos++;
                    }
            }
            for(; aPos<terms;aPos++)
                    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            for(; bPos<terms;bPos++)
                    c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            return c;

    }

</code>

### $ cat hw2b.cpp
 
<code>

    #include<iostream>
    using namespace std;
    #include "polyb.h"
    int main()
    {
            Polynomial p1, p2, p3;

            cin>>p1>>p2;
            p3=p1*p2;
            cout<<p1<<p2<<p3;
    }
    //결과 : 3x^13+2x^11-21x^10-21x^8-2x^6+19x^5-2x^3+12

</code>

### $ cat polyb.h
 
<code>

    #ifndef POLYNOMIAL_H
    #define POLYNOMIAL_H
    using namespace std;

    struct Term
    {
            float coef;
            int exp;
    };
    class Polynomial
    {
            public:
                    Polynomial();
                    Polynomial operator+(Polynomial&);
                    Polynomial operator*(Polynomial&);
                    void NewTerm(const float, const int);
            friend ostream& operator<<(ostream&, Polynomial&);
            friend istream& operator>>(istream&, Polynomial&);
            private:
                    Term *termArray;
                    int capacity;
                    int terms;
    };
    #endif

</code>

### $ cat polyb.cpp
 
<code>

    #include <iostream>
    #include "polyb.h"
    using namespace std;

    istream& operator>> (istream& is, Polynomial& p)
    {
            int noofterms; float coef; int exp;
            is >> noofterms;
            for(int i=0; i<noofterms; i++)
            {
                    is >> coef >> exp;
                    p.NewTerm(coef, exp);
            }
            return is;
    }
    ostream& operator<< (ostream& os, Polynomial& p)
    {
            for(int i=0; i<p.terms; i++)
            {
                    if(i==0)
                    {
                            if(p.termArray[i].exp==0)
                                    os<<p.termArray[i].coef;
                            else if(p.termArray[i].exp!=0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef==-1)
                                            os<<"-x^"<<p.termArray[i].exp;
                                    else
                                            os<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                            }
                    }
                    else
                    {
                            if(p.termArray[i].exp!=0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"+x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef==-1)
                                            os<<"-x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef>1)
                                            os<<"+"<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                                    else if(p.termArray[i].coef<0)
                                            os<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
                            }
                            else if(p.termArray[i].exp==0)
                            {
                                    if(p.termArray[i].coef==1)
                                            os<<"+1";
                                    else if(p.termArray[i].coef==0)
                                            os<<"-1";
                                    else if(p.termArray[i].coef>1)
                                            os<<"+"<<p.termArray[i].coef;
                                    else if(p.termArray[i].coef<0)
                                            os<<p.termArray[i].coef;
                            }
                    }
            }
            os<<endl;
            return os;
    }
    Polynomial::Polynomial():capacity(4), terms(0)
    {
            termArray = new Term[capacity];
    }
    void Polynomial::NewTerm(const float theCoeff, const int theExp)
    {
            if(terms==capacity)
            {
                    capacity *= 2;
                    Term *temp = new Term[capacity];
                    copy(termArray, termArray+terms, temp);
                    delete [] termArray;
                    termArray = temp;
            }
            termArray[terms].coef = theCoeff;
            termArray[terms++].exp = theExp;
    }
    Polynomial Polynomial::operator+(Polynomial& b)
    {
            Polynomial c;
            int aPos=0, bPos=0;
            while((aPos<terms)&&(bPos<b.terms))
            {
                    if(termArray[aPos].exp==b.termArray[bPos].exp)
                    {
                            float t = termArray[aPos].coef+b.termArray[bPos].coef;
                            if(t) c.NewTerm(t, termArray[aPos].exp);
                            aPos++; bPos++;
                    }
                    else if(termArray[aPos].exp<b.termArray[bPos].exp)
                    {
                            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                            bPos++;
                    }
                    else
                    {
                            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                            aPos++;
                    }
            }
            for(; aPos<terms;aPos++)
                    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            for(; bPos<terms;bPos++)
                    c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            return c;
    }
    Polynomial Polynomial::operator*(Polynomial& b)
    {
            Polynomial c;
            int aPos = 0, bPos=0 ;
            for(;aPos<terms;aPos++)
            {
                    bPos=0;
                    for(;bPos<b.terms;bPos++)
                    {
                            float t = termArray[aPos].coef*b.termArray[bPos].coef;
                            int k = termArray[aPos].exp+b.termArray[bPos].exp;
                            int trueorfalse=0;
                            for(int i=0; i<c.terms;i++)
                            {
                                    if(c.termArray[i].exp==k)
                                    {
                                            c.termArray[i].coef=t+c.termArray[i].coef;
                                            trueorfalse=1;
                                            break;
                                    }
                            }
                            if(trueorfalse==0)
                                            c.NewTerm(t, k);
                    }
                    int tempcoef=0, tempexp=0;
                    for(int j=0; j<c.terms; j++)
                    {
                            for(int n=0; n<c.terms;n++)
                            {
                                    if(c.termArray[j].exp>c.termArray[n].exp)
                                    {
                                            tempcoef=c.termArray[n].coef;
                                            tempexp=c.termArray[n].exp;
                                            c.termArray[n].coef=c.termArray[j].coef;
                                            c.termArray[n].exp=c.termArray[j].exp;
                                            c.termArray[j].coef=tempcoef;
                                            c.termArray[j].exp=tempexp;
                                    }
                            }
                    }
            }
            for(; aPos<terms;aPos++)
                    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            for(; bPos<terms;bPos++)
                    c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            return c;
    }

</code>

### $ cat poly.dat

<code>

    3       3.0 5   2.0 3   -4.0 0
    4       1.0 8   -7.0 5  -1.0 3  -3.0 0

</code>
