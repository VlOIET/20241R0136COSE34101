#include "CPU_Scheduler.h"

void Preemptive_Priority(Process **process_list, int process_quantity)
{
    printf("-------------------------Preemptive Priority Scheduling------------------------\n");

    int time = 0;
    int process_end = 0;
    int new_signal = 0;
    int change_signal = 0;
    Queue *ready_queue = make_queue();

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

            if (In_CPU->process->CPU_burst == 0) // CPU에 프로세스가 할당이 되었을 경우
            {
                printf("[Time: %d] Process [%d] is terminated\n", time, In_CPU->process->process_id);
                In_CPU->end_time = time;
                In_CPU = NULL;
                process_end++;
            }
        }

        // ready_queue의 프로세스들 waiting time 증가
        traverse_ptr = ready_queue->start;

        while (ready_queue->start != NULL)
        {
            traverse_ptr->simul->waiting_time += 1;

            if (traverse_ptr == ready_queue->end)
                break;

            traverse_ptr = traverse_ptr->next;
        }

        // arrive time에 도달한 프로세스를 ready_queue에 삽입
        for (int i = 0; i < process_quantity; i++)
        {
            if (simul_list[i]->process->arrival_time == time)
            {
                printf("[Time: %d] Process [%d] is inserted in ready queue\n", time, simul_list[i]->process->process_id);
                insert(ready_queue, simul_list[i]);
                new_signal = 1;
            }
        }

        // Preemptive 구현
        Node *new_shortest_job = ready_queue->start;
        traverse_ptr = ready_queue->start;

        // ready_queue에 프로세스가 있고, 새로운 프로세스가 들어온 상황에서 CPU에 프로세스가 할당되어 있을 때
        while (ready_queue->start != NULL && new_signal == 1 && In_CPU != NULL)
        {
            Node *temp = traverse_ptr->next;

            // ready_queue를 순환하면서 CPU에 할당된 프로세스보다 높은 우선순위를 가진 프로세스를 찾음
            if (traverse_ptr->simul->process->priority < In_CPU->process->priority)
            {
                printf("[Time: %d] Process [%d] is halted\n", time, In_CPU->process->process_id);
                insert(ready_queue, In_CPU);
                In_CPU = delete (ready_queue, traverse_ptr);
                traverse_ptr = temp;
                change_signal = 1;

                if (temp == NULL)
                    break;
            }
            else
            {
                if (traverse_ptr == ready_queue->end)
                    break;

                traverse_ptr = traverse_ptr->next;
            }
        }

        // CPU에 할당된 프로세스가 preemptive로 인해 바뀌었을 경우
        if (change_signal)
            printf("[Time: %d] Process [%d] is executed by CPU\n", time, In_CPU->process->process_id);

        if (In_CPU == NULL) // CPU에 프로세스가 할당되지 않았을 경우
        {
            // ready_queue를 순환하면서 가장 높은 우선순위를 가지는 프로세스를 찾음
            Node *highest_priority_job = ready_queue->start;
            traverse_ptr = ready_queue->start;

            while (ready_queue->start != NULL)
            {
                if (traverse_ptr->simul->process->priority < highest_priority_job->simul->process->priority) // priority가 작을수록 더 빨리 실행
                {
                    highest_priority_job = traverse_ptr;
                }

                if (traverse_ptr == ready_queue->end)
                    break;

                traverse_ptr = traverse_ptr->next;
            }

            In_CPU = delete (ready_queue, highest_priority_job);

            if (In_CPU != NULL) // ready_queue에 프로세스가 있는 경우
            {
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

        new_signal = 0;
        change_signal = 0;
        time++;
    }

    Evaluation(simul_list, process_quantity);
    display_Gantt(record, time - 1);

    printf("-----------------------Preemptive Priority Scheduling END----------------------\n");

    // 할당된 메모리들 모두 해제
    for (int i = 0; i < process_quantity; i++)
    {
        free(simul_list[i]);
    }
    free(simul_list);
    free(ready_queue);
    free(record);
}