#include "CPU_Scheduler.h"

// pid는 랜덤으로 생성시 구별 어려움 -> 0에서 증가하는 값을 받아서 사용
Process *create_process(int pid)
{
    Process *new_process = (Process *)malloc(sizeof(Process));

    new_process->process_id = pid;
    new_process->CPU_burst = rand() % 8 + 1; // 1 ~ 8 사이 랜덤
    new_process->IO_burst = rand() % 5;      // 0 ~ 4 사이 랜덤
    new_process->arrival_time = rand() % 4;  // 0 ~ 3 사이 랜덤
    new_process->priority = rand() % 5 + 1;  // 1 ~ 5 사이 랜덤

    return new_process;
}

Simul *create_simul(Process *process)
{
    Simul *new_simul = (Simul *)malloc(sizeof(Simul));
    new_simul->process = process;
    new_simul->first_cpu_time = -1;
    new_simul->end_time = 0;
    new_simul->waiting_time = 0;

    return new_simul;
}

void Evaluation(Simul **simul_list, int process_quantity)
{
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    for (int i = 0; i < process_quantity; i++)
    {
        total_waiting_time += simul_list[i]->waiting_time;
        total_turnaround_time += (simul_list[i]->end_time - simul_list[i]->process->arrival_time);
        total_response_time += (simul_list[i]->first_cpu_time - simul_list[i]->process->arrival_time);
    }

    printf("Average waiting time : %.2lf\n", (double)total_waiting_time / process_quantity);
    printf("Average turnaround time : %.2lf\n", (double)total_turnaround_time / process_quantity);
    printf("Average response time : %.2lf\n", (double)total_response_time / process_quantity);
}

void display_Gantt(int *record, int time)
{
    printf("\nGantt Chart\n");

    int before = 0;
    int now = 0;

    // 0번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
        {
            if (i == 0)
                printf("0");
            else
                printf("  ");
        }
        else
            printf("   ");
    }
    printf("%d", time);
    printf("\n");

    // 1번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
            printf("--");
        else
            printf("---");
    }
    printf("-");
    printf("\n");

    // 2번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
        {
            if (i == 0)
                printf("| ");
            else
                printf("  ");
        }
        else
            printf("|%d ", now - 1);
    }
    printf("|");
    printf("\n");

    // 3번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
            printf("--");
        else
            printf("---");
    }
    printf("-");
    printf("\n");

    // 4번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
            printf("  ");
        else
            printf("^  ");
    }
    printf(" ");
    printf("\n");

    // 5번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
            printf("  ");
        else
            printf("|  ");
    }
    printf(" ");
    printf("\n");

    // 6번째 줄
    before = 0;
    now = 0;
    for (int i = 0; i < time; i++)
    {
        if (i != 0)
            before = now;

        now = record[i];

        if (before == now)
            printf("  ");
        else
            printf("%02d ", i);
    }
    printf(" ");
    printf("\n");
}
