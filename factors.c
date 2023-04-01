#include "main.h"
/**
 * main - Factorize as many numbers as possible into a product of two smaller numbers
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line;
	size_t size = 0;
	ssize_t read;
	mpz_t num, i;

	if (argc != 2)
	{
		printf("Usage: factors <file>\n");
		return (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	mpz_init(num);
	mpz_init(i);
	while ((read = getline(&line, &size, file)) != -1)
	{
		mpz_set_str(num, line, 10);
		mpz_set_ui(i, 2);

		gmp_printf("%Zd =", num);

		while (mpz_cmp(i, num) <= 0)
		{
			if (mpz_divisible_p(num, i))
			{
				gmp_printf(" %Zd", i);
				mpz_divexact(num, num, i);
				if (mpz_cmp_ui(num, 1) != 0)
				{
					gmp_printf(" x ");
				}
			}
			else
			{
				mpz_add_ui(i, i, 1);
			}
		}
		printf("\n");
	}

	fclose(file);
	mpz_clear(num);
	mpz_clear(i);
	if (line)
		free(line);


	return (0);
}
