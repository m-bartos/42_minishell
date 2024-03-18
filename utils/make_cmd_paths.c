/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:12:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:48:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(t_token *token)
{
	char	*str_path;
	char	*temp_path;
	char	**arr_of_paths;
	int		i;

	temp_path = getenv("PATH"); // update with minishell environmental vars
	arr_of_paths = ft_split_e(temp_path, ':');
	if (arr_of_paths == NULL)
		return (NULL);
	i = 0;
	while (arr_of_paths[i] != NULL)
	{
		temp_path = ft_strjoin_e(arr_of_paths[i], "/");
		str_path = ft_strjoin_e(temp_path, token->text);
		free(temp_path);
		if (access(str_path, X_OK) == 0)
			break ;
		free(str_path);
		str_path = NULL;
		i++;
	}
	ft_free_array(arr_of_paths);
	return (str_path);
}

void	expand_token_cmd_path(t_token *token)
{

	char	*cmd_path;

	if (access(token->text, X_OK) == 0)
		return ;
	cmd_path = get_cmd_path(token);
	if (cmd_path == NULL)
		token->type = CMD_ERR;
	else
	{
		free(token->text);
		token->text = cmd_path;
	}
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
