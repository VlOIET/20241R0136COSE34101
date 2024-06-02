#include "CPU_Scheduler.h"

void Preemptive_SJF(Process **process_list, int process_quantity)
{
    int time = 0;
    int process_end = 0;
    int new_signal = 0;
    int change_signal = 0;
    Queue *ready_queue = make_queue();

    Simul **simul_list = (Simul **)malloc(sizeof(Simul *) * process_quantity);
    for (int i = 0; i < process_quantity; i++)
    {
        Simul *new_simul = create_simul(process_list[i]);
        simul_list[i] = new_simul;
    }

    Simul *In_CPU = NULL;
    Node *traverse_ptr;

    while (process_end < process_quantity)
    {
        sleep(1);

        if (In_CPU != NULL)
        {
            In_CPU->process->CPU_burst -= 1;

            if (In_CPU->process->CPU_burst == 0)
            {
                printf("[Time: %d] Process [%d] is terminated\n", time, In_CPU->process->process_id);
                In_CPU->end_time = time;
                In_CPU = NULL;
                process_end++;
            }
        }

        traverse_ptr = ready_queue->start;

        while (ready_queue->start != NULL)
        {
            traverse_ptr->simul->waiting_time += 1;

            if (traverse_ptr == ready_queue->end)
                break;

            traverse_ptr = traverse_ptr->next;
        }

        for (int i = 0; i < process_quantity; i++)
        {
            if (simul_list[i]->process->arrival_time == time)
            {
                printf("[Time: %d] Process [%d] is inserted in ready queue\n", time, simul_list[i]->process->process_id);
                insert(ready_queue, simul_list[i]);
                new_signal = 1;
            }
        }

        traverse_ptr = ready_queue->start;
        
        // Preemptive 구현
        Node *new_shortest_job = ready_queue->start;
        traverse_ptr = ready_queue->start;

        while (ready_queue->start != NULL && new_signal == 1 && In_CPU != NULL)
        {
            Node *temp = traverse_ptr->next;

            if (traverse_ptr->simul->process->CPU_burst < In_CPU->process->CPU_burst)
            {
                printf("[Time: %d] Process [%d] is halted\n", time, In_CPU->process->process_id);
                insert(ready_queue, In_CPU);
                In_CPU = delete (ready_queue, traverse_ptr);
                traverse_ptr = temp;
                change_signal = 1;
            }
            
            if (traverse_ptr == ready_queue->end)
                break;

            traverse_ptr = traverse_ptr->next;
        }

        if (change_signal)
            printf("[Time: %d] Process [%d] is executed by CPU\n", time, In_CPU->process->process_id);

        if (In_CPU == NULL)
        {
            Node *shortest_job = ready_queue->start;
            traverse_ptr = ready_queue->start;

            while (ready_queue->start != NULL)
            {
                if (traverse_ptr->simul->process->CPU_burst < shortest_job->simul->process->CPU_burst)
                {
                    shortest_job = traverse_ptr;
                }

                if (traverse_ptr == ready_queue->end)
                    break;

                traverse_ptr = traverse_ptr->next;
            }

            In_CPU = delete (ready_queue, shortest_job);

            if (In_CPU != NULL)
                printf("[Time: %d] Process [%d] is executed by CPU\n", time, In_CPU->process->process_id);
        }

        new_signal = 0;
        change_signal = 0;
        time++;
    }
    Evaluation(simul_list, process_quantity);

    for (int i = 0; i < process_quantity; i++)
    {
        free(simul_list[i]);
    }
    free(simul_list);
    free(ready_queue);
}