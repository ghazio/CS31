/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */


#ifndef _MYSTRINGS_
#define _MYSTRINGS_

/* This header file defines the function prototypes for all of the functions in
 * our library.  By including this, any program that wants to use the library
 * knows what it needs to about the parameter types and return types of our
 * library's functions.  In a header file like this, you can optionally name
 * the function parameters or specify just the type, like I did below. */

/* Note: You *SHOULD NOT* change these function prototypes!  These functions
 * should have the same parameter types and return types as their C-library
 * counterparts! */

char *my_strcat(char *, const char *);

char *my_strchr(const char *, int c);

int my_strcmp(const char *, const char *);

char *my_strcpy(char *, const char *);

char *my_strdup(const char *);

size_t my_strlen(const char *);

char *my_strstr(const char *, const char *);

#endif
