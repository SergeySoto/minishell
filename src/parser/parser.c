
#include "../../includes/minishell.h"

static t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pid = 0;
	cmd->cmd_path = 0;
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_cmd_back(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*temp;
	t_cmd	*new_cmd;

	new_cmd = cmd;
	if (!new_cmd)
		return ;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return ;
	}
	temp = *cmd_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
}

int	count_args(t_token *token)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type > 1 && tmp->type < 6)
			tmp = tmp->next->next;
		else if (tmp->type == WORD || tmp->type == ENV_VAR || tmp->type == EXIT_STATUS)
		{
			count++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (count);
}

static void	handler_redirects(t_token **token, t_cmd *cmd, int *i)
{
	if ((*token)->type > 1 && (*token)->type < 6)
	{
		if ((*token)->type == REDIR_IN)
			cmd->fd_in = open((*token)->next->content, O_RDONLY);
		else if ((*token)->type == REDIR_OUT)
			cmd->fd_out = open((*token)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*token)->type == APPEND)
			cmd->fd_out = open((*token)->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if ((*token)->type == HEREDOC)
		{
			//cmd->fd_in = ; //Aqui va la logica del heredoc
		}
		(*token) = (*token)->next->next;
	}
	else if ((*token)->type == WORD || (*token)->type == ENV_VAR ||(*token)->type == EXIT_STATUS)
	{
		cmd->args[*i] = ft_strdup((*token)->content);
		(*i)++;
		(*token) = (*token)->next;
	}
}

void	init_cmd(t_mini **mini)
{
	t_token	*c_token;
	t_cmd	*cmd;
	int		i;

	c_token = (*mini)->tokens;
	while (c_token)
	{
		cmd = create_cmd_node();
		cmd->args = malloc(sizeof(char *) * (count_args(c_token) + 1));
		i = 0;
		while (c_token && c_token->type != PIPE)
			handler_redirects(&c_token, cmd, &i);
		cmd->args[i] = NULL;
		add_cmd_back(&(*mini)->cmds, cmd);
		if (c_token)
			c_token = c_token->next;
	}
}
