#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>
#include <gmp.h>
#include <pthread.h>
#include <stdint.h>

/**
 * struct FactorizationData: struct for factorization data
 * @num: number to factorize
 * @i: iterator
 */
typedef struct {
	mpz_t num;
	mpz_t i;
} FactorizationData;
void factorize(mpz_t num);
void *factorize_thread(void *arg);
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#endif
