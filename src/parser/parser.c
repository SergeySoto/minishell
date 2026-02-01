
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

static void	add_cmd_back(t_cmd **cmd, char *content)
{
	t_cmd	*temp;
	t_cmd	*new_cmd;

	new_cmd = create_cmd_node();
	if (!new_cmd)
		return ;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
}

t_cmd	*init_cmd(t_mini **mini)
{
	t_token	*c_token;
	t_cmd	*cmd;

	c_token = (*mini)->tokens;
	while (c_token->next)
	{
		//usar una flag para crear o no un nuevo nodo t_cmd *
		if (c_token->type == WORD || c_token->type == ENV_VAR)
	}
}

int	count_args(t_token **token)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = *token;
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

void	free_cmd(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while ((*cmd) != NULL)
	{
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		tmp = (*cmd)->next;
		free((*cmd)->cmd_path);
		free((*cmd));
	}
}
