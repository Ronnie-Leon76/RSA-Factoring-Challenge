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
	pthread_t threads[8];
	uint8_t thread_count = 0;

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

	while ((read = getline(&line, &size, file)) != -1)
	{
		FactorizationData *data = (FactorizationData *)malloc(sizeof(FactorizationData));
		mpz_init_set_str(data->num, line, 10);
		mpz_init(data->i);

		if (thread_count < 8)
		{
			pthread_create(&threads[thread_count], NULL, factorize_thread, data);
			thread_count++;
		}
		else
		{
			pthread_join(threads[thread_count - 1], NULL);
			pthread_create(&threads[thread_count - 1], NULL, factorize_thread, data);
		}
	}

	fclose(file);
	if (line)
		free(line);


	return (0);
}
