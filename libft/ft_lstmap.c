/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:36:51 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/28 10:52:10 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clear(t_list **lst, void (*del)(void *), void *cnt)
{
	ft_lstclear(lst, del);
	if (cnt)
		(*del)(cnt);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*buf;
	void	*cnt;

	if (!f || !del)
		return (0);
	res = 0;
	while (lst)
	{
		cnt = (*f)(lst->content);
		if (!cnt)
			return (clear(&res, del, 0));
		buf = ft_lstnew(cnt);
		if (!buf)
			return (clear(&res, del, cnt));
		ft_lstadd_back(&res, buf);
		lst = lst->next;
	}
	return (res);
}
