#include "../../includes/minishell.h"

/**
 * @brief Builds a new string by replacing a substring inside str with replace.
 * @param str Original string.
 * @param replace Replacement string to insert.
 * @param start Index in str where the replacement begins (points to the '$').
 * @param len_remove Number of characters to remove from str 
 * (variable name + '$').
 * @return Heap-allocated new string with the substitution applied,
 *		or NULL on malloc failure.
 */
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

/**
 * @brief Resolves and substitutes a single $VAR or $? occurrence in a token.
 *		Frees the old token content and replaces it with the expanded string.
 * @param token Pointer to the token whose content contains the variable.
 * @param dollar_pos Index of the character right after '$' in token->content.
 * @param mini Pointer to the main shell structure, used to look up env values.
 * @return void
 */
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

/**
 * @brief Expands all $VAR occurrences inside a single token, looping until
 *		no more '$' characters are found in the content.
 * @param tmp Pointer to the token to expand.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
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

/**
 * @brief Removes a token from the linked list and frees its memory.
 *		Used when a variable expands to an empty string.
 * @param mini Pointer to the main shell structure 
 * (updates mini->tokens if needed).
 * @param prev Pointer to the token before curr, or NULL if curr is the head.
 * @param curr Pointer to the token to remove.
 * @return Pointer to the token that follows the removed one.
 */
static t_token	*remove_empty_token(t_mini *mini, t_token *prev, t_token *curr)
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
				continue ;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
