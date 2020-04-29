#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "process.h"
#include "scheduler.h"
#include "CPU.h"

int next_process(Process* processes, int process_num, int policy_index, int running, int last, Process** mapping, int time) {
	if(running != -1 && (policy_index == FIFO || policy_index == SJF)) {
		return running;
	} else if(policy_index == FIFO) {
		
		int index = last + 1;
		return processes[index].pid == -1 ? -1 : index;

	} else if(policy_index == SJF || policy_index == PSJF) {
		
		int res = -1;
		int time = 2147483647;
		for(int i = 0; i < process_num; i++) {
			if(processes[i].pid != -1 && processes[i].exec_time < time && processes[i].run_time < processes[i].exec_time) {

				res = i;
				time = processes[i].exec_time;
			}
		}
		return res;

	} else if(policy_index == RR) {
		
		if(running == -1 || processes[running].run_time % 500 == 0) {
			
			if(running != -1) {
						
				int index = 0;
				for(; index < process_num; index++) {
					if(mapping[index]->pid != -1 && mapping[index]->run_time < mapping[index]->exec_time) {
						break;
					}
				}
				
				int i = index;
				Process* tmp = mapping[i];
				for(; i < process_num - 1; i++) {
					if(mapping[i + 1]->pid != -1 && mapping[i + 1]->ready_time < time) {
						mapping[i] = mapping[i + 1];
					} else {
						break;
					}
				}
				mapping[i] = tmp;
			}

			for(int i = 0; i < process_num; i++) {
				if(mapping[i]->pid != -1 && mapping[i]->run_time < mapping[i]->exec_time) {
					return mapping[i] - processes;
				}
			}
			return -1;

		} else {
			
			return running;

		}
	}

	return -1;
}

void debug(Process* processes, int process_num, int time, int last) {
	for(int i = 0; i < process_num; i++) {
		printf("i: %d, pid: %d, ready: %d, exec: %d, run: %d, time: %d, last: %d\n", i, processes[i].pid, processes[i].ready_time, processes[i].exec_time, processes[i].run_time, time, last);
	}
}

void schedule(Process* processes, int process_num, int policy_index) {

	int time = 0;
	int running = -1;
	int last = -1;
	int finish_process = 0;

	Process** mapping = (Process**)malloc(sizeof(Process*) * process_num);
	for(int i = 0; i < process_num; i++) {
		mapping[i] = &processes[i];
	}		

	pid_t pid = getpid();
	unblock(pid, PARENT);

	for(int i = 0; i < process_num; i++) {
		processes[i].pid = -1;
	}

	while(finish_process != process_num) {

		for(int i = last + 1; i < process_num; i++) {
			if(processes[i].ready_time == time) {
				create(&processes[i]);
			}
		}
		
		int next = next_process(processes, process_num, policy_index, running, last, mapping, time);
		/*
		if(time % 100 == 0) {
			printf("time = %d, next = %d\n", time, next);
			for(int i = 0; i < process_num; i++) {
				printf("%s ", mapping[i]->name);
			}
			printf("\n");
		}*/
		if(next != running) {
			if(running != -1) {
				block(processes[running].pid, PARENT);
			}
			if(next != -1) {
				unblock(processes[next].pid, CHILD);
			}
			running = next;
		}
		
		unit_time(1);
		
		if(running != -1) {
			
#ifdef THEORETICAL
			if(processes[running].run_time == 0) {
				processes[running].start_time = time;
			}
#endif
			
			processes[running].run_time++;
			last = running;
			
			if(processes[running].run_time == processes[running].exec_time) {
				
				waitpid(processes[running].pid, NULL, 0);

#ifdef THEORETICAL
				printf("%s %d\n", processes[running].name, time - processes[running].start_time + 1);
#else
				printf("%s %d\n", processes[running].name, processes[running].pid);
#endif
				
				fflush(stdout);
				
				running = -1;
				finish_process++;
			}
		}

		time++;
	}
}
