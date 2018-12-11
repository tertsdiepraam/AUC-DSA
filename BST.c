#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
// *** Create a program "bst.c" and implement all the functions that are
// *** not already implemented in BST_in_class.c.

// *** For convenience, the structure definitions have been moved from
// *** BST_in_class.c to here, so that they can be used in BST_balance.c as
// *** well.

// ------ The following are defined in BST_in_class.c, NOT homework -----------

// in: a key
// out: a newly allocated TreeNode with the given key, and both children
//      set to NULL.
TreeNode bst_make_new_node(int key) {
  TreeNode n = (TreeNode)malloc(sizeof(struct TreeNodeData));
  if (n==NULL) { printf("allocation error\n"); exit(1); }
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  return n;
}

// out: an empty BST
BST bst_create() {
  BST T = (BST)malloc(sizeof(struct BSTData));
  if (T==NULL) { printf("Allocation error\n"); exit(1); }
  T->root = NULL;
  return T;
}

// in: a BST T
// side effect: all memory associated with T is released
void free_all_the_nodes(TreeNode n) {
  if (n==NULL) { return; }
  free_all_the_nodes(n->left);
  free_all_the_nodes(n->right);
  free(n);
}

void bst_destroy(BST T) {
  free_all_the_nodes(T->root);
}

// in: a BST T
// side effect: the tree is printed with the root at the left hand side.
void bst_print_rec(TreeNode n, int depth) {
  if (n==NULL) { return; }
  bst_print_rec(n->right, depth+1);

  for (int i=0; i<depth; i++) {
    printf("   ");
  }

  printf(" %02d\n", n->key);

  bst_print_rec(n->left, depth+1);
}

void bst_print(BST T) {
  bst_print_rec(T->root, 0);
}

// in: a BST T and a key to insert
// side effect: the key is inserted in the tree such that the BST
//              property is preserved.
void bst_insert_rec(TreeNode n, int key) {
  if (key < n->key) {
    if (n->left == NULL) {
      n->left = bst_make_new_node(key);
    } else {
      bst_insert_rec(n->left, key);
    }
  } else {
    if (n->right == NULL) {
      n->right = bst_make_new_node(key);
    } else {
      bst_insert_rec(n->right, key);
    }
  }
}

void bst_insert(BST T, int key) {
    if (T->root == NULL) {
      T->root = bst_make_new_node(key);
      return;
    }
    bst_insert_rec(T->root, key);
}

// in: a BST T and a key to look up
// out: a TreeNode with the given key or NULL if it's not found.
TreeNode* bst_lookup_pointer_pointer(BST T, int key) {
  TreeNode* where_am_i = &T->root;
  while (*where_am_i != NULL) {
    if ((*where_am_i)->key == key) { return where_am_i; }
    if (key < (*where_am_i)->key) {
      where_am_i = &((*where_am_i)->left);
    } else {
      where_am_i = &((*where_am_i)->right);
    }
  }
  return where_am_i;
}

TreeNode bst_lookup(BST T, int key) {
  return *bst_lookup_pointer_pointer(T, key);
}

// in: a BST T and a key to delete
// side effect: if the key appears in the tree, one node with that key
//              is deleted in such a way that the BST property is preserved.
void bst_delete(BST T, int key) {
  TreeNode* to_delete_p = bst_lookup_pointer_pointer(T, key);
  if (*to_delete_p == NULL) { return; }

  if ((*to_delete_p)->left == NULL && (*to_delete_p)->right == NULL) {
    // node has no children
    free(*to_delete_p);
    *to_delete_p = NULL;
    return;
  } else if ((*to_delete_p)->left == NULL) {
    // node has only a right child
    TreeNode to_delete = *to_delete_p;
    *to_delete_p = to_delete->right;
    free(to_delete);
  } else if ((*to_delete_p)->right == NULL) {
    // node has only a left child
    TreeNode to_delete = *to_delete_p;
    *to_delete_p = to_delete->left;
    free(to_delete);
  } else {
    // node has both children
    TreeNode* ls_rightmost_p = &((*to_delete_p)->left);
    while ((*ls_rightmost_p)->right != NULL) {
      ls_rightmost_p = &((*ls_rightmost_p)->right);
    }
    TreeNode ls_rightmost = *ls_rightmost_p;
    TreeNode to_delete = *to_delete_p;
    *ls_rightmost_p = ls_rightmost->left;
    ls_rightmost->left = to_delete->left;
    ls_rightmost->right = to_delete->right;
    *to_delete_p = ls_rightmost;
    free(to_delete);
  }
}

// ------- the following are homework, to be implemented in BST.c ------------

// *** First, to get some practice, write functions to work out the size and
// *** the height of the tree.
// *** Be careful to think about boundary conditions, such as the empty tree.

// in: a BST T
// out: the number of keys in the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_size_rec(TreeNode n) {
  if (n == NULL) { return 0; }
  return 1 + bst_size_rec(n->left) + bst_size_rec(n->right);
}

int bst_size(BST T) {
  return bst_size_rec(T->root);
}

// in: a BST T
// out: the height of the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_height_rec(TreeNode n) {
  if (n == NULL) { return -1; }
  int height_left  = bst_height_rec(n->left);
  int height_right = bst_height_rec(n->right);
  if (height_left > height_right) {
      return 1 + height_left;
  } else {
      return 1 + height_right;
  }
}

int bst_height(BST T) {
  return bst_height_rec(T->root);
}

// *** We will also need a function to traverse the tree in order, and dump the
// *** result in an array. You'll need to think about *where* in the array
// *** each key needs to be stored.

// in: a BST T and a pointer to an array a of ints with enough space to hold
//     all keys in the tree. (There are bst_size(T) of them.)
// side effect: all keys in the tree are stored in a in ascending order, using
//     an in-order traversal of the tree.
// out: the number of keys that were stored in the array, that is, the same
//     as bst_size(T).
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_in_order_rec(TreeNode n, int* a, int i) {
  if (n == NULL) {
    return i;
  }
  i = bst_in_order_rec(n->left, a, i);
  a[i] = n->key;
  i += 1;
  return bst_in_order_rec(n->right, a, i);
}

int bst_in_order(BST T, int* a) {
  return bst_in_order_rec(T->root, a, 0);
}

// *** You can use the bst code you've written so far to sort an array
// *** of ints! The resulting sorting algorithm is pretty efficient
// *** on most data.

// in: an array a with n ints, in no particular order
// side effect: the items in the array are sorted using a BST in the process.
void bst_sort(int* a, int n) {
  BST T = bst_create();
  for (int i=0; i<n; i++) {
      bst_insert(T, a[i]);
  }
  bst_in_order(T, a);
}

// *** To balance a tree we need to be able to go the other way around, and
// *** construct a tree directly from a sorted array. Use the function
// *** bst_make_new_node.

// in: an array a with n ints, in sorted order
// out: a *perfectly balanced* BST containing the items in a.
// hint: use a recursive helper function that takes a TreeNode instead of a BST
TreeNode bst_create_from_sorted_rec(int* a, int n) {
  TreeNode node = bst_make_new_node(a[n/2]);
  if (n > 1) {
    node->left  = bst_create_from_sorted_rec(a, n/2);
  }
  if (n > 2) {
    node->right = bst_create_from_sorted_rec(&a[n/2+1], n-n/2-1);
  }
  return node;
}

BST bst_create_from_sorted(int* a, int n) {
  BST T = bst_create();
  T->root = bst_create_from_sorted_rec(a, n);
  return T;
}


// *** We can combine the functions we wrote to do a full tree rebalancing.

// in: a BST T
// side effect: the BST is made *perfectly balanced*
void bst_rebalance(BST T) {
  int n = bst_size(T);
  int* a = (int*) malloc(sizeof(int)*n);
  bst_in_order(T, a);
  BST new = bst_create_from_sorted(a, n);
  free_all_the_nodes(T->root);
  T->root = new->root;
}