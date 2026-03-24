/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_pars_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:44:37 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:44:38 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_double_pipes(char *str, int i)
{
	int	j;

	if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_fprintf(2, ERR_SYNTERR_TWO_PIPE);
		return (0);
	}
	else
	{
		j = i + 1;
		while (is_space(str[j]))
			j++;
		if (str[j] == '|' || str[j] == '\0')
		{
			ft_fprintf(2, ERR_SYNTERR_ONE_PIPE);
			return (0);
		}
	}
	return (1);
}
