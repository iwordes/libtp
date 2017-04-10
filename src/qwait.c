/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 19:48:19 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpt.h>

void	tp_qwait(t_tp *tp)
{
	tp_lock(JOB.lock);
	while (JOB.cnt != 0)
		tp_evwait(JOB.ev_done, JOB.lock);
	tp_unlock(JOB.lock);
}
