/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:26:45 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 18:50:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Retrieves the input for the echo command, excluding '-n' option.
 *
 * Iterates over the tokens of the command to find the first argument that
 * is not the '-n' option, indicating the start of the echo input text.
 *
 * @param cmd Pointer to the command structure containing tokens.
 * @return Pointer to the text to be echoed, or NULL if only '-n' is present.
 */

char	*ft_get_echo_input(t_cmd *cmd)
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

/**
 * @brief Checks if the echo command includes the '-n' option.
 *
 * Searches the command's tokens to determine if the '-n' option is present,
 * which instructs echo to not output the trailing newline.
 *
 * @param cmd Pointer to the command structure to search for '-n'.
 * @return TRUE if '-n' is found, FALSE otherwise.
 */

int	ft_has_option(t_cmd *cmd)
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

/**
 * @brief Executes the echo command with or without the trailing newline.
 *
 * Outputs the echo input text retrieved from the command tokens. If the '-n'
 * option is found, the trailing newline is omitted; otherwise, it's included.
 * Exits if executed within a child process.
 *
 * @param cmd Pointer to the command structure for echo input and options.
 * @param is_child Flag indicating if the function is called in a child process.
 */

void	ft_echo(t_cmd *cmd, int is_child)
{
	char	*echo_output;

	if (ft_has_option(cmd))
		ft_putstr_fd(ft_get_echo_input(cmd), STDOUT);
	else
	{
		echo_output = ft_strjoin(ft_get_echo_input(cmd), "\n");
		ft_putstr_fd(echo_output, STDOUT);
		free(echo_output);
	}
	if (is_child)
		exit(EXIT_SUCCESS);
}
