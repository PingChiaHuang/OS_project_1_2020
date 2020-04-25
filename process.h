#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>

#define MY_PRINTK   334
#define MY_GET_TIME 335

typedef struct process {
	char name[32];
	int ready_time;
	int exec_time;
	int run_time;
	int start_time;
	int end_time;
	pid_t pid;
	unsigned long long create_time_sec;
	unsigned long long create_time_nsec;
	unsigned long long start_time_sec;
	unsigned long long start_time_nsec;
	unsigned long long end_time_sec;
	unsigned long long end_time_nsec;
} Process;


void unblock(pid_t pid, int core);

void block(pid_t pid, int core);

void create(Process* process);

#endif
