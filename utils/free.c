/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:02:49 by csubires          #+#    #+#             */
/*   Updated: 2024/11/23 19:57:51 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(void *data)
{
	if (data)
	{
		free(data);
		data = 0;
	}
}

void	free_tokens(t_shell *shell)
{
	dlist_clear(&(shell->token_list), free_data);
	shell->token_list = 0;
}

static void	free_args(t_dllist *args)
{

	dlist_clear(&(args), free_data);
	args = 0;

/*
	
	t_dllist	*tmp_list;
	t_dllist	*next_arg;

	tmp_list = args;
	while (tmp_list)
	{
		next_arg = tmp_list->next;
		if (tmp_list->data)
			free_data(tmp_list->data);
		free(tmp_list);
		tmp_list = 0;
		tmp_list = next_arg;
	}
	*/
}

void	free_execs(void *item)
{
	t_exec	*exec_cmd;

	exec_cmd = (t_exec *)item;
	if (!exec_cmd)
		return ;
	free_args(exec_cmd->arg_list);
	if (exec_cmd->executable)
		free_data(exec_cmd->executable);
	if (exec_cmd->input_file)
		free_data(exec_cmd->input_file);
	if (exec_cmd->output_file)
		free_data(exec_cmd->output_file);
	if (exec_cmd->in_fd != 0)
		close(exec_cmd->in_fd);
	if (exec_cmd->out_fd != 1)
		close(exec_cmd->out_fd);
	if (exec_cmd->heredoc_delimiter)
		free_data(exec_cmd->heredoc_delimiter);
	if (exec_cmd->heredoc_data)
		free_data(exec_cmd->heredoc_data);
	free_data(exec_cmd);
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
		if (shell->env_list)
			dlist_clear(&shell->env_list, free_env_entry);
		if (shell->childrenpid_list)
			dlist_clear(&(shell->childrenpid_list), free_data);
		if (shell->prompt)
			free_data(shell->prompt);
		if (shell->input)
			free_data(shell->input);
		if (shell)
			free_data(shell);
	}
}
