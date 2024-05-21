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
	if (ft_strncmp(dup, "pwd", 3) != 0)
		return ;
	if (dup[4] && dup[4] == '-' && dup[5])
	{
		printf("bash: pwd: -k: invalid option\n"
			   "pwd: usage: pwd [-LP]\n");
		return ;
	}
	if (dup[3] && dup[3] != ' ')
	{

		return;
	}
	ft_pwd(&glob->build);
/*	printf("len = %zu", ft_strlen(dup));
	printf("dup 4 = %c\n", dup[4]);
	printf("dup 5 = %c\n", dup[5]);*/
	printf("%s\n", glob->build.pwd);
	free(glob->build.pwd);
}