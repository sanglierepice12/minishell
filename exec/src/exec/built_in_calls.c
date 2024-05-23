/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:53:07 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 17:53:07 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd_call(t_glob *glob, char *dup)
{
	if (dup[4] && dup[4] == '-' && dup[5])
		dprintf(2, "bash: pwd: %c%c: invalid option\n"
				   "pwd: usage: pwd [-LP]\n", dup[4], dup[5]);
	else if (dup[3] && dup[3] != ' ')
		dprintf(2, "Command : '%s' not found, did you mean: pwd ?\n", dup);
	else
	{
		ft_pwd(&glob->build);
		printf("%s\n", glob->build.pwd);
		free(glob->build.pwd);
	}
}

void	ft_call(t_glob *glob, char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		ft_pwd_call(glob, input);
	if (ft_strncmp(input, "cd", 2) == 0)
		ft_cd(input);
	if (ft_strncmp(input, "ls", 2) == 0)
		ft_ls();
	if (ft_strncmp(input, "echo", 4) == 0)
		ft_echo(input + 4);
	if (ft_strncmp(input, "clear", 5) == 0)
		printf("\033[2J\033[H");
	/*else if (ft_strncmp(input, "env", 3) == 0)
		ft_get_env(input + 4);*/
}