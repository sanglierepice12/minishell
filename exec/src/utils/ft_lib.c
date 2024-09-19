#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (0);
	return (1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = c;
		i++;
	}
	return (s);
}