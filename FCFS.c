#include "CPU_Scheduler.h"

void FCFS(Process **process_list, int process_quantity)
{
    printf("--------------------------------FCFS Scheduling--------------------------------\n");

    int time = 0;
    int process_end = 0;
    Queue *ready_queue = make_queue();

    Simul **simul_list = (Simul **)malloc(sizeof(Simul *) * process_quantity);
    for (int i = 0; i < process_quantity; i++)
    {
        Simul *new_simul = create_simul(process_list[i]);
        simul_list[i] = new_simul;
    }

    Simul *In_CPU = NULL;
    Node *traverse_ptr;

    int record_size = 10;
    int *record = (int *)malloc(sizeof(int) * record_size);
    memset(record, '\0', sizeof(int) * 10);

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
            }
        }

        if (In_CPU == NULL)
        {
            In_CPU = delete (ready_queue, ready_queue->start);

            if (In_CPU != NULL)
                printf("[Time: %d] Process [%d] is executed by CPU\n", time, In_CPU->process->process_id);
        }

        if (time == record_size)
        {
            record_size += 10;
            record = (int *)realloc(record, sizeof(int) * record_size);
            memset(record + time + 1, '\0', sizeof(int) * 10);
        }

        if (In_CPU != NULL)
            record[time] = In_CPU->process->process_id + 1;

        time++;
    }

    Evaluation(simul_list, process_quantity);
    display_Gantt(record, time - 1);

    printf("------------------------------FCFS Scheduling END------------------------------\n");

    for (int i = 0; i < process_quantity; i++)
    {
        free(simul_list[i]);
    }
    free(simul_list);
    free(ready_queue);
    free(record);
}