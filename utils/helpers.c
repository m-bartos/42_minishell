/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:38:55 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 14:44:20 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
