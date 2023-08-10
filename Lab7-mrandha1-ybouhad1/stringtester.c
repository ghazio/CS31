/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */


/* System headers to be included. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local headers to be included. */

#include "my_strings.h"

void test1_strcat(){

  char *mytest_1 = "Hello, world!\0";
  char *mytest_2 = "Potatoes\0";
  char *mytest_1_cpy=mytest_1;
  int total_length;
  char *final_str;
  char *final_str_cpy;

  total_length= my_strlen(mytest_1)+my_strlen(mytest_2);
  final_str = malloc(sizeof(char)*(total_length+1));
  final_str_cpy=final_str;
  while(*mytest_1_cpy!='\0'){
    *final_str=*mytest_1_cpy;
     final_str++;
     mytest_1_cpy++;
  }
  *final_str='\0';
  char* my_str=  my_strcat(mytest_1, mytest_2);

  printf("Given '%s' as first string, and '%s' as second string:\n", mytest_1,mytest_2);
  printf("\tThe result of strcat() is %s\n", strcat(final_str_cpy, mytest_2));
  printf("\tThe result of my_strcat() is %s\n", my_str);
  printf("\n");
  free(final_str_cpy);
  free(my_str);
}

void test2_strcat(){


  char *mytest_1 = "!           \0";
  char *mytest_2 = "The fitnessgram pacer test is a multistage aerobic capacity test that progressively gets more difficult as it continues.\0";
  char *mytest_1_cpy=mytest_1;
  int total_length;
  char *final_str;
  char *final_str_cpy;

  total_length= my_strlen(mytest_1)+my_strlen(mytest_2);
  final_str = malloc(sizeof(char)*(total_length+1));
  final_str_cpy=final_str;
  while(*mytest_1_cpy!='\0'){
    *final_str=*mytest_1_cpy;
     final_str++;
     mytest_1_cpy++;
  }
  *final_str='\0';
  char* my_str=  my_strcat(mytest_1, mytest_2);

  printf("Given '%s' as first string, and '%s' as second string:\n", mytest_1,mytest_2);
  printf("\tThe result of strcat() is %s\n", strcat(final_str_cpy, mytest_2));
  //our function does the malloc function itself
  printf("\tThe result of my_strcat() is %s\n", my_str);
  printf("\n");
  free(final_str_cpy);
  free(my_str);

}

void test1_strchr(){
  char *test_1 = "Hello, world!";
  char c = 'r';

  printf("Given '%s' as string, and '%d' as char to find:\n", test_1,c);
  printf("\tThe result of strchr() is %s\n", strchr(test_1, c));
  printf("\tThe result of my_strchr() is %s\n", my_strchr(test_1, c));
  printf("\n");
}

void test2_strchr(){
  char *test_1 = "Hello, world!";
  char c = 'p';

  printf("Given '%s' as string, and '%d' as char to find:\n", test_1,c);
  printf("\tThe result of strchr() is %s\n", strchr(test_1, c));
  printf("\tThe result of my_strchr() is %s\n", my_strchr(test_1, c));
  printf("\n");
}


void test1_strcmp(){
  char *test_1 = "Hello, world!";
  char *test_2 = "Potatoes";

  printf("Given '%s' as first string, and '%s' as second string:\n", test_1,test_2);
  printf("\tThe result of strcmp() is %d\n", strcmp(test_1, test_2));
  printf("\tThe result of my_strcmp() is %d\n", my_strcmp(test_1, test_2));
  printf("\n");



}
void test2_strcmp(){
  char *test_1 = "Potatoes are good";
  char *test_2 = "Potatoes are good";

  printf("Given '%s' as first string, and '%s' as second string:\n", test_1,test_2);
  printf("\tThe result of strcmp() is %d\n", strcmp(test_1, test_2));
  printf("\tThe result of my_strcmp() is %d\n", my_strcmp(test_1, test_2));
  printf("\n");


}

void test1_strcpy(){
  char *test_1 = "Potatoes are good\0";
  char *test_2 = "Tomatoes aint bad\0";
  char *test_1_cpy=test_1;
  int total_length;
  char *final_str;
  char *final_str_cpy;
  //allocates size for the copied string and gives a pointer to the allocated array

  total_length= my_strlen(test_1)+my_strlen(test_2);
  final_str = malloc(sizeof(char)*(total_length+1));
  final_str_cpy=final_str;
  while(*test_1_cpy!='\0'){
    *final_str=*test_1_cpy;
     final_str++;
     test_1_cpy++;
  }
  *final_str='\0';//assigns null character





  printf("Given '%s' as first string, and '%s' as second string:\n", test_1,test_2);
  printf("\tThe result of strcpy() is %s\n", strcpy(final_str_cpy, test_2));
  printf("\tThe result of my_strcpy() is %s\n", my_strcpy(final_str_cpy, test_2));
  printf("\n");
  free(final_str_cpy);

}

void test2_strcpy(){
  char *test_1 = "United States";
  char *test_2 = "Murica";
  char *test_1_cpy=test_1;
  int total_length;
  char *final_str;
  char *final_str_cpy;

  total_length= my_strlen(test_1)+my_strlen(test_2);
  //allocates size for the copied string and gives a pointer to the allocated array
  final_str = malloc(sizeof(char)*(total_length+1));
  final_str_cpy=final_str;
  while(*test_1_cpy!='\0'){
    *final_str=*test_1_cpy;
     final_str++;
     test_1_cpy++;
  }
  *final_str='\0';//assigns null character





  printf("Given '%s' as first string, and '%s' as second string:\n", test_1,test_2);
  printf("\tThe result of strcpy() is %s\n", strcpy(final_str_cpy, test_2));
  printf("\tThe result of my_strcpy() is %s\n", my_strcpy(final_str_cpy, test_2));
  printf("\n");
  free(final_str_cpy);

}


void test1_strdup(){
  char *test_1 = "Pakistan Zindabad";
  char* str_returned_strdup=NULL;
  char* str_returned_mystrdup=NULL;
  str_returned_strdup=strdup(test_1);
  str_returned_mystrdup=my_strdup(test_1);

  printf("Given '%s' as first string ", test_1);
  printf("\tThe result of strdup() is %s, and the original string is %s\n ", str_returned_strdup, test_1);
  printf("\tThe result of my_strdup() is %s, and the original string is %s\n ", str_returned_mystrdup, test_1);
  printf("\n");
  free(str_returned_strdup);
  free(str_returned_mystrdup);
}

void test2_strdup(){
  char *test_1 = "Potato";
  char* str_returned_strdup=NULL;
  char* str_returned_mystrdup=NULL;
  str_returned_strdup=strdup(test_1);
  str_returned_mystrdup=my_strdup(test_1);

  printf("Given '%s' as first string ", test_1);
  printf("\tThe result of strdup() is %s, and the original string is %s\n ", str_returned_strdup, test_1);
  printf("\tThe result of my_strdup() is %s, and the original string is %s\n ", str_returned_mystrdup, test_1);
  printf("\n");
  free(str_returned_strdup);
  free(str_returned_mystrdup);
}



void test_strlen_1() {
    char *test_string = "Hello, world!";

    printf("Given '%s':\n", test_string);
    printf("\tThe result of strlen() is %ld\n", strlen(test_string));
    printf("\tThe result of my_strlen() is %ld\n", my_strlen(test_string));
    printf("\n");
}


void test_strlen_2() {
    char *test_string = "";

    printf("Given the empty string, '%s':\n", test_string);
    printf("\tThe result of strlen() is %ld\n", strlen(test_string));
    printf("\tThe result of my_strlen() is %ld\n", my_strlen(test_string));
    printf("\n");
}



void test1_strstr() {
    char* haystack = "Hello, world!";
    char* needle= "world";
    printf("We need to find %s in %s:\n", needle,haystack);
    printf("\tThe result of strstr() is %s\n", strstr(haystack,needle));
    printf("\tThe result of my_strstr() is %s\n", my_strstr(haystack,needle));
    printf("\n");
}


void test2_strstr() {
    char* haystack = "Main Marna Chahta Hooon";
    char* needle= "Chahta";
    printf("We need to find %s in %s:\n", needle,haystack);
    printf("\tThe result of strstr() is %s\n", strstr(haystack,needle));
    printf("\tThe result of my_strstr() is %s\n", my_strstr(haystack,needle));
    printf("\n");
}





int main(int argc, char **argv) {


  test1_strcat();
  test2_strcat();

  test1_strchr();//works
  test2_strchr();//works

  test1_strcmp();//works
  test2_strcmp();//works

  test1_strcpy();//doesnt work
  test2_strcpy();

  test1_strdup(); //works
  test2_strdup(); //works

  test1_strstr();// works
  test2_strstr();//works


  test_strlen_1();//works
  test_strlen_2();//works



    return 0;
}
