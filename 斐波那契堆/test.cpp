#include<iostream>
#

typedef int Type;

typedef struct _FibonacciNode
{
    Type   key;                     // �ؼ���(��ֵ)
    int degree;                     // ����
    struct _FibonacciNode* left;    // ���ֵ�
    struct _FibonacciNode* right;   // ���ֵ�
    struct _FibonacciNode* child;   // ��һ�����ӽڵ�
    struct _FibonacciNode* parent;  // ���ڵ�
    int marked;                     //�Ƿ�ɾ����1������(1��ʾɾ����0��ʾδɾ��)
}FibonacciNode, FibNode;

typedef struct _FibonacciHeap {
    int   keyNum;                   // ���нڵ������
    int   maxDegree;                // ����
    struct _FibonacciNode* min;     // ��С�ڵ�(ĳ����С�ѵĸ��ڵ�)
    struct _FibonacciNode** cons;   // ���ȵ��ڴ�����
}FibonacciHeap, FibHeap;

/*
 * ��"�����ڵ�node"����"����root"֮ǰ
 *   a ���� root
 *   a ���� node ���� root
 *
 * ע�⣺ �˴�node�ǵ����ڵ㣬��root��˫������
*/
static void fib_node_add(FibNode* node, FibNode* root)
{
    node->left = root->left;
    root->left->right = node;
    node->right = root;
    root->left = node;
}

/*
 * ���ڵ�node���뵽쳲�������heap��
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
 * ��˫������b���ӵ�˫������a�ĺ���
 *
 * ע�⣺ �˴�a��b����˫������
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
 * ��h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
 */
FibHeap* fib_heap_union(FibHeap* h1, FibHeap* h2)
{
    FibHeap* tmp;

    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    // ��h1Ϊ"ĸ"����h2���ӵ�h1�ϣ������Ǳ�֤h1�Ķ����󣬾����ܵ��ٲ�����
    if (h2->maxDegree > h1->maxDegree)
    {
        tmp = h1;
        h1 = h2;
        h2 = tmp;
    }

    if ((h1->min) == NULL)                // h1��"��С�ڵ�"
    {
        h1->min = h2->min;
        h1->keyNum = h2->keyNum;
        free(h2->cons);
        free(h2);
    }
    else if ((h2->min) == NULL)           // h1��"��С�ڵ�" && h2��"��С�ڵ�"
    {
        free(h2->cons);
        free(h2);
    }                                   // h1��"��С�ڵ�" && h2��"��С�ڵ�"
    else
    {
        // ��"h2�и�����"��ӵ�"h1"��
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
 * ��node���ӵ�root�����
 */
static void fib_heap_link(FibHeap* heap, FibNode* node, FibNode* root)
{
    // ��node��˫�������Ƴ�
    fib_node_remove(node);
    // ��node��Ϊroot�ĺ���
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
 * ����fib_heap_consolidate����ռ�
 */
static void fib_heap_cons_make(FibHeap* heap)
{
    int old = heap->maxDegree;

    // ����log2(x)��"+1"��ζ������ȡ����
    // ex. log2(13) = 3������ȡ��Ϊ3+1=4��
    heap->maxDegree = LOG2(heap->keyNum) + 1;

    // ���ԭ���ռ䲻�������ٴη����ڴ�
    if (old >= heap->maxDegree)
        return;

    // ��Ϊ��Ϊheap->maxDegree���ܱ��ϲ�������ҪmaxDegree+1
    heap->cons = (FibNode**)realloc(heap->cons,
        sizeof(FibHeap*) * (heap->maxDegree + 1));
}

/*
 * �ϲ�쳲������ѵĸ�������������ͬ��������
 */

FibNode* fib_heap_remove_min(FibHeap* heap)
{

}
static void fib_heap_consolidate(FibHeap* heap)
{
    int i, d, D;
    FibNode* x, * y, * tmp;

    fib_heap_cons_make(heap);//���ٹ�ϣ���ÿռ�
    D = heap->maxDegree + 1;

    for (i = 0; i < D; i++)
        heap->cons[i] = NULL;

    // �ϲ���ͬ�ȵĸ��ڵ㣬ʹÿ����������Ψһ
    while (heap->min != NULL)
    {
        x = fib_heap_remove_min(heap);    // ȡ�����е���С��(��С�ڵ����ڵ���)
        d = x->degree;                    // ��ȡ��С���Ķ���
        // heap->cons[d] != NULL����ζ����������(x��y)��"����"��ͬ��
        while (heap->cons[d] != NULL)
        {
            y = heap->cons[d];            // y��"��x�Ķ�����ͬ����" 
            if (x->key > y->key)        // ��֤x�ļ�ֵ��yС
            {
                tmp = x;
                x = y;
                y = tmp;

            }
            fib_heap_link(heap, y, x);    // ��y���ӵ�x��
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;

    // ��heap->cons�еĽ�����¼ӵ�������
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
 * �Ƴ���С�ڵ㣬�������Ƴ��ڵ���쳲�������
 */
FibNode* _fib_heap_extract_min(FibHeap* heap)
{
    if (heap == NULL || heap->min == NULL)
        return NULL;

    FibNode* child = NULL;
    FibNode* min = heap->min;
    // ��minÿһ������(���ӺͶ��ӵ��ֵ�)����ӵ�"쳲������ѵĸ�����"��
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

    // ��min�Ӹ��������Ƴ�
    fib_node_remove(min);
    // ��min�Ƕ���Ψһ�ڵ㣬�����öѵ���С�ڵ�ΪNULL��
    // �������öѵ���С�ڵ�Ϊһ���ǿսڵ�(min->right)��Ȼ���ٽ��е��ڡ�
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
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
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
        // ��node�Ӹ��ڵ�parent�а������������node��ӵ���������
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    // ������С�ڵ�
    if (node->key < heap->min->key)
        heap->min = node;
}

/*
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
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

    // ��nodeÿһ������(����������,����,...)����ӵ�"쳲������ѵĸ�����"��
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // ��child��node����������ɾ��
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // ��child��ӵ���������
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // ���node���ڸ������У�
    //     ��node�Ӹ��ڵ�parent���������а��������
    //     ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
    //     Ȼ�����"��������"
    // �������ж��Ƿ���Ҫ���¶ѵ���С�ڵ�
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
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
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

    // ��nodeÿһ������(����������,����,...)����ӵ�"쳲������ѵĸ�����"��
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // ��child��node����������ɾ��
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // ��child��ӵ���������
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // ���node���ڸ������У�
    //     ��node�Ӹ��ڵ�parent���������а��������
    //     ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
    //     Ȼ�����"��������"
    // �������ж��Ƿ���Ҫ���¶ѵ���С�ڵ�
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
 * ɾ�����node
 */
static void _fib_heap_delete(FibHeap* heap, FibNode* node)
{
    Type min = heap->min->key;
    fib_heap_decrease(heap, node, min - 1);
    _fib_heap_extract_min(heap);
    free(node);
}