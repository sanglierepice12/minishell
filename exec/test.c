#include <stdio.h>

void	hello(int *i)
{
	printf("hello before %d\n", *i);
	while (*i = *i + 1, *i < 10)
		;
	printf("hello after %d\n", *i);
}

int	main()
{
	int	i;

	i = 5;
	printf("main before %d\n", i);
	i++;
	hello(&i);
	printf("main after %d\n", i);

}