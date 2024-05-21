#include "../include/minishell.h"

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