#include<iostream>
using namespace std;
//ȷ������Ĵ�С
const int N = 100000;
//һ�����ֵ��һ�������һ���ڵ���±�
int e[N], ne[N];
//һ������һ���ڵ��������һ�������洢ͷ�ڵ�
int idx, head;
//��������
int M;

void  Init()
{
    //����ڵ����������ǵ�head����-1����ʾ��û���κνڵ�
    head = -1;
    //idx����Ϊ0����ʾ��һ���ڵ���±���0
    idx = 0;
}
//��ͷ�������ڵ�
void PushFront(int x)
{
    //�����½ڵ�洢��ֵ
    e[idx] = x;
    //�½ڵ����һ���ڵ���ԭ����ͷ���
    ne[idx] = head;
    //����ͷ��㣬Ϊidx
    head = idx;
    //����idx
    idx++;
}
//�ڵ�k���ڵ�ĺ������һ������
void Insert(int k, int x)
{
    //���´洢�ڵ�ֵ������
    e[idx] = x;
    //׼������Ľڵ����һ���ڵ���k�ڵ�ָ�����һ���ڵ�
    ne[idx] = ne[k];
    //k�ڵ�ָ�����һ���ڵ���idx
    ne[k] = idx;
    //����idx
    idx++;
}
//ɾ����k���ڵ�ĺ�һ���ڵ�
void Earase(int k)
{
    //��k���ڵ����һ���ڵ��ǵ�k���ڵ�����¸��ڵ�
    ne[k] = ne[ne[k]];
}


int main()
{
    //��ʼ��
    Init();
    //���������
    cin >> M;
    while (M--)
    {
        int x, k;
        char op;
        //��������дһ��ifelse
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
    //�������
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
    //��ֵ
    e[idx] = x;
    //idx���ұ���k�ڵ���ұߵĽڵ�
    r[idx] = r[k];
    //idx�������k
    l[idx] = k;
    //k���ұߵ�ָ��������idx
    l[r[k]] = idx;
    //kָ����ұ���idx
    r[k] = idx;
    //idx++��
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
        //������ұ߲���
        if (op == "L")
        {
            cin >> x;
            Push_Right(0, x);
        }
        //��1����߲��룬1�������һ���ڵ㣬����ֻ��Ҫ�����һ���ڵ����߲���
        else if (op == "R")
        {
            cin >> x;
            Push_Right(l[1], x);
        }
        //ɾ������Ϊidx�Ǵ�2��ʼ�ģ�����ɾ����k���ڵ㣬��ֵ�Ľڵ��Ǵ�2��ʼ������ɾ����k��
        //ʵ����ɾ����k+1��
        else if (op == "D")
        {
            cin >> k;
            Earase(k + 1);
        }
        //�ڵڿ����ڵ����߲��룬�൱���ڵ�k+1���ڵ����߽ڵ���ұ߲���һ��ֵ
        else if (op == "IL")
        {
            cin >> k >> x;
            Push_Right(l[k + 1], x);
        }
        //���ұ߲��룬�൱�ھ����ڵ�k+1��ڵ���ұ߲���һ����
        else if (op == "IR")
        {
            cin >> k >> x;
            Push_Right(k + 1, x);
        }
    }
    //��ӡ����һ���ڵ�����0�ڵ���ұ߿�ʼ��Ȼ��1����
    for (int i = r[0];i != 1;i = r[i])cout << e[i] << ' ';
    cout << endl;
    return 0;
}
#include<iostream>
using namespace std;
const int N = 100000;
//�洢ֵ������ʹ洢��һ���ڵ��±������
int e[N], ne[N];
//����
int idx;
//������
int m;
void Init()
{
    //��������ֱ�ӽ�idx����
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
    ne[idx] = -1; // ����Ԫ�ص���һ��λ������Ϊ -1����ʾĩβ
    if (head == -1)
    {
        // �������Ϊ�գ��� head �� tail ������Ϊ��ǰ�� idx
        head = idx;
        tail = idx;
    }
    else
    {
        ne[tail] = idx; // ����ǰ�� tail ָ����Ԫ�ص�λ��
        tail = idx; // ���� tail
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
