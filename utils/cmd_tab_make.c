/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:22:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/15 13:21:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_cmd_tab_from_cmd(t_cmd_tab *cmd_tab, t_cmd *parsed_line)
{
	t_token	*token;
	t_token	*temp_token;

	token = parsed_line->first_token;
	ft_push_rotate_cmd(cmd_tab);
	while (token != NULL)
	{
		temp_token = token->next;
		if (is_pipe_type(token->prev))
			ft_push_rotate_cmd(cmd_tab);
		ft_move_token(cmd_tab->last_cmd, token);
		token = temp_token;
	}
	ft_init_cmd_struct(parsed_line);
}