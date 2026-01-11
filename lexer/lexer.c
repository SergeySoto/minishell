/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:36:14 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/10 00:36:14 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_tokens(t_mini *mini, char *line)
{
	int		i;
	t_token	*tokens;
	i = 0;
	while (line[i])
	{
		if (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		else if (line[i] == '|')
		{
			tokens = malloc(sizeof(t_token));
			mini->tokens->content = line[i];
			mini->tokens->type = 1;
			//conectar la estructura t_token con la T_mini
			i++;
		}
		else if ()
		{
		}
	}
	return (0);
}
