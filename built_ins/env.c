/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:02:16 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 11:18:52 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	buildin_env(t_shell *shell, t_exec *exec_cmd)
{
	t_dllist	*tmp_list;
	t_envp		*env_item;

	tmp_list = shell->env_list;
	while (tmp_list)
	{
		env_item = (t_envp *)tmp_list->data;
		if (env_item)
			ft_fdprint(exec_cmd->out_fd, "%s=%s\n", \
			env_item->key, env_item->value);
		tmp_list = tmp_list->next;
	}
	shell->exit_stat = 0;
	return (0);
}
