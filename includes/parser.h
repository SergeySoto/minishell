/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:02:25 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/02 21:04:16 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		is_space(char c);
int		check_pipe(char *str);
int		check_pending_pipe(char *str);
int		check_quotes(char *str);
int		check_forbidden(char *str);
void	update_quote_status(char c, char *quotes);
int		pre_pars(char	*input);
t_env	*init_env(char **envp);
char	**env_to_array(t_env *envp);
int	count_args(t_token *token);
void	init_cmd(t_mini **mini);


#endif
