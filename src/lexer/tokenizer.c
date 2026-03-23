#include "../../includes/minishell.h"

/**
 * @brief Determines the token type from a raw string by comparing it against
 *		known operator strings.
 * @param line The raw token string.
 * @return Token type integer: 0=WORD, 1=PIPE, 2=REDIR_IN, 3=REDIR_OUT,
 *		4=HEREDOC, 5=APPEND.
 */
static int	get_type(char *line)
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

t_token	*create_token(char *str, int type)
{
	t_token	*token;

	token = malloc(1 * sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = str;
	token->type = type;
	token->expand = 0;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **head, char *token)
{
	t_token	*temp;

	if (!head || !*head)
	{
		*head = create_token(token, get_type(token));
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = create_token(token, get_type(token));
}

void	input_to_token(char *input, t_token **tokens, t_mini *mini)
{
	char	**temp_split;
	int		i;

	add_history(input);
	if (pre_pars(input) == 0)
	{
		mini->exit_status = 2;
		return ;
	}
	temp_split = smart_split(input);
	i = 0;
	while (temp_split && temp_split[i])
	{
		add_token_back(tokens, temp_split[i]);
		i++;
	}
	free(temp_split);
	mini->tokens = (*tokens);
}

void	process_and_execute(t_mini *mini)
{
	ft_lstiter(mini->tokens, expand_checker);
	ft_lstiter(mini->tokens, heredoc_bf_dollar);
	expander(mini);
	ft_lstiter(mini->tokens, trim_quotes);
	init_cmd(&mini);
	if (g_signal != 0)
	{
		mini->exit_status = 130;
		g_signal = 0;
		return ;
	}
	find_full_path(mini);
	executor_dispatch(mini);
}
