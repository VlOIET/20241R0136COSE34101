CC = gcc
TARGET = a.out
OBJS = a.o b.o c1.o c2.o c3.o c4.o c5.o c6.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

a.o : CPU_Scheduler.c
	$(CC) -c -o a.o CPU_Scheduler.c

b.o : Simulator.c
	$(CC) -c -o b.o Simulator.c

c1.o : FCFS.c
	$(CC) -c -o c1.o FCFS.c

c2.o : SJF.c
	$(CC) -c -o c2.o SJF.c

c3.o : RR.c
	$(CC) -c -o c3.o RR.c

c4.o : Priority.c
	$(CC) -c -o c4.o Priority.c

c5.o : Preemptive_SJF.c
	$(CC) -c -o c5.o Preemptive_SJF.c

c6.o : Preemptive_Priority.c
	$(CC) -c -o c6.o Preemptive_Priority.c

clean :
	rm -f *.o
	rm -f $(TARGET)