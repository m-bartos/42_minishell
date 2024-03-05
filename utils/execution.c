/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/05 23:16:14 by aldokezer        ###   ########.fr       */
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

		if (ft_strncmp(cmds[process_count][0], "<", 1) == 0)
		{
			process_count++;
			if (ft_input_file("infile.txt") != -1)
			{
				prev_in_fd = ft_input_file("infile.txt");
				process_count++;
			}
			else
				return ;
		}
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

/*
		if (ft_input_file("infile.txt") != -1)
			prev_in_fd = ft_input_file("infile.txt");
*/

