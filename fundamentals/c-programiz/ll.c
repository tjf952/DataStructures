#include <stdio.h>
#include <stdlib.h>

// Simple node
typedef struct ll_node
{
    int data;
    struct ll_node* next;
}
node;

void print_list(node* head);

// Tried to simulate the making of the LL from interview, won't worry about cleanup
node* makelist()
{
    node* head = NULL;
    node* curr = NULL;

    for (int i = 0; i < 3; ++i)
    {
        node* new = calloc(1, sizeof(node));
        new->data = i;
        new->next = NULL;

        if (!head)
        {
            head = new;
            curr = head;
        }
        else
        {
            curr->next = new;
            curr = curr->next;
        }
    }

    return head;
}

/*
The below are implementations of what I explained were two methods of how you could reverse it.
There are probably many ways to do this but these were the first 2 I thought of during the 
interview. I tried to replicate what I remember seeing in the original problem.
*/

// O(n)
node* reverse_short(node* head)
{
    node* _prev = NULL;
    node* _next = NULL;

    /* 
    Because I was only using 2 pointers during the interview instead of 3, I was disconnecting 
    the linked list into 2 pieces and not shifting the head over to keep track of it.
    */
    while (head)
    {
        // Reverses as it iterates through
        _next = head->next;
        head->next = _prev;
        _prev = head;
        head = _next;
    }

    return _prev;
}

// O(n^2)
node* reverse_long(node* head)
{
    // Gonna keep track of a new list
    node* newhead = NULL;
    node* newcurr = NULL;

    // Each loop should add the last of the original to new list
    while (head)
    {
        // Keep place of current and previous node of original
        node* curr = head;
        node* prev = NULL;

        // Traverse to last
        while (curr->next)
        {
            prev = curr;
            curr = curr->next;
        }

        // Handles adding to new list and deleting tail of original list
        if (!newhead)
        {
            newhead = curr;
            newcurr = newhead;

            if (prev)
            {
                prev->next = NULL;
            }
            else
            {
                head = NULL;
            }
        }
        else
        {
            newcurr->next = curr;
            newcurr = curr;

            if (prev)
            {
                prev->next = NULL;
            }
            else
            {
                head = NULL;
            }
        }
    }

    return newhead;
}

// Interview print function
void print_list(node* head)
{
    puts("Printing List: ");
    node* temp = head;

    while (temp) {
        printf("[%d]->", temp->data);
        temp = temp->next;
    }

    puts("NULL\n");
}
 
int main()
{
    node* head = NULL;
    head = makelist();
    print_list(head);
    head = reverse_long(head);
    print_list(head);
    head = reverse_short(head);
    print_list(head);
}