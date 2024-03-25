/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution_update.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:47:51 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/25 20:39:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_fork(t_cmd *cmd, t_mini_data *minidata, t_exec_data *data)
{
	int	p_fd[2];
	int	p_id;

	if (pipe(p_fd) == -1)
	{
		perror("Pipe error");
		return ;
	}
	p_id = fork();
	if (p_id == -1)
	{
		perror("Fork error");
		return ;
	}
	if (p_id == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		ft_redirect_io(cmd, &p_fd[0], &p_fd[1]);
		//ft_redir_process_io(data, cmd);
		ft_exec_commands(cmd, minidata);
		//execve(cmd->execve_cmd[0], cmd->execve_cmd, minidata->env_arr);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

void	ft_exec_input(t_cmd_tab *tab, t_mini_data *minidata)
{
	t_exec_data data;
	t_cmd	*cmd;

	ft_init_exec_data(&data);
	cmd = tab->first_cmd;
	while (cmd)
	{
		pipe_fork(cmd, minidata, &data);
		cmd = cmd->next;
	}
	ft_parent_process(&data, minidata);
}

// int	open_files(int argc, char **argv, int *fd_in, int *fd_out)
// {
// 	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0 \
// 		&& ft_strlen("here_doc") == ft_strlen(argv[1]) && argc > 5)
// 	{
// 		ft_read_heredoc(argv[2]);
// 		*fd_in = open("here_doc", O_RDONLY, 0444);
// 		*fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
// 		return (3);
// 	}
// 	else
// 	{
// 		*fd_in = open(argv[1], O_RDONLY, 0444);
// 		*fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 		return (2);
// 	}
// }

// int	main(int argc, char **argv, char **env)
// {
// 	int	i;
// 	int	fd_in;
// 	int	fd_out;

// 	if (argc < 5)
// 	{
// 		ft_putstr_fd("Error format: ./pipex file1 cmd1 .. cmdn file2\n", 2);
// 		ft_putstr_fd("./pipex here_doc LIMITER cmd1 .. cmdn file2\n", 2);
// 		return (1);
// 	}
// 	i = open_files(argc, argv, &fd_in, &fd_out);
// 	if (fd_in < 0 || fd_out < 0)
// 	{
// 		perror("File error");
// 		return (1);
// 	}
// 	dup2(fd_in, STDIN_FILENO);
// 	while (i < (argc - 2))
// 		pipe_fork(argv[i++], env);
// 	unlink("here_doc");
// 	dup2(fd_out, STDOUT_FILENO);
// 	execute(argv[i], env);
// }

// void	ft_exec_input(t_cmd_tab *tab, t_mini_data *minidata)
// {
// 	t_exec_data data;
// 	t_cmd	*cmd;

// 	ft_init_exec_data(&data);
// 	cmd = tab->first_cmd;
// 	while (cmd)
// 	{
// 		pipe(data.pipe_fd);
// 		if (fork() == 0)
// 		{
// 			ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
// 			ft_redir_process_io(&data, cmd);
// 			ft_exec_commands(cmd, minidata);
// 		}
// 		else
// 			ft_parent_process(&data, minidata);
// 		cmd = cmd->next;
// 	}
// }