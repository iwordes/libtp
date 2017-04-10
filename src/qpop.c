/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 10:20:38 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 19:42:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

t_job	*tp_qpop(t_tp *tp)
{
	t_job	*job;

	tp_lock(&JOB.lock);
	while (JOB.q == NULL)
		tp_evwait(&JOB.ev_new, &JOB.lock);
	job = JOB.q;
	JOB.q = JOB.q->next;
	tp_unlock(&JOB.lock);
	return (job);
}
