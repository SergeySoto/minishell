/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:06:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/19 16:58:29 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*free_token(char *str, char **env);
void	print_tokens(t_token *head);
void	print_env(t_env *envp);
void	print_cmds(t_cmd *cmds);
void	free_struct_token(t_token **token);
void	free_struct_mini(t_mini *mini);
/**
 * @brief Removes surrounding quotes from a string while handling nested quotes.
 *
 * This function iterates through the input string and copies characters to a
 * new string, omitting quoting characters (' or ") unless they are preserved
 * by context. It maintains a state to track whether the current character is
 * inside quotes to correctly handle nested or escaped sequences (though logic
 * for escaping is delegated to `update_quote_status`).
 *
 * @param input The input string containing potential quotes to be trimmed.
 * @return A newly allocated string with the quotes removed. The caller is
 *         responsible for freeing this memory.
 */
void	trim_quotes(t_token *input);
void	ft_lstiter(t_token *lst, void (*f)(t_token *));
char	**dup_arr(char **envp);
void	free_env(t_env **envp);
void	free_cmd(t_cmd **cmd);
void	free_iteration_data(t_mini *mini);

#endif