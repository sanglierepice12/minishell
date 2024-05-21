#include "../include/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int main(void)
{
	char *input;
	t_glob	glob;
	//t_input command;

	while (1)
	{
		input = readline("command >");
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break;
		}
		if (ft_strlen(input) > 0)
		{
			if (check_command(input) == 1)
				parse_in_struct(&glob, input);
			else
				printf("Error\n");
		}
		free(input);
	}
	return (0);
}