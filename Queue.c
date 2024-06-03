#include "CPU_Scheduler.h"

Queue *make_queue()
{
    Queue *queue_ptr = malloc(sizeof(Queue));
    queue_ptr->start = NULL;
    queue_ptr->end = NULL;

    return queue_ptr;
}

void insert(Queue *queue_ptr, Simul *simul_ptr)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->simul = simul_ptr;
    new_node->next = NULL;

    if (queue_ptr->start == NULL)
        queue_ptr->start = new_node;
    else
        queue_ptr->end->next = new_node;

    queue_ptr->end = new_node;
}

Simul *delete(Queue *queue_ptr, Node *subject)
{
    Node *before_node = NULL;
    Node *target_node = queue_ptr->start;
    Simul *target_simul = NULL;

    while (target_simul == NULL && target_node != NULL)
    {
        if (target_node == subject) // 삭제할 노드가 있는 경우
        {
            if (before_node == NULL) // 삭제할 노드가 맨 앞에 있는 경우
            {
                queue_ptr->start = target_node->next;
                target_simul = target_node->simul;
                free(target_node);
            }
            else // 삭제할 노드가 중간 & 맨 뒤에 있는 경우
            {
                before_node->next = target_node->next;

                if (before_node->next == NULL) // 삭제할 노드가 맨 뒤에 있는 경우
                    queue_ptr->end = before_node;

                target_simul = target_node->simul;
                free(target_node);
            }
        }
        else // 삭제할 노드가 없는 경우
        {
            before_node = target_node;
            target_node = target_node->next;
        }
    }

    return target_simul;
}

void remove_queue(Queue *queue_ptr)
{
    free(queue_ptr);
}