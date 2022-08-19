/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:01:23 by bkristen          #+#    #+#             */
/*   Updated: 2022/06/26 19:51:17 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_philo
{
	int					id;
	int					ate;
	long long			last_meal;
	struct s_rules		*rules;
	pid_t				proc_id;
	pthread_t			check_death;
}						t_philo;

typedef struct s_rules
{
	int					philo_amount;
	int					death_time;
	int					eat_time;
	int					sleep_time;
	int					meals_amount;
	int					death;
	long long			start_time;
	sem_t				*data;
	sem_t				*fork;
	sem_t				*print;
	t_philo				philosofers[201];
}						t_rules;

int						ft_atoi(const char *str);
void					exit_executer(t_rules *rules);
int						executer(t_rules *rules);
void					p_proc(void *p_proc);
void					eating_proc(t_philo *philosofers);

long long				ft_gettime(void);
long long				time_diff(long long prev, long long current);
void					ft_sleep(long long time, t_rules *rules);
void					my_print(t_rules *rules, int id, char *text);

int						argv_initialization(t_rules *rules, char **argv);
int						philo_initialazation(t_rules *rules);
int						sem_initialization(t_rules *rules);

int						write_error(char *str);
int						error_manager(int error);

#endif