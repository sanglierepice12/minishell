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

void	free_parse(t_glob *glob, int i)
{
	if (i >= 1)
		free(glob->command);
}

void	ft_free_build(t_build *build)
{
	if (build->pwd)
		free(build->pwd);
}

void	ft_free_all(t_glob *glob)
{
	ft_free_build(&glob->build);
}
