/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 22:25:50 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_commands(char ***cmds)
{
	int	process_count;
	int	prev_in_fd;
	int	fd[2];

	prev_in_fd = 0;
	process_count = 0;
	while (cmds[process_count])
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(prev_in_fd, STDIN);
			if (cmds[process_count + 1] != NULL)
				dup2(fd[1], STDOUT);
			close(fd[0]);
			execv(cmds[process_count][0], cmds[process_count]);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			prev_in_fd = fd[0];
		}
		process_count++;
	}
}
