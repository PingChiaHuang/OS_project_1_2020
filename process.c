#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#include "process.h"
#include "CPU.h"

void unblock(pid_t pid, int core) {

	set_CPU(pid, core);
	struct sched_param param;
	param.sched_priority = 99;
	sched_setscheduler(pid, SCHED_FIFO, &param);

}

void block(pid_t pid, int core) {

	struct sched_param param;
	param.sched_priority = 1;
	sched_setscheduler(pid, SCHED_FIFO, &param);
	set_CPU(pid, core);

}

void create(Process* process) {
	pid_t pid = fork();

	if(pid == 0) {
		
		pid = getpid();

		struct sched_param param;
		while(1) {
			sched_getparam(pid, &param);
			if(param.sched_priority == 99) {
				break;
			}
		}

		unsigned long long start_sec, start_nsec;
		syscall(MY_GET_TIME, &start_sec, &start_nsec);
		
		unit_time(process->exec_time);
		
		unsigned long long end_sec, end_nsec;
		syscall(MY_GET_TIME, &end_sec, &end_nsec);

		char str[256];
		sprintf(str, "[Project1] %d %llu.%09llu %llu.%09llu\n", pid, start_sec, start_nsec, end_sec, end_nsec);
		syscall(MY_PRINTK, str);

		exit(0);

	} else {
		block(pid, PARENT);
		process->pid = pid;
	}
}

