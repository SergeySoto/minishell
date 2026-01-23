/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:04:03 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/21 19:42:48 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_token	*create_token(char *token, int type);
void	input_to_token(char *input, t_token **tokens);
void	add_token_back(t_token **head, char *token);
char	**smart_split(char *input);
void	expand_checker(t_token *lst);
void	heredoc_bf_dollar(t_token *lst);

#endif
