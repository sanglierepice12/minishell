#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_str_copy_n(char *str, int n)
{
	char	*dup;
	int		i;

	dup = calloc(n, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	main(int arc, char **argv)
{
	(void)arc;
	int	i;
	int	j;
	char	*str;

	i = 1;
	while (argv[i] && i < arc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '=')
			{
				printf("%d\n", j);
				printf("arg = $%s$\n", argv[i] + j + 1);
				str = ft_str_copy_n(argv[i], j);
				printf("debut = $%s$\n", str);
				free(str);
				break;
			}
			j++;
		}
		i++;
	}
}