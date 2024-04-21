/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:11:22 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 20:21:38 by mbartos          ###   ########.fr       */
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
