/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_and_execve_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:26:48 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 21:17:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_token_cmd_path(t_token *token)
{
	char	*str_path;
	char	*temp_path;
	char	**arr_of_paths;
	int		i;

	if (access(token->text, X_OK) == 0)
		return ;
	temp_path = getenv("PATH");
	arr_of_paths = ft_split(temp_path, ':');
	i = 0;
	while (arr_of_paths[i] != NULL)
	{
		temp_path = ft_strjoin(arr_of_paths[i], "/");
		str_path = ft_strjoin(temp_path, token->text);
		free(temp_path);
		if (access(str_path, X_OK) == 0)
			break ;
		free(str_path);
		i++;
	}
	if (arr_of_paths[i] == NULL)
		token->type = CMD_ERR;
	else
	{
		free(token->text);
		token->text = str_path;
	}
	free_array(arr_of_paths);
}

void	make_cmd_paths(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		token = cmd->first_token;
		while(token != NULL)
		{
			if (token->type == CMD)
			{
				expand_token_cmd_path(token);
			}
			token = token->next;
		}
		cmd = cmd->next;
	}
}

int	count_cmd_length(t_cmd *cmd)
{
	t_token	*token;
	int		length;

	token = cmd->first_token;
	length = 0;
	while(token != NULL)
	{
		if (token->type == CMD || token->type == ARG)
			length++;
		else if (token->type == CMD_ERR)
			return (-1);
		token = token->next;
	}
	return (length);
}

void	make_one_execve_cmd(t_cmd *cmd)
{
	t_token	*token;
	char	**execve_cmd;
	int		length;
	int		i;

	length = count_cmd_length(cmd);
	if (length == -1)
	{
		cmd->execve_cmd = NULL;
		return ;
	}
	execve_cmd = (char **) malloc(sizeof(char *) * (length + 1));
	token = cmd->first_token;
	i = 0;
	while(i < length)
	{
		if (token->type == CMD || token->type == ARG)
			execve_cmd[i++] = token->text;
		token = token->next;
	}
	execve_cmd[i] = NULL;
	cmd->execve_cmd = execve_cmd;
}

void	make_execve_cmds(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;

	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		make_one_execve_cmd(cmd);
		cmd = cmd->next;
	}
}
