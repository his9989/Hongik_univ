### $ cat makefile

<code>

    hw5a: hw5.o evala.o post.o
            g++ -o hw5a hw5.o evala.o post.o
    hw5b: hw5.o evalb.o post.o
            g++ -o hw5b hw5.o evalb.o post.o
    hw4: hw4.o post.o
            g++ -o hw4 hw4.o post.o
    hw4.o hw5.o post.o evala.o evalb.o: post.h

</code>

### $ cat hw4.cpp

<code>

    #include <iostream>
    #include "post.h"
    using namespace std;
    void PostFix(Expression);

    int main(){
            char linebuf[MAXLEN];
            while(cin.getline(linebuf, MAXLEN)){
                    Expression e(linebuf, true);
                    try {PostFix(e);}
                    catch(char const *msg){
                            cerr<<"Exception: "<<msg<<endl;}
            }
    }

</code>

### $ cat post.h
 
<code>

    #ifndef POSTFIX_H
    #define POSTFIX_H
    #define ID      257
    #define NUM     258
    #define EQ      259
    #define NE      260
    #define GE      261
    #define LE      262
    #define AND     263
    #define OR      264
    #define UMINUS  265
    #define MAXLEN  80
    #include <cstring>
    struct Expression{
            Expression(char* linebuf, bool inf=false)
                    : buf(linebuf), pos(0), len(strlen(buf)), infix(inf) {}
            char * buf;
            int pos;
            int len;
            bool infix;
    };

    struct Token{
            bool operator==(char);
            bool operator!=(char);
            Token();
            Token(char);
            Token(char, char, int);
            Token(char*, int, int);
            bool IsOperand();
            int type;
            char *str;
            int len;
            float val;
    };
    #endif

</code>

### $ cat post.cpp
 
<code>

    #include<iostream>
    #include<stack>
    #include "post.h"
    using namespace std;

    bool Token::operator==(char b)
            {return len==1 && str[0]==b;}
    bool Token::operator!=(char b)
            {return len!=1 || str[0]!=b;}

    Token::Token() {}
    Token::Token(char c): len(1), type(c)
            {str = new char[1]; str[0] = c;}
    Token::Token(char c, char c2, int ty): len(2), type(ty)
            {str = new char[2]; str[0] = c; str[1] = c2;}
    Token::Token(char *arr, int l, int ty=ID): len(l), type(ty){
            str = new char[len+1]; strcpy(str, arr);
            if(type==NUM){
                    val=str[0]-'0';
                    for (int i=1; i<len; i++)
                            val=val*10+str[i]-'0';
            }
            else if(type==ID) val=0;
            else throw "must be ID or NUM";
    }
    bool Token::IsOperand()
            {return type==ID||type==NUM;}
    ostream& operator<<(ostream& os, Token& t){
            if(t.type == UMINUS) os << "-u";
            else if (t.type==NUM) os<<t.val;
            else for(int i=0; i<t.len; i++)
                    os<<t.str[i];
            os<<" "; return os;
    }
    bool IsAlpha(char c)
            {return c>='a' && c<='z' || c>='A' && c<='Z';}
    bool IsDigit(char c)
            {return c>='0' && c<='9';}
    bool GetID(Expression& e, Token& tok){
            char arr[MAXLEN]; int idlen;
            char c=e.buf[e.pos];
            if(!IsAlpha(c)) return false;
            arr[0]=c; idlen=1;
            e.pos++;
            while(IsAlpha(c=e.buf[e.pos])||IsDigit(c))
                    {arr[idlen++]=c; e.pos++;}
            arr[idlen]='\0';
            char *arr2 = new char[idlen+1]; strcpy(arr2, arr);
            tok = Token(arr2, idlen, ID);
            return true;
    }
    bool GetNUM(Expression& e, Token& tok){
            char arr[MAXLEN]; int numlen;
            char c=e.buf[e.pos];
            if(!IsDigit(c)) return false;
            arr[0]=c; numlen=1;
            e.pos++;
            while(IsDigit(c=e.buf[e.pos])||IsAlpha(c)){
                    arr[numlen++]=c;
                    e.pos++;
            }
            arr[numlen]='\0';
            char *arr2 = new char[numlen+1]; strcpy(arr2, arr);
            tok = Token(arr2, numlen, NUM);
            return true;
    }
    void SkipBlanks(Expression& e){
            char c;
            while(e.pos<e.len&&((c=e.buf[e.pos])==' '||c=='\t'))
                    e.pos++;
    }
    bool TwoCharOp(Expression& e, Token& tok){
            char c=e.buf[e.pos];
            char c2=e.buf[e.pos+1];
            int op;
            if(c=='<' && c2=='=') op = LE;
            else if (c=='=' && c2=='=') op = EQ;
            else if (c=='!' && c2=='=') op = NE;
            else if (c=='>' && c2=='=') op = GE;
            else if (c=='&' && c2=='&') op = AND;
            else if (c=='|' && c2=='|') op = OR;
            else if (c=='-' && c2=='u') op = UMINUS;
            else return false;
            tok=Token(c, c2, op);
            e.pos+=2;
            return true;
    }
    bool OneCharOp(Expression& e, Token& tok){
            char c = e.buf[e.pos];
            if(c=='-' || c=='!' || c=='*' || c=='/' || c=='%'|| c=='+' || c=='<'|| c=='>'||c=='(' || c==')'||c=='=')
                    {tok = Token(c); e.pos++; return true;}
            return false;
    }
    Token NextToken(Expression& e){
            static bool opndFound = false;
            Token tok;
            SkipBlanks(e);
            if(e.pos==e.len) tok = Token('#');
            else if (GetID(e, tok) || GetNUM(e, tok)){}
            else if (TwoCharOp(e, tok)) {}
            else if (OneCharOp(e, tok)) {
                    if(e.infix && tok.type=='-' && !opndFound)
                            tok = Token('-', 'u', UMINUS);
            }
            else throw "Illegal Character Found";
            if (e.infix) opndFound = tok.IsOperand();
            return tok;
    }

    int icp(Token& t) {
            if(t.type=='(')
                    return 0;
            else if(t.type==265 || t.type=='!')
                    return 1;
            else if(t.type=='*' || t.type=='/' || t.type=='%')
                    return 2;
            else if(t.type=='+' || t.type=='-')
                    return 3;
            else if(t.type=='<' || t.type=='>' || t.type==261 || t.type==262)
                    return 4;
            else if(t.type==259 || t.type==260)
                    return 5;
            else if(t.type==263)
                    return 6;
            else if(t.type==264)
                    return 7;
            else if(t.type=='=')
                    return 8;
            else if(t.type=='#')
                    return 10;
    }
    int isp(Token& t) {
            if (t.type=='(')
                    return 9;
            else
                    return icp(t);
    }

    void PostFix(Expression e) {
            stack<Token> stack;
            stack.push('#');
            for(Token x=NextToken(e); x!='#'; x=NextToken(e)){
                    if(x.IsOperand())
                            cout<<x;
                    else if(x==')'){
                            for(;stack.top() !='('; stack.pop())
                                    cout<<stack.top();
                            stack.pop();
                    }
                    else {
                            for(; isp(stack.top())<=icp(x); stack.pop())
                                    cout<<stack.top();
                            stack.push(x);
                    }
            }
            while(stack.top()!='#'){
                    cout<<stack.top();
                    stack.pop();
            }
            stack.pop();
            cout<<endl;
    }

</code>

### $ cat hw5.cpp

<code>

    #include<iostream>
    #include "post.h"
    using namespace std;
    void Eval(Expression);
    //void PostFix(Expression);

    int main(void){
            char line[MAXLEN];
            while (cin.getline(line, MAXLEN)){
                    Expression e(line);
                    try{
    //                      PostFix(e);
                            Eval(e);
                    }
                    catch (char const *msg){
                            cerr << "Exception: "<< msg <<endl;
                    }
            }
    }

</code>

### $ cat evala.cpp
 
<code>

    #include<iostream>
    #include<stack>
    #include "post.h"
    using namespace std;

    ostream& operator<<(ostream&, Token&);
    Token NextToken(Expression&);

    float GetVal(Token& opnd)
    {
            if (opnd.type == NUM)
                    return opnd.val;
            return 0;
    }

    Token UnaryOp(int op, Token& x)
    {
            if(!x.IsOperand())
                    throw "Operand only for Unary Operator";
            Token tmp;
            tmp.type = NUM;
            if(op==UMINUS)
                    tmp.val = -GetVal(x);
            else if(op=='!')
                    tmp.val = !GetVal(x);
            else
                    throw "Invalid unary operator";
            return tmp;
    }

    Token BinaryOp(int op, Token& left, Token& right)
    {
            if(!left.IsOperand() || !right.IsOperand())
                    throw "Two Operands required for Binary Operation";
            Token tmp;
            tmp.type = NUM;
            float val1 = GetVal(left), val2 = GetVal(right);
            if(op=='+')
                    tmp.val=val1+val2;
            else if(op=='-')
                    tmp.val=val1-val2;
            else if(op=='*')
                    tmp.val=val1*val2;
            else if(op=='/')
                    tmp.val=val1/val2;
            else if(op=='<')
                    tmp.val=val1<val2;
            else if(op=='>')
                    tmp.val=val1>val2;
            else if(op==GE)
                    tmp.val=val1>=val2;
            else if(op==LE)
                    tmp.val=val1<=val2;
            else if(op==EQ)
                    tmp.val=val1==val2;
            else if(op==NE)
                    tmp.val=val1!=val2;
            else if(op==AND)
                    tmp.val=val1&&val2;
            else if(op==OR)
                    tmp.val=val1||val2;
            else if(op=='=')
                    throw "Assignment Not Yet Implemented";
            else
                    throw "No such binary operator";
            return tmp;
    }

    void Eval(Expression e)
    {
            stack<Token> stack;
            Token opnd1, opnd2;
            for(Token x = NextToken(e); x!='#'; x=NextToken(e))
            {
                    if(x.IsOperand())
                            stack.push(x);
                    else
                    {
                            int op = x.type;
                            if(op==UMINUS|| op=='!')
                            {
                                    opnd1=stack.top();
                                    stack.pop();
                                    stack.push(UnaryOp(op, opnd1));
                            }
                            else
                            {
                                    opnd2 = stack.top();
                                    stack.pop();
                                    opnd1=stack.top();
                                    stack.pop();
                                    stack.push(BinaryOp(op, opnd1, opnd2));
                            }
                    }
            }
                    cout<<stack.top()<<endl;
                    stack.pop();
    }

</code>

### $ cat evalb.cpp
 
<code>

    #include<iostream>
    #include<stack>
    #include<map>
    #include"post.h"
    using namespace std;

    ostream& operator<<(ostream&, Token& );
    Token NextToken(Expression&);
    struct cmp_str
    {
            bool operator() (char const *a, char const *b)
            {
                    return strcmp(a, b) <0;
            }
    };

    map<char *, float, cmp_str> ST;
    map<char *, float, cmp_str>::iterator iter;

    float GetVal(Token& opnd)
    {
            if(opnd.type == NUM)
                    return opnd.val;
            else if(opnd.type == ID)
            {
                    iter = ST.find(opnd.str);
                    return iter->second;
            }
            else
                    return 0;
    }

    Token UnaryOp(int op, Token& x)
    {
            if(!x.IsOperand())
                    throw "Operand only for Unary Operator";
            Token tmp;
            tmp.type = NUM;
            if(op==UMINUS)
                    tmp.val = -GetVal(x);
            else if(op=='!')
                    tmp.val = !GetVal(x);
            else
                    throw "Invalid unary operator";
            return tmp;
    }

    Token BinaryOp(int op, Token& left, Token& right)
    {
            if(!left.IsOperand()||!right.IsOperand())
                    throw "Two Operands required for Binary Operation";
            Token tmp;
            tmp.type = NUM;
            float val1 = GetVal(left), val2 = GetVal(right);
            if(op=='+')
                    tmp.val=val1+val2;
            else if(op=='-')
                    tmp.val=val1-val2;
            else if(op=='*')
                    tmp.val=val1*val2;
            else if(op=='/')
                    tmp.val=val1/val2;
            else if(op=='<')
                    tmp.val=val1<val2;
            else if(op=='>')
                    tmp.val=val1>val2;
            else if(op==GE)
                    tmp.val=val1>=val2;
            else if(op==LE)
                    tmp.val=val1<=val2;
            else if(op==EQ)
                    tmp.val=val1==val2;
            else if(op==LE)
                    tmp.val=val1!=val2;
            else if(op==AND)
                    tmp.val=val1&&val2;
            else if(op==OR)
                    tmp.val=val1||val2;
            else if(op=='=' && left.type==ID)
            {
                    ST[left.str]=val2;
                    return left;
            }
            else
                    throw "No such binary operator";
            return tmp;
    }

    void Eval(Expression e)
    {
            stack<Token> stack;
            Token opnd1, opnd2;
            for(Token x= NextToken(e);x!='#'; x=NextToken(e))
            {
                    if(x.IsOperand())
                            stack.push(x);
                    else
                    {
                            int op = x.type;
                            if(op==UMINUS||op=='!')
                            {
                                    opnd1=stack.top();
                                    stack.pop();
                                    stack.push(UnaryOp(op, opnd1));
                            }
                            else
                            {
                                    opnd2=stack.top();
                                    stack.pop();
                                    opnd1=stack.top();
                                    stack.pop();
                                    stack.push(BinaryOp(op, opnd1, opnd2));
                            }
                    }
            }
            cout<<stack.top()<<endl;
            stack.pop();
    }

</code>

### $ cat infix.dat

<code>

    A*B*C
    -A+B-C+D
    A*-B+C
    (A+B)*D+E / (F+A*D)+C

</code>

### $ cat infix2.dat

<code>

    A && B || C || !(E>F)
    !(A&&!((B<C)||(C>D)))||(C<E)

</code>

### $ cat infix3.dat

<code>

    34*56+11/2
    1+2*3+ -4*2

</code>

### $ cat infix4.dat

<code>

    33+55*2
    an77 = 2+7*5
    b=2
    an77+b*2
    a+5

</code>

### $ cat symboltable.cpp
 
<code>

    #include<iostream>
    #include<map>
    #include"post.h"
    using namespace std;
    struct cmp_str
    {
            bool operator() (char const *a, char const *b)
                    {return strcmp(a, b) <0;}
    };

    map<char *, float, cmp_str> ST;

    void PrintValue(char *name)
    {
            map<char *, float, cmp_str>::iterator iter;
            iter=ST.find(name);
            if(iter==ST.end())
                    cout<<name<<" does not exist" <<endl;
            else
                    cout<<iter->first<<" "<<iter->second<<endl;
    }

    void StoreIntoST(char *name, float val)
    {
            map<char *, float, cmp_str>::iterator iter;
            iter = ST.find(name);
            if(iter!=ST.end())
                    ST.erase(name);
            ST[name]=val;
    }

    int main()
    {
            StoreIntoST((char *)"abro", 23);
            StoreIntoST((char *)"bb", 34.5);
            StoreIntoST((char *)"haha", 99);

            StoreIntoST((char *)"bb", 1234.5);

            PrintValue((char *)"bb");
            PrintValue((char *)"haha");
            PrintValue((char *)"hoho");
    }

</code>
