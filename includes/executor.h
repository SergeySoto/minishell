/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:20:37 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/17 18:55:09 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*get_env_val(char *name, t_mini *mini);
void	find_full_path(t_mini *mini);
void	get_cmd_path(char **path_env, t_cmd *cmd);
void	assign_full_path(char **path_env, t_cmd **cmd);
int		is_builtin(char *cmd_name);
int		is_built_father(char *cmd_name);
int		run_builtin(t_mini *mini, t_cmd *cmd);
int		apply_redirections(t_cmd *cmd);
int		save_std_fds(t_mini *mini);
int		restore_std_fds(t_mini *mini);
void	exec_built_father(t_mini *mini, t_cmd *cmd);
void	exec_built_child(t_mini *mini, t_cmd *cmd);
void	exec_child_smp(t_mini *mini, t_cmd *cmd);
void	wait_father_smp(t_mini *mini, t_cmd *cmd);
void	child_process_mlt(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd);
void	father_process_mlt(t_cmd *cmd, int *prev_pipe, int *pipe_fd);
void	wait_children_mlt(t_mini *mini);
int		create_pipe(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd);
int		fork_process(t_cmd *cmd, int prev_pipe, int *pipe_fd);


#endif