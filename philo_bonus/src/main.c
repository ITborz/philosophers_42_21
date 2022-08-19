/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:50:38 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 19:58:58 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		res;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong format!"));
	res = argv_initialization(&rules, argv);
	if (res != 0)
		return (error_manager(res));
	if (executer(&rules))
		return (write_error("Error in creating the threads"));
	return (0);
}
