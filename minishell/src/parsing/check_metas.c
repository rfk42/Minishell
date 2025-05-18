/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:23:45 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 13:23:47 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_meta_next(char *s1, char *s2)
{
	if (is_redirect(s1))
	{
		if (is_meta_char(s2))
		{
			printf("minishell: parse error near \'%s\'\n", s2);
			return (0);
		}
	}
	else
	{
		if (!ft_strcmp(s2, "|") || is_logical(s2))
		{
			printf("minishell: parse error near \'%s\'\n", s1);
			return (0);
		}
	}
	return (1);
}

int	check_metas(char **tokens)
{
	int	i;

	i = 0;
	if (!ft_strcmp(tokens[0], "|") || is_logical(tokens[0]))
		return (printf("minishell: syntax error near \'%s\'\n", tokens[0]), 0);
	while (tokens[i + 1])
	{
		if (is_meta_char(tokens[i]))
		{
			if (!check_meta_next(tokens[i], tokens[i + 1]))
				return (0);
		}
		i++;
	}
	if (is_meta_char(tokens[i]))
		return (printf("minishell: syntax error near \'%s\'\n", tokens[i]), 0);
	return (1);
}
