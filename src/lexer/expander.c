/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/13 19:33:00 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static char	*replace_string(char *str, char *replace, int start, int len_remove)
{
	int		len_total;
	char	*new_str;

	len_total = ft_strlen(str) + ft_strlen(replace) - len_remove;
	new_str = malloc(sizeof(char) * (len_total + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, start + 1);
	ft_strlcat(new_str, replace, len_total + 1);
	ft_strlcat(new_str, &str[start + len_remove], len_total + 1);
	return (new_str);
}

static void	perform_expansion(t_token *token, int dollar_pos, t_mini *mini)
{
	char	*var_name;
	char	*env_value;
	char	*new_content;

	var_name = get_var_name(&token->content[dollar_pos]);
	if (!var_name)
		return ;
	env_value = get_env_content(var_name, mini);
	if (!env_value)
	{
		free(var_name);
		return ;
	}
	new_content = replace_string(token->content, env_value,
			dollar_pos - 1, ft_strlen(var_name) + 1);
	if (new_content)
	{
		free(token->content);
		token->content = new_content;
	}
	free(var_name);
	free(env_value);
}

static void	expand_one_token(t_token *tmp, t_mini *mini)
{
	int	dollar_pos;

	dollar_pos = get_after_dollar(tmp->content);
	while (dollar_pos != 0)
	{
		perform_expansion(tmp, dollar_pos, mini);
		tmp->expand = 0;
		dollar_pos = get_after_dollar(tmp->content);
	}
}

static t_token *remove_empty_token(t_mini *mini, t_token *prev, t_token *curr)
{
	t_token	*next;

	next = curr->next;
	if (prev)
		prev->next = next;
	else
		mini->tokens = next;
	free(curr->content);
	free(curr);
	return (next);
}

void	expander(t_mini *mini)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = mini->tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->expand == 1)
		{
			expand_one_token(tmp, mini);
			if (tmp->content[0] == '\0')
			{
				tmp = remove_empty_token(mini, prev, tmp);
				continue;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
