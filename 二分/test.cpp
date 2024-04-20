

//�߾��ȼӷ�
#include<iostream>
#include<vector>
using namespace std;

vector<int> add(vector<int>& A, vector<int>& B)
{
    //ͬ������һ��int������
    vector<int> c;
    //t���ڽ�λ
    int t = 0;
    //��һ��ѭ����
    for (int i = 0;i < A.size() || i < B.size();i++)
    {
        //��iС��A��size��ʱ��ֱ��+=t
        if (i < A.size()) t += A[i];
        //Ҳ���������ж�B
        if (i < B.size()) t += B[i];
        //��t���������c����֤c��һλ��
        c.push_back(t % 10);
        //����Ҫ��λ��ʮλ������һ��ѭ��
        t /= 10;
    }
    //������ѭ������֮��t��Ϊ�㣬֤�������һ����λ������ֱ��β��һ��1
    if (t) c.push_back(1);
    //����c
    return c;
}


int main()
{
    string a, b;//���ٱ����ĵ��ã�����ֱ�ӵ��ÿ⺯��size
    vector<int> A, B;//��������int���͵�����
    cin >> a >> b;

    //�����������Ŵ�ţ�����˳���ţ�ÿ�ν�λ����Ҫ�ƶ�Ԫ��
    //���ǰ��ŵ���ķ�ʽ��žͲ���Ҫ������λ������
    for (int i = a.size() - 1;i >= 0;i--)A.push_back(a[i] - '0');
    for (int i = b.size() - 1;i >= 0;i--)B.push_back(b[i] - '0');
    //��autoʶ�����ķ���ֵ��add��������λ���
    auto c = add(A, B);
    //���Ž�c���
    for (int i = c.size() - 1;i >= 0;i--) printf("%d", c[i]);
    return 0;
}

//�߾��ȼ���
// ��������������
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
        C.push_back((t + 10) % 10); // �϶�Ϊ1
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