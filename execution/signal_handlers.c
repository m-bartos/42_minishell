/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:49:43 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/14 21:59:15 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


volatile sig_atomic_t sigint_received = 0;

void	sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sigint_received = 1;
}

void	setup_signal_handling(void) {
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	disable_ctrl_c_output(void) {
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
