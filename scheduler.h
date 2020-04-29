#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "process.h"

#define FIFO 1
#define RR   2
#define SJF  3
#define PSJF 4

int next_process(Process* processes, int process_num, int policy_index, int running, int last, Process** mapping, int time);

void schedule(Process* processes, int process_num, int policy_index);

#endif
