/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:41 by csubires          #+#    #+#             */
/*   Updated: 2024/11/15 14:29:39 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *adjust_prompt(char **prompt)
{
	int term_len;
	int prompt_len;
	char *new_prompt;
	struct winsize w;

	ioctl(1, TIOCGWINSZ, &w);
	term_len = w.ws_col;
	prompt_len = ft_strlen(*prompt);
	if (prompt_len >= (term_len))
	{
		new_prompt = ft_calloc((term_len) + 4, sizeof(char));
		ft_strlcpy(new_prompt, *prompt, term_len);
		*prompt = ft_strconcat(3, GREEN, "@minishell:...", new_prompt);
		return (*prompt);
	}
	return (*prompt);
}

static void manage_sigint(int sig)
{
	(void)sig;
	if (isatty(0))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void manage_sigquit(int sig)
{
	(void)sig;
	if (isatty(0))
		signal(3, SIG_IGN);
}

void init_signals(void)
{
	signal(2, manage_sigint);
	signal(3, manage_sigquit);
}

void restore_signals(void)
{
	signal(2, SIG_DFL);
	signal(3, SIG_DFL);
}
