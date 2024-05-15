/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:49:43 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/15 09:27:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sigint_received = 130;
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	disable_ctrl_c_output();
}

void	disable_ctrl_c_output(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	clean_cmd(NULL, 0, NULL);
	exit_minishell(NULL, 130);
}

void	handle_sigint_heredoc_parent(int sig)
{
	(void)sig;
	g_sigint_received = 130;
}
