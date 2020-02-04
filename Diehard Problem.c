#include <stdio.h>
int cap1,cap2,cap3;
int req1,req2,req3;
int Is_Found = 0;
struct node{
  int key1;
  int key2;
  int key3;
  struct node* prev;
  struct node* next;
};
struct list{
    struct node* head;
    struct node* tail;
};
int Is_Empty(struct node* A){
    if(A->key1==0 && A->key2==0 && A->key3==0){
        return 1;
    }
    else{
        return 0;
    }
}
struct list* permute(struct node* A,int arr[cap1][cap2][cap3]){
    struct list* T;
    T = (struct list*)malloc(sizeof(struct list));
    T->head=NULL;
    T->tail=NULL;
    if(Is_Empty(A)){
        // printf("HI");
        return T;
    }
    struct node* H;
    H = (struct node*)malloc(sizeof(struct node));
    T->head = H;
    // printf("%p",T->head);
    // return NULL;
    struct node* curr = H;
    struct node* pre = NULL;
    if(A->key1!=0&&A->key2<cap2){
        if(A->key1+A->key2<=cap2){
            if(!arr[0][A->key1+A->key2][A->key3]){
                curr->key1 = 0;
                curr->key2 = A->key1+A->key2;
                arr[0][A->key1+A->key2][A->key3]++;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[A->key1+A->key2-cap2][cap2][A->key3]){
                curr->key1 = (A->key1+A->key2) - cap2;
                curr->key2 = cap2;
                arr[A->key1+A->key2-cap2][cap2][A->key3]++;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }
    if(A->key1!=0&&A->key3<cap3){
        if(A->key1+A->key3<=cap3){
            if(!arr[0][A->key2][A->key1+A->key3]){
                curr->key1 = 0;
                curr->key3 = A->key1+A->key3;
                arr[0][A->key2][A->key1+A->key3]++;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[A->key1+A->key3-cap3][A->key2][cap3]){
                curr->key1 = (A->key1+A->key3) - cap3;
                curr->key3 = cap3;
                arr[A->key1+A->key3-cap3][A->key2][cap3]++;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }
    if(A->key2!=0&&A->key3<cap3){
        if(A->key2+A->key3<=cap3){
            if(!arr[A->key1][0][A->key2+A->key3]){
                curr->key2 = 0;
                curr->key3 = A->key2+A->key3;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[A->key1][A->key2+A->key3-cap3][cap3]){
                curr->key2 = (A->key2+A->key3) - cap3;
                curr->key3 = cap3;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }

    }
    if(A->key2!=0&&A->key1<cap1){
        if(A->key2+A->key1<=cap1){
            if(!arr[A->key2+A->key1][0][A->key3]){
                curr->key2 = 0;
                curr->key1 = A->key2+A->key1;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[cap1][A->key2+A->key1-cap1][A->key3]){
                curr->key2 = (A->key2+A->key1) - cap1;
                curr->key1 = cap1;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }

    }
    if(A->key3!=0&&A->key1<cap1){
        if(A->key3+A->key1<=cap1){
            if(!arr[A->key1+A->key1][A->key2][0]){
                curr->key3 = 0;
                curr->key1 = A->key3+A->key1;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[cap1][A->key2][A->key1+A->key1-cap1]){
                curr->key3 = (A->key3+A->key1) - cap1;
                curr->key1 = cap1;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }

    }
    if(A->key3!=0&&A->key2<cap2){
        if(A->key3+A->key2<=cap2){
            if(!arr[A->key1][A->key2+A->key2][0]){
                curr->key3 = 0;
                curr->key2 = A->key3+A->key2;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
            }
        }
        else{
            if(!arr[A->key1][cap2][A->key2+A->key2-cap2]){
                curr->key3 = (A->key3+A->key2) - cap2;
                curr->key2 = cap2;
                struct node* H;
                H = (struct node*)malloc(sizeof(struct node));
                curr->next = H;
                H->prev = curr;
                curr = H;
                }    
        }

    }
    if(A->key1!=0){
        curr->key1 = 0;
        struct node* H;
            H = (struct node*)malloc(sizeof(struct node));
            curr->next = H;
            H->prev = curr;
            curr = H;
    }
    if(A->key2!=0){
        curr->key2 = 0;
        struct node* H;
            H = (struct node*)malloc(sizeof(struct node));
            curr->next = H;
            H->prev = curr;
            curr = H;
    }
    if(A->key3!=0){
        curr->key1 = 0;
        struct node* H;
            H = (struct node*)malloc(sizeof(struct node));
            curr->next = H;
            H->prev = curr;
            curr = H;
    }
    struct node* W = curr->prev;
    T->tail = W;
    free(curr);
    if(arr[req1][req2][req3]){
        Is_Found = 1;
    }
    
    
    
    } 
    // printf("%p",T->head);
    return T;   
}
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
	        Is_Found = 0;
	        scanf("%d %d %d\n",&req1,&req2,&req3);
	        arr[root->key1][root->key2][root->key3]++;
	        if(req1+req2+req3>root->key1+root->key2+root->key3||((root->key1>0&&root->key1<cap1)||(root->key2>0&&root->key2<cap2)||(root->key3>0&&root->key3<cap3))){
	            printf("IMPOSSIBLE\n");
	        }
	        else{
    	        int num_layers = 1;
    	        if(arr[req1][req2][req3]){
    	            printf("%d\n",num_layers);
    	        }
    	        else{
        	        struct list* l = permute(root,arr);
        	        struct node* k=l->head;
        	        while(k!=NULL)
        	        {
        	            printf("%p ",k);
        	            k=k->next;
        	        }
        	       // printf("%p",l->head);
        	        struct node* p = l->head;
        	        while(p!=NULL){
        	           // printf("%d %d %d\n",p->key1,p->key2,p->key3);
        	            p = p->next;
        	        }
        	        num_layers++;
        	        struct node* x = l->head;
        	           printf("%p %d %d %d\n",x,x->key1,x->key2,x->key3);
        	        struct node* a = x;
        	        struct node* pre;
        	       // while(!Is_Found)
        	        {
        	            num_layers++;
        	            x = a;
        	            struct list *l = permute(a,arr);
        	            x = x->next;
        	            a = l->head;
        	            
        	            pre = l->tail;
        	           // while(x!=NULL){
        	           printf("%p %d %d %d\n",x,x->key1,x->key2,x->key3);
        	                struct list* l1 = permute(x,arr);
        	               // printf("%p",l1->head);
        	               // pre->next = l1->head;
        	               // l1->head->prev = pre;
        	               // pre = l1->tail;
        	               // x = x->next;
        	       
        	                
        	           // }
        	            
    	            }
    	           // printf("%d\n",num_layers);
    	            
    	        }
	        }
	    }
	    
	}
	
}
//return 0;



