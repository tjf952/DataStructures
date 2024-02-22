#ifndef _BST_H
#define _BST_H

#include <stdio.h>
#include <stdlib.h>

/*
* Compares two node data values
* args: void* data
* returns: -1 if arg1 < arg2; 0 if arg1 = arg2; 1 if arg1 > arg2
*/
typedef int (*fp_comp)(void*, void*);

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* BST_NODE struct
*/
typedef struct bst_node
{
    void* data;
    struct bst_node* left;
    struct bst_node* right;
}
bst_node_t;

/*
* BST struct
*/
typedef struct bst
{
    bst_node_t* root;
    fp_comp node_compare;
    fp_print node_print;
}
bst_t;

bst_t* bst_init(fp_comp comp_func, fp_print print_func);
void bst_destroy(bst_t** tree);

bst_node_t* bst_search(bst_t* tree, void* data);
bst_node_t* bst_insert(bst_t* tree, void* data);
bst_node_t* bst_delete(bst_t* tree, void* data);
void bst_empty(bst_t* tree);

void bst_print(bst_t* tree);

#endif

#if 0

An AVL tree is a self-balancing Binary Search Tree (BST) where the difference
between heights of left and righ subtrees cannot be more than one for all nodes.
To make sure the given tree remains AVL after every insertion, the BST must
perform re-balancing. This is done by two basic operations: (1) Left Rotation
(2) Right Rotation.

T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side)  

     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3

Keys in both of the above trees follow the following order: 
keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.

#endif
