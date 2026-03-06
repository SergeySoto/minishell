#include "../../includes/minishell.h"

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
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup((*token)->next->content);
		cmd->append = 0;
	}
	else if ((*token)->type == APPEND)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup((*token)->next->content);
		cmd->append = 1;
	}
	else if ((*token)->type == HEREDOC)
	{
		fd = handle_heredoc((*token)->next->content, mini);
		if (fd == -1)
			cmd->fd_in = -1;
		else
			cmd->fd_in = fd;
	}
	(*token) = (*token)->next->next;
}
