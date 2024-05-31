// 우선 싱글코어로 구현
//

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int Process_id;
    int CPU_burst;
    int IO_burst;
    int Arrival_time;
    int Priority;
} Process;

// Create_Process 함수 구현 -> 프로세스 생성
// Config 함수 구현
// Evaluation 함수 구현

// Scheduling Algortihm들 구현
// Preemptive는 다른 프로세스를 확인하는 기점을 변경함으로써 구현
// Alogrithm 실행할 때 레디 큐만 넣어서 가능할까?
// 안될 듯 알고리즘 함수 내에서 시간 돌리면서, 모든 상황을 저장해 두어야 Gantt Chart 구현가능할 것 같은데

Process *Create_Process(int pid);