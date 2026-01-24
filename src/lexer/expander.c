/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/24 23:13:50 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_checker(t_token *lst)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (lst->content[i])
	{
		update_quote_status(lst->content[i], &quote);
		if (lst->content[i] == '$' && quote != '\'')
		{
			if (lst->content[i + 1] == '?')
			{
				lst->type = 7;
				lst->expand = 1;
			}
			else if (ft_isalnum(lst->content[i + 1])
				|| lst->content[i + 1] == '_')
			{
				lst->type = 6;
				lst->expand = 1;
			}
			break ;
		}
		i++;
	}
}

void	heredoc_bf_dollar(t_token *lst)
{
	if (!lst || !lst->content)
		return ;
	if (lst->type == 4 && lst->next->expand == 1)
		lst->next->expand = 0;
}

static int	get_after_dollar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

static int	get_len(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

char	*get_env_content( char *var_name, char **envp)
{
	int		i;
	int		len_name;

	i = 0;
	len_name = ft_strlen(var_name);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var_name, len_name) == 0) && envp[i][len_name] == '=')
			return (ft_strdup(&envp[i][len_name + 1]));
		i++;
	}
	return (ft_strdup(""));
}

char	*get_var_name(char *str)
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

char	*replace_string(char *str, char *replacement, int start, int len_remove)
{
	int		len_mid;
	char	*new_str;
	int		len_end;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	len_mid = (start + len_remove) - ft_strlen(replacement);
	new_str = malloc(start + len_mid + len_str + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, start);
	ft_strlcat(new_str, replacement, len_mid);
	i = start + len_remove;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
