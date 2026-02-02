/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:13:06 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/02 21:11:19 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_cmds(t_cmd *cmds)
{
    t_cmd	*current;
    int		i;
    int		count;

    current = cmds;
    count = 1;
    printf("\n--- VISTA DE COMANDOS (PARSER) ---\n");
    if (!current)
        printf("Lista de comandos vacía.\n");
    while (current)
    {
        printf("CMD #%d:\n", count);
        
        // 1. Imprimir Argumentos (Char **)
        printf("  Args: [");
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                printf("\"%s\"", current->args[i]);
                if (current->args[i + 1])
                    printf(", ");
                i++;
            }
        }
        else
            printf("(null)");
        printf("]\n");

        // 2. Imprimir File Descriptors
        printf("  FDs : In [%d] | Out [%d]\n", current->fd_in, current->fd_out);

        // 3. Imprimir Path (si ya lo has buscado, si no saldrá null)
        if (current->cmd_path)
            printf("  Path: %s\n", current->cmd_path);
        else
            printf("  Path: (null)\n");

        printf("----------------------------------\n");
        current = current->next;
        count++;
    }
    printf("\n");
}

static void	trim_loop(t_token *lst, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (lst->content[i])
	{
		update_quote_status(lst->content[i], &quote);
		if (quote == 0 && (lst->content[i] == '"' || lst->content[i] == '\''))
			i++;
		else if (lst->content[i] == quote && quote != 0)
			i++;
		else
		{
			result[j] = lst->content[i];
			j++;
			i++;
		}
	}
	result[j] = '\0';
	free(lst->content);
	lst->content = result;
}

void	trim_quotes(t_token *lst)
{
	char	*result;

	if (!lst || !lst->content)
		return ;
	result = malloc(ft_strlen(lst->content) + 1);
	if (!result)
		return ;
	trim_loop(lst, result);
}
