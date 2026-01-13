/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:36:14 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/13 16:05:17 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_type(char *line)
{
	if (ft_strncmp(line, "|", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(line, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(line, "<<", 3) == 0)
		return (4);
	else if (ft_strncmp(line, ">>", 3) == 0)
		return (5);
	else
		return (0);
}
