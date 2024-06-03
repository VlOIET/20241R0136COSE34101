#include "CPU_Scheduler.h"
// level은 priority로 구분되고, 각 레벨은 모두 RR방식으로 스케줄링 된다.
void Multilevel_queue(Process **process_list, int process_quantity, int time_quantum)
{
    printf("---------------------------Multilevel Queue Scheduling-------------------------\n");

    int time = 0;
    int process_end = 0;
    int quantum = 0;
    int max_priority = 0;

    // Multilevel Queue 만들기
    for (int i = 0; i < process_quantity; i++)
    {
        if (max_priority < process_list[i]->priority)
            max_priority = process_list[i]->priority;
    }

    Queue **ready_queue_priority = (Queue **)malloc(sizeof(Simul *) * max_priority);
    for (int i = 0; i < max_priority; i++)
    {
        Queue *ready_queue = make_queue();
        ready_queue_priority[i] = ready_queue;
    }

    Simul **simul_list = (Simul **)malloc(sizeof(Simul *) * process_quantity); // Simul 구조체 생성 및 메모리 할당
    for (int i = 0; i < process_quantity; i++)
    {
        Simul *new_simul = create_simul(process_list[i]);
        simul_list[i] = new_simul;
    }

    Simul *In_CPU = NULL;
    Node *traverse_ptr;

    // 실행 중인 프로세스 저장을 위한 배열 생성
    int record_size = 10;
    int *record = (int *)malloc(sizeof(int) * record_size);
    memset(record, '\0', sizeof(int) * 10);

    while (process_end < process_quantity) // 스케줄링 시작
    {
        sleep(1);

        if (In_CPU != NULL)
        {
            In_CPU->process->CPU_burst -= 1;
            quantum++;

            if (In_CPU->process->CPU_burst == 0) // 프로세스가 CPU 실행을 모두 완료한 경우
            {
                printf("[Time: %d] Process [%d] is terminated\n", time, In_CPU->process->process_id);
                In_CPU->end_time = time;
                In_CPU = NULL;
                process_end++;
                quantum = 0;
            }
            else if (quantum == time_quantum) // 프로세스가 time_quantum 만큼 실행된 경우
            {
                printf("[Time: %d] Process [%d] is halted\n", time, In_CPU->process->process_id);
                insert(ready_queue_priority[In_CPU->process->priority - 1], In_CPU);
                In_CPU->waiting_time -= 1; // ready_queue 내에 없었음에도 waiting time이 증가하는 것을 방지
                In_CPU = NULL;
                quantum = 0;
            }
        }

        // ready_queue의 프로세스들 waiting time 증가
        for (int i = 0; i < max_priority; i++)
        {
            traverse_ptr = ready_queue_priority[i]->start;

            while (ready_queue_priority[i]->start != NULL)
            {
                traverse_ptr->simul->waiting_time += 1;

                if (traverse_ptr == ready_queue_priority[i]->end)
                    break;

                traverse_ptr = traverse_ptr->next;
            }
        }

        // arrive time에 도달한 프로세스를 ready_queue에 삽입
        for (int i = 0; i < process_quantity; i++)
        {
            if (simul_list[i]->process->arrival_time == time)
            {
                printf("[Time: %d] Process [%d] is inserted in ready queue\n", time, simul_list[i]->process->process_id);
                insert(ready_queue_priority[simul_list[i]->process->priority - 1], simul_list[i]);
            }
        }

        if (In_CPU == NULL) // CPU에 프로세스가 할당되지 않았을 경우
        {
            Queue *now_queue = NULL;
            for (int i = 0; i < max_priority; i++) // 가장 높은 레벨의 레디큐부터 프로세스가 있는지 찾음
            {
                if (ready_queue_priority[i]->start != NULL)
                {
                    now_queue = ready_queue_priority[i];
                    break;
                }
            }

            if (now_queue != NULL) // ready_queue들에 프로세스가 있는 경우
            {
                In_CPU = delete (now_queue, now_queue->start);

                if (In_CPU->first_cpu_time == -1)
                    In_CPU->first_cpu_time = time;
                printf("[Time: %d] Process [%d] is executed by CPU\n", time, In_CPU->process->process_id);
            }
        }

        if (time == record_size) // 배열의 크기가 부족하면 추가 할당
        {
            record_size += 10;
            record = (int *)realloc(record, sizeof(int) * record_size);
            memset(record + time, '\0', sizeof(int) * 10);
        }

        if (In_CPU != NULL) // CPU에 할당된 프로세스가 있는 경우
            record[time] = In_CPU->process->process_id + 1;

        time++;
    }

    Evaluation(simul_list, process_quantity);
    display_Gantt(record, time - 1);

    printf("-------------------------Multilevel Queue Scheduling END-----------------------\n");

    for (int i = 0; i < process_quantity; i++)
    {
        free(simul_list[i]);
    }
    free(simul_list);
    for (int i = 0; i < max_priority; i++)
    {
        free(ready_queue_priority[i]);
    }
    free(ready_queue_priority);
    free(record);
}