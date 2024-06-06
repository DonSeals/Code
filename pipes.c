#include <stdio.h>
#include <string.h>   // for strlen
#include <stdlib.h>   // for exit
#include <unistd.h>

int main() 
{
	int pipes[2]; // allocates 2 pipes for, 0 (read) and 1 (write)
	int r;
	r = pipe(pipes); // creates pipes 0 and 1
	if (r < 0) {
		fprintf(stderr, "pipe failed\n\n");
		// stderr is a FILE* variable for the standard error file (terminal)
		exit(2);
	}fprintf;
	// use pipes[0] to read and pipes[1] to write

	int pid1 = fork(); // creates 1 child which inherits the above pipes. must create pipes before forking
	if (pid1 > 0) {  // PARENT
		int pid2 = fork(); // create second child
		if(pid2<0){
			fprintf(stderr, "FORK 2 FAILED\n\n");
			exit(2);
		}
		else if(pid2>0){ // parent 
			close(pipes[0]);  // close unusued pipes so children will send status
			close(pipes[1]);  // close unusued pipes so children will send status
			wait(NULL); // wait until child process(1) completes
			wait(NULL); // wait until child process(2) completes
		}
		else{ // pid2 == 0 (child) which is 2nd child created but first child acting?
			close(pipes[0]); // close unused pipe(read)
			dup2(pipes[1],STDOUT_FILENO); // redirect write end of pipe to [1] Standard Output in file descriptor table  -- pg 130  [Robbins and Robbins]
			execlp("ps","ps","-aux",(char *)NULL);
			close(pipes[1]);
			exit(0); // sends status to parent
		}

	}
	else if (pid1 == 0) { // CHILD
		char buff[1000];
		close(pipes[1]); 
		dup2(pipes[0],STDIN_FILENO);
		execlp("sort","sort","-r","-n","-k","5",(char *)NULL);
		close(pipes[0]); // closes read end of pipe after use
		exit(0); // sends status to parent

	}
	else {
		fprintf(stderr, "FORK 1 FAILED\n\n");
		return 1;
	}
	// both parent and child process get here:
	return 0;
}