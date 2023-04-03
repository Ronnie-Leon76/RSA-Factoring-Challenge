#include <gmp.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * main - Factorize as many numbers as possible into a product of two smaller
 * numbers
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0
 */
int main(int argc, char *argv[]) {
  FILE *file;
  char *line = NULL;
  size_t size = 0;
  ssize_t read;
  mpz_t i;
  mpz_t num;

  if (argc != 2) {
    printf("Usage: factors <file>\n");
    return (1);
  }
  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: Can't open file %s\n", argv[1]);
    return (1);
  }

  while ((read = getline(&line, &size, file)) != -1) {

    mpz_init_set_str(num, line, 10);

    mpz_init(i);
    mpz_set_ui(i, 2);
    gmp_printf("%Zd=", num);
    while (mpz_cmp_ui(num, 1) > 0 && mpz_cmp(i, num) <= 0) {
      if (mpz_divisible_p(num, i)) {
        mpz_divexact(num, num, i);
        gmp_printf("%Zd", i);
        if (mpz_cmp_ui(num, 1) != 0)
          gmp_printf("*");
      } else {
        mpz_add_ui(i, i, 1);
      }
    }
    if (mpz_cmp_ui(num, 1) != 0)
      gmp_printf("%Zd", num);
    gmp_printf("\n");
    mpz_clear(num);
    mpz_clear(i);
  }
  fclose(file);
  if (line)
    free(line);

   return (0);
}
