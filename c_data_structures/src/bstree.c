#include "../include/bstree.h"

/*
* Constructor for BST_NODE
* data: void* argument to act as a template
* returns: a new bst_node object
*/
static bst_node_t* bst_node_init(void* data)
{
    bst_node_t* node = calloc(1, sizeof(bst_node_t));

    if (NULL == node)
    {
        fprintf(stderr, "[Error: bst_node_init() failed]\n");
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
* Deconstructor for BST_NODE
* node: an existing bst_node object
* returns: none
*/
static void bst_node_destroy(bst_node_t** node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }

    free(*node);
    *node = NULL;
}

/* 
* Constructor for BST
* returns: a new bst object
*/
bst_t* bst_init(fp_comp comp_func, fp_print print_func)
{
    if (NULL == comp_func || NULL == print_func)
    {
        fprintf(stderr, "[Error: comp_func or print_func are NULL]\n");
        return NULL;
    }

    bst_t* tree = calloc(1, sizeof(bst_t));

    if (NULL == tree)
    {
        fprintf(stderr, "[Error: bst_init() failed]\n");
        return NULL;
    }

    tree->root = NULL;
    tree->node_compare = comp_func;
    tree->node_print = print_func;

    return tree;
}

/*
* Deconstructor for BST
* q: an existing bst object
* returns: none
*/
void bst_destroy(bst_t** tree)
{
    if (NULL == tree || NULL == *tree)
    {
        return;
    }

    bst_empty(*tree);
    free(*tree);
    *tree = NULL;
}

/*
* Helper function for bst_search()
*/
static bst_node_t* bst_search_helper(bst_node_t* root, void* data, fp_comp comp_func)
{
    if (NULL == root || root->data == data)
    {
        return root;
    }
    else if(comp_func(data, root->data) == 1)
    {
        return bst_search_helper(root->right, data, comp_func);
    }
    else
    {
        return bst_search_helper(root->left, data, comp_func);
    }
}

/*
* Finds the first occurence of the specified data in the tree
* root: the root node of an existing bst object
* data: value to find in bst
* returns: the node if in the bst or NULL if not found
*/
bst_node_t* bst_search(bst_t* tree, void* data)
{
    if (NULL == tree)
    {
        return NULL;
    }

    return bst_search_helper(tree->root, data, tree->node_compare);
}

/*
* Helper function for bst_insert()
*/
static bst_node_t* bst_insert_helper(bst_node_t* root, void* data, fp_comp comp_func)
{
    if (NULL == root)
    {
        return bst_node_init(data);
    }
    else if(comp_func(data, root->data) == 1)
    {
        root->right = bst_insert_helper(root->right, data, comp_func);
    }
    else
    {
        root->left = bst_insert_helper(root->left, data, comp_func);
    }

    return root;
}

/*
* Inserts a new node into the bst
* root: the root node of an existing bst object
* data: void* argument to be passed to new node
* returns: the updated root if success or NULL if failed
*/
bst_node_t* bst_insert(bst_t* tree, void* data)
{
    if (NULL == tree)
    {
        return NULL;
    }

    tree->root = bst_insert_helper(tree->root, data, tree->node_compare);
    return tree->root;
}

/*
* Iterative Insert
*
bst_node_t* bst_insert(bst_t* tree, void* data)
{
    if (NULL == tree)
    {
        return NULL;
    }

    if (NULL == tree->root)
    {
        tree->root = bst_node_init(data);
        return tree->root;
    }

    bst_node_t* curr = tree->root;

    while (NULL != curr)
    {
        if (tree->node_compare(data, curr->data) == 1)
        {
            if (NULL == curr->right)
            {
                curr->right = bst_node_init(data);
                return curr->right;
            }
            else
            {
                curr = curr->right;
            }
        }
        else
        {
            if (NULL == curr->left)
            {
                curr->left = bst_node_init(data);
                return curr->left;
            }
            else
            {
                curr = curr->left;
            }
        }
    }

    return NULL;
}
*/

/*
* Finds minimum value given a root node
* root: the root node of an existing bst object
* returns: the node if in the bst or NULL if not found
*/
static bst_node_t* find_minimum(bst_node_t* root)
{
    if (NULL == root)
    {
        return NULL;
    }
    else if (NULL != root->left)
    {
        return find_minimum(root->left);
    }

    return root;
}

/*
* Helper function for bst_delete()
*/
static bst_node_t* bst_delete_helper(bst_node_t* root, void* data, fp_comp comp_func)
{
    if (NULL == root)
    {
        return NULL;
    }

    if (comp_func(data, root->data) == 1) // data > root->data
    {
        root->right = bst_delete_helper(root->right, data, comp_func);
    }
    else if (comp_func(data, root->data) == -1) // data < root->data
    {
        root->left = bst_delete_helper(root->left, data, comp_func);
    }
    else // data = root->data
    {
        if(NULL == root->left && NULL == root->right)
        {
            bst_node_destroy(&root);
            return NULL;
        }
        else if (NULL == root->left || NULL == root->right)
        {
            bst_node_t* temp = NULL;
            if (NULL == root->left)
            {
                temp = root->right;
            }
            else
            {
                temp = root->left;
            }

            bst_node_destroy(&root);
            return temp;
        }
        else
        {
            bst_node_t* temp = find_minimum(root->right);
            root->data = temp->data;
            root->right = bst_delete_helper(root->right, temp->data, comp_func);
        }
    }

    return root;
}

/*
* Deletes specified node in tree
* root: the root node of an existing bst object
* returns: the updated root if success or NULL if failed
*/
bst_node_t* bst_delete(bst_t* tree, void* data)
{
    if (NULL == tree)
    {
        return NULL;
    }

    tree->root = bst_delete_helper(tree->root, data, tree->node_compare);
    return tree->root;
}

/*
* Helper function for bst_empty()
*/
static void bst_empty_helper(bst_node_t* root)
{
    if (NULL == root)
    {
        return;
    }
    
    bst_empty_helper(root->left);
    bst_empty_helper(root->right);
    bst_node_destroy(&root);
}


/*
* Removes and frees all nodes from bst
* root: the root node of an existing bst object
* returns: none
*/
void bst_empty(bst_t* tree)
{
    if (NULL == tree)
    {
        return;
    }
    
    bst_empty_helper(tree->root);
    tree->root = NULL;
}

/*
* Helper function for bst_print()
*/
static void bst_print_helper(bst_node_t* root, fp_print print_func, int indent)
{
    if (NULL != root)
    {
        bst_print_helper(root->right, print_func, indent + 4);

        for (int i = 0; i < indent; ++i)
        {
            printf(" ");
        }

        printf("[");
        print_func(root->data);
        printf("]\n");

        bst_print_helper(root->left, print_func, indent + 4);
    }
}

/*
* Prints the bst INORDER
* root: the root node of an existing bst object
* returns: none
*/
void bst_print(bst_t* tree)
{
    if (NULL == tree || NULL == tree->root)
    {
        printf("\n=== Empty Tree ===\n");
    }
    else
    {
        printf("\n=== TREE TOP ===\n");
        bst_print_helper(tree->root, tree->node_print, 0);
        printf("=== TREE BOTTOM ===\n");
    }
}