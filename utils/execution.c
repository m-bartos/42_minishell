/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/09 00:47:25 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_token *token;
	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			if (ft_input_file(token->text) == -1)
			{
				perror(token->text);
				return (-1);
			}
			else
				*fd_in = ft_input_file(token->text);
		}
		else if (token->type == R_OUTFILE)
			*fd_out = ft_output_file(token->text);
		else if (token->type == R_OUTFILE_APP)
		{
			if (ft_append_file(token->text) == -1)
			{
				perror(token->text);
				return (-1);
			}
			else
				*fd_out = ft_append_file(token->text);
		}
		token = token->next;
	}
	return (0);
}

void	ft_exec_commands(t_cmd_tab *tab)
{
	t_command	*cmd;
	int	prev_in_fd;
	int	fd_out;
	int	fd[2];

	prev_in_fd = 0;
	fd_out = -10;
	cmd = tab->first_cmd;
	while (cmd)
	{
		if (ft_redirects(cmd, &prev_in_fd, &fd_out) == -1)
		{
			cmd = cmd->next_cmd;
			continue;
		}
		pipe(fd);
		if (fork() == 0)
		{
			dup2(prev_in_fd, STDIN);
			if ((cmd + 1) != NULL && fd_out == -10)
				dup2(fd[1], STDOUT);
			else
				dup2(fd_out, STDOUT);
			close(fd[0]);
			execv(cmd->execve_cmd[0], cmd->execve_cmd);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			prev_in_fd = fd[0];
		}
		cmd = cmd->next_cmd;
	}
}
