#ifndef SIGNAL_H
# define SIGNAL_H

void	handler_sigint_interactive(int signum);
void	handler_signals_child(int signum);
void	set_signals_interactive(void);
void	set_signals_child(void);
void	set_signals_ignore(void);
void	set_signals_default(void);


#endif