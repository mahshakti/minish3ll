/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:43:18 by csubires          #+#    #+#             */
/*   Updated: 2024/11/22 12:27:22 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	trim_executable(t_exec *exec_cmd, t_dllist **tmp_list)
{
	if (tmp_list && *tmp_list && !isnt_metachar(((char *)(*tmp_list)->data)[0]))
		print_error(1, 0, ERR_TOKEN, 0);
	exec_cmd->executable = ft_strdup((char *)(*tmp_list)->data);
	if (!exec_cmd->executable)
		print_error(-1, 0, ERR_NOTCMD, 0);
}

static void	args_to_dllist(t_shell *shell, t_exec *exec_cmd, char *data)
{
	t_dllist	*arg_node;

	if (data && data[(ft_strlen(data)) - 1] == ';')
		data[(ft_strlen(data)) - 1] = '\0';
	arg_node = dlist_new(ft_strdup(data));
	if (!arg_node)
	{
		print_error(-1, shell, ERR_NOTCMD, 0);
		free_execs(exec_cmd);
	}
	dlist_add_after(&(exec_cmd->arg_list), arg_node);
}

static int	is_redirect(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || \
		!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	else
		return (0);
}

static t_exec	*fill_cmd_struct(t_shell *shell, t_dllist **tmp_list)
{
	t_exec		*exec_cmd;
	t_dllist	*token;

	if (!tmp_list || !*tmp_list)
		return ((void *)0);
	if (!ft_strcmp((char *)(*tmp_list)->data, "|"))
		*tmp_list = (*tmp_list)->next;
	exec_cmd = ft_calloc(1, sizeof(t_exec));
	exec_cmd->in_fd = 0;
	exec_cmd->out_fd = 1;
	trim_executable(exec_cmd, tmp_list);
	token = (*tmp_list)->next;
	while (token && ft_strcmp((char *)token->data, "|"))
	{
		if (token->next && is_redirect((char *)token->data))
			manage_redirection(exec_cmd, &token);
		else
			args_to_dllist(shell, exec_cmd, (char *)token->data);
		token = token->next;
	}
	*tmp_list = token;
	return (exec_cmd);
}

void	exec_cmd_to_dllist(t_shell *shell)
{
	t_dllist	*tmp_list;
	t_dllist	*node;
	t_exec		*exec_cmd;

	tmp_list = shell->token_list;
	while (tmp_list)
	{
		exec_cmd = fill_cmd_struct(shell, &tmp_list);
		if (!exec_cmd)
			print_error(-1, shell, ERR_NOTCMD, "");
		node = dlist_new(exec_cmd);
		if (!node)
			print_error(-1, shell, ERR_NOTCMD, "");
		dlist_add_after(&(shell->exec_list), node);
		shell->num_of_cmds++;
	}
	free_tokens(shell);
}
