/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:00:17 by csubires          #+#    #+#             */
/*   Updated: 2024/11/16 18:15:44 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	free_pwd(char *path, char *old_pwd, char *new_pwd)
{
	if (path)
		free(path);
	if (old_pwd)
		free(old_pwd);
	if (new_pwd)
		free(new_pwd);
	return (0);
}

static void	update_pwd(t_shell *shell, char *old_pwd, char *new_pwd)
{
	t_dllist		*env_item;

	env_item = search_env_item(shell->env_list, "PWD");
	if (new_pwd && env_item)
		update_envp(search_env_item(shell->env_list, "PWD"), new_pwd);
	else
		print_error(1, (void *)0, ERR_PATH, "cd");
	env_item = search_env_item(shell->env_list, "OLDPWD");
	if (old_pwd && env_item)
		update_envp(search_env_item(shell->env_list, "OLDPWD"), old_pwd);
	else
		print_error(1, (void *)0, ERR_PATH, "cd");
}

static char	*get_working_dir(t_exec	*exec_cmd)
{
	char	*path;
	char	*pwd;

	if (exec_cmd->arg_list && \
	((char *)exec_cmd->arg_list->data)[0] == '~')
		exec_cmd->arg_list->data = ft_strconcat(2, getenv("HOME"), \
		++exec_cmd->arg_list->data);
	if (!exec_cmd->arg_list)
		return (ft_strdup("."));
	//path = ft_strdup(getenv("HOME"));
	if (!ft_strcmp(exec_cmd->arg_list->data, "."))
	{
		pwd = getcwd(0, 0);
		path = ft_strdup(pwd);
		free(pwd);
	}
	else if (!ft_strcmp(exec_cmd->arg_list->data, ".."))
		path = 0;
	else
		path = ft_strdup(exec_cmd->arg_list->data);
	return (path);
}

size_t	buildin_cd(t_shell *shell, t_exec *exec_cmd)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = 0;
	new_pwd = 0;
	if (dlist_size(exec_cmd->arg_list) > 1)
	{
		print_error(1, (void *)0, ERR_MANY, "cd");
		return (0);
	}
	path = get_working_dir(exec_cmd);
	if (path && access(path, F_OK))
	{
		print_error(1, 0, ERR_PATH, "cd");
		return (free_pwd(path, old_pwd, new_pwd));
	}
	old_pwd = getcwd(0, 0);
	if (!path)
		chdir("..");
	if (path)
		chdir(path);
	new_pwd = getcwd(0, 0);
	update_pwd(shell, old_pwd, new_pwd);
	//print_cd_change(shell, old_pwd, new_pwd, path);
	return (free_pwd(path, old_pwd, new_pwd));
}
