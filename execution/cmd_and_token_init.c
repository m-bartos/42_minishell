/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_token_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:32:11 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 19:00:53 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Initializes a command table.
 *
 * Sets up an empty command table by setting first and last command pointers
 * to NULL and size to 0.
 *
 * @param cmd_tab Pointer to the command table to initialize.
 */

void	ft_init_cmd_table(t_cmd_tab *cmd_tab)
{
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}

/**
 * @brief Initializes a command structure.
 *
 * Sets all fields of a command structure to their default values, indicating
 * an empty command.
 *
 * @param cmd Pointer to the command to initialize.
 */

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->execve_cmd = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->first_token = NULL;
	cmd->last_token = NULL;
	cmd->size = 0;
}

/**
 * @brief Initializes a token structure.
 *
 * Sets all fields of a token to their default values, including setting text
 * to NULL and type to -1.
 *
 * @param token Pointer to the token to initialize.
 */

void	ft_init_token(t_token *token)
{
	token->text = NULL;
	token->type = -1;
	token->next = NULL;
	token->prev = NULL;
}
