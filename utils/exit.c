/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:39:39 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/14 13:12:31 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	This function is supposed to be used at the begining just after parser does its job.
	It will efectivelly exit minishell
*/
void	ft_exit_minishell(t_cmd_tab *tab)
{
	t_command *cmd;

	cmd = tab->first_cmd;
	if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0 && tab->size == 1)
	{
		// add cleaning function - to clean the tab
		exit(EXIT_SUCCESS);
	}
}

// This function is supposed to be use if the exit cmd is nested inside pipeline
// It will exit the child process
void	ft_exit(t_command *cmd)
{
	if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0)
		exit(EXIT_SUCCESS);
}
