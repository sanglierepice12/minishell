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

void	ft_echo(char *dup)
{
	size_t	i;

	if (dup[0] && dup[0] != ' ')
	{
		dprintf(2, "Command : %s not found, did you mean: echo ?\n", dup + 1);
		return;
	}
	if (dup[1] == '-' && dup[2] == 'n' && dup[3])
	{
		i = 3;
		while (++i, dup[i] && dup[3] != ' ')
		{
			if (dup[i] != 'n')
				return((printf("%s\n", dup + 1), (void)0));
		}
		if (!dup[i])
			return ;
		else
			printf("%s", dup + 4);
	}
	else if (dup[1] == '-' && dup[2] == 'n' && !dup[3])
		return ;
	else
		printf("%s\n", dup + 1);
}

void	ft_pwd_call(t_glob *glob, char *dup)
{
	if (dup[4] && dup[4] == '-' && dup[5])
	{
		dprintf(2, "bash: pwd: %c%c: invalid option\n"
			   "pwd: usage: pwd [-LP]\n", dup[4], dup[5]);
		return ;
	}
	if (dup[3] && dup[3] != ' ')
	{
		dprintf(2, "Command : %s not found, did you mean: pwd ?\n", dup);
		return;
	}
	ft_pwd(&glob->build);
	printf("%s\n", glob->build.pwd);
	free(glob->build.pwd);
}

void	ft_cd_call(char *dup)
{
	if (dup[3] == '-' && dup[4] == '-')
		chdir("~");
	else if (!dup[2] || (dup[3] == '~' && !dup[4]))
		chdir("/valgrind");
	else if (dup[3] == '-' && dup[4] != '-')
		dprintf(2, "bash: cd: %c%c: invalid option\n"
				   "cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", dup[3], dup[4]);
	else if (chdir(dup + 3) != 0)
		dprintf(2, "bash: cd: %s: No such file or directory\n", dup + 3);
}

void	ft_call(t_glob *glob, char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		ft_pwd_call(glob, input);
	if (ft_strncmp(input, "cd", 2) == 0)
		ft_cd_call(input);
	if (ft_strncmp(input, "ls", 2) == 0)
		ft_ls();
	if (ft_strncmp(input, "echo", 4) == 0)
		ft_echo(input + 4);
}