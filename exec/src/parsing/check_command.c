#include "../../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	check_input(char *input, int letter)
{
	(void)input;
	(void)letter;
	return (1);
/*	if (input[letter] == ' ' || input[letter] == 0)
		return (1);
	return (0);*/
}

int	check_command(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		return (check_input(input, 3));
	else if (ft_strncmp(input, "echo", 4) == 0)
		return (check_input(input, 4));
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (check_input(input, 2));
	else if (ft_strncmp(input, "export", 6) == 0)
		return (check_input(input, 6));
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (check_input(input, 5));
	else if (ft_strncmp(input, "env", 3) == 0)
		return (check_input(input, 3));
	/*else if (ft_strncmp(input, "exit", 4) == 0)
		return (check_input(input, 4));*/
	else if (ft_strncmp(input, "ls", 2) == 0)
		return (check_input(input, 2));
	return (0);
}