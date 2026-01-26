/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:04:03 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/26 18:07:36 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_token	*create_token(char *token, int type);
void	input_to_token(char *input, t_token **tokens, t_mini *mini);
void	add_token_back(t_token **head, char *token);
char	**smart_split(char *input);
void	expand_checker(t_token *lst);
int		get_after_dollar(char *str);
void	heredoc_bf_dollar(t_token *lst);
void	expander(t_mini *mini);



#endif
