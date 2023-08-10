/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */


/* System headers to be included. */

/* Note: your string librhan, equal to, or greater than zero if s1 is found,  respec‐
       tively, to be less than, to match, or be greaterary functions should NOT print anything in the code
 * that you submit.  The standard I/O library is included here in case you
 * wish to do any debug printing as you go. */
#include <stdio.h>
#include <stdlib.h>

/* Note: You *SHOULD NOT* include <string.h> or use any C-library string
 * functions in this file! */


/* Local headers to be included. */

#include "my_strings.h"


/* Library functions for you to implement.
 * Look at the manual page and/or the my_strings.h header file for a
 * description of the arguments and return types.  The man pages will also give
 * you a summary of the expected behavior. */

/* Note: You *SHOULD NOT* change the prototypes of these functions!  They
 * should have the same parameter types and return types as their C-library
 * counterparts! */

/*Inputs: takes in address to two strings
  Output: returns the address of the
  it puts the second string at the end of the first string and returns the
  pointer to the first string. It does this by allocating
  */
char *my_strcat(char *dest, const char *src){
  char *final_str = NULL;
  char *final_str_cpy=NULL;
  char *copy_src = (char * ) src;//we get a pointer that points to src but is not constant
  int total_length;



  /*calculates the totallength of both of the strings and subtracts one from it
   because there are two null terminaters in the two strings*/
  total_length= my_strlen(copy_src)+my_strlen(dest)+1;

  //allocates memory for both memories
  final_str = malloc(sizeof(char)*total_length);

  //so that we can edit the string without loosing track of initial character
  final_str_cpy=final_str;


  //copies dest string in to the malloced address until null character
  while(*dest!='\0'){
    *final_str=*dest;
     final_str++;
     dest++;
  }
  //copies source after string into the malloced address after dest
  while(*copy_src!= '\0'){
      *final_str=*copy_src;
       final_str++;
       copy_src++;

  }

*final_str='\0';
return final_str_cpy;
}



/*Inputs: takes in address to a string and a character
  output: returns a pointer to the first instance of the character or NULL
  pointer if the character is not found

  it finds where the character first occurs by comparing each successive
  chaaracter of the string with the character to be found until it either
  reaches the null terminator(in which case it returnes a NULL pointer).
  or tt finds the given character(and so it then returns the pointer to that)
  */
char *my_strchr(const char *s, int c){
  char *copy = (char * ) s;
  while(*copy != c && *copy != '\0'){//runs loop as long as character is not found or null character is reached
    copy++;
  }
  if(*copy == '\0'){//if the string pointed is at null character, it returns NULL addresss.
    return NULL;
  }
  else{//otherwise, it returns the pointer to the character found
    return copy;
  }
}

/*Inputs: takes in address to two strings
  Output: It returns an integer which is equal to difference between first and second string
  It compares the two string's total Isci value by adding Isci value of each variable
  */

int my_strcmp(const char *s1, const char *s2){
  int loop = 0;
  int returned =0;
  while(loop == 0){
    if(*s1 != *s2){
      if(*s1 == '\0'){
        loop=1;
        returned = (*s2 * -1);
      }
      if(*s2 == '\0'){
        loop=1;
        returned= *s1;
      }
      else{
        loop=1;
        returned= *s1 - *s2;
      }
    }
    if(*s1 == '\0' && *s1 == *s2){
      returned=0;
      loop=1;
    }
    s1++;
    s2++;
  }
  return returned;

}
/*Inputs: takes in pointers to two strings
  Output: It returns a pointer which points to the copy of the string
  It copies second string onto the first string.

  */


char *my_strcpy(char *dest, const char *src){
  char* dest_cpy = dest;

  while(*src!='\0'){//as long as the end is not reached
    *dest = *src;
    dest++;
    src++;
  }
  dest='\0';
return dest_cpy;

}
/*Inputs: takes in pointer to a strings

  Output: It returns a pointer which points to the duplicated copy
  It duplicates a string. It allocates space in heap for the new string and
  copyies each character from the original string, and returns it.
  */
char *my_strdup(const char *s){
 char* new_s;
 char* cpy_new_s;
 int len_s;

 len_s=my_strlen(s);//calculates length of the string
 new_s=malloc(sizeof(char)*(len_s+1)); //allocates space in the heap
 cpy_new_s=new_s;
 while (*s != '\0'){//runs until null character is reached
   *cpy_new_s=*s;
   s++;
   cpy_new_s++;
 }
*cpy_new_s='\0';//adds null terminater


return new_s;

}


/* Input: takes in a pointer to a string
   Output: returns an integer
   Given a pointer to the beginning of a string, my_strlen computes the length
 * of the string by counting the number of characters it encounters before
 * finding a null-terminator. */
size_t my_strlen(const char *s) {
    size_t result = 0;
    char *copy = (char *) s;  // Create a copy of input s that we can modify.

    int i = 0;
    while(*copy != '\0'){
      copy++;
      i++;
    }
    result = i;
    return result;
}
/*Input:takes in two pointers
 Given two pointers to the beginning of two strings, my_strstr returns
 *the pointer to the start of the second string in the first string.
 It does this by first comparing the first character of the second strings
 to each successive character of the first string. If it finds any characters
 that matches with the first character of the second string, it verfies that
 the successive characters of both strings are same. If they are not same, then
 it breaks out of the loop and starts the comparison of the first character
 of second string to next character of first string.
 If the successive characters were found to be equal, it returns
 the pointer to the start of the substring in the first strings
 If it does not find the second string to be a substring, it returns a NULL
 pointer.
 Returns: a pointer.  */

char *my_strstr(const char *haystack, const char *needle){

  int n_found=0;
  char nfirst = *needle;


  char *copy_haystack_1 = (char *) haystack;
  char *copy_haystack_2 = (char *) haystack;
  char *copy_needle_1 = (char *) needle;
  char *copy_needle_2 = (char *) needle;



  while(*copy_haystack_1!= '\0'){
      n_found=0;


    if(*copy_haystack_1 == nfirst){
      copy_haystack_2=copy_haystack_1;
      copy_needle_2=copy_needle_1;

      while (n_found == 0){
        copy_haystack_2++;
        copy_needle_2++;
       if (*copy_needle_2 != *copy_haystack_2){
         n_found=1;
       }
       if (*copy_needle_2 == '\0'){
         return(copy_haystack_1);
       }

     }
   }
   copy_haystack_1++;
 }
 return NULL;
}
