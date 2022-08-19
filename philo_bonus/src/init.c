/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:02:47 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 19:58:52 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_initialization(t_rules *rules)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/data");
	rules->fork = sem_open("/fork", O_CREAT, S_IRWXU, rules->philo_amount);
	rules->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	rules->data = sem_open("/data", O_CREAT, S_IRWXU, 1);
	if (rules->fork <= 0 || rules->print <= 0 || rules->data <= 0)
		return (1);
	return (0);
}

int	philo_initialazation(t_rules *rules)
{
	int	i;

	i = 0;
	while (i <= rules->philo_amount)
	{
		rules->philosofers[i].id = i;
		rules->philosofers[i].ate = 0;
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
	rules->death = 0;
	if (rules->philo_amount < 1 || rules->death_time < 0 || rules->eat_time < 0
		|| rules->sleep_time < 0)
		return (1);
	if (argv[5])
	{
		rules->meals_amount = ft_atoi(argv[5]);
		if (rules->meals_amount <= 0)
			return (1);
	}
	else
		rules->meals_amount = -1;
	if (rules->meals_amount == 1)
		rules->meals_amount++;
	if (sem_initialization(rules))
		return (2);
	philo_initialazation(rules);
	return (0);
}
