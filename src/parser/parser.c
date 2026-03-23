#include "../../includes/minishell.h"

/**
 * @brief Allocates and zero-initialises a new t_cmd node.
 * @return Pointer to the new t_cmd node, or NULL on malloc failure.
 */
static t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->pid = 0;
	cmd->cmd_path = 0;
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Appends a t_cmd node at the end of the command linked list.
 * @param cmd_list Address of the head pointer of the t_cmd list.
 * @param cmd Pointer to the t_cmd node to append.
 * @return void
 */
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
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type > 1 && tmp->type < 6)
			tmp = tmp->next->next;
		else if (tmp->type == WORD || tmp->type == ENV_VAR
			|| tmp->type == EXIT_STATUS)
		{
			count++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (count);
}

int	process_cmd_tokens(t_mini **mini, t_token **c_token, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->args = malloc(sizeof(char *) * (count_args(*c_token) + 1));
	if (!cmd->args)
		return (-1);
	while (*c_token && (*c_token)->type != PIPE)
	{
		handler_redirects(*mini, c_token, cmd, &i);
		if (cmd->fd_in == -1)
		{
			cmd->args[i] = NULL;
			free_cmd(&cmd);
			free_cmd(&(*mini)->cmds);
			return (-1);
		}
	}
	cmd->args[i] = NULL;
	return (0);
}

void	init_cmd(t_mini **mini)
{
	t_token	*c_token;
	t_cmd	*cmd;

	c_token = (*mini)->tokens;
	while (c_token)
	{
		cmd = create_cmd_node();
		if (!cmd)
			return ;
		if (process_cmd_tokens(mini, &c_token, cmd) == -1)
			return ;
		add_cmd_back(&(*mini)->cmds, cmd);
		if (c_token)
			c_token = c_token->next;
	}
}
