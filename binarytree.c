/* This code is meant to create a Binary Tree 
   for a postfix expression
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct tag1{
    char data;
    struct tag1 *left;
    struct tag1 *right;
}tree_node;

typedef struct tag2{
    tree_node* x;
    struct tag2 *next;
}stack_node;

void push(stack_node** top, stack_node*topush){
    if(*top == NULL){
        *top = topush;
    }else{
        topush->next = *top;
        *top = topush;
} 
}

tree_node* pop(stack_node**top){
    tree_node* toreturn;
    stack_node* temp;
    if(*top == NULL){
        return NULL;
    }else{
        toreturn = (*top)->x;
        temp = *top;
        *top = (*top)->next;
        free(temp);
        return toreturn;
    }
}

tree_node* create_node_tree(char ch){
    tree_node* new_node;

    new_node = (tree_node*) malloc(sizeof(tree_node));
    new_node ->data = ch;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

stack_node* create_node_stack(tree_node* Y){
    stack_node*new_node;
    new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->x=Y;
    new_node->next=NULL;
    return(new_node);
}

tree_node* create_binary_tree(FILE*infp,stack_node*top){
    char ch;
    ch=getc(infp);
    tree_node* new_node;
    stack_node* new_stack_node;
    while(ch!=EOF){
        new_node = create_node_tree(ch);
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
           new_node->right = pop(&top);
           new_node->left = pop(&top);
        }
           new_stack_node = create_node_stack(new_node);
           push(&top,new_stack_node);
           ch = getc(infp);
    }

    return pop(&top);

}
void menu(void){
   printf("\n\t\t-------- Binary Tree From a Postfix Expression --------\n"); 
   printf("\n\t\t 1. Create the Binary Tree\n");
   printf("\n\t\t 2. Print Infix Expression (Traverse inOrder)\n");
   printf("\n\t\t 3. Print Prefix Expression (Traverse preOrder)\n");
   printf("\n\t\t 4. Quit\n");
   printf("\n\t\t Your choice please:");
}

void traverse_inOrder(tree_node*root){
  
  if(root==NULL)
    return; 
    
  else{
    traverse_inOrder(root->left); 
    printf("%c",root->data); 
    traverse_inOrder(root->right); 
  }
}
void traverse_preOrder(tree_node*root){
  
  if(root==NULL)
    return; 
    
  else{
    printf("%c",root->data);
    traverse_preOrder(root->left); 
     
    traverse_preOrder(root->right); 
  }}
int main(void){

FILE*infp; 
int choice;
tree_node*root=NULL; 
stack_node*top=NULL; 

  infp=fopen("postfix.txt","r"); 
  if(infp==NULL)
    printf("\n\t\tCould not open the FILE!\n"); 
  else{
  	do{
    menu(); 
	scanf("%d",&choice);  
	switch(choice){
	
	case 1:root=create_binary_tree(infp,top);
	       printf("\n\t\tBinary Tree was Created!\n");
		   break;
    case 2:if(root==NULL)
             printf("\n\t\tBinary Tree is not Contstructed YET!\n");
           else{
	       printf("\n\t\tYour Infix Expression is:\n\n\t\t");
		   traverse_inOrder(root);
           printf("\n");
           }
		   break;
    case 3:
           printf("\n");
           traverse_preOrder(root);
           break;
    case 4: printf("\n\t\tTake Care!\n\n\t\t");
	        break; 
	default:printf("\n\t\tINVALID CHOICE!\n");
	}
	}while(choice!=4);
  }
}
