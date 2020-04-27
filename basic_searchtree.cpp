#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef int key_t;
typedef int object_t;
int COUNT = 10;
typedef struct tr_n_t {key_t      key; 
                struct tr_n_t   *left;
                struct tr_n_t  *right;
               /* possibly additional information */ } tree_node_t;


#define BLOCKSIZE 256

tree_node_t *currentblock = NULL;
int    size_left;
tree_node_t *free_list = NULL;
int nodes_taken = 0;
int nodes_returned = 0;

tree_node_t *get_node()
{ tree_node_t *tmp;
  nodes_taken += 1;
  if( free_list != NULL )
  {  tmp = free_list;
     free_list = free_list -> right;
  }
  else
  {  if( currentblock == NULL || size_left == 0)
     {  currentblock = 
                (tree_node_t *) malloc( BLOCKSIZE * sizeof(tree_node_t) );
        size_left = BLOCKSIZE;
     }
     tmp = currentblock++;
     size_left -= 1;
  }
  return( tmp );
}


void return_node(tree_node_t *node)
{  node->right = free_list;
   free_list = node;
   nodes_returned +=1;
}


tree_node_t *create_tree(void)
{  tree_node_t *tmp_node;
   tmp_node = get_node();
   tmp_node->left = NULL;
   return( tmp_node );
}

object_t *find(tree_node_t *tree, key_t query_key)
{  tree_node_t *tmp_node;
   if( tree->left == NULL )
     return(NULL);
   else
   {  tmp_node = tree;
      while( tmp_node->right != NULL )
      {   if( query_key < tmp_node->key )
               tmp_node = tmp_node->left;
          else
               tmp_node = tmp_node->right;
      }
      if( tmp_node->key == query_key )
         return( (object_t *) tmp_node->left );
      else
         return( NULL );
   }
}

int insert(tree_node_t *tree, key_t new_key, object_t *new_object)
{  tree_node_t *tmp_node;
   if( tree->left == NULL )
   {  tree->left = (tree_node_t *) new_object;
      tree->key  = new_key;
      tree->right  = NULL; 
   }
   else
   {  tmp_node = tree;
      while( tmp_node->right != NULL )
      {   if( new_key < tmp_node->key )
               tmp_node = tmp_node->left;
          else
               tmp_node = tmp_node->right;
      }
      /* found the candidate leaf. Test whether key distinct */
      if( tmp_node->key == new_key )
         return( -1 );
      /* key is distinct, now perform the insert */ 
      {  tree_node_t *old_leaf, *new_leaf;
         old_leaf = get_node();
         old_leaf->left = tmp_node->left; 
         old_leaf->key = tmp_node->key;
         old_leaf->right  = NULL;
         new_leaf = get_node();
         new_leaf->left = (tree_node_t *) new_object; 
         new_leaf->key = new_key;
         new_leaf->right  = NULL; 
         if( tmp_node->key < new_key )
         {   tmp_node->left  = old_leaf;
             tmp_node->right = new_leaf;
             tmp_node->key = new_key;
         } 
         else
         {   tmp_node->left  = new_leaf;
             tmp_node->right = old_leaf;
         } 
      }
   }
   return( 0 );
}

object_t *deleteion(tree_node_t *tree, key_t delete_key)
{  tree_node_t *tmp_node, *upper_node, *other_node;
   object_t *deleted_object;
   if( tree->left == NULL )
      return( NULL );
   else if( tree->right == NULL )
   {  if(  tree->key == delete_key )
      {  deleted_object = (object_t *) tree->left;
         tree->left = NULL;
         return( deleted_object );
      }
      else
         return( NULL );
   }
   else
   {  tmp_node = tree;
      while( tmp_node->right != NULL )
      {   upper_node = tmp_node;
          if( delete_key < tmp_node->key )
          {  tmp_node   = upper_node->left; 
             other_node = upper_node->right;
          } 
          else
          {  tmp_node   = upper_node->right; 
             other_node = upper_node->left;
          } 
      }
      if( tmp_node->key != delete_key )
         return( NULL );
      else
      {  upper_node->key   = other_node->key;
         upper_node->left  = other_node->left;
         upper_node->right = other_node->right;
         deleted_object = (object_t *) tmp_node->left;
         return_node( tmp_node );
         return_node( other_node );
         return( deleted_object );
      }
   }
}

void remove_tree(tree_node_t *tree)
{  tree_node_t *current_node, *tmp;
   if( tree->left == NULL )
      return_node( tree );
   else
   {  current_node = tree;
      while(current_node->right != NULL )
      {  if( current_node->left->right == NULL )
         {  return_node( current_node->left );
            tmp = current_node->right;
            return_node( current_node );
            current_node = tmp;
         }
         else
         {  tmp = current_node->left;
            current_node->left = tmp->right;
            tmp->right = current_node; 
            current_node = tmp;
         }
      }
      return_node( current_node );
   }
}

void check_tree( tree_node_t *tr, int depth, int lower, int upper )
{  if( tr->left == NULL )
   {  printf("Tree Empty\n"); return; }
   if( tr->key < lower || tr->key >= upper )
         printf("Wrong Key Order \n");
   if( tr->right == NULL )
   {  if( *( (int *) tr->left) == 10*tr->key + 2 )
         printf("%d(%d)  ", tr->key, depth );
      else
         printf("Wrong Object \n");
   }
   else
   {  check_tree(tr->left, depth+1, lower, tr->key ); 
      check_tree(tr->right, depth+1, tr->key, upper ); 
   }
}

void print2DUtil(tree_node_t *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->key ); 

    // Process left child 
    print2DUtil(root->left, space); 
} 

void print2D(tree_node_t *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
} 

int main()
{  tree_node_t *searchtree;
   char nextop;
   searchtree = create_tree();
   printf("Made Tree\n");
   printf("In the following, the key n is associated wth the objecct 10n+2\n");
   while( (nextop = getchar())!= 'q' )
   { if( nextop == 'i' )
     { int inskey,  *insobj, success;
       insobj = (int *) malloc(sizeof(int));
       scanf(" %d", &inskey);
       *insobj = 10*inskey+2;
       success = insert( searchtree, inskey, insobj );
       if ( success == 0 )
         printf("  insert successful, key = %d, object value = %d, \n",
        	  inskey, *insobj);
       else
           printf("  insert failed, success = %d\n", success);
     }  
     if( nextop == 'f' )
     { int findkey, *findobj;
       scanf(" %d", &findkey);
       findobj = find( searchtree, findkey);
       if( findobj == NULL )
         printf("  find failed, for key %d\n", findkey);
       else
         printf("  find successful, found object %d\n", *findobj);
     }

     if( nextop == 'p' )
     {
      print2D(searchtree); 
     }
     if( nextop == 'd' )
     { int delkey, *delobj;
       scanf(" %d", &delkey);
       delobj = deleteion( searchtree, delkey);
       if( delobj == NULL )
         printf("  delete failed for key %d\n", delkey);
       else
         printf("  delete successful, deleted object %d for key %d\n", *delobj, delkey);
     }
     if( nextop == '?' )
     {  printf("  Checking tree\n"); 
        check_tree(searchtree,0,-1000,1000);
        printf("\n");
        if( searchtree->left != NULL )
 	   printf("key in root is %d\n",	 searchtree->key );
        printf("  Finished Checking tree\n"); 
     }
   }

   remove_tree( searchtree );
   printf("Removed tree.\n");
   printf("Total number of nodes taken %d, total number of nodes returned %d\n",
	  nodes_taken, nodes_returned );
   return(0);
}
