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
string modewd[3]={"ͨ�ʽan=","ǰn��͹�ʽsn=","���ƹ�ʽan="};
int main()
{
    system("cls");
    cout<<"*****************************************************************"<<endl;
    cout<<"                           ���м�����"<<endl;
    cout<<"                       Version alhpa1.1"<<endl;
    cout<<"          ��д�ߣ�TeacherLi���Ż�,���ִ�����Դ��ChatGPT"<<endl;
    cout<<"*****************************************************************"<<endl<<endl;
    Sleep(1000);
L1:    cout<<"ʹ��˵����"<<endl<<endl;
    cout<<"����ʽ�ð�ǣ�Ӣ�ģ��ַ���ʾ,֧�ּӣ�+������-���ˣ�*)��(/)�˷�(^),�ݲ�֧�ָ��š�"<<endl<<endl;
    cout<<"����ĳ����an��ʾ��ǰn�����sn��ʾ���������������Ϊ100000�"<<endl<<endl;
    cout<<"�����±�����ж����Ϊ�±�����š�"<<endl<<endl;
    cout<<"�Ϸ�������磺an��a(n+1)��a((3n+5)^2)��a114��"<<endl<<endl;
    cout<<"�˷������У�ָ���͵�����ǵ���ĸ�����֣���Ҫ������"<<endl<<endl;
    cout<<"���ʽ��n��x�ȼۣ���Сд�����У���֧��С���������÷�����ʾ��"<<endl<<endl;
    cout<<"�������Ƿ������޷����㣬���ܻ��и�������ֵֹ����������ȷ���Ƿ�Ϊbug������ϵ�ң�"<<endl<<endl<<endl;
    cout<<"����ģʽ��\n1.��ͨ�ʽ�������\n2.��ǰn����������\n3.�ɵ��ƹ�ʽ�������\n������ģʽ��";
    cin>>mode;
    cout<<"������"<<modewd[mode-1];
    cin>>equa;
    transform(equa.begin(),equa.end(),equa.begin(),::tolower);//�����Сд�������⣬ʹ�÷�����ע��
    for(int i=0;i<equa.length();i++)//����x��n���⣬ʹ�÷�����ע��
        equa[i]= equa[i]=='x' ? 'n' : equa[i];
    for(int i=1;i<equa.length();i++)
        if((equa[i]=='n' || equa[i]=='a' || equa[i]=='s') && isdigit(equa[i-1]))
        {
            char whichsymbol=1;//�ж�xnǰ��ʲô����
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
        }//�������ʽ����ʱ��n��an��snǰϵ���޳˺����⣬δ����˷���������ȼ����⣬������ʹ�÷�������ע��
    cout<<"������������� ";
    cin>>n;
    if(mode==1)
        gene_arr();
    // else if(mode==2)
    //     sum_arr();
    // else if(mode==3)
    //     rec_arr();
    else{
        cout<<"δ֪ģʽ������������"<<endl<<endl;
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
