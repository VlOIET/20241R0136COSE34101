#include "CPU_Scheduler.h"

// pid는 랜덤으로 생성시 구별 어려움 -> 0에서 증가하는 값을 받아서 사용
// 이거 컴파일 한번하면 랜덤이 정해짐. 나중에 고칠 수 있으면 고쳐야 할듯
Process *create_process(int pid)
{
    Process *new_process = (Process *)malloc(sizeof(Process));

    new_process->process_id = pid;
    new_process->CPU_burst = rand() % 10 + 1; // 1 ~ 10 사이 랜덤
    new_process->IO_burst = rand() % 6; // 0 ~ 5 사이 랜덤
    new_process->arrival_time = rand() % 11; // 0 ~ 10 사이 랜덤
    new_process->priority = rand() % 10 + 1; // 1 ~ 10 사이 랜덤
}