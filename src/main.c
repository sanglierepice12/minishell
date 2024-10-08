/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:29:57 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/08 19:40:51 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_code = 0;

int	main(int arc, char **argv, char **env)
{
	char		*input;
	t_glob		glob;

	//ft_print_style();
	if (arc > 1)
		return (printf("%s: you don't need this\n", argv[1]), 1);
	glob.env = NULL;
	if (env && *env)
		ft_get_env(&glob, env);
	else
		ft_main_get_env(&glob);
	while (8)
	{
		ft_handle_signal(PARENT);
		input = readline("minisHell-1.0$ ");
		if (input == NULL)
		{
			printf("exit\n");
			glob.cmd = NULL;
			ft_exit(&glob, NULL);
		}
		parse_in_struct(&glob, input);
		add_history(input);
		free(input);
	}
}
