/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:06:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/23 19:48:32 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*free_token(char *str, char **env);
void	print_tokens(t_token *head);
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

#endif