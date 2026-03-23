#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               path.c                                       */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Looks up a variable by name in the t_env linked list and returns
 *		a direct pointer to its value string (not a copy).
 * @param name The environment variable name to search for.
 * @param mini Pointer to the main shell structure.
 * @return Pointer to the value string inside the t_env node, or NULL if
 *		the variable is not found.
 */
char	*get_env_val(char *name, t_mini *mini);

/**
 * @brief Resolves the full executable path for every t_cmd in mini->cmds
 *		by splitting $PATH and calling assign_full_path().
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	find_full_path(t_mini *mini);

/**
 * @brief Searches for the full executable path of cmd->args[0] across all
 *		directories in path_env. If args[0] already contains '/' and is
 *		accessible, it is used directly.
 * @param path_env NULL-terminated array of directories from $PATH.
 * @param cmd Pointer to the t_cmd node to update with cmd_path.
 * @return void
 */
void	get_cmd_path(char **path_env, t_cmd *cmd);

/**
 * @brief Iterates over the full t_cmd linked list and calls get_cmd_path()
 *		on each node to resolve all command paths.
 * @param path_env NULL-terminated array of directories from $PATH (may be NULL).
 * @param cmd Address of the head pointer of the t_cmd list.
 * @return void
 */
void	assign_full_path(char **path_env, t_cmd **cmd);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           executor_builtins.c                              */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Checks whether a command name matches any of the 7 
 * supported builtins.
 * @param cmd_name The command name string to check.
 * @return 1 if cmd_name is a builtin, 0 otherwise.
 */
int		is_builtin(char *cmd_name);

/**
 * @brief Checks whether a builtin must be executed in the parent process.
 * @param cmd_name The command name string to check.
 * @return 1 if the builtin must run in the parent, 0 otherwise.
 */
int		is_parent_builtin(char *cmd_name);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            executor_main.c                                 */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Entry point for command execution. Dispatches to single-command or
 *		pipeline handler depending on the number of t_cmd nodes.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	executor_dispatch(t_mini *mini);

/**
 * @brief Handles execution of a single command (no pipes). Runs parent
 *		builtins directly in the parent process; forks a child for everything
 *		else.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the single t_cmd node to execute.
 * @return void
 */
void	handle_single_cmd(t_mini *mini, t_cmd *cmd);

/**
 * @brief Handles execution of a pipeline. Iterates over all t_cmd nodes,
 *		creating pipes and forking a child process for each command.
 *		Waits for all children when the loop ends.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	handle_pipeline_loop(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           handle_execution.c                               */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Dispatches execution to the correct builtin function based on
 *		cmd->args[0].
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the t_cmd node whose args[0] is the builtin name.
 * @return Exit code returned by the called builtin function.
 */
int		execute_builtin_func(t_mini *mini, t_cmd *cmd);

/**
 * @brief Sets up redirections and executes a command node inside a child
 *		process. Handles both builtins (exit after) and external binaries.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the t_cmd node to execute.
 * @return void (always terminates the child process via exit or execve).
 */
void	execute_command_node(t_mini *mini, t_cmd *cmd);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            handle_pipeline.c                               */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Creates a pipe (pipe_fd[0], pipe_fd[1]) if there is a next command.
 *		Cleans up and returns -1 on failure.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the current t_cmd node.
 * @param prev_pipe Read end of the previous pipe (-1 if none), closed on 
 * error.
 * @param pipe_fd Array of 2 ints to receive the new pipe file descriptors.
 * @return 0 on success, -1 on pipe() failure.
 */
int		init_pipe(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd);

/**
 * @brief Forks a new child process for the current pipeline command.
 *		Closes pipe FDs and returns -1 on fork failure.
 * @param cmd Pointer to the current t_cmd node (pid stored here).
 * @param prev_pipe Read end of the previous pipe.
 * @param pipe_fd Array of 2 ints with the current pipe FDs.
 * @return 0 on success, -1 on fork() failure.
 */
int		spawn_process(t_cmd *cmd, int prev_pipe, int *pipe_fd);

/**
 * @brief Child-side pipeline setup: resets signals, redirects stdin from
 *		prev_pipe and stdout to pipe_fd[1] if not the last command,
 *		then calls execute_command_node().
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the current t_cmd node.
 * @param prev_pipe Read end of the previous pipe (-1 if first command).
 * @param pipe_fd Array of 2 ints with the current pipe FDs.
 * @return void (never returns; process is replaced or exits).
 */
void	pipe_child_process(t_mini *mini, t_cmd *cmd, int prev_pipe,
			int *pipe_fd);

/**
 * @brief Parent-side pipeline cleanup: closes the previous pipe read end
 *		and stores the new pipe read end in *prev_pipe for the next iteration.
 * @param cmd Pointer to the current t_cmd node.
 * @param prev_pipe Pointer to the previous pipe read FD (updated in place).
 * @param pipe_fd Array of 2 ints with the current pipe FDs.
 * @return void
 */
void	pipe_parent_process(t_cmd *cmd, int *prev_pipe, int *pipe_fd);

/**
 * @brief Waits for all child processes in the pipeline to finish and stores
 *		the exit status of the last command in mini->exit_status.
 *		Handles SIGINT and SIGQUIT termination signals.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	wait_all_children(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                          handle_redirections.c                             */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Applies both input and output redirections for a command node.
 *		Called inside child processes before executing the command.
 * @param cmd Pointer to the t_cmd node to set up.
 * @return 1 if both redirections succeed, 0 if either fails.
 */
int		setup_redirections(t_cmd *cmd);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                        handle_redirections_utils.c                         */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Saves copies of STDIN and STDOUT file descriptors into
 *		mini->stdin_backup and mini->stdout_backup using dup().
 *		Used before executing a parent builtin with redirections.
 * @param mini Pointer to the main shell structure.
 * @return 0 on success, -1 on dup failure.
 */
int		backup_std_fds(t_mini *mini);

/**
 * @brief Restores STDIN and STDOUT from mini->stdin_backup and
 *		mini->stdout_backup using dup2(), then closes the backup FDs.
 *		Used after executing a parent builtin with redirections.
 * @param mini Pointer to the main shell structure.
 * @return 0 on success, -1 on dup2 failure.
 */
int		restore_std_fds(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                             handle_single.c                                */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Executes a parent builtin (cd, export, unset, exit) directly in the
 *		parent process. Backs up and restores std FDs around the call so
 *		that any output redirections are applied and then undone.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the t_cmd node to execute.
 * @return void
 */
void	execute_builtin_in_parent(t_mini *mini, t_cmd *cmd);

/**
 * @brief Child-side execution for a single command (no pipeline). Resets
 *		signals to default and calls execute_command_node(). If args[0] is
 *		NULL, only applies redirections and exits cleanly.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the t_cmd node to execute.
 * @return void (never returns; child exits or calls execve).
 */
void	single_cmd_child_process(t_mini *mini, t_cmd *cmd);

/**
 * @brief Parent-side wait for a single forked command. Sets child signal
 *		handling, waits with waitpid() and stores the exit status in
 *		mini->exit_status. Handles SIGQUIT core dump message.
 * @param mini Pointer to the main shell structure.
 * @param cmd Pointer to the t_cmd node whose pid to wait on.
 * @return void
 */
void	single_cmd_parent_wait(t_mini *mini, t_cmd *cmd);

#endif
