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
        Process *new_process = Create_Process(i);
        process_list[i] = new_process;
    }

    for (int i = 0; i < process_quantity; i++)
    {
        Process *now_process = *(process_list + i);
        printf("%d %d %d %d %d\n", now_process->Process_id, now_process->CPU_burst, now_process->IO_burst, now_process->Priority, now_process->Arrival_time);
    }

    for (int i = 0; i < process_quantity; i++)
    {
        free(process_list[i]);
    }
    free(process_list);
}