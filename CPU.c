#define _GNU_SOURCE
#include <sys/types.h>
#include <sched.h>

#include "CPU.h"

#include <stdio.h>
void set_CPU(pid_t pid, int core) {
	
	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);
	CPU_SET(core, &cpu_set);

	sched_setaffinity(pid, sizeof(cpu_set), &cpu_set);
}

void unit_time(int n) {
	for(int i = 0; i < n; i++) {
		for(volatile unsigned long j = 0; j < 1000000UL; j++);
	}	
}
