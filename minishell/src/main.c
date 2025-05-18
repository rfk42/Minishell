/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:26:16 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/06 13:46:58 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_pid = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	if (argc > 1)
		return (printf("Error: Too many arguments\n"), 1);
	begin_check(&mem, argv, envp);
	while (1)
	{
		sig_init_signals();
		mem.input = readline("minishell$>");
		if (g_pid)
			mem.exit_stat = g_pid;
		if (!mem.input)
			break ;
		if (*(mem.input))
			add_history(mem.input);
		if (!init_mem(&mem))
			continue ;
		if (mem.tokens)
			exec(&mem);
		free_mem(&mem);
		if (mem.exit == 1)
			break ;
	}
	end_check(&mem);
	return (mem.exit_stat);
}
