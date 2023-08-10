
 /* Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsecmd.h"

//To do: fix valgrind errors, do last case where ampersand is attached to last
//string


//this function finds if the commandline contains '&'. It takes in a string and
//returns an address
char* ampersand_finder(char* cmdline){

    while (*cmdline!='\0'){
      if (*cmdline=='&'){
        return cmdline;
      }
    cmdline++;
    }
return NULL;
}
//when called, this function checks if the pointer passed in is pointing to a
// space. If it is, then it keeps incrementing until the pointer is pointing to a
// non_space character.
char* space_skipper(char* cmdline){
  int space_checker = isspace(*cmdline);
  while (space_checker != 0){
    cmdline++;
    space_checker=isspace(*cmdline);
  }
return cmdline;

}

char **parse_cmd_dynamic(const char *cmdline, int *bg) {
    char **result = NULL;
    //int len_input=strlen(cmdline);
    char* cpy_cmdline= (char * ) cmdline;
    int space_checker=0;
    int counter=0;
    char* ampersand_location=ampersand_finder(cpy_cmdline);
    space_checker=isspace(*cpy_cmdline);

    //Step 1: count the inputs, need to make sure that we don't count the
    //ampersand if there is one in the command line. If there is an ampersand,
    //we set bg = 1



//this checks if there is any space before the first non_space character
    cpy_cmdline=space_skipper(cpy_cmdline);

    *bg = 0;
    while(*cpy_cmdline!='\0'){
      space_checker=isspace(*cpy_cmdline);
      if (space_checker != 0){
        //printf("counter: %d\n",counter);
        counter++;
        cpy_cmdline=space_skipper(cpy_cmdline);
      }
      else{
          cpy_cmdline++;
        }
      if (*cpy_cmdline == '&') {
          *bg = 1;
      }
    }

  //  printf("counter end: %d\n",counter+1);

    //Step 2: Allocate the memory for the argv
    result=malloc(sizeof(char*)*(counter+1));




      char* cpy_cmdline1= (char * ) cmdline;
      char* cpy_cmdline2= (char * ) cmdline;
      space_checker=0;
      int lengthCurrentString = 0;
      int j = 0;








      while(*cpy_cmdline2!='\0'){
        //get rid of all of white space before finding a character, unless we have
        // space after the last substring, in which case we have to increment
        //until we find the null terminator
        space_checker=isspace(*cpy_cmdline1);
        while (space_checker != 0 && *cpy_cmdline2 != '\0'){
          cpy_cmdline1++;
          cpy_cmdline2++;
          space_checker=isspace(*cpy_cmdline1);
        }
        //first consider the case where the first character of the string
        //is not an ampersand
          //iterate through string until we reach a space or ampersand, keeping
          //track of string length through counter
          space_checker = isspace(*cpy_cmdline2);
          while (space_checker == 0 && *cpy_cmdline2 != '\0') {
              cpy_cmdline2 ++;
              space_checker = isspace(*cpy_cmdline2);
              lengthCurrentString ++;
              }

          if (lengthCurrentString != 0){
            result[j]=malloc(sizeof(char)*(lengthCurrentString+1));
          //  printf("length: %d\n",lengthCurrentString);
            for (int i=0; i<(lengthCurrentString);i++){

                //  printf("%d  %c\n",i,*cpy_cmdline1);
                  result[j][i]=*cpy_cmdline1;
                  cpy_cmdline1++;

            }
            result[j][lengthCurrentString]='\0';
          }

          //lengthCurrentString also represents the index of the null terminator
          //in that string
          printf("j:%d\n",j);
          //increment j to move to the next bucket of our array
          j++;

          //reset lengthCurrentString to 0
          lengthCurrentString=0;
        }
        else{
          // if the first character of the string is an ampersand, we simply
          //increment by one to reach the null terminator and
          //exit the while loop
          cpy_cmdline2 ++;
        }
      }
    printf("end j:%d\n",j);
    result[j] = NULL;




    return result;
}
