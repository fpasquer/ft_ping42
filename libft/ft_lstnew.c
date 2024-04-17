#include "libft.h"

t_list				*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)calloc(1, sizeof(t_list));
	if (new != NULL)
		new->content = content;
	return (new);
}