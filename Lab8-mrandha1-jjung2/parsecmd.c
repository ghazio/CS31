
/*
 * Swarthmore College, CS 31
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
    return NULL;// if there is no ampersand
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
    char* cpy_cmdline= (char * ) cmdline;
    int space_checker=0;
    int counter=0;

    //finds the location of the ampersand
    char* ampersand_location=ampersand_finder(cpy_cmdline);

    //this checks if there is any space before the first non_space character
    cpy_cmdline=space_skipper(cpy_cmdline);
    //we set it to 0 and change it only if there is an ampersand
    *bg = 0;

    while(*cpy_cmdline!='\0'){
      space_checker=isspace(*cpy_cmdline);

      if (space_checker != 0){//if the character is space,we count one string and skip to next non_space character
        counter++;
        cpy_cmdline=space_skipper(cpy_cmdline);
      }

      else{//if it is a non_space, we go farther
          cpy_cmdline++;
        }

  //if there is an ampersand, it sets *bg to 1
      if (*cpy_cmdline == '&') {
          *bg = 1;
      }
    }


    //Allocate the memory for the argv
    result=malloc(sizeof(char*)*(counter+1));




    char* cpy_cmdline1= (char * ) cmdline;
    char* cpy_cmdline2= (char * ) cmdline;
//we use two points. We increment one pointer until it reaches a space, and then use the previous one to catch up
    space_checker=0;
    int lengthCurrentString = 0;//this will be used to track length of indivual elements
    int j = 0;//we will use this to keep record of members of array


//intialize every member of the results array
    for (int i=0; i<(counter+1);i++){
        result[i]=NULL;
        }



    while(*cpy_cmdline2!='\0'&& *cpy_cmdline2!='&'){
        //if the cpy_cmdline2 is pointing to space, we skip the spaces until
        //we reach a character.
        space_checker=isspace(*cpy_cmdline1);
        while (space_checker != 0 && *cpy_cmdline2 != '\0'){
          cpy_cmdline1++;
          cpy_cmdline2++;
          space_checker=isspace(*cpy_cmdline1);
        }

          //iterate through string until we reach a space, or the null terminal,
          //or ampersand. We keep track of string length through counter
          space_checker = isspace(*cpy_cmdline2);
          while (space_checker == 0 && *cpy_cmdline2 != '\0' && *cpy_cmdline2 != '&') {
              cpy_cmdline2 ++;
              lengthCurrentString ++;
              space_checker = isspace(*cpy_cmdline2);
              }
          //once we reach an end, we malloc for that substring/token into results array
          if (lengthCurrentString != 0){
            result[j]=malloc(sizeof(char)*(lengthCurrentString+1));
            for (int i=0; i<(lengthCurrentString);i++){
                  result[j][i]=*cpy_cmdline1;
                  cpy_cmdline1++;

            }
            //adds null terminater to the end of the string/token
            result[j][lengthCurrentString]='\0';
          }

          //increment j to move to the next bucket of our array
          j++;

          //reset lengthCurrentString to 0
          lengthCurrentString=0;

      }


    return result;
}
