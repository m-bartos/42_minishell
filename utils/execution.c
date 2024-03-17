/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 10:57:07 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// test function - no longer in use
void	ft_exec_built_cmds(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (ft_strncmp(cmd->execve_cmd[0], "echo", 5) == 0)
	{
		ft_putstr_fd(cmd->execve_cmd[1], STDOUT);
		exit(EXIT_SUCCESS);
	}
	else
	{
		errno = ENOENT;
		if (errno == ENOENT)
		{
			ft_putstr_fd(error, STDERR);
			free(error);
			exit(CMD_NOT_FOUND);
		}
	}
}

// handles redirection of io in the child process just after fork
void	ft_redir_process_io(t_exec_data *data, t_command *cmd)
{
	dup2(data->fd_in, STDIN);
	if (cmd->next_cmd != NULL && (ft_has_out_redir(cmd) == 0))
		dup2(data->pipe_fd[1], STDOUT);
	else
		dup2(data->fd_out, STDOUT);
	close(data->pipe_fd[0]);
}


// executes commands
void	ft_exec_input(t_cmd_tab *tab)
{
	t_exec_data data;
	t_command	*cmd;

	ft_init_exec_data(&data);
	cmd = tab->first_cmd;
	while (cmd)
	{
		pipe(data.pipe_fd);
		if (fork() == 0)
		{
			ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
			ft_redir_process_io(&data, cmd);
			ft_exec_commands(cmd);
		}
		else
			ft_parent_process(&data);
		cmd = cmd->next_cmd;
	}
}
