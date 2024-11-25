/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:19:52 by csubires          #+#    #+#             */
/*   Updated: 2024/11/25 11:30:21 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_input(t_shell *shell)
{
	if (shell->token_list)
		free_tokens(shell);
	if (shell->exec_list)
		dlist_clear(&(shell->exec_list), free_execs);
	if (shell->input)
	{
		free_data(shell->input);
		shell->input = 0;
	}
	if (shell->prompt)
	{
		free_data(shell->prompt);
		shell->prompt = 0;
	}
}

static t_shell	*init_shell(char *envp[])
{
	t_shell	*shell;
	char	*value;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		print_error(-1, shell, ERR_MALLOC, 0);
	shell->error = 0;
	shell->exit_stat = 0;
	envp_to_dllist(shell, envp);
	value = get_env_value(shell->env_list, "SHLVL");
	if (value)
	{
		value = ft_itoa(ft_atoi(value) + 1);
		update_envp(search_env_item(shell->env_list, "SHLVL"), value);
		free(value);
	}
	value = get_env_value(shell->env_list, "OLDPWD");
	if (value)
	{
		value = ft_itoa(ft_atoi(value) + 1);
		update_envp(search_env_item(shell->env_list, "OLDPWD"), "");
		free(value);
	}
	return (shell);
}

static char	*get_input(t_shell *shell)
{
	char	*path;

	path = ft_strltrim(get_env_value(shell->env_list, "PWD"), \
	get_env_value(shell->env_list, "HOME"));
	if (!path || ft_strlen(path) == 1)
		path = ft_strdup(get_env_value(shell->env_list, "PWD"));
	else
		path = ft_strjoin("~", path);
	shell->prompt = ft_strconcat(5, YELLOW, "42@minishell:", GREEN, \
	path, ENDC);
	printf("%s\n", shell->prompt);
	free(path);
	shell->input = readline(" $ ");
	if (!shell->input)
	{
		free_input(shell);
		free_all(shell);
		exit (0);
	}
	if (*(shell->input))
		add_history(shell->input);
	return (shell->input);
}

static void	fill_lists(t_shell *shell)
{
	tokens_to_dllist(shell);
	if (1)
		print_token_list(shell);
	if (!shell->error)
	{
		exec_cmd_to_dllist(shell);
		manage_fds(shell);
		if (1)
			print_exec_list(shell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	(void)argv;
	check_args(argc, envp);
	init_signals();
	shell = init_shell(envp);
	while (1 && !shell->error)
	{
		if (get_input(shell) && !is_empty(shell->input))
		{
			fill_lists(shell);
			if (shell->error)
			{
				shell->error = 0;
				free_input(shell);
				continue ;
			}
			execute_execs(shell);
			free_input(shell);
		}
	}
	restore_signals();
	free_all(shell);
	return (shell->exit_stat);
}
