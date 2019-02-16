#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print_array(a,n) for(ll i=0;i<n;i++) cout<<a[i]<<" ";
#define test int t; cin>>t; while(t--)

struct node
{
    int data,h;
    struct node *p,*l,*r;
};

struct AVLTree
{
    int size;
    struct node* root;
};

struct node* createNode(int val)
{
   struct node* temp=(struct node*)malloc(sizeof(struct node));
   temp->data=val;
   temp->h=0;
   temp->l=temp->r=temp->p=0;

   return temp;
}

struct AVLTree* createAVLTree()
{
   struct AVLTree* newTree=(struct AVLTree*)malloc(sizeof(struct AVLTree));
   newTree->size=0;
   newTree->root=0;

   return newTree;
}

int Size(struct AVLTree* tree)
{
   return tree->size;
}

void UpdateNodeHeight(struct node* n)
{
   if(n->l && n->r) n->h= max(n->l->h,n->r->h)+1;
   else if(n->l)    n->h= n->l->h + 1;
   else if(n->r)    n->h= n->r->h + 1;
   else n->h=0;
}

void UpdateAboveHeight(struct node* n)
{
   while(n)
   {
     UpdateNodeHeight(n);
     n=n->p;
   }
}

int BalanceFactor(struct node *curr)
{
    int ans = 0;
    if(curr->l && curr->r)
		ans = (curr->l->h)-(curr->r->h);
	  else if(curr->l)
		ans = curr->l->h + 1;
	  else if (curr->r)
		ans = -1 - (curr->r->h);
	  else
		 ans = 0;
    return ans;
}

struct node* unbalancedNode(struct node *start)
{
    struct node* current=start;
    while(current && BalanceFactor(current)<=1)
    {
        current=current->p;
    }

   return current;
}

struct node* LLRotation(struct node *current)
{
   struct node *a,*b;
   a=current->l;
   b=a->l;
   a->p = current->p;
   current->l = a->r;
   if(a -> r)
   {
     a->r->p = current;
   }
   a->r = current;
   current -> p = a;
   UpdateAboveHeight(current);
   return a;
}

struct node* RRRotation(struct node *current)
{
   struct node *a,*b;
   a=current->r;
   b=a->r;
   a->p = current->p;
   current->r = a->l;
   if(a -> l)
   {
     a->l->p = current;
   }
   a->l = current;
   current -> p = a;
   UpdateAboveHeight(current);
   return a;
}

void balance(struct AVLTree* avl , struct node* curr, int val)
{
  if (curr)
   {
       int b = BalanceFactor(curr);
       // CASE 1: apply LL rotation

       if (curr->l && (b>1) && (val < curr->l->data))
       {
           if (curr->p)
           {
               if ((curr->p->l) == curr)
                   curr->p->l = LLRotation(curr);

               else if ((curr->p->r) == curr)
                   curr->p->r = LLRotation(curr);
           }

           else
               avl->root = LLRotation(curr);

       }
        // CASE 2: apply RR rotation
       else if ((curr->r) && (b<-1 && (val>curr->r->data)))
       {
           if (curr->p)
           {
               if ((curr->p->r) == curr)
                   curr->p->r = RRRotation(curr);

               else if ((curr->p->l) == curr)
                   curr->p->l = RRRotation(curr);
           }
           else
               avl->root = RRRotation(curr);

       }
        // CASE 3: apply LR rotation
       else if (curr->l && (b>1) && (val > curr->l->data))
       {
           if (curr->p)
           {
               if ((curr->p->l) == curr)
               {
                   curr->l = RRRotation(curr->l);
                   curr->p->l = LLRotation(curr);
               }
               else if ((curr->p->r) == curr)
               {
                   curr->l = RRRotation(curr->l);
                   curr->p->r = LLRotation(curr);
               }
           }
           else
           {
               curr->l = RRRotation(curr->l);
               avl->root = LLRotation(curr);
           }
       }
        // CASE 4: apply RL rotation
       else if ((curr->r) && (b<-1) && (val<curr->r->data))
       {
           if (curr->p)
           {
               if (curr->p->r == curr)
               {
                   curr->r = LLRotation(curr->r);
                   curr->p->r = RRRotation(curr);
               }
               else if(curr->p->l == curr)
               {
                   curr->r = LLRotation(curr->r);
                   curr->p->l = RRRotation(curr);
               }
           }
           else
           {
               curr->r = LLRotation(curr->r);
               avl->root = RRRotation(curr);
           }
       }
   }
}

void insert(struct AVLTree* tree,int val)
{
   struct node* newNode=createNode(val);
   struct node* curr=tree->root;

   if(!curr)
     tree->root=newNode;

  else
  {
     while(curr)
     {
        if(curr->data==val) return;


        if(curr->data < val)
        {
            if(!(curr->r))
            {
               curr->r = newNode;
               newNode->p = curr;
               UpdateAboveHeight(newNode);
               break;
            }
           else curr=curr->r;

        }
        if(curr->data > val)
        {
            if(!(curr->l))
            {
               curr->l = newNode;
               newNode->p = curr;
               UpdateAboveHeight(newNode);
               break;
            }
           else curr=curr->l;
        }
     }
    // curr=unbalancedNode(newNode);
     //balance(tree,curr,val);

  }
  tree->size++;

}

void print(struct node *r)
{
   struct node *curr=r;
   if(curr)
   {
     print(curr->l);
     cout<<curr->data<<" ";
     print(curr->r);
   }

}

int getHeight(struct node *root){
if(root==NULL)return 0;
return 1+max(getHeight(root->l),getHeight(root->r));
}

int main()
{
    struct AVLTree* s=createAVLTree();
    int n;
    cin>>n;
    int a;
    for(int i=0;i<n;i++)
     {
        cin>>a;
        insert(s,a);
      //  cout<<"hi"<<endl;
     }

     print(s->root);

	return 0;
}

