#include "../../includes/minishell.h"

void	set_redirects(t_token **token, t_cmd *cmd)
{
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
		//cmd->fd_in = ; //Aqui va la logica del heredoc
	}
	(*token) = (*token)->next->next;
}
