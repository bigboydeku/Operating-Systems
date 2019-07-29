#include "fcntl.h"
#include "types.h"
#include "user.h"
#include "stat.h"


/* Programmed by Denis Nadarevic. 
* Program uses syscall chpty. 
* User executes program with two arguments, pid and priority.
* Inputs are used to change priority of a process.
*/
int main(int argc, char * argv[]) {
	int priority;
	int pid;
	
	//take two arguments, priority and process id, verify only two
	if (argc < 3 ) {
			exit();
	}

	
	pid = atoi( argv[1] );
	priority = atoi( argv[2] );
	
	//im unsure what "range of priority values" means, but im assuming you mean the actual integer, so...
	//im making a range from 0 to 30
	if (priority < 0 || priority > 30) {
		printf(1,"Priority value out of range! Pick within the range -> 0-30.");
		exit();
	}
	
	chpty(pid, priority); // change priority using system call that i made.
	
	exit();
}
