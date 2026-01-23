/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:06:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/21 17:46:30 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*free_token(char *str, char **env);
void	print_tokens(t_token **head);
void	trim_quotes(t_token *input);
void	ft_lstiter(t_token *lst, void (*f)(t_token *));

#endif