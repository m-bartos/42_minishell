/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:11:22 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/15 11:32:29 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a command has input redirection.
 *
 * Iterates through command tokens to determine if there is any form of
 * input redirection.
 *
 * @param cmd Pointer to the command structure.
 * @return 1 if input redirection exists, 0 otherwise.
 */

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

/**
 * @brief Checks if a command has output redirection.
 *
 * Iterates through command tokens to determine if there is any form of
 * output redirection (overwrite or append).
 *
 * @param cmd Pointer to the command structure.
 * @return 1 if output redirection exists, 0 otherwise.
 */

int	ft_has_out_redir(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_OUT || token->type == R_OUT_APP)
			return (1);
		token = token->next;
	}
	return (0);
}

int	ft_pre_exec_check_valid_infile(t_cmd *cmd, t_env_list *envs)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			if (access(token->text, F_OK | R_OK) == 0)
			{
				token = token->next;
				continue ;
			}
			else
			{
				perror(token->text);
				ft_add_env(envs, "?=1");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

void	ft_exec_check_valid_infile(t_exec_data *data, t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			if (access(token->text, F_OK | R_OK) == 0)
			{
				token = token->next;
				continue ;
			}
			else
			{
				perror(token->text);
				close(data->ori_fd_in);
				close(data->ori_fd_out);
				exit_minishell(NULL, EXIT_FAILURE);
			}
		}
		token = token->next;
	}
}
