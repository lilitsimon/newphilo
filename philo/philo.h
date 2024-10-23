/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:56 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:09:58 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				num_philos;
	long long		last_meal;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				eating;
	int				must_eat_count;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	int				*dead;
}					t_philo;
typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

int					check_args(int argc, char **argv);
void				cleanup(t_data *data, pthread_mutex_t *forks);
void				full_cleanup(char *str, t_data *data,
						pthread_mutex_t *forks);
long				ft_atol(char *str);
int					is_number(char *str);
int					ft_strlen(char *str);
void				data_init(t_data *data, t_philo *philos);
void				fork_init(pthread_mutex_t *forks, int philo_num);
void				philo_init(t_philo *philos, t_data *data,
						pthread_mutex_t *forks, char **argv);
long long			get_time(void);
int					ft_usleep(long long microseconds);
void				input_init(t_philo *philo, char **argv);
int					thread_create(t_data *data, pthread_mutex_t *forks);
void				*monitor_routine(void *pointer);
void				*philo_routine(void *pointer);
int					philo_dead(t_philo *philo, long long time_to_die);
void				print_status(char *str, t_philo *philo, int id);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
int					philo_die_loop(t_philo *philo);
int					check_all_ate_enough(t_philo *philos);
int					philo_death_check(t_philo *philos);

#endif
