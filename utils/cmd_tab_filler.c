/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/04 12:38:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_and_fill_cmd_tab(t_command_table *ptr_cmd_tab, char **arr_of_tokens)
{
	size_t	index;

	ft_init_command_table(ptr_cmd_tab);
	index = 0;
	while (arr_of_tokens[index])
	{
		ft_push_rotate_token(ptr_cmd_tab, arr_of_tokens[index]);
		index++;
	}
}

void	print_cmd_tab(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;
	int		i;

	ptr_node = ptr_cmd_tab->first_node;
	i = 0;
	printf("-------------\n");
	while (ptr_node != NULL)
	{
		printf("%*i - Token: |%*s|     ", 2, i, 20, ptr_node->token);
		printf("Type: %i\n", ptr_node->type);
		ptr_node = ptr_node->next;
		i++;
	}
	printf("-------------\n");
}

int	is_pipe_type(t_node *ptr_node)
{
	int	type;

	type = ptr_node->type;
	if (type == PIPE)
		return (1);
	return (0);
}

int	is_redirection_type(t_node *ptr_node)
{
	int	type;

	type = ptr_node->type;
	if (type == R_IN || type == HERE_DOC
		|| type == R_OUT || type == R_OUT_APPND)
		return (1);
	return (0);
}

int	is_operator_type(t_node *ptr_node)
{
	int	type;

	type = ptr_node->type;
	if (is_pipe_type(ptr_node) || is_redirection_type(ptr_node))
		return (1);
	return (0);
}

void	assign_operator_types(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!ft_strncmp(ptr_node->token, "|", 2))
			ptr_node->type = PIPE;
		else if (!ft_strncmp(ptr_node->token, "<<", 3))
			ptr_node->type = HERE_DOC;
		else if (!ft_strncmp(ptr_node->token, "<", 2))
			ptr_node->type = R_IN;
		else if (!ft_strncmp(ptr_node->token, ">>", 3))
			ptr_node->type = R_OUT_APPND;
		else if (!ft_strncmp(ptr_node->token, ">", 2))
			ptr_node->type = R_OUT;
		ptr_node = ptr_node->next;
	}
}

void	assign_cmds_and_args(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;
	int		search_cmd_flag;
	int		redirect_file_flag;

	search_cmd_flag = 1;
	redirect_file_flag = 0;
	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (search_cmd_flag == 1 && redirect_file_flag == 0 && !is_operator_type(ptr_node))
		{
			ptr_node->type = COMMAND;
			search_cmd_flag = 0;
		}
		else if (is_redirection_type(ptr_node))
			redirect_file_flag = 1;
		else if ((search_cmd_flag == 0 && !is_operator_type(ptr_node)) ||
				(search_cmd_flag == 1 && redirect_file_flag == 1 && !is_operator_type(ptr_node)))
		{
			ptr_node->type = ARG;
			redirect_file_flag = 0;
		}
		else if (is_pipe_type(ptr_node))
			search_cmd_flag = 1;
		ptr_node = ptr_node->next;
	}
}

void	assign_types_to_tokens(t_command_table *ptr_cmd_tab)
{
	assign_operator_types(ptr_cmd_tab);
	assign_cmds_and_args(ptr_cmd_tab);
}

int	is_in_single_quotes(t_node *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (1);
	return (0);
}

int	is_in_double_quotes(t_node *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	len = ft_strlen(token);
	if (token[0] == '"' && token[len - 1] == '"')
		return (1);
	return (0);
}

void	remove_quotes(t_node *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	if (is_in_double_quotes(ptr_node) || is_in_single_quotes(ptr_node))
	{
		len = ft_strlen(token);
		token[len - 1] = '\0';
		ptr_node->token = ft_strdup(&token[1]);
		free(token);
	}
}

void	remove_quotes_from_cmd_table(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!is_operator_type(ptr_node))
			remove_quotes(ptr_node);
		ptr_node = ptr_node->next;
	}
}

void	expand_cmd_table(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!is_operator_type(ptr_node) && !is_in_single_quotes(ptr_node))
			ptr_node->token = expand_all_vars_in_str(ptr_node->token);
		ptr_node = ptr_node->next;
	}
}
