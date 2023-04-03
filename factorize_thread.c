#include "main.h"
/**
 * factorize: factorize a number in a thread
 *
 * @num: number to factorize
 * return void
 */
void factorize(mpz_t num)
{
	mpz_t i, factor;
	mpz_init(i);
	mpz_init(factor);
	mpz_set_ui(i, 2);

	while (mpz_cmp_ui(num, 1) > 0 && mpz_cmp(i, num) <= 0)
	{
		if (mpz_divisible_p(num, i))
		{
			mpz_divexact(num, num, i);
			gmp_printf(" %Zd", i);
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

	if ( mpz_cmp_ui(num, 1) != 0)
	{
		gmp_printf(" %Zd", num);
	}

	mpz_clear(i);
	mpz_clear(factor);
}

/**
 * factorize_thread - factorize a number in a thread
 *
 * arg - FactorizationData
 * return - void pointer
 */
void *factorize_thread(void *arg)
{
	FactorizationData *data = (FactorizationData *) arg;
	gmp_printf("%Zd =", data->num);
	factorize(data->num);
	gmp_printf("\n");
	mpz_clear(data->num);
	mpz_clear(data->i);
	free(data);
	return NULL;
}
