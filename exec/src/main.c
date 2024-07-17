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
int	g_error_code = 0;

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
		return (printf("To much args\n"), g_error_code);
	ft_handle_signal();
	glob.env = NULL;
	if (env && *env)
		ft_get_env(&glob, env);
	else
		ft_main_get_env(&glob);
	while (1)
	{
		input = readline("MinisHell-1.0$ ");
		if (input == NULL)
			return (ft_free_env(glob.env), g_error_code);
		if (parse_in_struct(&glob, input) == 0)
			printf("\n");
		if (*input)
			add_history(input);
		free(input);
	}
}