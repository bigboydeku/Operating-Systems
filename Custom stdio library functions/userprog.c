#include "types.h"
#include "user.h"
#include "stdio.h"

int main(int argc, char * argv[]) {
	char * arguments[argc];
	for(int i = 0; i < argc ; i++)
		arguments[i] = argv[i+1];

	arguments[argc] = (char*)0;
	int time, timefinal, processTime;
	int  proc = fork();

	if (proc == 0)
		exec(arguments[0], arguments);
	else {
		time = uptime();
		wait();
		timefinal = uptime();
		processTime = timefinal - time;
		fprintf(mystdout, "uptime: %d\n", processTime); //uses my version of stdio.h
		flushBuff(mystdout); //flushes buffer
	}
	exit();
}
