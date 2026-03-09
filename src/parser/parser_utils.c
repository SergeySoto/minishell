#include "../../includes/minishell.h"

static void	handle_output_redirect(t_token **token, t_cmd *cmd, int is_append)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*token)->next->content);
	cmd->append = is_append;
}

void	set_redirects(t_mini *mini, t_token **token, t_cmd *cmd)
{
	int	fd;

	if ((*token)->type == REDIR_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup((*token)->next->content);
	}
	else if ((*token)->type == REDIR_OUT)
		handle_output_redirect(token, cmd, 0);
	else if ((*token)->type == APPEND)
		handle_output_redirect(token, cmd, 1);
	else if ((*token)->type == HEREDOC)
	{
		fd = handle_heredoc((*token)->next->content, mini);
		cmd->fd_in = fd;
	}
	(*token) = (*token)->next->next;
}

void	handler_redirects(t_mini *mini, t_token **token, t_cmd *cmd, int *i)
{
	if ((*token)->type > 1 && (*token)->type < 6)
		set_redirects(mini, token, cmd);
	else if ((*token)->type == WORD || (*token)->type == ENV_VAR
		|| (*token)->type == EXIT_STATUS)
	{
		cmd->args[*i] = ft_strdup((*token)->content);
		(*i)++;
		(*token) = (*token)->next;
	}
}
