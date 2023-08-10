/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parsecmd.h"

/* The maximum size of your circular history queue. */
#define MAXHIST 10

/*
 * A struct to keep information one command in the history of
 * command executed
 */
struct histlist_t {
    unsigned int cmd_num;
    char cmdline[MAXLINE]; // command line for this process
};

/* Global variables declared here.
 * For this assignment, only use globals to manage history list state.
 * all other variables should be allocated on the stack or heap.
 *
 * Recall "static" means these variables are only in scope in this .c file. */
static struct histlist_t history[MAXHIST];

  int added= 0; //this helps me keep track of what has been entered or not into history queue
 int queue_next = 0;//helps me keep record of the index of each of the inputs
 int real_index[MAXLINE];//This array will keep record of real indices of all inputs
 int queue_size=0;//this keeps record of the size of the history queue



/*
Input: pointer to commandline
Function: adds the new user input to the history queue
Output: Returs nothing
*/
void history_adder(char* commandline);
/*
Input: Nothing(uses global variables)
Function: if our history queue is already filled, this function kicks the first
          index and first elements in our real_index array and our history array.
          It basically moves each element to previous slot and  frees up the
          last slot in each case.
Output: Returs nothing
*/
void history_arranger();
/*
Input: array of pointers to arguments and pointer to commandline
Function: it finds if the inputed index to be found is in the index list. If it is,
          then it makes it the new commandline and in doing so, makes sure that the
          instruction is carried out and recorded.
Output: Returs nothing
*/
void index_finder(char** args,char* cmdline);

/*
Input: singal that a child process has completed execution
Function: reaps a dead child process without blocking the shell.
Output: Returns nothing
*/
void freer(char ** args){
  char**  cpy_args=args;
  while (*cpy_args != NULL){//as long as it is not a NULL

    free(*cpy_args);
    cpy_args ++;
  }
  free(args);
}

void sigchild_handler(int sig){
  pid_t pid;
   while((pid = waitpid(-1, NULL, WNOHANG)) >0){

  }
}



int main(int argc, char **argv) {
    char cmdline[MAXLINE];
    char **args=NULL;
    int bg;
    int pid;


    //adds a call to signal to register our SIGCHLD signal handler.
    signal(SIGCHLD,sigchild_handler);

    while(1) {
        // prints the shell prompt

        int added=0;//writes added as 0 for each input
        int valid_input=0;//this would be set to 1 if the shell accepts the input
                          // it will help us tell if the input was not valid
        printf("cs31shell> ");
        fflush(stdout);

        // reads in the next command entered by the user
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
        }
        if (feof(stdin)) { /* End of file (ctrl-D) */
            fflush(stdout);
            exit(0);
        }
        printf("DEBUG: %s\n", cmdline);
        //  makes a call to the parsing library to parse it into its
        //args format

        args=parse_cmd_dynamic(cmdline,&bg);

        if(args[0]==NULL){
          continue;
        }
        //if the first argument is a string saying exit, it frees the array and exits.
        if(strcmp(args[0],"exit")==0){
          printf("Quiting!! \n");
          fflush(stdout);
          freer(args);
          return 0;
        }

        if(strchr(args[0],'!')!=NULL){
          if (*(args[0]+1)>='0' && *(args[0]+1)<='9'){
            index_finder(args,cmdline);//sets cmdline to some previous cmdline if it was able to find it. Otherwise, it remains as it was.
            history_adder(cmdline);//we add recovered/unrecovered cmdline to history.
            added=1;//to mark that this has cmdline has been added.
            freer(args);//this frees up the args array.
            args=parse_cmd_dynamic(cmdline,&bg);//this makes sure that the arguments are update too.

          }

          //prints a error message when someone inputs something other than the exclaimation point
          else{
            printf("You can only enter a digit after ! to access a previous command\n");
            fflush(stdout);
          }
        }

      // if the first argument is history, it prints all the history.
      //adds the commandline to history
      if(strcmp(args[0],"history")==0){

      history_adder(cmdline);//we call it before we print so that history also shows up on the list
      added=1;//to mark that this has cmdline has been added.
      if (queue_size<11){
      for(int i =0; i<queue_size; i++){

          printf("%d\t  %s\t \n",(real_index[i]+1),history[i].cmdline);
          fflush(stdout);

      }}
      else{
          for(int i =0;i<MAXHIST;i++){
            printf("%d\t  %s\t \n",(real_index[(i+queue_next)%MAXHIST]+1),history[(i+queue_next)%MAXHIST].cmdline);
            fflush(stdout);
          }


      }
    }
        //if the first argument has the character NULL in it, it calls the index_finder function, which was described above.


      if (added==0){
        history_adder(cmdline);//if the current cmdline has not yet been added to queue.
      }
      int rt_val=0;
      if (bg!=1){//for foreground
        //cals fork
        pid=fork();
        if (pid==-1){
          printf("Fork did not work. Exiting! \n");
          fflush(stdout);
          exit(1);

        }
        if (pid==0){
          rt_val=execvp(args[0],args);//calls sleeper only for the child
          if(rt_val==-1 && strchr(args[0],'!')==NULL &&strcmp(args[0],"history")!=0){
              printf("Command is not recognised\n");
              fflush(stdout);
              exit(0);
          }
          }
          //waits until the child is dead and reaped before allowing the function to process
          pid = waitpid(pid, NULL, 0);
        }
      else{//for background
        pid=fork();
        if (pid==-1){
          printf("Fork did not work. Exiting! \n");
          fflush(stdout);
          exit(0);

        }
        //calls sleeper only for the child
        if (pid==0){
          rt_val=execvp(args[0],args);
          if((rt_val==-1 && strchr(args[0],'!')==NULL &&strcmp(args[0],"history")!=0)){
              printf("Command is not recognised\n");
          }

          }
        }
      //frees up the arguments array from heap.
      freer(args);


    }

    return 0;
}

void history_adder(char* commandline){
  int index=0;//to keep track

  if (queue_size<=MAXHIST){//only increments the variable if it is less than 10. We use this later in main.
    queue_size++;
  }

  index=queue_next%MAXHIST;//finds where we need to input the data in the array.


 real_index[index]=queue_next;//this stores the real indices of the entered command if it has not acceded 10
 queue_next++;//increments


 int i=0;
 while(commandline[i]!='\0'){//copies the commandline until it reaches null terminator.
  history[index].cmdline[i] =commandline[i];
  i++;
}
  history[index].cmdline[i]='\0';//adds null terminator to the end.

}



void index_finder(char** args,char* cmdline ){
char* args_used=(args[0]+1);
int index_used=atoi(args_used)-1;

int j=0;
int found=0;
int index_inarray=0;
if (queue_size>MAXHIST){//if the list has overflowed already
  for (int i=0;i<MAXHIST;i++){
    if(real_index[i]==index_used){
      found=1;
      index_inarray=i;
    }
  }
}
else{//if it is less than or equal to 9
  index_inarray=index_used;
  found=1;
}



if(found==0){//if not found

  printf("you cannot access the command line at this index\n");
}
else{//if found, it reloads it into the cmdline argument
  while(history[index_inarray].cmdline[j]!='\0'){
    cmdline[j]=history[index_inarray].cmdline[j];
    j++;
  }
    cmdline[j]='\0';
}
}
