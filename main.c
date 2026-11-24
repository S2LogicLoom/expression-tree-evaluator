#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int errorFlag = 0;
int parError = 0;
int charError = 0;
int syntaxError = 0;
  struct Node {
    int isOp;
    char op;
    double num;
    struct Node* left;
    struct Node* right;
  };

  struct Node* newNumNode(double v){
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->isOp = 0;
    n->op=' ';
    n->num=v;
    n->right = NULL;
    n->left = NULL;
    return n;
  }
  struct Node* newOpNode(char c){
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->isOp=1;
    n->op = c;
    n->num = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
  }

  struct Node* stack[100];
  int top = -1;
 
  void push(struct Node* n) {
    stack[++top] = n;
  } struct Node* pop(){
   return stack[top--];
  }

  struct Node* buildTree(char postfix[]){
    syntaxError = 0;
    top = -1;
    int i =0;
    while(postfix[i] != '\0'){
      if(postfix[i] == ' '){
        i++;
        continue;
      }
    if(isdigit(postfix[i]) || postfix[i] == '.'){
      char *end;
      double v = strtod(&postfix[i] , &end);
        push(newNumNode(v));
        i =end - postfix;
    }else {
      if(top < 1) {
        syntaxError =1;
        return NULL;
      }
        struct Node *node = newOpNode(postfix[i]);
        node->right = pop();
        node->left = pop();
        push(node);
        i++;
    }
  }
    if(top != 0){
      syntaxError = 1;
      return NULL;
  }
  return pop();
  }
  double evaluate(struct Node *root){
    if(!root->isOp){
        return root->num;
    } double l = evaluate(root->left);
    double r = evaluate(root->right);
    switch( root -> op) {
        case '+' : return l+r;
        case '-' : return l-r;
        case '*' : return l*r;
        case '/' : 
        if(r==0) { errorFlag =1;
        return 0; }
        return l/r;
        case '^' : return pow(l,r);
    } return 0;
  }

  void printNode(struct Node* r){
    if(r->isOp) printf("%c", r->op);
    else printf("%g", r->num);
  }

  void inorder(struct Node* r){
    if(r == NULL)
        return;
        inorder(r->left);
        printNode(r);
        inorder(r->right);
  }

  void preorder(struct Node* r) {
    if(r ==  NULL){
        return;
    }
    printNode(r);
    preorder(r->left);
    preorder(r->right);
  }

  void postorder(struct Node* r) {
    if(r ==  NULL){
        return;
    }
    postorder(r->left);
    postorder(r->right);
    printNode(r);
  }

  char opStack[100];
  int opTop = -1;

  int precedence(char op){
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
  }

  void infixTopostfix(char infix[], char postfix[]) {
    int j = 0;
    parError = 0;
    charError = 0;
    opTop = -1;
    for(int i=0; infix[i] != '\0'; i++){
        char c= infix[i];
        if(c == ' ' || c == '\n')  continue;
        if(isdigit(c) || c== '.') {
          while(isdigit(infix[i]) || infix[i]=='.'){
            postfix[j++] = infix[i++];
          }
          i--;
        postfix[j++] = ' ';
    }else if(c == '(') {
        opStack[++opTop] = c;
    }else if(c == ')') {
        while(opTop != -1 && opStack[opTop] != '(') {
        postfix[j++] = opStack[opTop--];
        postfix[j++] = ' ';
      } if(opTop == -1){
        parError = 1;
        return;
      }
        opTop--;
    }else {
      if(c != '+' && c != '-' && c != '*' && c != '/' && c != '^'){
        charError = 1;
        return;
      }
        while(opTop != -1 && (precedence(opStack[opTop]) > precedence(c) || (precedence(opStack[opTop]) == precedence(c) && c!= '^'))) {
        postfix[j++] = opStack[opTop--];
        postfix[j++] = ' ';
    }
        opStack[++opTop] = c;
  }
}
  while(opTop !=  -1){
    if(opStack[opTop] == '('){
      parError = 1;
      return;
    }
      postfix[j++] = opStack[opTop--];
      postfix[j++] = ' ';
  }
  postfix[j] = '\0';
}


  int main(){
    char infix[100], postfix[200];

    printf("Enter expression\n");
    fgets(infix , 100 , stdin);

    infixTopostfix(infix, postfix);
    if (parError){
      printf("Error : brackets mismatch\n");
      return 0;
    }
    if(charError){
      printf("Error : Invalid character\n");
      return 0;
    }
    printf("Postfix: %s\n", postfix);
    struct Node* root = buildTree(postfix);
    if(syntaxError){
      printf("Error : incomplete expression\n");
      return 0;
    }

    printf("INORDER:  "); inorder(root);  printf("\n");
    printf("PREORDER:  "); preorder(root);   printf("\n");
    printf("POSTORDER:  "); postorder(root);  printf("\n");

    double result = evaluate(root);
    if(errorFlag) printf("Error : division by zero\n");
    else
    printf("RESULT = %g\n" , result);
    return 0;
  }