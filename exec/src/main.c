/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:29:57 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 09:53:42 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	show_struct(t_input *command)
{
	size_t	i;

	printf("ARGS = %zu\n", command->args);
	printf("command = %s\n", command->command);
	i = 0;
	while (i != command->args)
	{
		printf("ARGV = %s\n", command->argv[i]);
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
}

int	main(int arc, char **argv, char **env)
{
	char		*input;
	t_glob		glob;

	if (arc)
		(void)argv;
	ft_get_env(&glob, env);
	if (!env)
		dprintf(2, "Malloc crash, no env\n");
	while (1)
	{
		input = readline("MinisHell-1.0$ "/*getcwd(NULL,0)*/);
		add_history(input);
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		/*if (ft_strncmp(input, "exit", 4) == 0)
		{
			ft_free_all(&glob);
			free(input);
			break ;
		}*/
		if (rl_on_new_line() == 0)
		{
			if(parse_in_struct(&glob, input) == 0)
				printf("Error\n");
		}
		//free(input);
	}
	return (0);
}