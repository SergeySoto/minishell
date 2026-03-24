/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:38:09 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:38:10 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_mini *mini, char **av)
{
	int	i;

	mini->env_array = env_to_array(mini->env);
	if (!mini || !mini->env_array)
		return (1);
	if (av[1] != NULL)
	{
		ft_fprintf(2, ERR_ENV_NOT_FILORDIR, av[1]);
		return (127);
	}
	i = 0;
	while (mini->env_array[i] != NULL)
	{
		printf("%s\n", mini->env_array[i]);
		i++;
	}
	return (0);
}
