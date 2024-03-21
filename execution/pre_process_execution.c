/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:19:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/21 11:12:23 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pre_exec_select_built_cmd(t_cmd *cmd, t_env_list *env_list)
{
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name) + 1) == 0)
		ft_echo(cmd, 0);
	else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name) + 1) == 0)
		ft_pwd(0);
	else if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name) + 1) == 0)
		ft_cd(cmd, 0);
	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name) + 1) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name) + 1) == 0)
		ft_export(env_list, cmd, 0);
	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name) + 1) == 0)
		ft_unset(env_list, cmd, 0);
	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name) + 1) == 0)
		ft_env(env_list, 0);
}

int	ft_is_inbuilt(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD_BUILT)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

int	ft_has_in_redir(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_IN)
			return (1);
		token = token->next;
	}
	return (0);
}

void	ft_redir_original_io(t_cmd *cmd, int *ori_in, int *ori_out)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			close(STDIN);
			dup2(*ori_in, STDIN);
			close(*ori_in);

		}
		else if (token->type == R_OUTFILE)
		{
			close(STDOUT);
			dup2(*ori_out, STDOUT);
			close(*ori_out);
		}
		else if (token->type == R_OUTFILE_APP)
		{
			close(STDOUT);
			dup2(*ori_out, STDOUT);
			close(*ori_out);
		}
		token = token->next;
	}
	return ;
}

// void	ft_close_io(t_cmd *cmd, int *fd_in, int *fd_out)
// {
// 	t_token	*token;

// 	token = cmd->first_token;
// 	while (token)
// 	{
// 		ft_printf("In close IO\n");
// 		if (token->type == R_INFILE)
// 		{
// 			dup2(STDIN, fd_in);
// 			close(fd_in);

// 		}
// 		else if (token->type == R_OUTFILE)
// 		{
// 			dup2(STDOUT, fd_out);
// 			close(fd_out);
// 		}
// 		else if (token->type == R_OUTFILE_APP)
// 		{
// 			dup2(STDOUT, fd_out);
// 			close(fd_out);
// 		}
// 		token = token->next;
// 	}
// 	return ;
// }

void	ft_pre_exec_redir_process_io(t_exec_data *data, t_cmd *cmd)
{
	if (ft_has_in_redir(cmd))
	{
		dup2(data->fd_in, STDIN);
		close (data->fd_in);
	}
	if (ft_has_out_redir(cmd))
	{
		dup2(data->fd_out, STDOUT);
		close(data->fd_out);
	}
}

int	ft_pre_exec(t_cmd_tab *tab, t_mini_data *minidata)
{
	t_exec_data data;
	t_cmd	*cmd;
	t_env_list	*envs;
	int		ori_in;
	int		ori_out;

	ori_in = dup(STDIN);
	ori_out = dup(STDOUT);

	ft_init_exec_data(&data);
	cmd = tab->first_cmd;
	envs = minidata->env_list;

	if (tab->size == 1 && ft_is_inbuilt(cmd))
	{
		ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
		ft_pre_exec_redir_process_io(&data, cmd);
		ft_pre_exec_select_built_cmd(cmd, envs);
		//ft_close_io(cmd, &data.fd_in, &data.fd_out);
		ft_redir_original_io(cmd, &ori_in, &ori_out);
		return (1);
	}
	return (0);
}