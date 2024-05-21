/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:38:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 16:38:16 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_build *build)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("getcwd : error\n");
	build->pwd = ft_str_dup(path);
	free(path);
}