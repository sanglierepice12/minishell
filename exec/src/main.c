/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:22:28 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/28 16:22:28 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int arc, char **argv, char **env)
{
	char		*input;
	char		*wiam;
	t_glob		glob;

	if (arc)
		(void)argv;
	ft_get_env(&glob, env);
	if (!env)
		dprintf(2, "Malloc crash, no env\n");
	while (1)
	{
		ft_pwd(&glob.build);
		wiam = ft_super_dup(glob.build.pwd, "$ ");
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
			break ;
		}
		if (rl_on_new_line() == 0)
		{
			if (check_command(input) == 1)
				parse_in_struct(&glob, input);
			/*else
				printf("Error\n");*/
		}
		free(input);
		free(wiam);
	}
	return (0);
}
