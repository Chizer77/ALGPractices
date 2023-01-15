//输入整数n，表示有编号为0~n-1的木块，分别放在顺序排列编号为0~n-1的位置。
//设a和b是木块块号。现对这些木块进行操作，操作指令有如下四种：
//move a onto b：把a、b上的木块放回各自原来的位置，再把a放到b上；
//move a over b：把a上的木块放回各自的原来的位置，再把a放到包含了b的堆上；
//pile a onto b：把b上的木块放回各自的原来的位置，再把a以及在a上面的木块放到b上；
//pile a over b：把a连同a上木块放到包含了b的堆上。
//当输入quit时，结束操作并输出0~n-1位置上的木块情况。
//在操作指令中，如果a = b，其中a和b在同一堆块，则该操作指令是非法指令。非法指令要忽略，并且不应影响块的放置。

//输入
//输入的第一行给出一个整数n，表示木块的数目。本题设定0 < n < 25。
//然后给出一系列操作指令，每行一个操作指令。您的程序要处理所有命令直到遇到quit指令。
//本题设定，所有的操作指令都是上面给出的格式，不会有语法错误的指令。
//输出
//输出给出木块的最终状态。每个原始块位置i（0<=i<n，其中n是木块的数目）之后给出一个冒号。如果在这一位置至少有一个木块，则冒号后面输出一个空格，然后输出在该位置的一个木块列表，每个木块编号与其他块编号之间用空格隔开。在一行结束时不要在结尾加空格。
//每个块位置要有一行输出（也就是说，要有n行输出，其中n是第一行输入给出的整数）。

//来源：POJ 1208，UVA 101

#include<iostream>
#include<cstring>
#include<string>
using namespace std;

struct node {
    int data;
    struct node *next;
};

int main() {
    node *p, *q, *t, *head[30], *pa, *pb, *qa, *qb, *tt;    //链表 *head[i] 为位置 i 上木块的放置情况，按自下而上的顺序存储，结点a和结点b的指针分别为*pa, *pb;
                                                            //指向结点a和结点b的前驱的指针分别为*qa, *qb, 其他为辅助指针
    int i, j, d, n;
    cin >> n;
    for(i = 0; i < n; i++) {    //链表初始化
        p = (node*) malloc(sizeof (node));
        p->data = i;
        p->next = NULL;
        head[i] = p;
    }

    char aa[10], bb[10];    //命令类型aa（move, pile, quit），操作形态bb（onto, over）
    int a, b;
    getchar();  //忽略输入n后的回车
    while (cin >> aa) {
        qa = NULL;
        qb = NULL;
        if(strcmp("quit", aa) == 0) break;  //结束
        cin >> a >> bb >> b;
        if(a == b) continue;    //非法指令
        for(i = 0; i < n; i++) {    //找到a, b及其前驱的位置
            t = head[i];
            while (t != NULL) {
                if(t->data == a) pa = t;
                if(t->next != NULL && t->next->data == a) qa = t;
                if(t->data == b) pb = t;
                if(t->next != NULL && t->next->data == b) qb = t;
                t = t->next;
            }
        }

        //判别pa与pb是否在同一链表上,即是否非法
        node *ta, *tb;
        ta = pa;
        while (ta->next != NULL) ta = ta->next;
        tb = pb;
        while (tb->next != NULL) tb = tb->next;

        if(ta == tb) continue;  //非法指令

        if(strcmp("move", aa) == 0) {   //a点其上的结点都放回原来位置
            if(qa != NULL) { //a结点有前驱
                qa->next = NULL;
            }else { //a结点无前驱,则为head的头结点
                head[pa->data] = NULL;
            }
            t = pa->next;   //遍历a结点后的每个结点
            while (t != NULL) {
                head[t->data] = t;
                tt = t->next;   //保存t的下一个结点
                t->next = NULL;
                t = tt; //继续遍历
            }
            if(strcmp("onto", bb) == 0) {   //结点b也需进行相同操作,之后将a放至b后
                t = pb->next;   //遍历b后的每个结点
                while(t != NULL) {
                    head[t->data] = t;
                    tt = t->next;
                    t->next = NULL;
                    t = tt;
                }
                pb->next = pa;  //将a放至b后
                pa->next = NULL;
            }
            else {  //over，将a放至b链表尾
                t = pb;
                while (t->next != NULL) t = t->next;
                t->next = pa;
                pa->next = NULL;
            }
        }
        else {  //pile
            if(strcmp("onto", bb) == 0) {   //将b上的结点放回原来位置,再将a放置b后
                if(qa != NULL) qa->next = NULL;
                else head[pa->data] = NULL;
                t = pb->next;
                while (t != NULL) {
                    head[t->data] = t;
                    tt = t->next;
                    t->next = NULL;
                    t = tt;
                }
                pb->next = pa;
            }
            else {  //将a放置b链表尾
                if(qa != NULL) qa->next = NULL;
                else head[pa->data] = NULL;
                t = pb;
                while (t->next != NULL) t = t->next;
                t->next = pa;
            }
        }
    }

    //输出
    for(i = 0; i < n; i++) {
        cout << i << ':';
        if(head[i] != NULL) {
            t = head[i];
            while (t != NULL) {
                cout << ' ' << t->data;
                t = t->next;
            }
        }
        cout << '\n';
    }
}

