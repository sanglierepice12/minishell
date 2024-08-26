#include "../../include/minishell.h"

static int	ft_size_num(int num)
{
	int	size;

	size = 0;
	if (num == 0)
		return (1);
	while(num != 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int num)
{
	char	*tab;
	int		size;

	size = ft_size_num(num);
	tab = malloc((size + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[size--] = '\0';
	while (num > 9)
	{
		tab[size] = num + 48;
		size--;
		num /= 10;
	}
	tab[size] = num + 48;
	return(tab);
}