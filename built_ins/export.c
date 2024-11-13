/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:56:55 by csubires          #+#    #+#             */
/*   Updated: 2024/11/13 11:33:26 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	export_arg(t_shell *shell, t_exec *exec_cmd)
{
	t_dllist	*node;
	t_dllist	*tmp_list;
	char		**one_var;

	tmp_list = exec_cmd->arg_list;
	while (tmp_list)
	{
		one_var = split_env_item((char *)tmp_list->data, '=');
		if (!one_var)
		{
			print_error(1, 0, ERR_ASIG);
			return (0);
		}
		node = search_env_item(shell->env_list, one_var[0]);
		if (node)
			update_envp(node, one_var[1]);
		else
			insert_env_item(shell, create_env_item(one_var));
		free(one_var);
		tmp_list = tmp_list->next;
	}
	shell->exit_stat = 0;
	return (0);
}

size_t	buildin_export(t_shell *shell, t_exec *exec_cmd)
{
	size_t	stat;

	stat = 0;
	if (exec_cmd->arg_list)
		stat = export_arg(shell, exec_cmd);
	shell->exit_stat = 0;
	return (stat);
}
