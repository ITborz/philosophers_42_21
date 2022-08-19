/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:49:46 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 18:01:12 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long prev, long long current)
{
	return (current - prev);
}

void	ft_sleep(long long time, t_rules *rules)
{
	long long	pause;

	pause = ft_gettime() + time;
	while (!rules->death)
	{
		if (ft_gettime() >= pause)
			break ;
		usleep(50);
	}
}

void	my_print(t_rules *rules, int id, char *text)
{
	pthread_mutex_lock(&(rules->print));
	if (!(rules->death))
	{
		printf("%lli ", ft_gettime() - rules->start_time);
		printf("%i ", id + 1);
		printf("%s\n", text);
	}
	pthread_mutex_unlock(&(rules->print));
	return ;
}

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}
