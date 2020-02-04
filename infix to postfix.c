#include<stdio.h>
char postfix_exp[10000];
int len;
int counter=0;
int bracket_counter = 0;
struct stack {
    char* st;
    int top;
};
void Make_Empty(struct stack* S){
    S->top = 0;
    return ; 
}
int Is_Empty(struct stack* S){
    return S->top == 0;
}
void Push(struct stack* S,char x){
    S->st[S->top] = x;
    S->top = S->top+1;
    
}
char Top(struct stack* S){
    return S->st[S->top -1];
}
char Pop(struct stack* S){
    char val;
    val = S->st[S->top -1];
    S->top = S->top-1;
    return val;
}
int find_value(char* val){
    int ans=0;
    for(int i=0;i<length(val);i++){
        ans = ans*10 + (val[i] - '0');
    }
    return ans;
}
int length(char* exp){
    int i =0;
    while(exp[i]!='\0'){
        i++;
    }
    return i;
}
int Is_Expression(char* val){
    if(val[0] =='+'||val[0] =='-'||val[0] =='*'||val[0] =='/'||val[0] =='^'||val[0] =='%'||val[0] =='('||val[0] ==')' ){
        return 1;
    }
    else{
        return 0;
    }
}
int check_invalid(char* exp){
    char val[10];
    char prev[10];
    int i=0;
    prev[0] = 'a';
    
    while(i<len+1){
        int j=0;
        while(exp[i]!=' '&&exp[i]!='\0'){
            val[j] = exp[i];
            j++;
            i++;
        }
        val[j] = '\0';
        if(val[0]=='('){
            bracket_counter++;
            int yes=0;
            for(int l=i;l<len;l++){
                if(exp[l]==')'){
                    yes = 1;
                }
            }
            if(!yes){
                return 1;
            }
        }
        if(val[0]==')'){
            bracket_counter--;
        }
        if(prev[0]!='a'){
            if(!Is_Expression(prev)&&!Is_Expression(val)){
                return 1;
            }
            if(prev[0]=='('&&val[0]!='('&&Is_Expression(val)){
                return 1;
            }
            if(val[0] =='('&&!Is_Expression(prev)){
                return 1;
            }
            if(val[0] !='('&&prev[0]!= '('&&val[0] !=')'&&prev[0]!= ')'&&Is_Expression(prev)&&Is_Expression(val)){
                return 1;
            }
            if(prev[0]==')'&&!Is_Expression(val)){
                return 1;
            }
            if(val[0] ==')'&&prev[0]!= ')'&&Is_Expression(prev)){
                return 1;
            }
            if(prev[0] ==')'&&val[0]=='('){
                return 1;
            }
            if(prev[0] =='('&&val[0]==')'){
                return 1;
            }
            
        }
        else{
            if(prev[0]!='('&&Is_Expression(prev)){
                return 1;
            }
        }
        
        for(int t=0;t<=j;t++){
            prev[t] = val[t];
        }
        i++;
    }
    if(prev[0]!=')'&&Is_Expression(prev)){
        return 1;
    }
    if(bracket_counter!=0){
            return 1;
    }
    return 0;
    
    
    
}
int* tokenizer(char val){
    int* ans;
    ans =(int*)malloc(2*sizeof(int));
    if(val =='+'||val =='-'){
        ans[0] = 1;
        ans[1] = 1;
        
    }
    if(val =='*'){
        ans[0] = 2;
        ans[1] = 1;
        
    }
    if(val=='%'||val == '/'){
        ans[0] = 3;
        ans[1] = 1;
    }
    if(val=='^'){
        ans[0] = 4;
        ans[1] = 0;
    }
    if(val=='('){
        ans[0] = 0;
        ans[1] = 1;
        
    }
    if(val ==')')
    {
        ans[0] = 5;
        ans[1] = -1;
        
    }
    return ans;
    
}
void convert_postfix(char* exp){
    char val[10];
    int i = 0;
    struct stack S;
    S.st = (char*)malloc(len*sizeof(char));
    Make_Empty(&S);
    while(i<len+1){
        int j=0;
        while(exp[i]!=' '&&exp[i]!='\0'){
            val[j] = exp[i];
            j++;
            i++;
        }
        val[j] = '\0';
        //printf("%s\n",val);
        if(Is_Expression(val)){
            // if(val[0] =='('){
            //     bracket_counter++;
            // }
            // if(val[0]==')'){
            //     bracket_counter--;
            // }
            if(Is_Empty(&S)){
                Push(&S,val[0]);
            }
            else{
                char prev = Top(&S);
                int* token_this;
                int* token_prev;
                token_prev = tokenizer(prev);
                token_this = tokenizer(val[0]);
                //printf("%c %c\n",prev,val[0]);
                if(val[0] =='('){
                    Push(&S,val[0]);
                }
                else if(val[0] ==')'){
                    while(Top(&S)!='('){
                        char a = Pop(&S);
                        postfix_exp[counter++] = a;
                        postfix_exp[counter++] = ' ';
                    }
                    Pop(&S);
                }
                else if(token_this[0]<token_prev[0]){
                        //printf("%c %c ghusaa\n",prev,val[0]);
                        while(token_prev[0]>token_this[0]){
                            char a = Pop(&S);
                            postfix_exp[counter++] = a;
                            postfix_exp[counter++] = ' ';
                            prev = Top(&S);
                            token_prev = tokenizer(prev);
                            
                            
                        }
                        if(token_prev[0]==token_this[0]){
                            if(token_prev[1]){
                            char a = Pop(&S);
                            postfix_exp[counter++] = a;
                            postfix_exp[counter++] = ' ';
                            }
                            
                        }
                        Push(&S,val[0]);
                        
                    }
                else if(token_prev[0]==token_this[0]){
                    //printf("%c %c ghusaa11\n",prev,val[0]);
                        if(token_prev[1]){
                            char a = Pop(&S);
                            postfix_exp[counter++] = a;
                            postfix_exp[counter++] = ' ';
                            }
                            Push(&S,val[0]);
                            
                    }
                    else{
                        Push(&S,val[0]);
                    }
            }    
        }
      else{
          for(int t=0;t<length(val);t++){
              postfix_exp[counter++] = val[t];
          }
          postfix_exp[counter++] = ' ';
      } 
        
    i++;    
    }    
    while(!Is_Empty(&S)){
        char a = Pop(&S);
        postfix_exp[counter++] = a;
        postfix_exp[counter++] = ' ';
    }
    
}
int main(){
    int n;
    scanf("%d\n",&n);
    for(int i=0;i<n;i++){
        char exp[100000];
        scanf("%[^\n]\n",exp);
        len = length(exp);
        counter =0;
        bracket_counter = 0;
        for(int i=0;i<len+1;i++){
            postfix_exp[i] = '\0';
        }
        
        //printf("%d", bracket_counter);
        if(!check_invalid(exp)){
            convert_postfix(exp);
            postfix_exp[len+1] = '\0';
            printf("%s\n",postfix_exp);
        }
         else{
             printf("INVALID\n");
         }
    }
}