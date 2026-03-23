#include "../../includes/minishell.h"

/**
 * @brief Opens the output file for a redirection and updates cmd->fd_out.
 *		Supports both truncate (>) and append (>>) modes.
 * @param token Address of the current token pointer (points to the redirect
 *		operator; its ->next is the filename token).
 * @param cmd Pointer to the t_cmd being populated.
 * @param is_append 1 for append mode (>>), 0 for truncate mode (>).
 * @return void
 */
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
		ft_fprintf(2, ERR_ENV_NOT_FILORDIR, (*token)->next->content);
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
