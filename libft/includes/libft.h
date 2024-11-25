/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:29:02 by saberton          #+#    #+#             */
/*   Updated: 2024/11/25 18:21:14 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define U_MAX 4294967295
# define DEC_BASE "0123456789"
# define HEX_BASE_MIN "0123456789abcdef"
# define HEX_BASE_MAJ "0123456789ABCDEF"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// ---------------- char -----------------
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

// ---------------- convert -----------------
int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);

// ---------------- gnl -----------------
int					ft_strlen_modif(char *str);
char				*ft_strjoin_modif(char *s1, char *s2);
char				*ft_substr_modif(char const *s, unsigned int start,
						size_t len);
char				*get_next_line(int fd);

// ---------------- list -----------------
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// ---------------- memory -----------------
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

// ---------------- printf -----------------
int					ft_len_nb(size_t nb, size_t len);
int					ft_putnbr(int nbr);
int					ft_putnbr_base(char *base, int nbr, int len);
int					ft_print_ptr(char *base, void *ptr, size_t len);
void				ft_putptr(char *base, size_t p, size_t len);
int					ft_putchar(char c);
int					ft_putstr(char *str);
int					ft_check_var(char format, va_list args);
int					ft_check_percent(const char *format);
int					ft_printf(const char *format, ...);

// ---------------- put_fd -----------------
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// ---------------- string -----------------
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t siz);
size_t				ft_strlcat(char *dst, const char *src, size_t siz);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strcmp(const char *s1, const char *s2);

#endif
