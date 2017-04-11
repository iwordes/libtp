/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:01:19 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/11 10:41:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTP_H
# define LIBTP_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define TP_ON_EXEC 0
# define TP_ON_START 1

# define T_TP_MU pthread_mutex_t
# define T_TP_EV pthread_cond_t

typedef T_TP_MU	t_tp_mut;
typedef T_TP_EV	t_tp_evt;

# define S_TP_JOB struct s_tp_job

typedef struct	s_tp_job
{
	void		(*fn)(void*);
	void		*ctx;
	S_TP_JOB	*next;
}				t_tp_job;

typedef struct	s_tp_jobq
{
	t_tp_job	*q;
	t_tp_mut	lock;
	unsigned	cnt;

	t_tp_evt	ev_new;
	t_tp_evt	ev_done;
}				t_tp_jobq;

typedef struct	s_tp
{
	pthread_t	*th;
	unsigned	nth;
	t_tp_jobq	job;
}				t_tp;

t_tp			*tp_create(unsigned nth);
void			tp_destroy(t_tp *tp);

bool			tp_qpush(t_tp *tp, void *job, void *context);
void			tp_qwait(t_tp *tp);

void			tp_evfire(t_tp_evt *ev);
void			tp_evwait(t_tp_evt *ev, t_tp_mut *lock);

bool			tp_lock(t_tp_mut *lock);
bool			tp_locked(t_tp_mut *lock);
void			tp_unlock(t_tp_mut *lock);

int				tp_ncpu(void);

/*
** (Mandatory)
*/

void			tp_exec_queue_add(t_tp *tp, void *job, void *context);
void			tp_wait_for_queue(t_tp *tp);
int				tp_get_nbr_proc(void);

#endif
