#include<iostream>
#

typedef int Type;

typedef struct _FibonacciNode
{
    Type   key;                     // 关键字(键值)
    int degree;                     // 度数
    struct _FibonacciNode* left;    // 左兄弟
    struct _FibonacciNode* right;   // 右兄弟
    struct _FibonacciNode* child;   // 第一个孩子节点
    struct _FibonacciNode* parent;  // 父节点
    int marked;                     //是否被删除第1个孩子(1表示删除，0表示未删除)
}FibonacciNode, FibNode;

typedef struct _FibonacciHeap {
    int   keyNum;                   // 堆中节点的总数
    int   maxDegree;                // 最大度
    struct _FibonacciNode* min;     // 最小节点(某个最小堆的根节点)
    struct _FibonacciNode** cons;   // 最大度的内存区域
}FibonacciHeap, FibHeap;

/*
 * 将"单个节点node"加入"链表root"之前
 *   a …… root
 *   a …… node …… root
 *
 * 注意： 此处node是单个节点，而root是双向链表
*/
static void fib_node_add(FibNode* node, FibNode* root)
{
    node->left = root->left;
    root->left->right = node;
    node->right = root;
    root->left = node;
}

/*
 * 将节点node插入到斐波那契堆heap中
 */
static void fib_heap_insert_node(FibHeap* heap, FibNode* node)
{
    if (heap->keyNum == 0)
        heap->min = node;
    else
    {
        fib_node_add(node, heap->min);
        if (node->key < heap->min->key)
            heap->min = node;
    }
    heap->keyNum++;
}

/*
 * 将双向链表b链接到双向链表a的后面
 *
 * 注意： 此处a和b都是双向链表
*/
static void fib_node_cat(FibNode* a, FibNode* b)
{
    FibNode* tmp;

    tmp = a->right;
    a->right = b->right;
    b->right->left = a;
    b->right = tmp;
    tmp->left = b;
}

/*
 * 将h1, h2合并成一个堆，并返回合并后的堆
 */
FibHeap* fib_heap_union(FibHeap* h1, FibHeap* h2)
{
    FibHeap* tmp;

    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    // 以h1为"母"，将h2附加到h1上；下面是保证h1的度数大，尽可能的少操作。
    if (h2->maxDegree > h1->maxDegree)
    {
        tmp = h1;
        h1 = h2;
        h2 = tmp;
    }

    if ((h1->min) == NULL)                // h1无"最小节点"
    {
        h1->min = h2->min;
        h1->keyNum = h2->keyNum;
        free(h2->cons);
        free(h2);
    }
    else if ((h2->min) == NULL)           // h1有"最小节点" && h2无"最小节点"
    {
        free(h2->cons);
        free(h2);
    }                                   // h1有"最小节点" && h2有"最小节点"
    else
    {
        // 将"h2中根链表"添加到"h1"中
        fib_node_cat(h1->min, h2->min);
        if (h1->min->key > h2->min->key)
            h1->min = h2->min;
        h1->keyNum += h2->keyNum;
        free(h2->cons);
        free(h2);
    }

    return h1;
}

void fib_node_remove(FibNode* node)
{

}
/*
 * 将node链接到root根结点
 */
static void fib_heap_link(FibHeap* heap, FibNode* node, FibNode* root)
{
    // 将node从双链表中移除
    fib_node_remove(node);
    // 将node设为root的孩子
    if (root->child == NULL)
        root->child = node;
    else
        fib_node_add(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = 0;
}

int LOG2(int x)
{

}
/*
 * 创建fib_heap_consolidate所需空间
 */
static void fib_heap_cons_make(FibHeap* heap)
{
    int old = heap->maxDegree;

    // 计算log2(x)，"+1"意味着向上取整！
    // ex. log2(13) = 3，向上取整为3+1=4。
    heap->maxDegree = LOG2(heap->keyNum) + 1;

    // 如果原本空间不够，则再次分配内存
    if (old >= heap->maxDegree)
        return;

    // 因为度为heap->maxDegree可能被合并，所以要maxDegree+1
    heap->cons = (FibNode**)realloc(heap->cons,
        sizeof(FibHeap*) * (heap->maxDegree + 1));
}

/*
 * 合并斐波那契堆的根链表中左右相同度数的树
 */

FibNode* fib_heap_remove_min(FibHeap* heap)
{

}
static void fib_heap_consolidate(FibHeap* heap)
{
    int i, d, D;
    FibNode* x, * y, * tmp;

    fib_heap_cons_make(heap);//开辟哈希所用空间
    D = heap->maxDegree + 1;

    for (i = 0; i < D; i++)
        heap->cons[i] = NULL;

    // 合并相同度的根节点，使每个度数的树唯一
    while (heap->min != NULL)
    {
        x = fib_heap_remove_min(heap);    // 取出堆中的最小树(最小节点所在的树)
        d = x->degree;                    // 获取最小树的度数
        // heap->cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (heap->cons[d] != NULL)
        {
            y = heap->cons[d];            // y是"与x的度数相同的树" 
            if (x->key > y->key)        // 保证x的键值比y小
            {
                tmp = x;
                x = y;
                y = tmp;

            }
            fib_heap_link(heap, y, x);    // 将y链接到x中
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;

    // 将heap->cons中的结点重新加到根表中
    for (i = 0; i < D; i++)
    {
        if (heap->cons[i] != NULL)
        {
            if (heap->min == NULL)
                heap->min = heap->cons[i];
            else
            {
                fib_node_add(heap->cons[i], heap->min);
                if ((heap->cons[i])->key < heap->min->key)
                    heap->min = heap->cons[i];
            }
        }
    }
}
/*
 * 移除最小节点，并返回移除节点后的斐波那契堆
 */
FibNode* _fib_heap_extract_min(FibHeap* heap)
{
    if (heap == NULL || heap->min == NULL)
        return NULL;

    FibNode* child = NULL;
    FibNode* min = heap->min;
    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (min->child != NULL)
    {
        child = min->child;
        fib_node_remove(child);
        if (child->right == child)
            min->child = NULL;
        else
            min->child = child->right;

        fib_node_add(child, heap->min);
        child->parent = NULL;
    }

    // 将min从根链表中移除
    fib_node_remove(min);
    // 若min是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(min->right)，然后再进行调节。
    if (min->right == min)
        heap->min = NULL;
    else
    {
        heap->min = min->right;
        fib_heap_consolidate(heap);
    }
    heap->keyNum--;

    return min;
}

/*
 * 将斐波那契堆heap中节点node的值减少为key
 */

void fib_heap_cut(FibHeap* heap, FibNode* node, FibNode* parent)
{

}

void fib_heap_cascading_cut(FibHeap* heap, FibNode* parent)
{

}

static void fib_heap_decrease(FibHeap* heap, FibNode* node, Type key)
{
    FibNode* parent;

    if (heap == NULL || heap->min == NULL || node == NULL)
        return;

    if (key >= node->key)
    {
        printf("decrease failed: the new key(%d) is no smaller than current key(%d)\n", key, node->key);
        return;
    }

    node->key = key;
    parent = node->parent;
    if (parent != NULL && node->key < parent->key)
    {
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    // 更新最小节点
    if (node->key < heap->min->key)
        heap->min = node;
}

/*
 * 将斐波那契堆heap中节点node的值增加为key
 */
static void fib_heap_increase(FibHeap* heap, FibNode* node, Type key)
{
    FibNode* child, * parent, * right;

    if (heap == NULL || heap->min == NULL || node == NULL)
        return;

    if (key <= node->key)
    {
        printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
        return;
    }

    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // 将child从node的子链表中删除
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // 将child添加到根链表中
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // 如果node不在根链表中，
    //     则将node从父节点parent的子链接中剥离出来，
    //     并使node成为"堆的根链表"中的一员，
    //     然后进行"级联剪切"
    // 否则，则判断是否需要更新堆的最小节点
    parent = node->parent;
    if (parent != NULL)
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
    else if (heap->min == node)
    {
        right = node->right;
        while (right != node)
        {
            if (node->key > right->key)
                heap->min = right;
            right = right->right;
        }
    }
}
/*
 * 将斐波那契堆heap中节点node的值增加为key
 */
static void fib_heap_increase(FibHeap* heap, FibNode* node, Type key)
{
    FibNode* child, * parent, * right;

    if (heap == NULL || heap->min == NULL || node == NULL)
        return;

    if (key <= node->key)
    {
        printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
        return;
    }

    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // 将child从node的子链表中删除
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // 将child添加到根链表中
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // 如果node不在根链表中，
    //     则将node从父节点parent的子链接中剥离出来，
    //     并使node成为"堆的根链表"中的一员，
    //     然后进行"级联剪切"
    // 否则，则判断是否需要更新堆的最小节点
    parent = node->parent;
    if (parent != NULL)
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
    else if (heap->min == node)
    {
        right = node->right;
        while (right != node)
        {
            if (node->key > right->key)
                heap->min = right;
            right = right->right;
        }
    }
}
/*
 * 删除结点node
 */
static void _fib_heap_delete(FibHeap* heap, FibNode* node)
{
    Type min = heap->min->key;
    fib_heap_decrease(heap, node, min - 1);
    _fib_heap_extract_min(heap);
    free(node);
}