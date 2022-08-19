/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:50:38 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 19:20:07 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	for_norm(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_amount && rules->death == 0)
	{
		pthread_mutex_lock(&(rules->data));
		if (time_diff(philo[i].last_meal, ft_gettime()) > rules->death_time)
		{
			my_print(rules, i, "died");
			rules->death = 1;
		}
		pthread_mutex_unlock(&(rules->data));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	int		res;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (1);
	if (argc != 5 && argc != 6)
		return (write_error("Wrong format!"));
	res = argv_initialization(rules, argv);
	if (res != 0)
		return (error_manager(res));
	if (executer(rules))
		return (write_error("Error in creating the threads"));
	free(rules);
	return (0);
}
