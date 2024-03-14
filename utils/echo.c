/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:26:45 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/14 12:21:37 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_echo_input(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == ARG && ft_strncmp(token->text, "-n", 3) != 0)
			return (token->text);
		token = token->next;
	}
	return (NULL);
}

int	ft_is_option(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == ARG && ft_strncmp(token->text, "-n", 3) == 0)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

void	ft_echo(t_command *cmd)
{
	char	*echo_output;

	if (ft_is_option(cmd))
			ft_putstr_fd(ft_get_echo_input(cmd), STDOUT);
	else
	{
		echo_output = ft_strjoin(ft_get_echo_input(cmd), "\n");
		ft_putstr_fd(echo_output, STDOUT);
		free(echo_output);
	}
	exit(EXIT_SUCCESS);
}
