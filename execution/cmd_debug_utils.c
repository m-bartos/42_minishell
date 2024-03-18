/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_debug_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:38:55 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 10:19:11 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Prints the commands and their arguments in a command table.
 *
 * Iterates through each command in the command table and prints its tokens
 * (arguments and options). Commands are separated by " | ", and tokens within
 * a command are separated by a space. Ends the output with a newline.
 *
 * @param tab Pointer to the command table containing commands to print.
 */

void	ft_print_cmd(t_cmd_tab *tab)
{
	t_command	*command;
	t_token		*token;

	command = tab->first_cmd;
	while (command != NULL)
	{
		token = command->first_token;
		while (token != NULL)
		{
			if (token->next != NULL)
				ft_printf("%s ", token->text);
			else
				ft_printf("%s", token->text);
			token = token->next;
		}
		command = command->next_cmd;
		if (command != NULL)
			ft_printf(" | ");
	}
	ft_putstr_fd("\n", 1);
}

/**
 * @brief Prints the types of tokens in each command in a command table.
 *
 * Iterates through each command in the command table and prints the type of
 * each token (e.g., argument, option). Commands are separated by " | ", and
 * token types within a command are separated by a space. Ends the output with
 * a newline.
 *
 * @param tab Pointer to the command table containing commands to print.
 */

void	ft_print_cmd_types(t_cmd_tab *tab)
{
	t_command	*command;
	t_token		*token;

	command = tab->first_cmd;
	while (command != NULL)
	{
		token = command->first_token;
		while (token != NULL)
		{
			if (token->next != NULL)
				ft_printf("%d ", token->type);
			else
				ft_printf("%d", token->type);
			token = token->next;
		}
		command = command->next_cmd;
		if (command != NULL)
			ft_printf(" | ");
	}
	ft_putstr_fd("\n", 1);
}
