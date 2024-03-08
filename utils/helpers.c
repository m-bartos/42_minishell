/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:49:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 16:27:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	t_token	*ptr_token;

	ptr_token = cmd->first_token;
	while (ptr_token != NULL)
	{
		ft_printf(" %s", ptr_token->text);
		ptr_token = ptr_token->next;
	}
	ft_putstr_fd("\n", 1);
}
