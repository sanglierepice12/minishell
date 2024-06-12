#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen_double(char **str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	main(int arc, char **argv)
{
	printf("arc = %d\n", arc -1);
	printf("len = %zu\n", ft_strlen_double(argv) - 1);

	return (0);
}