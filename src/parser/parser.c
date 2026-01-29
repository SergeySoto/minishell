
#include "../../includes/minishell.h"

static t_cmd	*create_cmd_node(char *content)
{
	t_cmd	*cmd;
	int		count;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	count = 
}

static void	add_cmd_back(char *content)
{
	t_cmd	*temp;
	t_cmd	*new_cmd;

	new_cmd = create_cmd_node(content);
}

t_cmd	*init_cmd(t_mini **mini)
{
	t_token	*c_token;

	c_token = (*mini)->tokens;
	while (c_token)
	{
		if (c_token->type == WORD || c_token->type == ENV_VAR)

	}
}

void	free_cmd();