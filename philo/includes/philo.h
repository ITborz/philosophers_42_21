/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:42:02 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 18:21:08 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_rules
{
	int					philo_amount;
	int					death_time;
	int					eat_time;
	int					sleep_time;
	int					meals_amount;
	int					death;
	int					all_ate;
	long long			start_time;
	pthread_mutex_t		data;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	t_philo				*philosofers;

}						t_rules;

int						ft_atoi(const char *str);

int						executer(t_rules *rules);
void					*p_thread(void *vargp);
void					eating_proc(t_philo *philosofers);

long long				ft_gettime(void);
long long				time_diff(long long prev, long long current);
void					ft_sleep(long long time, t_rules *rules);
void					my_print(t_rules *rules, int id, char *text);

int						argv_initialization(t_rules *rules, char **argv);
int						philo_initialazation(t_rules *rules);
int						mutex_initialization(t_rules *rules);

int						write_error(char *str);
int						error_manager(int error);
void					for_norm(t_philo *philo, t_rules *rules);

#endif