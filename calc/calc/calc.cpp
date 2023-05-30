#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Stack {
    char info;
    Stack* next;
};

int prioritet(char);
Stack* add(Stack*, char);
Stack* del(Stack*, char*);
void result(string, Stack*);
double mas[201];
char znach[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int kol;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Stack* begin=NULL;
    char ss;
    char a = ' ';
    string InStr, OutStr;
    cout << "Введите формулу: ";
    cin >> InStr;
    int len = InStr.size(), k;
    for (k = 0; k < len; k++) {
        ss = InStr[k];
        if (ss == '(')
            begin = add(begin, ss);
        if (ss == ')') {
            
            while ((begin->info) != '(') {
                begin = del(begin, &a);
                OutStr += a;
            }
            begin = del(begin, &a);
        }
        
        if (ss >= 'a' && ss <= 'z') {
            kol++;
            OutStr += ss;
        }
        
        if (ss=='*' or ss == '/' or ss == '+' or ss == '-' or ss == '^') {
            while (begin != NULL && prioritet(begin->info) >= prioritet(ss)) {
                begin = del(begin, &a);
                
                OutStr += a;
            }
            begin = add(begin, ss);
        }
    }
    
    while (begin != NULL) {
        begin = del(begin, &a);
        OutStr += a;
    }
    cout<<"ОПЗ: "<<OutStr << endl;
    
    
    char ch;
    cout << "Введите значения переменных: ";
    for (int i = 0; i < kol; i++) {
        ch = znach[i];
        cout << ch << " = ";
        cin>>mas[int(ch)];
    }
    result(OutStr, begin);
}

int prioritet(char a) {
    switch (a) {
    case '^': return 4;
    case '*': case '/': return 3;
    case '-': case '+': return 2;
    case '(': return 1;
    }
    return 0;
}


void result(string opz, Stack* begin) {
    begin = NULL;
    char ch, ch1 = ' ', ch2 = ' ';
    double op1 = 0, op2 = 0, rez = 0;
    char chr = 'z' + 1;
    for (int i = 0; i < opz.size(); i++) {
        ch = opz[i];
        cout << ch << endl;
        if (ch >= 'a' && ch <= 'z') {
            begin = add(begin, ch);
        }
        else {
            begin = del(begin, &ch1);
            begin = del(begin, &ch2);
            op1 = mas[int(ch1)];
            op2 = mas[int(ch2)];
            switch (ch) {
            case '+': rez = op2 + op1; break;
            case '-': rez = op2 - op1; break;
            case '*': rez = op2 * op1; break;
            case '/': rez = op2 / op1; break;
            case '^': rez = pow(op2, op1); break;
            }
            mas[int(chr)] = rez;
            begin = add(begin, chr);
            chr++;
        }
    }
    cout << "Результат: "<<rez;
    return ;
}

Stack* del(Stack* p, char* out) {
    Stack* t = p; 
    (*out) = p->info;
    p = p->next; 
    delete t; 
    return p; 
}

Stack* add(Stack* p, char in) {
    Stack* t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

