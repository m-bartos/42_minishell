/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:49:43 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/14 17:03:53 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ctrl_c_sig(int signal)
{
	// implement logic to load the prompt
	// it will not be inherited to execve!
	// it will be inherited to inbuilds - need to add the signal to each function to mimic it is a process
	ft_printf("\nYou pressed ctrl + c and the signal was: %d\n", signal);
	//exit(1);
}

// no need for this function, it is ignored in the signal function
// by providing macro instead of a pointer to a function
void	ft_ctrl_slash_sig(int signal)
{
	ft_putstr_fd("\nYou pressed ctrl + \\ and the signal was: ", 1);
	ft_putnbr_fd(signal, 1);
}
