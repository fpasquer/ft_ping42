#include "libft.h"

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list			*new;
	t_list			*begin;
	t_list			*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	begin = NULL;
	tmp = lst;
	while (lst != NULL)
	{
		if ((new = ft_lstnew(f(lst->content))) == NULL)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, new);
		lst = lst->next;
	}
	ft_lstclear(&tmp, del);
	return (begin);
}