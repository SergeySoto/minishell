/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:36:34 by carmegon          #+#    #+#             */
/*   Updated: 2026/02/02 20:34:38 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

void	*free_token(char *str, char **env)
{
	int	i;

	if (env)
	{
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
	if (str)
		free(str);
	return (NULL);
}

void	free_struct_token(t_token **token)
{
	t_token	*temp;
	
	if (!token || !*token)
		return ;
	
	while ((*token) != NULL)
	{
		temp = (*token)->next;
		free((*token)->content);
		free((*token));
		(*token) = temp;
	}
	*token = NULL;
}

void	free_env(t_env **envp)
{
	t_env	*temp;
	
	if (!envp || !*envp)
		return ;
	
	while ((*envp) != NULL)
	{
		temp = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free((*envp));
		(*envp) = temp;
	}
	*envp = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return ;
	while ((*cmd) != NULL)
	{
		i = 0;
		while ((*cmd)->args && (*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		free((*cmd)->args);
		free((*cmd)->cmd_path);
		if ((*cmd)->fd_in > 2)
			close((*cmd)->fd_in);
		if ((*cmd)->fd_out > 2)
			close((*cmd)->fd_out);
		tmp = (*cmd)->next;
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	free_struct_mini(t_mini *mini)
{
	if (!mini)
		return ;

	if (mini->tokens)
		free_struct_token(&mini->tokens);
	if (mini->env)
		free_env(&mini->env);
	if (mini->cmds)
		free_cmd(&mini->cmds);
	if (mini->input || mini->env_array)
	{
		free_token(mini->input, mini->env_array);
		mini->input = NULL;
		mini->env = NULL;
	}
}
