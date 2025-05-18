/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_and_more_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:16:57 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/10 13:23:43 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_token **list, t_env *env, t_mem *mem)
{
	t_token	*temp;

	temp = *list;
	while (temp)
	{
		if (!handle_expansion(temp, env, mem))
			return (0);
		temp = temp->next;
	}
	return (1);
}
