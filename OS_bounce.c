//Raneem Alomari 2006352
//demonstrate wait_marcos_status()
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <sys/types.h>
#include<unistd.h>
void waitexample (){
  int i, status;
  pid_t pid[5];
  // genrate child procee
 for (i = 0; i < 5; i++)
   {
   if ((pid[i] = fork ()) == 0)
	{ 
	 sleep (1);
	 exit (100 + i);}
  }
    //test wait status
 for (i = 0; i < 5; i++)
   {
      pid_t cpid = waitpid (pid[i], &status, 0);
   if (WIFEXITED (status))// if the child terminated normally.
	printf ("Child %d terminated normally with status: %d\n",
		cpid, WEXITSTATUS (status));
    
   else if (WIFSIGNALED (status)){//if child terminated because it received unhandled signal.
    printf ("child  %d killed by signal %d ", cpid, WTERMSIG (status)); //returns the signal number that terminated the child 
	}
	else if (WCOREDUMP (status)){ // if child terminated and produced a core dump.
      printf ("(core dumped)\n");
   }
   else if (WIFSTOPPED (status))// if child stopped.
   {
    printf ("child %d stopped by signal %d\n", cpid, WSTOPSIG (status)); //returns signal number that caused child to stop.
   }  
   else
   {		// lastly else if there no wait macros status then procee continued normally
    printf ("child %d continued status: %d \n", cpid,(unsigned int)status);
   }
   }
}
int main ()
{
  waitexample ();
  return 0;
}

