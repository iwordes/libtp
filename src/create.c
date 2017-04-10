/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:09:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 19:17:46 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

t_tp	*mpanic_(t_tp *tp)
{
	if (tp && tp.th)
		free(tp.th);
	if (tp)
		free(tp);
	return (NULL);
}

t_tp	*qpanic_(t_tp *tp, int flag)
{
	if (flag & 1)
		pthread_mutex_destroy(&JOB.lock);
	if (flag & 2)
		pthread_cond_destroy(&JOB.ev_new);
	if (flag & 4)
		pthread_cond_destroy(&JOB.ev_done);
	return (mpanic_(tp));
}

t_tp	*tpanic_(t_tp *tp, unsigned n)
{
	t_job		ex;
	unsigned	i;

	i = 0;
	ex.ctx = NULL;
	ex.fn = tp__kill_thread;
	while (i < n)
	{
		tp_lock(&JOB.lock);
		JOB.q = &ex;
		tp_evfire(&JOB.ev_new);
		tp_unlock(&JOB.lock);
	}
	return (qpanic_(tp, 7));
}

#define MFAIL(M) if ((M) == NULL) return (mpanic_(tp))
#define QFAIL(Q, F) if (Q) return (qpanic_(tp, F))

t_tp	*tp_create(unsigned nth)
{
	unsigned	i;

	MFAIL(tp = ZALT(t_tp, 1));
	MFAIL(tp.th = ZALT(pthread_t, nth));
	QFAIL(pthread_mutex_init(&JOB.lock), 0);
	QFAIL(pthread_cond_init(&JOB.ev_new), 1);
	QFAIL(pthread_cond_init(&JOB.ev_done), 3);
	i = 0;
	tp.nth = nth;
	while (i < nth)
	{
		if (pthread_create(th->id + i, NULL, tp__work_loop, tp))
			return (tpanic_(tp, i));
		i += 1;
	}
	return (tp);
}
