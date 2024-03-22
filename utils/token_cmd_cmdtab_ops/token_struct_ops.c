/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:50:42 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/21 11:33:46 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token_utils.c
 * @brief Utility functions for handling token structures.
 */

#include "../../minishell.h"

/**
 * @brief Initializes a token structure with default values.
 * 
 * @param token The token structure to initialize.
 */
void	ft_init_token_struct(t_token *token)
{
	token->text = NULL;
	token->type = NOT_ASSIGNED;
	token->next = NULL;
	token->prev = NULL;
}

/**
 * @brief Creates a new token with the given text and type.
 * 
 * @param text The text of the token.
 * @param type The type of the token.
 * @return A pointer to the newly created token.
 */
t_token	*ft_create_new_token(char *text, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("minishell: ");
		exit (EXIT_FAILURE);
	}
	ft_init_token_struct(token);
	token->text = text;
	token->type = type;
	return (token);
}
