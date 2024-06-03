// 싱글코어로 구현
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

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
    int first_cpu_time;
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

// Simulation을 위한 구조체 생성
Simul *create_simul();

// Scheduling Algortihm들 구현
void FCFS(Process **process_list, int process_quantity);
void SJF(Process **process_list, int process_quantity);
void Priority(Process **process_list, int process_quantity);
void RR(Process **process_list, int process_quantity, int time_quantum);
void Preemptive_SJF(Process **process_list, int process_quantity);
void Preemptive_Priority(Process **process_list, int process_quantity);
void Multilevel_queue(Process **process_list, int process_quantity, int time_quantum);

// Evaluation 함수 구현
void Evaluation(Simul **simul_list, int process_quantity);
void display_Gantt(int *record, int time);
