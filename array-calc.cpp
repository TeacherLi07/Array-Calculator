#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int N=10005;

void gene_arr();
void sum_arr();
void rec_arr();
void printans();
void array2sum();
void sum2array();

int priority(char op);
int performOperation(int a, int b, char op);
int evaluateExpression(string expression);

string equa;
int mode,a[N],s[N],n;
string modewd[3]={"通项公式an=","前n项和公式sn=","递推公式an="};
int main()
{
    system("cls");
    cout<<"*****************************************************************"<<endl;
    cout<<"                           数列计算器"<<endl;
    cout<<"                       Version alhpa1.1"<<endl;
    cout<<"          编写者：TeacherLi李信辉,部分代码来源于ChatGPT"<<endl;
    cout<<"*****************************************************************"<<endl<<endl;
    Sleep(1000);
L1:    cout<<"使用说明："<<endl<<endl;
    cout<<"代数式用半角（英文）字符表示,支持加（+）减（-）乘（*)除(/)乘方(^),暂不支持根号。"<<endl<<endl;
    cout<<"数列某项以an表示，前n项和以sn表示，计算总项数最大为100000项。"<<endl<<endl;
    cout<<"序数下标如果有多项，请为下标打括号。"<<endl<<endl;
    cout<<"合法表达例如：an；a(n+1)；a((3n+5)^2)；a114。"<<endl<<endl;
    cout<<"乘方运算中，指数和底数如非单字母或纯数字，需要打括号"<<endl<<endl;
    cout<<"表达式中n与x等价，大小写不敏感，不支持小数，可以用分数表示。"<<endl<<endl;
    cout<<"如果输入非法或者无法计算，可能会有各种奇奇怪怪的现象，如果不确定是否为bug可以联系我（"<<endl<<endl<<endl;
    cout<<"计算模式：\n1.由通项公式输出数列\n2.由前n项和输出数列\n3.由递推公式输出数列\n请输入模式：";
    cin>>mode;
    cout<<"请输入"<<modewd[mode-1];
    cin>>equa;
    transform(equa.begin(),equa.end(),equa.begin(),::tolower);//处理大小写敏感问题，使用方法已注明
    for(int i=0;i<equa.length();i++)//处理x和n问题，使用方法已注明
        equa[i]= equa[i]=='x' ? 'n' : equa[i];
    for(int i=1;i<equa.length();i++)
        if((equa[i]=='n' || equa[i]=='a' || equa[i]=='s') && isdigit(equa[i-1]))
        {
            char whichsymbol=1;//判断xn前是什么符号
            for(int j=i-1;j>=0;j--)
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
    cout<<"请输入计算项数 ";
    cin>>n;
    if(mode==1)
        gene_arr();
    // else if(mode==2)
    //     sum_arr();
    // else if(mode==3)
    //     rec_arr();
    else{
        cout<<"未知模式，请重新输入"<<endl<<endl;
        goto L1;
    }
    printans();
}

void gene_arr()
{
    for(int i=1;i<=n;i++)
    {
        string equan=equa;
        for(int j=0;j<equan.length();j++)
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
}

void array2sum()
{
    for(int i=1;i<=n;i++)
        s[i]=a[i]+s[i-1];
}

void sum2array()
{
    for(int i=1;i<=n;i++)
        a[i]=s[i]-s[i-1];
}

void printans()
{
    cout<<"n\tan\tSn\t"<<endl;
    for(int i=1;i<=n;i++)
        cout<<i<<"\t"<<a[i]<<"\t"<<s[i]<<"\t"<<endl;
    system("pause");
}

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

int performOperation(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

int evaluateExpression(string expression) {
    stack<int> values;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        else if (expression[i] == '(')
            operators.push(expression[i]);

        else if (isdigit(expression[i])) {
            int val = 0;
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
                int val=0;
                while (i < expression.length() && isdigit(expression[i])) 
                {
                    val = (val*10) + (expression[i] - '0');
                    i++;
                }
                values.push(a[val]);
            }
            else if (expression[i+1]=='(')
            {
                int flag=0;
                while (i+flag < expression.length() && expression[i+flag]!=')') 
                {
                    flag++;
                }
                values.push(a[evaluateExpression(expression.substr(i+1,flag+1))]);
                i+=flag;
            }
        }

        else if (expression[i]=='s')
        {
            if (isdigit(expression[i+1]))
            {
                int val=0;
                while (i < expression.length() && isdigit(expression[i])) 
                {
                    val = (val*10) + (expression[i] - '0');
                    i++;
                }
                values.push(s[val]);
            }
            else if (expression[i+1]=='(')
            {
                int flag=0;
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
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
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
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(performOperation(val1, val2, op));
            }

            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(performOperation(val1, val2, op));
    }

    return values.top();
}
