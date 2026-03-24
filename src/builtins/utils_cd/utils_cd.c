/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:42:19 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:42:23 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_av(char **av)
{
	int	i;

	if (!av || !*av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	chdir_fail(char **av)
{
	if (errno == ENOTDIR)
		ft_fprintf(2, ERR_CD_NOT_DIR, av[0]);
	else if (errno == ENOENT)
		ft_fprintf(2, ERR_CD_NO_FIL_OR_DIR, av[0]);
	else if (errno == EACCES)
		ft_fprintf(2, ERR_CD_PERMISSION, av[0]);
}
