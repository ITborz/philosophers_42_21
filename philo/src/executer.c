/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:07:43 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 18:20:47 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_proc(t_philo *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	pthread_mutex_lock(&(rules->fork[phil->left_fork_id]));
	my_print(rules, phil->id, "has taken a fork");
	pthread_mutex_lock(&(rules->fork[phil->right_fork_id]));
	my_print(rules, phil->id, "has taken a fork");
	pthread_mutex_lock(&(rules->data));
	my_print(rules, phil->id, "is eating");
	phil->last_meal = ft_gettime();
	pthread_mutex_unlock(&(rules->data));
	ft_sleep(rules->eat_time, rules);
	(phil->ate)++;
	pthread_mutex_unlock(&(rules->fork[phil->right_fork_id]));
	pthread_mutex_unlock(&(rules->fork[phil->left_fork_id]));
}

void	*p_thread(void *vargp)
{
	int		i;
	t_philo	*philosovers;
	t_rules	*rules;

	i = 0;
	philosovers = (t_philo *)vargp;
	rules = philosovers->rules;
	if (philosovers->id % 2)
		usleep(15000);
	while (!(rules->death))
	{
		eating_proc(philosovers);
		if (rules->all_ate)
			break ;
		my_print(rules, philosovers->id, "is sleeping");
		ft_sleep(rules->sleep_time, rules);
		my_print(rules, philosovers->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_executer(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->philo_amount)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->philo_amount)
		pthread_mutex_destroy(&(rules->fork[i]));
	pthread_mutex_destroy(&(rules->print));
	free(rules->fork);
	free(rules->philosofers);
}

void	died_test(t_rules *rules, t_philo *philo)
{
	int	i;

	while (!rules->all_ate)
	{
		for_norm(philo, rules);
		if (rules->death)
		{
			pthread_detach(philo->thread_id);
			break ;
		}
		i = 0;
		while (rules->meals_amount != -1 && i < rules->philo_amount && \
			philo[i].ate >= rules->meals_amount)
			i++;
		if (i == rules->philo_amount)
				rules->all_ate = 1;
	}
}

int	executer(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philosofers;
	rules->start_time = ft_gettime();
	while (i < rules->philo_amount)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])))
			return (1);
		philo[i].last_meal = ft_gettime();
		i++;
	}
	died_test(rules, rules->philosofers);
	exit_executer(rules, philo);
	return (0);
}
