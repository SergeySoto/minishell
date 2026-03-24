/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:36:44 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:37:59 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] != '-' || str[i + 1] == '\0')
		return (0);
	else
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	whitout_n(char **av)
{
	int	i;

	if (!av || !*av)
		return (0);
	i = 0;
	while (check_flag(av[i]) == 1)
		i++;
	while (av[i])
	{
		if (av[i + 1] == NULL)
			ft_putstr_fd(av[i], 1);
		else
		{
			ft_putstr_fd(av[i], 1);
			write(1, " ", 1);
		}
		i++;
	}
	return (1);
}

int	whit_n(char **av)
{
	int	i;

	if (!av || !*av)
		return (0);
	i = 1;
	if (!av[i])
		write(1, "\n", 1);
	while (av[i])
	{
		if (av[i + 1] == NULL)
		{
			ft_putstr_fd(av[i], 1);
			write(1, "\n", 1);
		}
		else
		{
			ft_putstr_fd(av[i], 1);
			write(1, " ", 1);
		}
		i++;
	}
	return (1);
}

int	ft_echo(char **av)
{
	if (!av || !*av)
		return (1);
	if (check_flag(av[1]) == 1)
		whitout_n(&av[1]);
	else
		whit_n(av);
	return (0);
}
