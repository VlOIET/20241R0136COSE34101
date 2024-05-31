#include "CPU_Scheduler.h"

// pid는 랜덤으로 생성시 구별 어려움 -> 0에서 증가하는 값을 받아서 사용
Process *Create_Process(int pid)
{
    Process *new_process = (Process *)malloc(sizeof(Process));

    new_process->Process_id = pid;
    new_process->CPU_burst = rand() % 10 + 1; // 1 ~ 10 사이 랜덤
    new_process->IO_burst = rand() % 6; // 0 ~ 5 사이 랜덤
    new_process->Priority = rand() % 10 + 1; // 1 ~ 10 사이 랜덤
    new_process->Arrival_time = rand() % 11; // 0 ~ 10 사이 랜덤
}