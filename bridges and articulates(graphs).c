#include <stdio.h>
int time = 0;
int num_bridges = 0;
struct node{
    int key;
    struct node* next;
    int color;
    int dis;
    int aug;
    int parent;
    int art;
};
struct graph{
    int V;
    struct node* G;
};
struct edge{
    int a1;
    int b1;
    
};
int min(int a,int b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}
void Merge_Sort(struct edge*A,int p, int r){
    if(r>p){
        int q = (r+p)/2;
        Merge_Sort(A,p,q);
        Merge_Sort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
void Merge(struct edge*A,int p,int q,int r){
    struct edge* L;
    L = (struct edge*)malloc((q-p+2)*sizeof(struct edge));
    struct edge* R;
    R = (struct edge*)malloc((r-q+1)*sizeof(struct edge));
    for(int i=0;i<q-p+1;i++){
        L[i] = A[p+i];
    }
    L[q-p+1].a1 = 100000;
    L[q-p+1].b1 = 100000;
    for(int i=0;i<r-q;i++){
        R[i] = A[q+1+i];
    }
    R[r-q].a1 = 100000;
    R[r-q].b1 = 100000;
    int i=0;
    int j=0;
    for(int k=p;k<=r;k++){
        if(L[i].a1<R[j].a1){
            A[k] = L[i];
            i++;
        }
        else if(L[i].a1>R[j].a1){
            A[k] = R[j];
            j++;
        }
        else{
            if(L[i].b1<R[j].b1){
            A[k] = L[i];
            i++;
            }
            else if(L[i].b1>R[j].b1){
            A[k] = R[j];
            j++;
            }
        }
    }
}
void DFS_Visit(struct graph*Gp,int a,struct edge* Ed){
    Gp->G[a].dis = time;
    Gp->G[a].aug = Gp->G[a].dis;
    time++;
    Gp->G[a].color = 1;
    int c=0;
    struct node* x = Gp->G[a].next;
    while(x!=NULL){
        
        if(!Gp->G[x->key].color){
            c++;
            Gp->G[x->key].parent = a;
            DFS_Visit(Gp,x->key,Ed);
            Gp->G[a].aug = min(Gp->G[a].aug,Gp->G[x->key].aug);
            if(Gp->G[a].parent>Gp->V-1&&c>1){
               Gp->G[a].art = 1; 
            }
            if(Gp->G[a].parent<Gp->V&&Gp->G[x->key].aug>=Gp->G[a].dis){
                Gp->G[a].art = 1;
                //printf("halo1\n");
                //printf("%d %d\n",Gp->G[x->key].aug,Gp->G[a].dis);
            }
            if(Gp->G[x->key].aug>Gp->G[a].dis){
                //printf("halo\n");
              if(x->key<a){
                Ed[num_bridges].a1 = x->key;
                Ed[num_bridges].b1 = a;
                num_bridges++;
              }
              else{
                Ed[num_bridges].b1 = x->key;
                Ed[num_bridges].a1 = a;
                num_bridges++;  
              }
            }
        }
        else{
            if(x->key!=Gp->G[a].parent){
                Gp->G[a].aug = min(Gp->G[a].aug,Gp->G[x->key].dis);
            } 
            else{
                //printf("SUB BRANCH");
            }
        }
        x = x->next;
    }
    Gp->G[a].color = 2;
    
}
int main(){
    int V,E;
    scanf("%d\n%d\n",&V,&E);
    struct graph Gp;
    Gp.V = V;
    Gp.G = (struct node*)malloc(V*sizeof(struct node));
    for(int i=0;i<V;i++){
            Gp.G[i].key = i;
            Gp.G[i].color = 0;
            Gp.G[i].art = 0;
            Gp.G[i].parent = V;
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
            if(Gp.G[a].next==NULL){
                
               Gp.G[a].next = A;
            }
            else{
                struct node* x = Gp.G[a].next;
                Gp.G[a].next = A;
                A->next = x;
            }
            if(Gp.G[b].next==NULL){
                Gp.G[b].next = B;
            }
            else{
               struct node* x = Gp.G[b].next;
                Gp.G[b].next = B;
                B->next = x; 
            }
            
        }
        struct edge* Ed;
        Ed = (struct edge*)malloc(E*sizeof(struct edge));
        // for(int i=0;i<E;i++){
        //     Ed->bridge=0;
        // }
        DFS_Visit(&Gp,0,Ed);
        int num=0;
        for(int i=0;i<V;i++){
            if(Gp.G[i].art){
                printf("%d ",i);
                num++;
            }
        }
        if(!num){
            printf("EMPTY\n");
        }
        printf("\n");
        Merge_Sort(Ed,0,num_bridges-1);
        for(int i=0;i<num_bridges;i++){
            printf("%d %d\n",Ed[i].a1,Ed[i].b1);
        }
        // for(int i=0;i<V;i++){
        //     printf("%d\n",Gp.G[i].aug);
        // }
        
}
