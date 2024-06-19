/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:09:48 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 17:09:48 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab, int lenght)
{
	while (lenght != 0)
	{
		free(tab[lenght]);
		lenght--;
	}
	free(tab);
}

/*void	ft_free_build(t_build *build)
{
	if (build->pwd)
		free(build->pwd);
}*/

void	ft_free_all(t_glob *glob)
{
	(void)glob;
	/*ft_free_build(&glob->build);*/
}
