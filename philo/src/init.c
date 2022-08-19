/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:02:47 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 17:53:27 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_initialization(t_rules *rules)
{
	int	i;

	rules->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* rules->philo_amount);
	if (!rules->fork)
		return (1);
	i = 0;
	while (i <= rules->philo_amount)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(rules->print), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->data), NULL))
		return (1);
	return (0);
}

int	philo_initialazation(t_rules *rules)
{
	int	i;

	rules->philosofers = (t_philo *)malloc(sizeof(t_philo) \
		* rules->philo_amount);
	if (!rules->philosofers)
		return (1);
	i = 0;
	while (i <= rules->philo_amount)
	{
		rules->philosofers[i].id = i;
		rules->philosofers[i].ate = 0;
		rules->philosofers[i].left_fork_id = i;
		rules->philosofers[i].right_fork_id = (i + 1) % rules->philo_amount;
		rules->philosofers[i].last_meal = 0;
		rules->philosofers[i].rules = rules;
		i++;
	}
	return (0);
}

int	argv_initialization(t_rules *rules, char **argv)
{
	rules->philo_amount = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->death = 0;
	if (rules->philo_amount < 1 || rules->death_time <= 0 \
		|| rules->eat_time <= 0
		|| rules->sleep_time <= 0)
		return (1);
	if (argv[5])
	{
		rules->meals_amount = ft_atoi(argv[5]);
		if (rules->meals_amount <= 0)
			return (1);
	}
	else
		rules->meals_amount = -1;
	if (mutex_initialization(rules))
		return (2);
	philo_initialazation(rules);
	return (0);
}
