/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrischma <hrischma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:24:24 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/08 10:51:59 by hrischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_stronly(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_token *arg, t_mem *mem)
{
	t_token	*temp;
	int		n;

	temp = arg->next;
	n = 0;
	if (temp && temp->value[0] == '-' && ft_stronly(temp->value + 1, 'n'))
		n = 1;
	if (n == 1)
		temp = temp->next;
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE)
		{
			if ((n && temp != arg->next->next) || (!n && temp != arg->next))
				printf(" ");
			printf("%s", temp->value);
		}
		temp = temp->next;
	}
	if (n == 0 || temp == arg->next)
		printf("\n");
	mem->exit_stat = 0;
	return (1);
}
