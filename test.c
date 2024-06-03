#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	ft_comp_str(char *src, char *str)
{
	size_t	i;

	if (!str || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == str[i])
			i++;
		else
			return (0);
	}
	if (src[i] || str[i])
		return (0);
	return (1);
}

int	main(int arc, char **argv)
{
	(void)arc;
	size_t	j;

	j = ft_comp_str(argv[1], argv[2]);
	printf("%zu", j);
	return (0);
}