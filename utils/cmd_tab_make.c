/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:22:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/10 10:23:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_cmd_tab(t_cmd_tab *cmd_tab, t_cmd *parsed_line)
{
	t_token	*token;
	t_token	*temp;

	token = parsed_line->first_token;
	ft_push_rotate_cmd(cmd_tab);
	while(token != NULL)
	{
		temp = token->next;
		if (is_pipe_type(token->prev))
			ft_push_rotate_cmd(cmd_tab);
		ft_move_token(cmd_tab->last_cmd, token);
		token = temp;
	}
	ft_init_cmd_struct(parsed_line);
}
