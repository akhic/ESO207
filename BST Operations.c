#include <stdio.h>
struct interval{
    int low;
    int high;
};
struct node{
    struct node* par;
    struct node* left;
    struct node* right;
    int key;
    struct interval Int;
   
    int max;
};
struct tree{
  struct node* Tlow;
  struct node* Thigh;
};
struct node* Search(struct node* T,int k){
    struct node* x = T;
    while(x!=NULL){
        if(x->key==k){
            return x;
        }
        else if(x->key>k){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    return x;
}
struct node* Search_Parent(struct node* T, int k){
    if(T==NULL){
        return T;
    }
    struct node* x = T;
    struct node* p= x->par;
    while(x!=NULL){
        if(x->key==k){
            return x->par;
        }
        else if(x->key>k){
            p = x;
            x = x->left;
        }
        else{
            p = x;
            x = x->right;
        }
    }
    return p;
}
long int Maxx(int a,int b,int c){
    if(a>=b && a>=c){
        return a;
    } 
    else if(b>=a && b>=c){
        return b;
    }
    else{
        return c;
    }
}
void Ins(struct node** T,int k,struct interval I){
    // printf("%p",*T);
    // return;
    struct node* p = Search_Parent(*T,k);
    if(p==NULL){
        *T = (struct node*)malloc(sizeof(struct node));
        (*T)->key = k;
        (*T)->Int = I;
        
        (*T)->max = I.high;
        // printf("In");
        return;
    }
    if(p->key >k){
        struct node* n;
        n = (struct node*)malloc(sizeof(struct node));
        p->left = n;
        n->par = p;
        n->key = k;
        n->Int = I;
        
        n->max = I.high;
    }
    else{
        struct node* n;
        n = (struct node*)malloc(sizeof(struct node));
        p->right = n;
        n->par = p;
        n->key = k;
        n->Int = I;
        
        n->max = I.high;
    }
    struct node* x = p;
    while(x!= NULL){
        if(x->left ==NULL &&x->right !=NULL){
            
            if(x->max < x->right->max){
                x->max = x->right->max;
            }
        }
        else if(x->left !=NULL &&x->right ==NULL){
            
            if(x->max < x->left->max){
                x->max = x->left->max;
            }
        }
        else{
            
            x->max = Maxx(x->max,x->left->max,x->right->max);
        }
        x = x->par;
    }
    
}
void Insert(struct tree** T,struct interval I){
    struct node** Tl = &((*T)->Tlow);
    struct node** Th = &((*T)->Thigh);
    // if(*Tl!=NULL)
    // {
    //     printf("%d",(*Tl)->key);
    // }
    Ins(Tl,I.low,I);
    Ins(Th,I.high,I);
    // printf("%p",Tl);
    // if(Tl!=NULL)
    // {
    //     printf("HI");
    // }
    // printf("%d",(*Tl)->key);
}
void Transplant(struct node** Tr,struct node** ur,struct node** vr){
    struct node* T = *Tr;
    struct node* u = *ur;
    struct node* v = *vr;
    if(u->par==NULL){
        
        *Tr = *vr;
        
    }
    else if(u==u->par->left){
        u->par->left = v;
    }
    else{
        u->par->right = v;
    }
    if(v!=NULL){
        v->par = u->par;
    }
}
void Del(struct node** S,int k){
    struct node * T=(*S);
    struct node* z = Search(T,k);
    struct node* x;
  
    if(z->left==NULL){
        Transplant(S,&z,&(z->right));
        if(z->right == NULL){
            x = z->par;
        }
        else{
        x = z->right;
        }
    }
    else if(z->right ==NULL){
        Transplant(S,&z,&(z->left));
        x = z->left;
    }
    else{
        struct node* y = z->right;
        while(y->left!=NULL){
            y = y->left;
        }
        x = y->right;
        if(y->par!=z){
            x = y->par;
            Transplant(S,&y,&(y->right));
            y->right = z->right;
            y->right->par = y;
            
        }
        Transplant(S,&z,&y);
        y->left = z->left;
        y->left->par = y;
    }
   
    while(x!= NULL){
        if(x->left ==NULL &&x->right ==NULL){
           
            x->max = x->Int.high;
        }
        else if(x->left ==NULL &&x->right !=NULL){
            
            if(x->max < x->right->max){
                x->max = x->right->max;
            }
        }
        else if(x->left !=NULL &&x->right ==NULL){
            
            if(x->max < x->left->max){
                x->max = x->left->max;
            }
        }
        else{
            
            // printf("%p",x->max);/
            // printf("%d",x->left->max);
            // printf("%d",x->right->key);
            x->max = Maxx(x->max,x->left->max,x->right->max);
        }
        x = x->par;
    }
    
}
void Delete(struct tree** T,struct interval I){
    struct node** Tl = &((*T)->Tlow);
    struct node** Th = &((*T)->Thigh);
    struct node* a = Search(*Tl,I.low);
    struct node* b = Search(*Th,I.high);
    
    if(a==NULL||b==NULL||a->Int.high!= b->key){
        
        return;
    }
    Del(Tl,I.low);
    Del(Th,I.high);
}
struct interval find_max(struct node* T){
    struct node* x =T;
    while(x->right!=NULL){
        x = x->right;
    }
    return x->Int;
}
struct interval find_min(struct node* T){
    struct node* x =T;
    while(x->left!=NULL){
        x = x->left;
    }
    return x->Int;
}
struct node* Succ(struct node* T,int k){
    struct node* x = Search(T,k);
    if(x == NULL){
        return x;
    }
    if(x->right!=NULL){
        struct node* y = x->right;
        while(y->left!=NULL){
            y = y->left;
        }
        return y;
    }
    else{
        struct node* y = x->par;
        while(y!=NULL&&x == x->par->right){
            x = x->par;
            y = y->par;
        }
        return y;
        
    }
}
struct node* Interval_Search(struct node*T, struct interval I){
    struct node* x = T;
    while(x != NULL&&(I.high < x->Int.low||I.low > x->Int.high)){
        if(x->left!=NULL&& x->left->max >= I.low){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    return x;
}


int main(){
    int t;
    scanf("%d\n",&t);
    for(int i=0;i<t;i++){
        struct tree* T;
        T = (struct tree*)malloc(sizeof(struct tree));
        T->Thigh=NULL;
        T->Tlow=NULL;
        int n;
        scanf("%d\n",&n);
        for(int j=0;j<n;j++){
            char s[20];
            scanf("%s",s);
            
            if(s[0]=='+'){
                struct interval I;
                scanf("%d %d\n",&I.low,&I.high);
                
                Insert(&T,I);
                
            }
            
            else if(s[0]=='-'){
                struct interval I;
                scanf("%d %d\n",&I.low,&I.high);
                
                Delete(&T,I);
                
                
                
            }
            else if(s[0]=='m'&&s[1]=='a'){
                struct node* x = T->Thigh;
                if(x!=NULL){
                    struct interval I = find_max(x);
                    printf("[%d %d]\n",I.low,I.high);
                }
                else{
                    printf("INVALID\n");
                }
                
            }
            else if(s[0]=='m'&&s[1]=='i'){
                struct node* x = T->Tlow;
                if(x!=NULL){
                    struct interval I = find_min(x);
                    printf("[%d %d]\n",I.low,I.high);
                }
                else{
                    printf("INVALID\n");
                }
            }
            else if(s[0]=='h'){
                struct interval I;
                scanf("%d %d\n",&I.low,&I.high);
                struct node* x = Succ(T->Thigh,I.high);
                if(x==NULL){
                    printf("INVALID\n");
                }
                else{
                    printf("[%d %d]\n",x->Int.low,x->Int.high);
                } 
            }
            else if(s[0]=='l'){
                struct interval I;
                scanf("%d %d\n",&I.low,&I.high);
                struct node* x = Succ(T->Tlow,I.low);
                if(x==NULL){
                    printf("INVALID\n");
                }
                else{
                    printf("[%d %d]\n",x->Int.low,x->Int.high);
                }
                
            }
            else if(s[0]=='o'){
                 struct interval I;
                 scanf("%d %d\n",&I.low,&I.high);
                struct node* x = Interval_Search(T->Tlow,I);
                if(x != NULL){
                    printf("1\n");
                }
                else{
                    printf("0\n");
                }
            }
            else{
                printf("INVALID\n");
            }
            
            
        }
    }
    
}