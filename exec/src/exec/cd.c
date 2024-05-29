/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:01:38 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 16:01:38 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(char *dup)
{
	if (dup[3] == '-' && dup[4] == '-')
		chdir("~");
	else if (!dup[2] || (dup[3] == '~' && !dup[4]))
		chdir("/valgrind");
	else if (dup[3] == '-' && dup[4] != '-')
		dprintf(2, "bash: cd: %c%c: invalid option\n"
			"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", dup[3], dup[4]);
	else if (chdir(dup + 3) != 0)
	{
		perror("bash: cd");
		dprintf(2, "bash: cd: %s: No such file or directory\n", dup + 3);
	}
}
