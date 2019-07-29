
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define M_PI 3.14159265358979323846

/* Programmed by Denis Nadarevic.
    User inputs the number of times they want to fork the processes.
	if user does not specify how many times they want to fork, default is set to 1 time.
*/
int main(int argc, char *argv[]) {
	int n;
	float x = 0, z;
	if (argc < 2) { //default, make program fork only once
		n = 1;
	}
	else {
		n = atoi(argv[1]); //user's input
	}

	int pid;
	//forks n number of times, based off user inut
	for (int i = 0 ; i < n ; i++) 
	{
		pid = fork ();

		if (pid < 0) {
			printf(1, "%d fork failed!\n", getpid());
		} 
		else if (pid > 0) {
			printf(1, "%d creating %d...\n", getpid(), pid);
			wait (); //to avoid starvation
		} 
		else {
			printf(1, "%d born!\n",getpid() );
			for ( z = 0; z < 5000000.0; z += 0.03 )
				x =  x + M_PI * 69.42; 
			break;
		}
	}
	//wait();
	exit();
}
