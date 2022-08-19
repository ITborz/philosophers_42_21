/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:07:43 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 19:33:18 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating_proc(t_philo *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	sem_wait(rules->fork);
	my_print(rules, phil->id, "has taken a fork");
	sem_wait(rules->fork);
	my_print(rules, phil->id, "has taken a fork");
	sem_wait(rules->data);
	my_print(rules, phil->id, "is eating");
	phil->last_meal = ft_gettime();
	sem_post(rules->data);
	ft_sleep(rules->eat_time, rules);
	(phil->ate)++;
	sem_post(rules->fork);
	sem_post(rules->fork);
}

void	*died_test(void *dead)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)dead;
	rules = philo->rules;
	while (1)
	{
		sem_wait(rules->data);
		if (time_diff(philo->last_meal, ft_gettime()) > rules->death_time)
		{
			my_print(rules, philo->id, "died");
			rules->death = 1;
			sem_wait(rules->print);
			exit(1);
		}
		sem_post(rules->data);
		if (rules->death)
			break ;
		usleep(1000);
		if (rules->meals_amount != -1 && philo->ate >= rules->meals_amount)
			break ;
	}
	return (NULL);
}

void	p_proc(void *p_proc)
{
	t_philo	*philosovers;
	t_rules	*rules;

	philosovers = (t_philo *)p_proc;
	rules = philosovers->rules;
	philosovers->last_meal = ft_gettime();
	pthread_create(&(philosovers->check_death), NULL, died_test, p_proc);
	if (philosovers->id % 2)
		usleep(15000);
	while (!(rules->death))
	{
		eating_proc(philosovers);
		if (rules->meals_amount != -1 && \
			philosovers->ate >= rules->meals_amount)
			break ;
		my_print(rules, philosovers->id, "is sleeping");
		ft_sleep(rules->sleep_time, rules);
		my_print(rules, philosovers->id, "is thinking");
	}
	pthread_join(philosovers->check_death, NULL);
	if (rules->death)
		exit(1);
	exit (0);
}

void	exit_executer(t_rules *rules)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < rules->philo_amount)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < rules->philo_amount)
				kill(rules->philosofers[i].proc_id, SIGTERM);
			break ;
		}
	}
	sem_close(rules->fork);
	sem_close(rules->print);
	sem_close(rules->data);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/data");
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
		philo[i].proc_id = fork();
		if (philo[i].proc_id < 0)
			return (1);
		if (philo[i].proc_id == 0)
			p_proc(&(philo[i]));
		usleep(100);
		i++;
	}
	exit_executer(rules);
	return (0);
}
