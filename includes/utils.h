/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:06:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/20 20:29:12 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*free_token(char *str, char **env);
void	print_tokens(t_token **head);
void	trim_quotes(t_token *input);


#endif