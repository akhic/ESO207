#include<stdio.h>
int cap1,cap2,cap3;
int req1,req2,req3;
int N = 100000;
struct node{
    int key1;
    int key2;
    int key3;
    int layer;
};
struct queue{
  struct node* Q;
  int head ;
  int tail ;
};
int IsFull(struct queue* Q){
    return ((Q->tail +1)%(N+1)==Q->head);
}
int IsEmpty(struct queue* Q){
    return (Q->head==Q->tail);
}
void Enqueue(struct queue* Q1,struct node x){
    if(IsFull(Q1)){
        return ;
    }
    else{
        Q1->Q[Q1->tail] = x;
        Q1->tail = (Q1->tail+1)%(N+1);
        return;
    }
}
struct node Dequeue(struct queue* Q1){
    struct node x;
    x = Q1->Q[Q1->head];
    Q1->head =(Q1->head+1)%(N+1);
    return x;
}
int BFS(struct node A,int arr[cap1+1][cap2+1][cap3+1]){
    if(req1>cap1||req2>cap2||req3>cap3){
        return 0;
    }
    int i = 1;
    struct queue Q1;
    Q1.Q = (struct node*)malloc(N*sizeof(struct node));
    Q1.head = 0;
    Q1.tail = 0;
    A.layer = 1;
    Enqueue(&Q1,A);
    while(!IsEmpty(&Q1)&&!arr[req1][req2][req3]){
        struct node x = Dequeue(&Q1);
        
        if(x.key1!=0&&x.key2<cap2){
            if(x.key1+x.key2<=cap2){
                if(!arr[0][x.key1+x.key2][x.key3]){
                    struct node a;
                    a.key1 = 0;
                    a.key2 = x.key1+x.key2;
                    a.key3 = x.key3;
                    a.layer = x.layer+1;
                    arr[0][x.key1+x.key2][x.key3] = a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[x.key1+x.key2-cap2][cap2][x.key3]){
                    struct node a;
                    a.key1 = x.key1+x.key2-cap2;
                    a.key2 = cap2;
                    a.key3 = x.key3;
                    a.layer = x.layer+1;
                    arr[x.key1+x.key2-cap2][cap2][x.key3] = a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key1!=0&&x.key3<cap3){
            if(x.key1+x.key3<=cap3){
                if(!arr[0][x.key2][x.key1+x.key3]){
                    struct node a;
                    a.key1 = 0;
                    a.key3 = x.key1+x.key3;
                    a.key2 = x.key2;
                    a.layer = x.layer+1;
                    arr[0][x.key2][x.key1+x.key3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[x.key1+x.key3-cap3][x.key2][cap3]){
                    struct node a;
                    a.key1 = x.key1+x.key3-cap3;
                    a.key3 = cap3;
                    a.key2 = x.key2;
                    a.layer = x.layer+1;
                    arr[x.key1+x.key3-cap3][x.key2][cap3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key2!=0&&x.key3<cap3){
            if(x.key2+x.key3<=cap3){
                if(!arr[x.key1][0][x.key2+x.key3]){
                    struct node a;
                    a.key2 = 0;
                    a.key3 = x.key2+x.key3;
                    a.key1 = x.key1;
                    a.layer = x.layer+1;
                    arr[x.key1][0][x.key2+x.key3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[x.key1][x.key2+x.key3-cap3][cap3]){
                    struct node a;
                    a.key2 = x.key2+x.key3-cap3;
                    a.key3 = cap3;
                    a.key1 = x.key1;
                    a.layer = x.layer+1;
                    arr[x.key1][x.key2+x.key3-cap3][cap3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key2!=0&&x.key1<cap1){
            if(x.key2+x.key1<=cap1){
                if(!arr[x.key2+x.key1][0][x.key3]){
                    struct node a;
                    a.key2 = 0;
                    a.key1 = x.key2+x.key1;
                    a.key3 = x.key3;
                    a.layer = x.layer+1;
                    arr[x.key2+x.key1][0][x.key3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[cap1][x.key2+x.key1-cap1][x.key3]){
                    struct node a;
                    a.key2 = x.key2+x.key1-cap1;
                    a.key1 = cap1;
                    a.key3 = x.key3;
                    a.layer = x.layer+1;
                    arr[cap1][x.key2+x.key1-cap1][x.key3]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key3!=0&&x.key1<cap1){
            if(x.key3+x.key1<=cap1){
                if(!arr[x.key3+x.key1][x.key2][0]){
                    struct node a;
                    a.key3 = 0;
                    a.key1 = x.key3+x.key1;
                    a.key2 = x.key2;
                    a.layer = x.layer+1;
                    arr[x.key3+x.key1][x.key2][0]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[cap1][x.key2][x.key3+x.key1-cap1]){
                    struct node a;
                    a.key3 = x.key3+x.key1-cap1;
                    a.key1 = cap1;
                    a.key2 = x.key2;
                    a.layer = x.layer+1;
                    arr[cap1][x.key2][x.key3+x.key1-cap1]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key3!=0&&x.key2<cap2){
            if(x.key3+x.key2<=cap2){
                if(!arr[x.key1][x.key3+x.key2][0]){
                    struct node a;
                    a.key3 = 0;
                    a.key2 = x.key3+x.key2;
                    a.key1 = x.key1;
                    a.layer = x.layer+1;
                    arr[x.key1][x.key3+x.key2][0]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
            else{
                if(!arr[x.key1][cap2][x.key3+x.key2-cap2]){
                    struct node a;
                    a.key3 = x.key3+x.key2-cap2;
                    a.key2 = cap2;
                    a.key1 = x.key1;
                    a.layer = x.layer+1;
                    arr[x.key1][cap2][x.key3+x.key2-cap2]=a.layer;
                    Enqueue(&Q1,a);
                    //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
                }
            }
        }
        if(x.key1!=0){
            if(!arr[0][x.key2][x.key3]){
                struct node a;
                a.key1 = 0;
                a.key2 = x.key2;
                a.key3 = x.key3;
                a.layer = x.layer+1;
                arr[0][x.key2][x.key3] = a.layer;
                Enqueue(&Q1,a);
                //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
            }
        }
        if(x.key2!=0){
            if(!arr[x.key1][0][x.key3]){
                struct node a;
                a.key2 = 0;
                a.key1 = x.key1;
                a.key3 = x.key3;
                a.layer = x.layer+1;
                arr[x.key1][0][x.key3] = a.layer;
                Enqueue(&Q1,a);
                //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
            }
        }
        if(x.key3!=0){
            if(!arr[x.key1][x.key2][0]){
                struct node a;
                a.key3 = 0;
                a.key1 = x.key1;
                a.key2 = x.key2;
                a.layer = x.layer+1;
                arr[x.key1][x.key2][0] = a.layer;
                Enqueue(&Q1,a);
                //printf("%d %d %d %d\n",a.key1,a.key2,a.key3,a.layer);
            }
        }
        
        
    }
    //printf("\n\n%d\n\n",arr[req1][req2][req3]);
    
    return arr[req1][req2][req3];
    
}
int main(){
	int t;
	scanf("%d\n", &t);
	for(int i=0;i<t;i++){
	    scanf("%d %d %d\n",&cap1,&cap2,&cap3);
	    struct node* root;
	    root = (struct node*)malloc(sizeof(struct node));
	    scanf("%d %d %d\n",&(root->key1),&(root->key2),&(root->key3));
	    int n;
	    scanf("%d\n",&n);
	    for(int j=0;j<n;j++){
	        int arr[cap1+1][cap2+1][cap3+1];
	        for(int q1=0;q1<cap1+1;q1++){
	            for(int q2=0;q2<cap2+1;q2++){
	                for(int q3=0;q3<cap3+1;q3++){
	                    arr[q1][q2][q3] = 0;
	                }
	            }
	        }
	        
	        scanf("%d %d %d\n",&req1,&req2,&req3);
	        arr[root->key1][root->key2][root->key3]++;
	       // if(req1+req2+req3>root->key1+root->key2+root->key3||((root->key1>0&&root->key1<cap1)||(root->key2>0&&root->key2<cap2)||(root->key3>0&&root->key3<cap3))){
	       //     printf("IMPOSSIBLE\n");
	       // }
	        //else{
	            int a = BFS(*root,arr);
	            
	            if(a){
	                printf("%d\n",a);
	            }
	            else{
	                printf("IMPOSSIBLE\n");
	            }
	        //}
	            
    	          
    	            
    	        
	   }
	    
	}
	    
}
	

