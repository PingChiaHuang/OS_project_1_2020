#ifndef _CPU_H_
#define _CPU_H_

#define _GNU_SOURCE
#include <sys/types.h>
#include <sched.h>

#define PARENT 0
#define CHILD  1

void set_CPU(pid_t pid, int core);

void unit_time(int n);

#endif
