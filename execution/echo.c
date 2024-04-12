/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:26:45 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/12 17:40:07 by aldokezer        ###   ########.fr       */
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
	int		index;
	char	*input;
	char	*tmp;

	input = malloc(sizeof(char));
	*input = '\0';
	if (ft_has_option(cmd))
	{
		if (cmd->first_token->next->next != NULL)
			index = 2;
		else
			return (input);
	}
	else
		index = 1;
	while (cmd->execve_cmd[index])
	{
		tmp = input;
		input = ft_strjoin(input, cmd->execve_cmd[index]);
		free(tmp);
		if (cmd->execve_cmd[index + 1] != NULL)
		{
			tmp = input;
			input = ft_strjoin(input, " ");
			free(tmp);
		}
		index++;
	}
	return (input);
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

	if (cmd->first_token->next != NULL)
	{
		token = cmd->first_token->next;
		if (token->type == ARG && ft_strncmp(token->text, "-n", 3) == 0)
			return (TRUE);
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

void	ft_echo(t_cmd *cmd, t_env_list *env_list, int is_child)
{
	char	*echo_output;
	char	*echo_input;
	int		fd_dev;
	// Ignores STDIN as the command is ECHO
	fd_dev = open("/dev/null", O_RDONLY);
	dup2(fd_dev, STDIN_FILENO);
	close(fd_dev);
	echo_input = ft_get_echo_input(cmd);
	if (ft_has_option(cmd))
		ft_putstr_fd(echo_input, STDOUT);
	else
	{
		echo_output = ft_strjoin(echo_input, "\n");
		ft_putstr_fd(echo_output, STDOUT);
		free(echo_output);
	}
	free(echo_input);
	if (is_child)
		exit_minishell(NULL, EXIT_SUCCESS);
	else
		ft_add_env(env_list, "?=0");
}
