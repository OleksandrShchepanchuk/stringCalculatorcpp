#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
// #include <bits/stdc++.h>

using namespace std;
const int maxN = 100;
struct stack
{
    char elem[maxN];
    int top;     
};

struct Sstack
{
    string elem[maxN];
    int top;
};

void init(stack* stk);
void push(stack* stk, char a);
char pop(stack* stk);
bool is_empty1(stack* stk);
char check_last(stack* stk);
void init1(Sstack* stk);
void push1(Sstack* stk, string a);
string pop1(Sstack* stk);
bool is_empty2(Sstack* stk);
string check_last1(Sstack* stk);
void print_stack(stack* stk);
int prioritet(char a);
string getPostFix(string str);
string getPreFix(string str);
double PostFixCalc(string str);
void replace1(string& str, string& from, string &to);
double calc(double a, double b, char op);
void deleteEl(string *arr, int r, int &n);
void deleteSame(string *arr, int &n);
double PreFixCalc(string str);

int main()
{
    string str;
    getline(cin, str);
    
    cout << "Postfix" << endl;
    // cout << getPostFix(str) << endl;
    PostFixCalc(getPostFix(str));
    cout << "Prefix" << endl;
    string str2 = getPreFix(str);
    cout << str2 << endl;
    cout << PreFixCalc(str2) << endl;
    // cout << getPreFix(str) << endl;
    return 0;
}


string getPostFix(string str)
{
    stack* A= new stack;
    string strResult;
    init(A);
    // print_stack(A);
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    // cout << "isalpha "<< isalpha(str[0]) << endl;
    for (int i = 0; i < str.length(); i++)
    {

        if (((isdigit(str[i])  || isalpha(str[i])) || (str[i] == '-' && (i == 0 || (!isdigit(str[i-1]) && !isalpha(str[i-1]) && str[i-1] != ')' )))))
        {
            do 
            {
                strResult += str[i];
                i++;
            } while(isdigit(str[i]) || isalpha(str[i]));
            strResult += " ";
            i--;
        } else if (str[i] == '(')
        {
            push(A, str[i]);
        } else if (str[i] == ')')
        {
            while (true)
            {
                if (check_last(A) == '(') 
                {
                    pop(A);    
                    break;
                } 

                strResult += check_last(A);
                strResult += " ";
                pop(A);
                if (is_empty1(A))
                {
                    cout << "error" << endl;
                    break;
                }
            }
        } else if (prioritet(str[i]) > prioritet(check_last(A)))
        {
            push(A, str[i]);

        } else if (prioritet(str[i]) <= prioritet(check_last(A)))
        {
            do 
            {
                strResult += check_last(A);
                strResult += " ";
                pop(A);
                if (is_empty1(A)) break;
            } while (prioritet(str[i]) <= prioritet(check_last(A)));
            push(A, str[i]);
            // cout << str[i] << "  str[i];" << endl;
        }
    }
    while(!is_empty1(A))
    {
        strResult +=  check_last(A);
        strResult += " ";
        pop(A);
    }
    return strResult;
}

double PostFixCalc(string str)
{
    double result;
    Sstack *A = new Sstack;
    init1(A);
    string str1;
    string arr[100];
    double variables[100];
    int counter = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (isalpha(str[i]))
        {
            do
            {
                arr[counter] += str[i];
                i++;
            } while (str[i] != ' ');
            counter++;
        }
    }
    deleteSame(arr,counter);
    // cout << "counter = " << counter << endl; 
    for (int i = 0; i < counter; i++)
    {
        cout << arr[i] << "= ";
        cin >> str1;
        replace1(str,arr[i],str1);
    }
    cout << str << endl;
    // str = string(str.rbegin(),str.rend());
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) || (i !=  str.length()-1 && str[i] == '-' && isdigit(str[i+1]) ))
        {
            str1 = "";
            do 
            {
                str1 += str[i];
                i++;
            } while(isdigit(str[i]));
            i--;
            push1(A, str1);
        } else if (str[i] != ' ')
        {
            double a = stod(check_last1(A));
            pop1(A);
            double b = stod(check_last1(A));
            pop1(A);
            // cout <<"calc  "<< calc(a,b, str[i]) << endl;
            push1(A, to_string(calc(a,b, str[i])));
        }
    }
    cout << check_last1(A) << endl;
    result = stod(check_last1(A));
    return result;
}

double PreFixCalc(string str)
{
    double result;
    Sstack *A = new Sstack;
    init1(A);
    string str1;
    string arr[100];
    double variables[100];
    int counter = 0;
    str = string(str.rbegin(),str.rend());
    for (int i =str.length()-1; i >= 0; i--)
    {
        if (isalpha(str[i]))
        {
            do 
            {
                arr[counter] += str[i];
                i--;
            } while (str[i] != ' ' && i >=0);
            // arr[counter] = string( arr[counter].rbegin(), arr[counter].rend());
            counter++;
        }
    }
    deleteSame(arr,counter);
    for (int i = 0; i < counter; i++)
    {
        cout << arr[i] << "= ";
        cin >> str1;
        str = string(str.rbegin(),str.rend());
        // str1 = string(str1.rbegin(),str1.rend());
        // cout << str << endl;
        replace1(str,arr[i],str1);
        // cout << str << endl;
        str = string(str.rbegin(),str.rend());
    }
    // str = string(str.rbegin(),str.rend());
    // cout << str << endl;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) || (i !=  str.length()-1 && str[i] == '-' && isdigit(str[i-1]) ))
        {
            str1 = "";
            do 
            {
                str1 += str[i];
                i++;
            } while(isdigit(str[i]) || (i !=  str.length()-1 && str[i] == '-' && isdigit(str[i-1]) ));
            i--;
            str1 = string(str1.rbegin(),str1.rend());
            push1(A, str1);
            // cout << check_last1(A) << endl;
        } else if (str[i] != ' ')
        {
            double b = stod(check_last1(A));
            // cout << "b = " << b << endl;
            pop1(A);
            double a = stod(check_last1(A));
            // cout << "a = " << a << endl;
            pop1(A);
            // cout << "str[i] = " << str[i] << endl;
            // cout <<"calc  "<< calc(a,b, str[i]) << endl;
            push1(A, to_string(calc(a,b, str[i])));
        }
    }
    result = stod(check_last1(A));
    return result;
}

string getPreFix(string str)
{
    stack* A=new stack;
    string strResult;
    string str1 = "";
    init(A);
    print_stack(A);
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = string(str.rbegin(),str.rend());
    // cout << str << endl;
    // cout << "isalpha "<< isalpha(str[0]) << endl;
    for (int i = 0; i < str.length(); i++)
    {

        if (((isdigit(str[i])  || isalpha(str[i])) || (str[i] == '-' && (i == str.length()-1 || (!isdigit(str[i+1]) && !isalpha(str[i+1]) && str[i+1] != ')')))))
        {
            str1 = "";
            do 
            {
                str1 += str[i];
                i++;
            } while((isdigit(str[i]) || isalpha(str[i])) || ( (str[i] == '-' && (i == str.length()-1 || (!isdigit(str[i+1]) && !isalpha(str[i+1]) && (str[i+1] != ')') )))));
            // str1  = string(str1.rbegin(),str1.rend());
            strResult += str1;
            strResult += " ";
            i--;
        } else if (str[i] == ')')
        {
            push(A, str[i]);
        } else if (str[i] == '(')
        {
            while (true)
            {
                if (check_last(A) == ')') 
                {
                    pop(A);    
                    break;
                } 

                strResult += check_last(A);
                strResult += " ";
                pop(A);
                if (is_empty1(A))
                {
                    cout << "error" << endl;
                    break;
                }
            }
        } else if (prioritet(str[i]) >= prioritet(check_last(A)))
        {
            push(A, str[i]);

        } else if (prioritet(str[i]) < prioritet(check_last(A)))
        {
            do 
            {
                strResult += check_last(A);
                strResult += " ";
                pop(A);
                if (is_empty1(A)) break;
            } while (prioritet(str[i]) < prioritet(check_last(A)));
            push(A, str[i]);
            // cout << str[i] << "  str[i];" << endl;
        }
    }
    while(!is_empty1(A))
    {
        strResult +=  check_last(A);
        strResult += " ";
        pop(A);
    }
    strResult = string(strResult.rbegin(),strResult.rend());
    // string str2 = strResult;
    // strResult = "";
    // for (int i = 0; i < str2.length(); i++)
    // {
    //     str1 = "";
    //     while (str2[i] != ' ')
    //     {
    //         str1 += str2[i];
    //         i++;
    //     }
    //     i--;
    //     str1 = string(str1.rbegin(), str.rend());
    //     strResult +=  str1;
    //     strResult += " ";
    // }
    return strResult;
}

int prioritet(char a)
{
    if (a == '(') return 0;
    if (a == ')' || a == '+' || a == '-') return 1;
    if (a ==  '*' || a == '/') return 2;
    if (a == '^') return 3; 
    else return 0;
}

void init(stack* stk)
{
    stk->top = 0;

}

void init1(Sstack* stk)
{
    stk->top = 0;

}


void push(stack* stk, char a)
{
    if (stk->top >= maxN)
    {
        cout << "stack if full" << endl;
        return;
    }
    stk->elem[stk->top] = a;
    stk->top++;
}
void push1(Sstack* stk, string a)
{
    if (stk->top >= maxN)
    {
        cout << "stack if full" << endl;
        return;
    }
    stk->elem[stk->top] = a;
    stk->top++;
}


char pop(stack* stk)
{
    if (stk->top == 0)
    {
        // cout << "stack is empty" << endl;
        return 0;
    }
    char b = stk->elem[stk->top - 1];
    stk->top--;
    /*(*stk).top = 10;*/
    return b;
}

string pop1(Sstack* stk)
{
    if (stk->top == 0)
    {
        // cout << "stack is empty" << endl;
        return 0;
    }
    
    string b = stk->elem[stk->top - 1];
    stk->top--;
    /*(*stk).top = 10;*/
    return b;
}



bool is_empty1(stack* stk)
{
    if (stk->top == 0)
    {
        return true;
    }
    return false;
}

bool is_empty2(Sstack* stk)
{
    if (stk->top == 0)
    {
        return true;
    }
    return false;
}


char check_last(stack* stk)
{
    if (!is_empty1(stk))
    {
        char b = stk->elem[stk->top - 1];
        return b;
    }
    else return 0;
}

string check_last1(Sstack* stk)
{

    if (!is_empty2(stk))
    {
        string b = stk->elem[stk->top - 1];
        return b;
    }
    else return 0;
}


void print_stack(stack* stk)
{
    int n = stk->top;
    if (!is_empty1(stk))
    {
        while (n != 0)
        {
            cout << stk->elem[n - 1] << " ";
            n--;
        }
        cout << endl;
    }
}


void replace1(string &str, string& from, string& to)
{
    if (from.empty())
    {
        return;
    }
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

double calc(double a, double b, char op)
{
    if (op == '+')return a + b;
    if(op == '-') return b - a;
    if (op ==  '*' )return a*b;
    if (op == '/') return b/a;
    if (op== '^') return pow(b,a); 
    // else return 0;
}

void deleteEl(string *arr, int r, int &n)
{
    for (int i = r; i < n-1; i++)
    {
        arr[i] = arr[i+1];
    }
    n--;
}

void deleteSame(string *arr, int &n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                deleteEl(arr, j , n);
                i--;
            }
        }
    }
}