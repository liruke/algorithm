//#include<iostream>
//#include<vector>
//using namespace std;
//
//int minSubArrayLen(int target, int* nums, int numsSize) {
//    int* S = new int[numsSize+1];
//    S[0] = 0;
//    for (int i = 1;i <= numsSize;i++)
//    {
//        S[i] = S[i - 1] + nums[i - 1];
//    }
//    int min = 0;
//    int l = 0;
//    int r = 1;
//    while (r < numsSize + 1)
//    {
//        if (l == r)
//        {
//            if (S[l] >= target)
//            {
//                if (min > l || min == 0)
//                    min = l;
//            }
//            r++;
//        }
//        else
//        {
//            if (S[r] - S[l] >= target)
//            {
//                if (min > r - l || min == 0)
//                {
//                    min = r - l;
//                }
//                l++;
//            }
//            else {
//                r++;
//            }
//        }
//    }
//
//    return min;
//}
//int main()
//{
//    int arr[] = { 1,2,3,4,5 };
//    int numsSize = sizeof(arr) / sizeof(arr[0]);
//    int target = 15;
//    int i = minSubArrayLen(target, arr, numsSize);
//    cout << i << endl;
//	return 0;
//}
#include<cstdlib>
#include<iostream>
using namespace std;
int* productExceptSelf(int* nums, int numsSize) {
    int sum = 1;
    for (int i = 0;i < numsSize;i++)
    {
        sum *= nums[i];
    }
    int* returnSize = (int*)malloc(sizeof(int) * numsSize);
    if (returnSize == NULL)
    {
        return NULL;
    }
    for (int i = 0;i < numsSize;i++)
    {
        returnSize[i] = sum / nums[i];
    }
    return returnSize;
}

int main()
{
    int nums[] = { 1,2,3,4 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int* newnode = productExceptSelf(nums, numsSize);
    for (int i = 0;i < numsSize;i++)
    {
        cout << newnode[i] << " ";
    }
    return 0;
}