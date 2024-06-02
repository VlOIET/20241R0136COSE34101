// 우선 싱글코어로 구현
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct
{
    int process_id;
    int CPU_burst;
    int IO_burst;
    int arrival_time;
    int priority;
} Process;

typedef struct
{
    Process *process;
    int end_time;
    int waiting_time;
} Simul;

typedef struct Node
{
    Simul *simul;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *start;
    Node *end;
} Queue;

// Create_Process 함수 구현 -> 프로세스 생성
Process *create_process(int pid);

// Ready / Waiting Queue를 위한 Queue
Queue *make_queue();
void insert(Queue *queue_ptr, Simul *simul_ptr);
Simul *delete(Queue *queue_ptr, Node *target_ptr);
void remove_queue(Queue *queue_ptr);

Simul *create_simul();

// Scheduling Algortihm들 구현
// Preemptive는 다른 프로세스를 확인하는 기점을 변경함으로써 구현
// Alogrithm 실행할 때 레디 큐만 넣어서 가능할까?
// 안될 듯 알고리즘 함수 내에서 시간 돌리면서, 모든 상황을 저장해 두어야 Gantt Chart 구현가능할 것 같은데
void FCFS(Process **process_list, int process_quantity);
void SJF(Process **process_list, int process_quantity);
void Priority(Process **process_list, int process_quantity);
void RR(Process **process_list, int process_quantity, int time_quantum);

// Config 함수 구현
// Evaluation 함수 구현
void Evaluation(Simul** simul_list, int process_quantity);