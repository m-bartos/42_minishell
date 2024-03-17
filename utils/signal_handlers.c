/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:49:43 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 10:25:42 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Handles the SIGINT signal (Ctrl+C).
 *
 * This function is called when a SIGINT signal is received, typically through
 * a Ctrl+C action in the terminal. It can be used to load a new prompt or
 * perform clean-up actions. The received signal is not passed to execve,
 * but inbuilt functions will inherit this behavior, and they should handle
 * the signal accordingly.
 *
 * @note This function may exit the program or perform specific actions
 *       like clearing input or displaying a new prompt.
 *
 * @param signal The signal number received (expected to be SIGINT).
 */

void	ft_ctrl_c_sig(int signal)
{
	// implement logic to load the prompt
	// it will not be inherited to execve!
	// it will be inherited to inbuilds - need to add the signal to each function to mimic it is a process
	ft_printf("\nYou pressed ctrl + c and the signal was: %d\n", signal);
	//exit(1);
}

/**
 * @brief Handles the SIGQUIT signal (Ctrl+\).
 *
 * This function is intended to respond to a SIGQUIT signal, triggered by
 * pressing Ctrl+\ in the terminal. It's designed to be ignored or to perform
 * specific actions, like printing a message, as part of a custom signal
 * handling strategy.
 *
 * @note By default, this behavior is set to be ignored in the program's
 *       signal handling setup.
 *
 * @param signal The signal number received (expected to be SIGQUIT).
 */

void	ft_ctrl_slash_sig(int signal)
{
	ft_putstr_fd("\nYou pressed ctrl + \\ and the signal was: ", 1);
	ft_putnbr_fd(signal, 1);
}
