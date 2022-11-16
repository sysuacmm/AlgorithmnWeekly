void swap(int &x,int &y){int t=x;x=y;y=t;}//交换函数 
int heap[N];//定义一个数组来存堆
int siz;//堆的大小 
void push(int x){//要插入的数 
    heap[++siz]=x;
    now=siz;
    //插入到堆底 
    while(now){//还没到根节点，还能交换 
        ll nxt=now>>1;//找到它的父亲 
        if(heap[nxt]>heap[now])swap(heap[nxt],heap[now]);//父亲比它大，那就交换 
        else break;//如果比它父亲小，那就代表着插入完成了 
        now=nxt;//交换 
    }
    return; 
}
void pop(){
    swap(heap[siz],heap[1]);siz--;//交换堆顶和堆底，然后直接弹掉堆底 
    int now=1;
    while((now<<1)<=siz){//对该节点进行向下交换的操作 
        int nxt=now<<1;//找出当前节点的左儿子 
        if(nxt+1<=siz&&heap[nxt+1]<heap[nxt])nxt++;//看看是要左儿子还是右儿子跟它换 
        if(heap[nxt]<heap[now])swap(heap[now],heap[nxt]);//如果不符合堆性质就换 
        else break;//否则就完成了 
        now=nxt;//往下一层继续向下交换 
    }
}
