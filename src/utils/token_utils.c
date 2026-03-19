/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:13:06 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/19 16:05:16 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_iteration_data(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->tokens)
		free_struct_token(&mini->tokens);
	if (mini->cmds)
		free_cmd(&mini->cmds);
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
}

char	**dup_arr(char **envp)
{
	int		i;
	char	**result;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		result[i] = ft_strdup(envp[i]);
		if (!result[i])
			return (NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	ft_lstiter(t_token *lst, void (*f)(t_token *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}

void	print_tokens(t_token *head)
{
	t_token	*temp;
	t_token	*next;

	temp = head;
	printf("\n--- VISTAS DE NODOS ---\n");
	while (temp)
	{
		printf("Token: [%s] | Type: %u | Expand: %d\n", temp->content, temp->type, temp->expand);
		next = temp->next;
		temp = next;
	}
	head = NULL;
	printf("-------------------------\n\n");
}

void	print_env(t_env *envp)
{
	t_env	*temp;
	t_env	*next;

	temp = envp;
	printf("\n--- VISTAS DE NODOS ---\n");
	while (temp)
	{
		printf("Key: [%s] | Value: [%s]\n", temp->key, temp->value);
		next = temp->next;
		temp = next;
	}
	envp = NULL;
	printf("-------------------------\n\n");
}
