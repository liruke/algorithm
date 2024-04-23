#include<iostream>
using namespace std;
#define N 100010
//n个数据和m行
int n, m;
//定义一个数组和一个前缀和数组
int a[N], S[N];
//定义两个边界
int l, r;
int main()
{
    //输入
    cin >> n >> m;
    //输入
    for (int i = 1;i <= n;i++)cin >> a[i];
    //将前缀和的s[0]定义为0，这样方便求出第多少到第多少的和
    S[0] = 0;
    //根据公式求出前缀和
    for (int i = 1;i <= n;i++)
    {
        S[i] = S[i - 1] + a[i];
    }
    //根绝条件输出
    while (m)
    {
        cin >> l >> r;
        cout << S[r] - S[l - 1] << endl;
        m--;
    }
    return 0;
}
#include<iostream>
using namespace std;
#define N 1010
int n, m, q;
int a[N][N], s[N][N];

int main()
{
    cin >> n >> m >> q;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    while (q--)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1] << endl;
    }
    return 0;
}
int minSubArrayLen(int target, int* nums, int numsSize) {
    int* S = (int*)malloc(sizeof(int) * (numsSize + 1));
    S[0] = 0;
    for (int i = 1;i <= numsSize;i++)
    {
        S[i] = S[i - 1] + nums[i - 1];
    }
    int min = 0;
    int l = 0;
    int r = 1;
    while (r < numsSize + 1)
    {
        if (l == r)
        {
            if (S[l] >= target)
            {
                if (min > l || min == 0)
                    min = l;
            }
            r++;
        }
        else
        {
            if (S[r] - S[l] >= target)
            {
                if (min > r - l || min == 0)
                {
                    min = r - l;
                }
                l++;
            }
            else {
                r++;
            }
        }
    }

    return min;
}
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    //累乘
    int sum = 1;
    //记录零的个数
    int count = 0;
    for (int i = 0;i < numsSize;i++)
    {
        //不等于0就乘到累乘中
        if (nums[i] != 0)
        {
            sum *= nums[i];
        }
        //如果是0就count++
        if (nums[i] == 0)
        {
            count++;
        }
    }
    //将*returnSize的大小用数组大小赋值
    *returnSize = numsSize;
    //创建空间
    int* newnode = (int*)malloc(sizeof(int) * (*returnSize));
    if (count >= 2)
    {
        for (int i = 0;i < (*returnSize);i++)
        {
            newnode[i] = 0;
        }
    }
    else if (count == 0)
    {
        for (int i = 0;i < (*returnSize);i++)
        {
            newnode[i] = sum / nums[i];
        }
    }
    else
    {
        for (int i = 0;i < (*returnSize);i++)
        {
            if (nums[i] == 0)
            {
                newnode[i] = sum;
            }
            else
            {
                newnode[i] = 0;
            }
        }
    }
    return newnode;
}
