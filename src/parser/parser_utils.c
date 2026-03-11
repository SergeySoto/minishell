#include "../../includes/minishell.h"

static void	handle_output_redirect(t_token **token, t_cmd *cmd, int is_append)
{
	int	fd;
	int	flags;

	fd = 0;
	if (is_append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open((*token)->next->content, flags, 0644);
	if (fd == -1)
	{
		perror((*token)->next->content);
		cmd->fd_out = -1;
		return ;
	}
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
	cmd->fd_out = fd;
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
