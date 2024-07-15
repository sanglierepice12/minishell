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

	(void)argv;
	if (arc > 1)
		return (printf("To much args\n"));
	ft_get_env(&glob, env);
	if (!env)
		dprintf(2, "Malloc crash, no env\n");
	while (1)
	{
		input = readline("MinisHell-1.0$ "/*getcwd(NULL,0)*/);
		if (input == NULL)
			return (printf("coucoucCUCOU\n"));
		if (parse_in_struct(&glob, input) == 0)
			printf("\n");
		add_history(input);
		free(input);
	}
}