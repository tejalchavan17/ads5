#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct node
{
      int data;
      struct node *left,*right;
      int ht;
}node;
node *insert(node *,int);
void inorder(node *);
int height(node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *RL(node *);
node *LL(node *);
node *LR(node *);
int BF(node *);
node * Delete(node *T,int x);
node *root=NULL;
int main()
{
    int x,n,i,op,choice;int key[20];
    do
    {
      printf("\n 1.Insert");
      printf("\n 2.Delete");
      printf("\n 3.Quit");  
      printf("\n Enter your choice");
      scanf("%d",&choice);
      switch(choice)
      {
           case 1: printf("\n Enter no.of nodes to be inserted in tree");
                   scanf("%d",&n);
                   printf("\n Enter data to be inserted");
                   printf("\n");
                   for(i=0;i<n;i++)
                   {
                      //printf("\n Enter node%d ",i+1);
                      scanf("%d",&key[i]);
                      printf("\t");
                   }
                   root=NULL;
                   for(i=0;i<n;i++)
                   {
                      root=insert(root,key[i]);
                      printf("\n After insertion of node:%d",key[i]);
                      printf("\n");
                      inorder(root);
                   }
                   printf("\n Inorder traversal");
                   printf("\n");
                   inorder(root);
                   break;
          case 2:  printf("\nEnter a data:");
                   scanf("%d",&x);
                   root=Delete(root,x);
                   printf("\n Inorder traversal after deletion");
                   printf("\n");
                   inorder(root);
                   break;
          default: printf("\n Wrong Choice");
                   break;
     }
   }while(choice!=3);
      return 0;
}
node * insert(node *T,int x)
{
     if(T==NULL)
     {
          T=(node *)malloc(sizeof(node));
          T->data=x;
          T->left=NULL;
           T->right=NULL;
      }
      else     
	    if(x>T->data)
	     {
                     
		    T->right=insert(T->right,x);
		    if(BF(T)==-2)
			 if(x>T->right->data)
                         {
                               printf("\n After insertion of node:%d",x);
                               printf("\n");
                               inorder(root);
			       T=RR(T);
                               printf("\n Rotation is Right of Right");
                               printf("\n");
                               inorder(T);
                         }
			  else
                          {
                                printf("\n After insertion of node:%d",x);
                                printf("\n");
                                inorder(root);
				T=RL(T);
                                printf("\n Rotation is Right of Left");
                                printf("\n");
                                inorder(T);
                           }
	      }
	      else
		   if(x<T->data)
		   {
		       T->left=insert(T->left,x);
                 
		       if(BF(T)==2)
			    if(x<T->left->data)
                            {	
                                 printf("\n After insertion of node:%d",x);
                                 printf("\n");
                                 inorder(root);
				 T=LL(T);
                                 printf("\n Rotation is Left of Left");
                                 printf("\n");
                                 inorder(T);
                            }
			     else
                             {
                                 printf("\n After insertion of node:%d",x);
                                 printf("\n");
                                 inorder(root);
				 T=LR(T);
                                 printf("\n Rotation is Left of Right");
                                 printf("\n");
                                 inorder(T);
                              }
		    }
		T->ht=height(T);
		return(T);
}
node * Delete(node *T,int x)
{
    node *p;
    if(T==NULL)
    {
        printf("\n No node in a tree ");
        return NULL;
    }
    else
        if(x > T->data)       
        {
            T->right=Delete(T->right,x);
            if(BF(T)==2)
                if(BF(T->left)>=0)
                    T=LL(T);
                else
                    T=LR(T);
        }
        else
            if(x<T->data)
            {
                T->left=Delete(T->left,x);
                if(BF(T)==-2)    
                    if(BF(T->right)<=0)
                        T=RR(T);
                    else
                        T=RL(T);
            }
            else
            {
                if(T->right!=NULL)
                {    
                    p=T->right;
                    
                    while(p->left!= NULL)
                        p=p->left;
                    
                    T->data=p->data;
                    T->right=Delete(T->right,p->data);
                    
                    if(BF(T)==2)
                        if(BF(T->left)>=0)
                            T=LL(T);
                        else
                            T=LR(T);
                }
                else
                    return(T->left);
            }
    T->ht=height(T);
    return(T);
}
int height(node *T)
{
      int lh,rh;
      if(T==NULL)
           return 0;
      if(T->left==NULL)
          lh=0;
      else
          lh=1+T->left->ht;
      if(T->right==NULL)
          rh=0; 
       else
           rh=1+T->right->ht;
       if(lh>rh)
           return(lh);
       return(rh);
}
node *rotateright(node *x)
{
      node *y;
      y=x->left;
      x->left=y->right;
      y->right=x;
      x->ht=height(x);
      y->ht=height(y);
      return(y);
}
node *rotateleft(node *x)
{
     node *y;
     y=x->right;
     x->right=y->left;
     y->left=x;
     x->ht=height(x);
     y->ht=height(x);
     return(y);
}
node *RR(node *T)
{
      T=rotateleft(T);
      return(T);
}
node *LL(node *T)
{
      T=rotateright(T);
      return(T);
}
node *LR(node *T)
{
      T->left=rotateleft(T->left);
      T=rotateright(T);
      return(T);
}
node *RL(node *T)
{
      T->right=rotateright(T->right);
      T=rotateleft(T);
      return(T);
}
int BF(node *T)
{
     int lh,rh;
     if(T==NULL)
         return(0);
     if(T->left==NULL)
        lh=0;
     else
         lh=1+T->left->ht;
     if(T->right==NULL)
        rh=0;
     else
         rh=1+T->right->ht;
     return(lh-rh);
}
void inorder(node *T)
{
     if(T!=NULL)
     {
         inorder(T->left);
         printf("%d(balance = %d)",T->data,BF(T));
         inorder(T->right);
      }
}

