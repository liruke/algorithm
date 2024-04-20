

//高精度加法
#include<iostream>
#include<vector>
using namespace std;

vector<int> add(vector<int>& A, vector<int>& B)
{
    //同样创建一个int的容器
    vector<int> c;
    //t用于进位
    int t = 0;
    //用一个循环简化
    for (int i = 0;i < A.size() || i < B.size();i++)
    {
        //当i小于A的size的时候，直接+=t
        if (i < A.size()) t += A[i];
        //也可以这样判断B
        if (i < B.size()) t += B[i];
        //将t的余数存进c，保证c是一位数
        c.push_back(t % 10);
        //将需要进位的十位进入下一轮循环
        t /= 10;
    }
    //如果最后循环结束之后，t不为零，证明最后有一个进位，所以直接尾插一个1
    if (t) c.push_back(1);
    //返回c
    return c;
}


int main()
{
    string a, b;//减少变量的调用，可以直接调用库函数size
    vector<int> A, B;//创建两个int类型的容器
    cin >> a >> b;

    //将整个数倒着存放，按者顺序存放，每次进位都需要移动元素
    //但是按着倒序的方式存放就不需要考虑移位的问题
    for (int i = a.size() - 1;i >= 0;i--)A.push_back(a[i] - '0');
    for (int i = b.size() - 1;i >= 0;i--)B.push_back(b[i] - '0');
    //用auto识别后面的返回值，add函数负责按位相加
    auto c = add(A, B);
    //倒着将c输出
    for (int i = c.size() - 1;i >= 0;i--) printf("%d", c[i]);
    return 0;
}

//高精度减法
// 给定两个正整数
#include <iostream>
#include <vector>
using namespace std;
bool cmp(vector<int>& A, vector<int>& B)
{
    if (A.size() != B.size())
    {
        return A.size() > B.size();
    }
    for (int i = A.size() - 1; i >= 0; i--)
    {
        if (A[i] != B[i])
        {
            return A[i] > B[i];
        }
    }
    return true;
}

vector <int> sub(vector<int>& A, vector<int>& B)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++)
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10); // 合而为1
        if (t < 0)  t = 1;
        else t = 0;

    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main()
{
    string a, b;
    vector<int> A, B;
    cin >> a >> b;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    if (cmp(A, B))
    {
        auto C = sub(A, B);
        for (int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    }
    else
    {
        auto C = sub(B, A);
        printf("-");
        for (int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    }
    return 0;
}