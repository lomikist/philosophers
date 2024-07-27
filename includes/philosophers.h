/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:30 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 17:01:06 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define USAGE "Usage: \n\
	./philosophers [NUM_PHILOS] [THINK_TIME] [EAT_TIME] [SLEEP_TIME] \
	[[NUM_MEALS]]\n\n\
	NUM_PHILOS   -  number of philosophers \n\
	THINK_TIME   -  maximum time philosopher can stay hungry/thinking (ms) \n\
	EAT_TIME     -  time philosopher spends eating (ms) \n\
	SLEEP_TIME   -  time philosopher spends sleeping (ms) \n\
	[NUM_MEALS]  -  optional, number of meals each philosophers eat to stop \
	simulation\n"
#define MALLOC_ERROR "Memory Error\n"

typedef enum s_status {
	eating = 0,
	sleeping,
	thinking
} t_status;

struct s_philo;

typedef struct	s_data
{
	unsigned int	n_philos;
	unsigned int	think_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	n_dinners;
	struct s_philo	*philos;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
} t_data;

typedef struct	s_philo
{
	unsigned int	id;
	unsigned int	eat_count;
	t_status		status;
	t_data			*data;
	pthread_t		t1;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

void	message(char *msg);
int		init_args(int argc, char **argv, t_data *data);
t_philo	*init_philos(t_data *data);

#endif
