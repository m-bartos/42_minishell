/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:49:43 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/15 09:34:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 * 
 * This function handles the SIGINT signal, which is typically generated 
 * by pressing Ctrl+C. It writes a newline character to the standard output,
 * resets the state of the readline library, and updates a global variable
 * to indicate the signal was received.
 * 
 * @param sig The signal number (unused in this function).
 */
void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sigint_received = 130;
}

/**
 * @brief Sets up signal handling for SIGINT, SIGQUIT and Ctrl+C
 * 
 * This function configures the signal handlers for SIGINT (Ctrl+C) 
 * and SIGQUIT (Ctrl+\). SIGINT is handled by the `sigint_handler` function, 
 * and SIGQUIT is ignored. Additionally, it disables the output of the Ctrl+C 
 * sequence in the terminal.
 */
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

/**
 * @brief Disables the display of Ctrl+C output in the terminal.
 * 
 * This function modifies the terminal settings to disable the echoing of Ctrl+C
 * (SIGINT) control character. It adjusts the terminal's local flags to turn off
 * the ECHOCTL option.
 */
void	disable_ctrl_c_output(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief Signal handler for SIGINT during heredoc input.
 * 
 * This function handles SIGINT signals received during heredoc input. It writes
 * a newline character to the standard output, cleans up command resources, 
 * and exits the minishell with a status code of 130.
 * 
 * @param sig The signal number (unused in this function).
 */
void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	clean_cmd(NULL, 0, NULL);
	exit_minishell(NULL, 130);
}

/**
 * @brief Signal handler for SIGINT in the heredoc parent process.
 * 
 * This function handles SIGINT signals in the parent process during heredoc
 * input. It sets a global variable to indicate that the SIGINT signal
 * was received, with a status code of 130.
 * 
 * @param sig The signal number (unused in this function).
 */
void	handle_sigint_heredoc_parent(int sig)
{
	(void)sig;
	g_sigint_received = 130;
}
