// 구현한 함수들을 실행하는 공간
// 처음에 몇개의 프로세스를 생성할 것인지 결정 후 배열이 프로세스들을 하나 하나 가리키도록
// Create_Process 함수에 pid 전달

#include "CPU_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int process_quantity = 0;

    if (argc != 2)
    {
        printf("Parameters input error.");
        return -1;
    }

    process_quantity = atoi(argv[1]);

    Process **process_list = (Process **)malloc(sizeof(Process *) * process_quantity);

    for (int i = 0; i < process_quantity; i++)
    {
        Process *new_process = create_process(i);
        process_list[i] = new_process;
        printf("%d %d %d %d %d\n", new_process->process_id, new_process->CPU_burst, new_process->IO_burst, new_process->arrival_time, new_process->priority);
    }

    FCFS(process_list, process_quantity);

    for (int i = 0; i < process_quantity; i++)
    {
        free(process_list[i]);
    }
    free(process_list);
}