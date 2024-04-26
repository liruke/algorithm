#include<iostream>
using namespace std;
//确定数组的大小
const int N = 100000;
//一个存放值，一个存放下一个节点的下标
int e[N], ne[N];
//一个是下一个节点的索引，一个变量存储头节点
int idx, head;
//操作次数
int M;

void  Init()
{
    //零个节点的情况下我们的head等于-1，表示还没有任何节点
    head = -1;
    //idx定义为0，表示下一个节点的下标是0
    idx = 0;
}
//在头部插插入节点
void PushFront(int x)
{
    //更新新节点存储的值
    e[idx] = x;
    //新节点的下一个节点是原来的头结点
    ne[idx] = head;
    //更新头结点，为idx
    head = idx;
    //更新idx
    idx++;
}
//在第k个节点的后面插入一个数据
void Insert(int k, int x)
{
    //更新存储节点值的数组
    e[idx] = x;
    //准备插入的节点的下一个节点是k节点指向的下一个节点
    ne[idx] = ne[k];
    //k节点指向的下一个节点是idx
    ne[k] = idx;
    //更新idx
    idx++;
}
//删除第k个节点的后一个节点
void Earase(int k)
{
    //第k个节点的下一个节点是第k个节点的下下个节点
    ne[k] = ne[ne[k]];
}


int main()
{
    //初始化
    Init();
    //输入操作数
    cin >> M;
    while (M--)
    {
        int x, k;
        char op;
        //根据样例写一个ifelse
        cin >> op;
        if (op == 'H')
        {
            cin >> x;
            PushFront(x);
        }
        else if (op == 'D')
        {
            cin >> k;
            if (!k) head = ne[head];
            Earase(k - 1);
        }
        else
        {
            cin >> k >> x;
            Insert(k - 1, x);
        }
    }
    //输出数据
    for (int i = head;i != -1;i = ne[i])cout << e[i] << ' ';
    return 0;
}
#include<iostream>
using namespace std;
const int N = 100000;
int l[N], r[N], idx;
int e[N];

int m;

void Init()
{
    r[0] = 1;
    l[1] = 0;
    idx = 2;
}
void Push_Right(int k, int x)
{
    //赋值
    e[idx] = x;
    //idx的右边是k节点的右边的节点
    r[idx] = r[k];
    //idx的左边是k
    l[idx] = k;
    //k的右边的指向的左边是idx
    l[r[k]] = idx;
    //k指向的右边是idx
    r[k] = idx;
    //idx++；
    idx++;
}

void Earase(int k)
{
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}

int main()
{
    cin >> m;
    Init();
    while (m--)
    {
        int k = 0, x = 0;
        string op;
        cin >> op;
        //在零的右边插入
        if (op == "L")
        {
            cin >> x;
            Push_Right(0, x);
        }
        //在1的左边插入，1代表最后一个节点，所以只需要在最后一个节点的左边插入
        else if (op == "R")
        {
            cin >> x;
            Push_Right(l[1], x);
        }
        //删除，因为idx是从2开始的，他是删除第k个节点，存值的节点是从2开始，所以删除第k个
        //实际是删除第k+1个
        else if (op == "D")
        {
            cin >> k;
            Earase(k + 1);
        }
        //在第看个节点的左边插入，相当于在第k+1个节点的左边节点的右边插入一个值
        else if (op == "IL")
        {
            cin >> k >> x;
            Push_Right(l[k + 1], x);
        }
        //在右边插入，相当于就是在第k+1哥节点的右边插入一个数
        else if (op == "IR")
        {
            cin >> k >> x;
            Push_Right(k + 1, x);
        }
    }
    //打印，第一个节点是在0节点的右边开始，然后到1结束
    for (int i = r[0];i != 1;i = r[i])cout << e[i] << ' ';
    cout << endl;
    return 0;
}
#include<iostream>
using namespace std;
const int N = 100000;
//存储值的数组和存储下一个节点下标的数组
int e[N], ne[N];
//索引
int idx;
//操作数
int m;
void Init()
{
    //这里我们直接将idx置零
    idx = 0;
}
void Push(int x)
{
    e[idx] = x;
    idx++;
}
void Pop()
{
    idx--;
}

bool Empty()
{
    return idx == 0;
}
int Query()
{
    return e[idx - 1];
}
int main()
{
    cin >> m;
    Init();
    while (m--)
    {
        string op;
        cin >> op;
        int x;
        if (op == "push")
        {
            cin >> x;
            Push(x);
        }
        else if (op == "pop")
        {
            Pop();
        }
        else if (op == "empty")
        {
            if (Empty())
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else if (op == "query")
        {
            cout << Query() << endl;
        }
    }
    return 0;
}
#include<iostream>
using namespace std;
const int N = 100000;
int head, idx, e[N], ne[N];
int tail;
int m;
void Init()
{
    head = -1;
    idx = 0;
    tail = -1;
    m = 0;
}

void Push(int x) {
    e[idx] = x;
    ne[idx] = -1; // 将新元素的下一个位置设置为 -1，表示末尾
    if (head == -1)
    {
        // 如果队列为空，将 head 和 tail 都设置为当前的 idx
        head = idx;
        tail = idx;
    }
    else
    {
        ne[tail] = idx; // 将当前的 tail 指向新元素的位置
        tail = idx; // 更新 tail
    }
    idx++;
}



void Pop()
{
    head = ne[head];
    if (head == -1)
    {
        tail = -1;
    }
}
bool Empty()
{
    return head == -1;
}
int Query()
{
    return e[head];
}
int main()
{
    Init();
    cin >> m;
    while (m--)
    {
        string op;
        cin >> op;
        int x;
        if (op == "push")
        {
            cin >> x;
            Push(x);
        }
        else if (op == "pop")
        {
            Pop();
        }
        else if (op == "empty")
        {
            if (Empty())
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else if (op == "query")
        {
            cout << Query() << endl;
        }
    }
    return 0;
}
