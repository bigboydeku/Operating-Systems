Assignment 5 - Denis Nadarevic - 104445626

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ Introduction ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This folder contains modified XV6 files that were used to understand how priority values aid in the selection of which processes should be run. I added extra stuff to be able to understand how to run the process with the highest priority value (in this case, the lower the number, the higher the priority); I did this by editing things such as the scheduler. Note: Any example will have a shell line indicator "$". Don't type this when testing, its just for showing.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ Explaining the Range of the Priority Values ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
By default, a process’ priority is set to 10.  Newly loaded processes have a value of 2. I made the range between 0 and 30 to be able to easily tell which values are lower and higher, any submitted value sent into assign5part2.c will change the priority only if its within the range. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ How to Set Priority in the Program ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Once the processes have loaded up, you can change the priority values of a process by using the program assign5.c. You can simply type “assign5part2 [process ID] [priority value]”. It takes two parameters, first the process ID and, second, the priority value you want to change the process to. By doing this and typing “ps”, you can see that the process’ priority value has changed. Example: 

	$ assign5part2 15 8

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ How Starvation is Avoided ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
To avoid starvation, the test programs that forked n times must be made in a way where the parent must wait for the child until the child’s process is done. This is done by adding a wait() in the parent’s code. Once the child terminates, it will then send a signal to the parent informing it of its termination. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ How to Test My Solution ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
To test it, it is best to start multiple processes at once, using this command:

	$ assign5 &; assign5 &; assign5 &; assign5 &

This command runs the program assign5.c multiple times in the background. Once it states that the programs and the children have been made, type ps to list all the processes that are running, runnable, or sleeping. Multiple processes will show up. To change the priority of a process, refer to the "How to Set Priority in the Program" section in this README. After changing the priority value for a process, it will take a very small amount of time until the process you changed the value of starts running (assuming you gave it the highest priority).

!! This assignment was done by Denis Nadarevic from the University of Windsor and it is for academic use. Any use by others without Denis Nadarevic’s permission is prohibited. !!

