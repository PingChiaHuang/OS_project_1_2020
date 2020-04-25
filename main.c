#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "scheduler.h"

int compare(const void* a, const void* b) {
	Process* first = (Process*) a;
	Process* second = (Process*) b;
	return first->ready_time - second->ready_time;
}

int main() {
	
	char policy[16];
	int process_num;
	scanf("%s", policy);
	scanf("%d", &process_num);
	
	Process* processes = (Process*)malloc(process_num * sizeof(Process));
	for(int i = 0; i < process_num; i++) {
		scanf("%s%d%d", processes[i].name, &processes[i].ready_time, &processes[i].exec_time);
	}
	
	int policy_index;
	if(strcmp(policy, "FIFO") == 0) {
		policy_index = FIFO;
	} else if(strcmp(policy, "RR") == 0) {
		policy_index = RR;
	} else if(strcmp(policy, "SJF") == 0) {
		policy_index = SJF;
	} else if(strcmp(policy, "PSJF") == 0) {
		policy_index = PSJF;
	}
	
	qsort(processes, process_num, sizeof(Process), compare);
	schedule(processes, process_num, policy_index);
}
