/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:19:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/13 19:20:12 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_str_alpha(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_is_str_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}


int	ft_is_cmd_valid_export(t_cmd *cmd)
{
	if (ft_strchr(cmd->execve_cmd[1], '=') == NULL)
		return (0);
	return (1);
}

char	*ft_extract_key(char *str)
{
	char	**data;
	char	*key;

	data = ft_split(str, '=');
	key = ft_strdup(data[0]);
	free(data[0]);
	free(data[1]);
	free(data);
	return (key);
}

int	ft_is_key_valid(char *str)
{
	char	*cp_str;

	cp_str = str;
	if (!ft_isalpha(*cp_str))
		return (0);
	cp_str++;
	while (*cp_str != '\0')
	{
		if (ft_isalpha(*cp_str) || ft_isdigit(*cp_str))
			cp_str++;
		else
			return (0);
	}
	return (1);
}
