/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:20:37 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/13 18:21:53 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*get_env_val(char *name, t_mini *mini);
void	find_full_path(t_mini *mini);
void	get_cmd_path(char **path_env, t_cmd *cmd);
void	assign_full_path(char **path_env, t_cmd **cmd);
int		apply_redirections(t_cmd *cmd);
int		save_std_fds(t_mini *mini);
int		restore_std_fds(t_mini *mini);
void	exec_built_child(t_mini *mini, t_cmd *cmd);


#endif