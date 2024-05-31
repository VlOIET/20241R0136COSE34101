#include "CPU_Scheduler.h"

Queue *make_queue()
{
    Queue *queue_ptr = malloc(sizeof(Queue));
    queue_ptr->start = NULL;
    queue_ptr->end = NULL; 

    return queue_ptr;
}

void enqueue(Queue* queue_ptr, Process* process_ptr)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->process = process_ptr;
    new_node->next = NULL;

    if(queue_ptr->start == NULL)
        queue_ptr->start = new_node;
    else
        queue_ptr->end->next = new_node;

    queue_ptr->end = new_node;
}

Process *dequeue(Queue* queue_ptr)
{
    Process* target_process;

    if(queue_ptr->start == NULL)
    {
        return NULL;
    }
    else
    {
        Node* target_node = queue_ptr->start;
        target_process = target_node->process;

        queue_ptr->start = queue_ptr->start->next;
        free(target_node);
    }
    return target_process;
}

void remove_queue(Queue* queue_ptr)
{
    free(queue_ptr);
}