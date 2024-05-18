#include "../../include/minishell.h"

static char	*set_command(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(input, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(input, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(input, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(input, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(input, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(input, "exit", 4) == 0)
		return ("exit");
	return (NULL);
}

static size_t	count_args(char *input, int lenght)
{
	size_t i;

	i = 0;
	lenght = 3;
	while (input[lenght])
	{
		printf("LETTRE = %c\n", input[lenght]);
		if (input[lenght] != ' ')
		{
			i++;
			while (input[lenght] != ' ' || input[lenght] != 0)
				lenght++;
		}
		if (input[lenght] == ' ')
			lenght++;
	}
	return (i);
}
/*
static char	**convert_argv(char *input, int lenght)
{
	//char **argv;
	//size_t i;

	printf("%ld", count_args(input, lenght));
	return (NULL);
}

static char	**set_argv(char *input, int lenght)
{
	char **argv;

	argv = convert_argv(input, lenght);
	return (NULL);
}*/

int parse_in_struct(t_input *command, char *input)
{
	command->command = set_command(input);
	//command->argv = set_argv(input, ft_strlen(input));
	//command->args = set_args(input, ft_strlen((input)));
	printf("NUMBER = %ld\n", count_args(input, ft_strlen(input)));
	printf("command = %s\n", input);
	printf("command = %s\n", command->command);
	return (1);
}