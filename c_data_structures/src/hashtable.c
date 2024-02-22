#include "../include/hashtable.h"

/*
* Constructor for HT_NODE
* data: void* argument to act as a template
* returns: a new ht_node object
*/
static ht_node_t* ht_node_init(void* data)
{
    ht_node_t* node = calloc(1, sizeof(ht_node_t));

    if (NULL == node)
    {
        fprintf(stderr, "[Error: ht_node_init() failed]\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

/*
* Deconstructor for HT_NODE
* node: an existing ht_node object pointer
* returns: none
*/
static void ht_node_destroy(ht_node_t** node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }

    free(*node);
    *node = NULL;
}

/* 
* Constructor for HT
* size: size of hashtable
* hash_func: user made hash function to hash void* data
* print_func: user made print function to print void* data
* returns: a new ht object
*/
ht_t* ht_init(int size, fp_hash hash_func, fp_print print_func)
{
    if (NULL == hash_func || NULL == print_func)
    {
        fprintf(stderr, "[Error: hash_func or print_func are NULL]\n");
        return NULL;
    }

    ht_t* ht = calloc(1, sizeof(ht_t));

    if (NULL == ht)
    {
        fprintf(stderr, "[Error: ht_init() failed due to hashtable]\n");
        return NULL;
    }

    ht->table = calloc(size, sizeof(ht_node_t*));

    if (NULL == ht->table)
    {
        fprintf(stderr, "[Error: ht_init() failed due to table]\n");
        free(ht);
        return NULL;
    }

    for (int i = 0; i < size; ++i)
    {
        (ht->table)[i] = NULL;
    }

    ht->table_size = size;
    ht->hash_func= hash_func;
    ht->print_func = print_func;

    return ht;
}

/*
* Deconstructor for HT
* ht: an existing ht object pointer
* returns: none
*/
void ht_destroy(ht_t** ht)
{
    if (NULL == ht || NULL == *ht)
    {
        return;
    }

    ht_empty(*ht);
    free((*ht)->table);
    (*ht)->table = NULL;
    free(*ht);
    *ht = NULL;
}

/*
* Removes and frees all nodes from hashtable
* ht: an existing ht object
* returns: none
*/
void ht_empty(ht_t* ht)
{
    if (NULL == ht)
    {
        return;
    }

    ht_node_t* curr = NULL;
    ht_node_t* temp = NULL;

    for (int i = 0; i < ht->table_size; ++i)
    {
        if (NULL != ht->table[i])
        {
            curr = ht->table[i];

            while (NULL != curr)
            {
                temp = curr;
                curr = curr->next;
                ht_node_destroy(&temp);
            }

            ht->table[i] = NULL;
        }
    }
}

/*
* Gets first ht_node at given key
* ht: an existing ht object
* key: hash key in hashtable
* returns: hashtable node on success else NULL
*/
ht_node_t* ht_get(ht_t* ht, int key)
{
    if (NULL == ht)
    {
        fprintf(stderr, "[Error: NULL hashtable]\n");
        return NULL;
    }

    if (key < 0 || key > ht->table_size)
    {
        fprintf(stderr, "[Error: key %d is out of bounds]", key);
        return NULL;
    }

    if (NULL != ht->table[key])
    {
        return ht->table[key];
    }

    return NULL;
}

/*
* Finds the first occurence of the specified data
* ht: an existing ht object
* data: value to find in ht
* returns: index in ht or -1 if not found
*/
int ht_search(ht_t* ht, void* data)
{
    if (NULL == ht)
    {
        fprintf(stderr, "[Error: NULL hashtable]\n");
        return -1;
    }

    int key = ht->hash_func(ht->table_size, data);

    if (NULL != ht->table[key])
    {
        ht_node_t* curr = ht->table[key];

        while (NULL != curr)
        {
            if (data == curr->data)
            {
                return key;
            }

            curr = curr->next;
        }
    }

    return -1;
}

/*
* Removes first occurence of data
* ht: an existing ht object
* data: value to remove from ht
* returns: void* data from removed node or NULL if not found
*/
void* ht_remove(ht_t*ht, void* data)
{
    if (NULL == ht)
    {
        fprintf(stderr, "[Error: hashtable]\n");
        return NULL;
    }

    int key = ht->hash_func(ht->table_size, data);

    if (NULL != ht->table[key])
    {
        ht_node_t* curr = ht->table[key];
        ht_node_t* prev = NULL;

        while (NULL != curr)
        {
            if (data == curr->data)
            {
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        if (NULL == curr)
        {
            return NULL;
        }

        if (NULL == prev)
        {
            ht->table[key] = curr->next;
            ht_node_destroy(&curr);
        }
        else
        {
            prev->next = curr->next;
            ht_node_destroy(&curr);
        }
    }

    return NULL;
}

/*
* Inserts a new node into the hashtable
* ht: an existing ht object
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int ht_insert(ht_t* ht, void* data)
{
    if (NULL == ht)
    {
        fprintf(stderr, "[Error: NULL hashtable]\n");
        return -1;
    }

    ht_node_t* node = ht_node_init(data);

    if (NULL == node)
    {
        return -1;
    }

    int key = ht->hash_func(ht->table_size, data);

    if (NULL == ht->table[key])
    {
        ht->table[key] = node;
    }
    else
    {
        ht_node_t* curr = ht->table[key];

        while (NULL != curr->next)
        {
            curr = curr->next;
        }

        curr->next = node;
    }

    return 1;
}

/*
* Prints the hashtable
* ht: an existing ht object
* returns: none
*/
void ht_print(ht_t* ht)
{
    if (NULL == ht)
    {
        printf("\n=== NULL HASHTABLE ===\n");
        return;
    }

    ht_node_t* curr = NULL;
    printf("\n=== HASHTABLE ===\n");

    for (int i = 0; i < ht->table_size; ++i)
    {
        printf("Key: %d | List: ", i);

        if (NULL != ht->table[i])
        {
            curr = ht->table[i];

            while (NULL != curr)
            {
                printf("[Data: ");
                ht->print_func(curr->data);
                printf("]->");
                curr = curr->next;
            }
            printf("[NULL]\n");
        }
        else
        {
            printf("- Empty -\n");
        }
    }

    printf("==== END ====\n");
}