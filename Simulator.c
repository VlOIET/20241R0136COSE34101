// 구현한 함수들을 실행하는 공간
#include "CPU_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int process_quantity = 0;
    int time_quantum = 0;

    if (argc != 2)
    {
        printf("Parameters input error.");
        return -1;
    }

    process_quantity = atoi(argv[1]);

    // 프로세스 생성 후 메모리에 할당된 리스트에 삽입
    Process **process_list = (Process **)malloc(sizeof(Process *) * process_quantity);

    for (int i = 0; i < process_quantity; i++)
    {
        Process *new_process = create_process(i);
        process_list[i] = new_process;
        printf("Pid: %d\tCPU_burst: %d  IO_burst: %d  Arrival_time: %d  Priority: %d\n", new_process->process_id, new_process->CPU_burst, new_process->IO_burst, new_process->arrival_time, new_process->priority);
    }

    // 스케줄러 유형 입력 받은 후 실행
    int type = 0;

    printf("-----------------------------Select Scheduler Type-----------------------------\n");
    printf("\t1) FCFS\n");
    printf("\t2) SJF\n");
    printf("\t3) Priority\n");
    printf("\t4) RR\n");
    printf("\t5) Preemptive_SJF\n");
    printf("\t6) Preemptive_Priority\n");
    printf("\t7) Multilevel Queue\n");
    printf("-----------------------------Select Scheduler Type-----------------------------\n");

    printf("Select: ");
    scanf("%d", &type);

    switch (type)
    {
    case 1:
        FCFS(process_list, process_quantity);
        break;

    case 2:
        SJF(process_list, process_quantity);
        break;

    case 3:
        Priority(process_list, process_quantity);
        break;

    case 4:
        printf("Input Time_quantum: ");
        scanf("%d", &time_quantum);
        RR(process_list, process_quantity, time_quantum);
        break;

    case 5:
        Preemptive_SJF(process_list, process_quantity);
        break;

    case 6:
        Preemptive_Priority(process_list, process_quantity);
        break;

    case 7:
        printf("Input Time_quantum: ");
        scanf("%d", &time_quantum);
        Multilevel_queue(process_list, process_quantity, time_quantum);
        break;
    }

    // 할당된 메모리 해제
    for (int i = 0; i < process_quantity; i++)
    {
        free(process_list[i]);
    }
    free(process_list);
    return 0;
}