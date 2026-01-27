/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/27 16:33:28 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_name(char *str)
{
	int		i;

	if (str[0] == '?')
		return (ft_strdup("?"));
	else
	{
		i = 0;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		return (ft_substr(str, 0, i));
	}
}

static char	*get_env_content(char *var_name, t_mini *mini)
{
	int		i;
	int		len_name;
	char	**envp;

	envp = mini->env;
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(mini->exit_status));
	i = 0;
	len_name = ft_strlen(var_name);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var_name, len_name) == 0)
			&& envp[i][len_name] == '=')
			return (ft_strdup(&envp[i][len_name + 1]));
		i++;
	}
	return (ft_strdup(""));
}

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

void	expander(t_mini *mini)
{
	int		dollar_pos;
	t_token	*tmp;

	tmp = mini->tokens;
	while (tmp)
	{
		if (tmp->expand == 1)
		{
			dollar_pos = get_after_dollar(tmp->content);
			while (dollar_pos != 0)
			{
				perform_expansion(tmp, dollar_pos, mini);
				tmp->expand = 0;
				dollar_pos = get_after_dollar(tmp->content);
			}
		}
		tmp = tmp->next;
	}
}
