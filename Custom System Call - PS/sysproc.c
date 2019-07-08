#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#define NULL (char*)0

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_ps(void) {
	
	struct proc process;
	char *states[] = { "unused", "embryo", "sleep ", "runble", "run   ", "zombie" };
	//char  * parentName;
	int counter = 0 ;
	char init[7]= "(init)\0";
	
	cprintf("pid\tname\tstate\t\tparent\n");
	cprintf("-----------------------------------------\n");
	for (int x= 0 ; x < NPROC ; x++) {
		process = getTable(x);
		//parentName = (char *) process.parent;
			
		switch(process.state) 
		{
			case RUNNING:
			case RUNNABLE:
			case SLEEPING:
				if ((char*)process.parent != NULL) 
					cprintf("%d\t%s\t%s\t\t%s\n", process.pid, process.name, states[process.state], process.parent-> name);
				else 
					cprintf("%d\t%s\t%s\t\t%s\n", process.pid, process.name, states[process.state], init);
				
				++counter;
				break;
			default:
				//cprintf("");
				break;
		}	
	}
	cprintf("\ntotal: %d\n", counter);
	for (int i = 0 ; i < ncpu ; i++) {
		if (((char*)cpus[i].proc) != NULL) 
			cprintf("cpu %d : %s\n", i, cpus[i].proc->name);
		else
			cprintf("cpu %d : %s\n", i, "idle");
	}
	return 0;
}
