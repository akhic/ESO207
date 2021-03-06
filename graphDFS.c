#include <stdio.h>
int u,v;
int flag=0;
struct node{
    int key;
    struct node* next;
    int color;
};
struct graph{
    int V;
    struct node* G;
};
int DFS_Visit(struct graph*Gp,int a){
    Gp->G[a-1].color = 1;
    struct node* x = Gp->G[a-1].next;
    while(x!=NULL){
        
        if(!Gp->G[x->key-1].color){
            if(x->key==v){
                flag =1;
            }
            DFS_Visit(Gp,x->key);
        }
        x = x->next;
    }
    Gp->G[a-1].color = 2;
    return flag;
}

int main(){
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;i++){
        int V;
        int E;
        scanf("%d\n%d\n",&V,&E);
        struct graph Gp;
        Gp.V = V;
        Gp.G = (struct node*)malloc(V*sizeof(struct node));
        for(int i=0;i<V;i++){
            Gp.G[i].key = i+1;
            Gp.G[i].color = 0;
        }
        for(int i=0;i<E;i++){
            int a,b;
            scanf("%d %d\n",&a,&b);
            struct node* A;
            A = (struct node*)malloc(sizeof(struct node));
            struct node* B;
            B = (struct node*)malloc(sizeof(struct node));
            A->key = b;
            B->key = a;
            if(Gp.G[a-1].next==NULL){
                
               Gp.G[a-1].next = A;
            }
            else{
                struct node* x = Gp.G[a-1].next;
                Gp.G[a-1].next = A;
                A->next = x;
            }
            if(Gp.G[b-1].next==NULL){
                Gp.G[b-1].next = B;
            }
            else{
               struct node* x = Gp.G[b-1].next;
                Gp.G[b-1].next = B;
                B->next = x; 
            }
            
        }
        scanf("%d %d\n",&u,&v);
        int a = DFS_Visit(&Gp,u);
        struct node* x = Gp.G[u-1].next;
        if(x->key==v){
            //printf("%d\n",x->key);
            Gp.G[u-1].next = x->next;
            x->next = NULL;
        }
        else{
            while(x->next->key!=v){
                x = x->next;
            }
            //printf("%d\n",x->next->key);
            struct node* y;
            y = x->next;
            x->next = y->next;
            y->next = NULL;
        }
        x = Gp.G[v-1].next;
        if(x->key==u){
            //printf("%d\n",x->key);
            Gp.G[v-1].next = x->next;
            x->next = NULL;
        }
        else{
            while(x->next->key!=u){
                x = x->next;
            }
            //printf("%d\n",x->next->key);
            
            struct node *y;
            y = x->next;
            x->next = y->next;
            y->next = NULL;
        }
        for(int i=0;i<V;i++){
            //Gp.G[i].key = i+1;
            Gp.G[i].color = 0;
        }
        flag = 0;
        int b = DFS_Visit(&Gp,u);
        if(b){
            printf("Not Bridge\n");
        }
        else{
            printf("Bridge\n");
        }
        
    }
}





