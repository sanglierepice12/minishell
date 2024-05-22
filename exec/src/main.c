#include "../include/minishell.h"

int main()
{
	char	*input;
	char	*wiam;
	t_glob	glob;
	//t_input command;

	while (1)
	{
		ft_pwd(&glob.build);
		wiam = ft_str_dup(glob.build.pwd, "$ ");
		input = readline(wiam);
		add_history(input);
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
		free(wiam);
	}
	return (0);
}