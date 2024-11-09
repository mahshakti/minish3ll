/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:01:16 by csubires          #+#    #+#             */
/*   Updated: 2024/11/09 11:04:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	is_narg(char *str)
{
	size_t	x;

	if (!str || !str[0] || str[0] != '-')
		return (0);
	x = 1;
	while (str[x])
		if (str[x++] == 'n')
			return (1);
	return (0);
}

static void	manage_new_line(t_dllist *arg_item[], size_t *line)
{
	if (*arg_item && (*arg_item)->data && \
	is_narg((char *)(*arg_item)->data))
	{
		*line = 0;
		*arg_item = (*arg_item)->next;
	}
}

static void	print_tokens(t_shell *shell, t_exec *exec_cmd)
{
	t_dllist	*tmp_list;
	char		*tmp_str;

	tmp_list = exec_cmd->arg_list;
	while (tmp_list)
	{
		tmp_str = (char *)tmp_list->data;
		if (!ft_strcmp(tmp_list->data, "$?"))
		{
			free(tmp_list->data);
			tmp_list->data = ft_itoa(shell->exit_stat);
		}
		ft_fdprint(exec_cmd->out_fd, "%s", tmp_str);
		if (tmp_str && tmp_str[0] != '$' && tmp_str[0])
			ft_fdprint(exec_cmd->out_fd, " ");
		tmp_list = tmp_list->next;
	}
}

size_t	buildin_echo(t_shell *shell, t_exec *exec_cmd)
{
	size_t	line;

	if (!exec_cmd)
	{
		print_error(1, shell, ERR_EXEC);
		shell->exit_stat = 1;
		return (1);
	}
	if (!exec_cmd->arg_list)
	{
		ft_fdprint(exec_cmd->out_fd, "\n");
		shell->exit_stat = 0;
		return (0);
	}
	line = 1;
	manage_new_line(&(exec_cmd->arg_list), &line);
	print_tokens(shell, exec_cmd);
	if (line)
		ft_fdprint(exec_cmd->out_fd, "\n");
	shell->exit_stat = 0;
	return (0);
}
