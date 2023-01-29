#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int N=10005;

void getinit();
void gene_arr();
void sum_arr();
void printans();
void array2sum();
void sum2array();

long long priority(char op);
long long performOperation(long long a, long long b, char op);
long long evaluateExpression(string expression);

string equa;
long long mode,a[N],s[N],n;
bool iscalca[N],iscalcs[N];
string modewd[3]={"","an=","sn="};
int main()
{
    system("title 数列计算器V1.1 by TeacherLi");
    system("mode con cols=120 lines=30");
    system("color f0");
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                     数列计算器                                                     ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                    Version 1.1                                                     ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                   编写者：TeacherLi李信辉，部分代码来源于ChatGPT                                   ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                  https://github.com/TeacherLi07/Array-Calculator                                   ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                    按回车键继续                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"========================================================================================================================";
    getchar();
    system("cls");
L1:
    cout<<"========================================================================================================================"<<endl;
    cout<<"|| 使用说明：                                                                                                         ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 代数式用半角（英文）字符表示，支持加（+）减（-）乘（*）除（/）乘方（^），暂不支持根号。                            ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 数列某项以an表示，前n项和以sn表示，计算总项数最大为10000项。                                                       ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 序数下标如果有多项，请为下标打括号。                                                                               ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 合法表达例如：an；a(n+1)；a((3n+5)^2)；a114。                                                                      ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 乘方运算中，指数和底数如非单字母或纯数字，需要打括号。                                                             ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 表达式中n与x等价，大小写不敏感，不支持小数，可以用分数表示。                                                       ||"<<endl;
    cout<<"||                                                                                                                    ||"<<endl;
    cout<<"|| 如果输入非法或者无法计算，可能会有各种奇奇怪怪的现象，如果不确定是否为bug可以联系我或提交issue。                   ||"<<endl;
    cout<<"========================================================================================================================"<<endl<<endl;
    cout<<"计算模式：\n1.an表达式\n2.sn表达式\n表达式均可含有n、s、a\n请输入模式：";
    cin>>mode;
    cout<<"请输入"<<modewd[mode];
    cin>>equa;
    transform(equa.begin(),equa.end(),equa.begin(),::tolower);//处理大小写敏感问题，使用方法已注明
    for(long long i=0;i<equa.length();i++)//处理x和n问题，使用方法已注明
        equa[i]= equa[i]=='x' ? 'n' : equa[i];
    for(long long i=1;i<equa.length();i++)
        if((equa[i]=='n' || equa[i]=='a' || equa[i]=='s') && isdigit(equa[i-1]))
        {
            char whichsymbol=1;//判断xn前是什么符号
            for(long long j=i-1;j>=0;j--)
                if(!isdigit(equa[j]))
                {
                    whichsymbol=equa[j];
                    break;
                }
            if(whichsymbol=='+' || whichsymbol=='-' || whichsymbol=='*' || whichsymbol=='^' || whichsymbol==1)
                equa.insert(i,"*");
            else if(whichsymbol=='/')
                equa.insert(i,"/");
        }//处理多项式计算时，n、an、sn前系数无乘号问题，未处理乘方运算的优先级问题，所以在使用方法中已注明
    cout<<"是否有已知数据？如有请输入如“s1=1”，“a3=2”，一项一行，如无或输入完成请输入-1"<<endl;
    getchar();
    getinit();
    cout<<"请输入计算项数 ";
    cin>>n;
    if(mode==1)
        gene_arr();
    else if(mode==2)
        sum_arr();
    else{
        cout<<"未知模式，请重新输入"<<endl<<endl;
        goto L1;
    }
    printans();
    return 0;
}

void getinit()
{
    string init;
    while(1)
    {
        getline(cin,init);
        if(init=="-1")
            return;
        transform(init.begin(),init.end(),init.begin(),::tolower);
        long long val1 = 0,val2=0;
        long long i=1;
        while (i < init.length() && isdigit(init[i]))
        {
            val1 = (val1*10) + (init[i] - '0');
            i++;
        }
        i++;
        while (i < init.length() && isdigit(init[i]))
        {
            val2 = (val2*10) + (init[i] - '0');
            i++;
        }
        if(init[0]=='a')
        {
            a[val1]=val2;
            iscalca[val1]=1;
        }
        else if(init[0]=='s')
        {
           s[val1]=val2;
            iscalcs[val1]=1;
        }
    }
}

void gene_arr()
{
    sum2array();
    for(long long i=1;i<=n;i++)
    {
        if(iscalca[i])
            continue;
        string equan=equa;
        for(long long j=0;j<equan.length();j++)
        {
            if(equan[j]=='n')
            {
                equan.erase(j,1);
                equan.insert(j,to_string(i));
            }
        }
        a[i]=evaluateExpression(equan);
    }
    array2sum();
}

void sum_arr()
{
    array2sum();
    for(long long i=1;i<=n;i++)
    {
        if(iscalca[i])
            continue;
        string equan=equa;
        for(long long j=0;j<equan.length();j++)
        {
            if(equan[j]=='n')
            {
                equan.erase(j,1);
                equan.insert(j,to_string(i));
            }
        }
        s[i]=evaluateExpression(equan);
    }
    sum2array();
}

void array2sum()
{
    for(long long i=1;i<=n;i++)
        if(!iscalcs[i])
            s[i]=a[i]+s[i-1];
}

void sum2array()
{
    for(long long i=1;i<=n;i++)
        if(!iscalca[i])
            a[i]=s[i]-s[i-1];
}

void printans()
{
    cout<<"n\tan\tSn\t"<<endl;
    for(long long i=1;i<=n;i++)
        cout<<i<<"\t"<<a[i]<<"\t"<<s[i]<<"\t"<<endl;
    cout<<"计算完毕，";
    system("pause");
}

long long priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

long long performOperation(long long a, long long b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

long long evaluateExpression(string expression) {
    stack<long long> values;
    stack<char> operators;

    for (long long i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        else if (expression[i] == '(')
            operators.push(expression[i]);

        else if (isdigit(expression[i])) {
            long long val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val*10) + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(val);
        }

        else if (expression[i]=='a')
        {
            if (isdigit(expression[i+1]))
            {
                long long val=0;
                while (i < expression.length() && isdigit(expression[i])) 
                {
                    val = (val*10) + (expression[i] - '0');
                    i++;
                }
                values.push(a[val]);
            }
            else if (expression[i+1]=='(')
            {
                long long flag=0;
                while (i+flag < expression.length() && expression[i+flag]!=')') 
                {
                    flag++;
                }
                values.push(a[evaluateExpression(expression.substr(i+1,flag))]);
                i+=flag;
            }
        }

        else if (expression[i]=='s')
        {
            if (isdigit(expression[i+1]))
            {
                long long val=0;
                while (i < expression.length() && isdigit(expression[i])) 
                {
                    val = (val*10) + (expression[i] - '0');
                    i++;
                }
                values.push(s[val]);
            }
            else if (expression[i+1]=='(')
            {
                long long flag=0;
                while (i+flag < expression.length() && expression[i+flag]!=')') 
                {
                    flag++;
                }
                values.push(s[evaluateExpression(expression.substr(i+1,flag+1))]);
                i+=flag;
            }
        }

        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                long long val2 = values.top();
                values.pop();

                long long val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(performOperation(val1, val2, op));
            }

            if (!operators.empty())
                operators.pop();
        }

        else {
            while (!operators.empty() && priority(operators.top()) >= priority(expression[i])) {
                long long val2 = values.top();
                values.pop();

                long long val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(performOperation(val1, val2, op));
            }

            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        long long val2 = values.top();
        values.pop();

        long long val1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(performOperation(val1, val2, op));
    }

    return values.top();
}
