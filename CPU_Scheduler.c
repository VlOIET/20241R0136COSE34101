#include "CPU_Scheduler.h"

// pid는 랜덤으로 생성시 구별 어려움 -> 0에서 증가하는 값을 받아서 사용
// 이거 컴파일 한번하면 랜덤이 정해짐. 나중에 고칠 수 있으면 고쳐야 할듯
Process *create_process(int pid)
{
    Process *new_process = (Process *)malloc(sizeof(Process));

    new_process->process_id = pid;
    new_process->CPU_burst = rand() % 8 + 1; // 1 ~ 10 사이 랜덤
    new_process->IO_burst = rand() % 5;       // 0 ~ 5 사이 랜덤
    new_process->arrival_time = rand() % 4;  // 0 ~ 6 사이 랜덤
    new_process->priority = rand() % 5 + 1;  // 1 ~ 5 사이 랜덤

    return new_process;
}

Simul *create_simul(Process *process)
{
    Simul *new_simul = (Simul *)malloc(sizeof(Simul));
    new_simul->process = process;
    new_simul->end_time = 0;
    new_simul->waiting_time = 0;

    return new_simul;
}

void Evaluation(Simul **simul_list, int process_quantity)
{
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < process_quantity; i++)
    {
        total_waiting_time += simul_list[i]->waiting_time;
        total_turnaround_time += (simul_list[i]->end_time - simul_list[i]->process->arrival_time);
    }

    printf("Average waiting time : %.2lf\n", (double)total_waiting_time / process_quantity);
    printf("Average turnaround time : %.2lf\n", (double)total_turnaround_time / process_quantity);
}