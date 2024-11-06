/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:42:13 by csubires          #+#    #+#             */
/*   Updated: 2024/10/23 12:16:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_builtin(t_shell *shell, t_dllist *exec_list)
{
	t_exec	*exec_cmd;
	int		stat;

	stat = 0;
	if (exec_list && exec_list->data)
	{
		exec_cmd = (t_exec *)exec_list->data;
		if (!ft_strcmp(exec_cmd->executable, "cd"))
			stat = buildin_cd(shell, exec_cmd);
		else if (!ft_strcmp(exec_cmd->executable, "echo"))
			stat = buildin_echo(shell, exec_cmd);
		else if (!ft_strcmp(exec_cmd->executable, "env"))
			stat = buildin_env(shell, exec_cmd);
		else if (!ft_strcmp(exec_cmd->executable, "exit"))
			buildin_exit(shell);
		else if (!ft_strcmp(exec_cmd->executable, "export"))
			stat = buildin_export(shell, exec_cmd);
		else if (!ft_strcmp(exec_cmd->executable, "pwd"))
			stat = buildin_pwd(shell, exec_cmd);
		else if (!ft_strcmp(exec_cmd->executable, "unset"))
			stat = buildin_unset(shell, exec_cmd);
	}
	shell->exit_stat = stat;
}

static void	get_children_stat(t_shell *shell, t_dllist **children_pid)
{
	int		*child_pid;
	int		stat;

	stat = 0;
	while (*children_pid)
	{
		child_pid = (int *)(*children_pid)->data;
		waitpid(*child_pid, &stat, 0);
		if (WIFEXITED(stat))
			shell->exit_stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			shell->exit_stat = WTERMSIG(stat);
		dlist_remove_before(children_pid, free_data);
	}
}

static void	close_fds(t_exec *exec_cmd)
{
	if (exec_cmd->in_fd != 0)
		close(exec_cmd->in_fd);
	if (exec_cmd->out_fd != 1)
		close(exec_cmd->out_fd);
}

static void	create_child(t_shell *shell, t_exec *exec_cmd)
{
	t_dllist	*new_node;
	char		**env_array;
	char		**arg_array;
	int			*child_pid;

	env_array = envp_to_array(shell);
	arg_array = args_to_array(exec_cmd);
	child_pid = ft_calloc(1, sizeof(int));
	*child_pid = fork();
	if (*child_pid < 0)
		print_error(-1, shell, ERR_FORK);
	else if (!*child_pid)
	{
		restore_signals();
		execute_child(shell, env_array, arg_array, exec_cmd);
	}
	new_node = dlist_new(child_pid);
	if (!new_node)
		print_error(-1, shell, ERR_FORK);
	dlist_add_after(&shell->childrenpid_list, new_node);
	close_fds(exec_cmd);
	free_exec_arrays(env_array, arg_array);
}

void	execute_execs(t_shell *shell)
{
	t_dllist	*tmp_list;
	t_exec		*exec_cmd;

	tmp_list = shell->exec_list;
	while (tmp_list)
	{
		exec_cmd = (t_exec *)tmp_list->data;
		if (is_builtin(exec_cmd->executable))
			execute_builtin(shell, tmp_list);
		else
			create_child(shell, exec_cmd);
		tmp_list = tmp_list->next;
	}
	get_children_stat(shell, &shell->childrenpid_list);
	shell->num_of_cmds = 0;
}
