Entonces empieza por las señales. Es parte obligatoria del subject y además te va a facilitar mucho el trabajo del heredoc después.

Cómo funcionan las señales en minishell
Tu shell tiene tres contextos donde las señales se comportan diferente, y necesitas cambiar los handlers según en qué contexto estés:
Contexto 1 — Shell interactivo (esperando input del usuario)
SeñalComportamientoCtrl+C (SIGINT)Cancela la línea actual, muestra prompt nuevoCtrl+D (EOF)Sale del shell (esto no es una señal, lo maneja readline)Ctrl+\ (SIGQUIT)No hace nada
Contexto 2 — Ejecutando un comando hijo
SeñalComportamientoCtrl+C (SIGINT)El hijo muere, el padre muestra prompt nuevoCtrl+\ (SIGQUIT)El hijo muere con core dump, el padre muestra prompt
Contexto 3 — Leyendo un heredoc
SeñalComportamientoCtrl+C (SIGINT)Cancela la lectura, vuelve al promptCtrl+\ (SIGQUIT)No hace nada

La variable global
El subject te permite una sola variable global, y debe ser únicamente para el número de señal recibida. El handler de señal escribe en ella, y el resto de tu código la lee para saber qué pasó.
El prototipo sería algo así:
extern int g_signal;
Nada más. Sin structs, sin punteros a t_mini, solo el número de señal.

Flujo general de cómo funciona un handler
Usuario pulsa Ctrl+C
        │
        ▼
El SO llama a tu función handler(int signum)
        │
        ▼
Handler escribe en g_signal
        │
        ▼
Tu código principal lee g_signal y actúa en consecuencia
La clave es que el handler debe ser lo más simple posible. Nada de malloc, nada de printf complejo, solo escribir en la variable global y como mucho usar write.

Lista de tareas para las señales
Tarea 1 — Declarar la variable global

 1.1 Declarar g_signal en un único archivo .c.
 1.2 Declarar extern g_signal en tu header para que todos los archivos puedan leerla.


Tarea 2 — Crear los handlers
Necesitas como mínimo dos handlers distintos, con estos prototipos:

void	handle_sigint_interactive(int signum);
void	handle_sigint_child(int signum);

 2.1 Handler interactivo: escribe en g_signal, imprime nueva línea con write, y le dice a readline que limpie la línea actual (funciones rl_on_new_line y rl_replace_line y rl_redisplay).
 2.2 Handler durante hijo: solo escribe en g_signal e imprime nueva línea. El hijo ya murió por la señal, el padre se encarga del resto.


Tarea 3 — Crear funciones para instalar los handlers
En lugar de llamar a sigaction cada vez disperso por el código, centraliza esto en funciones dedicadas. Prototipos sugeridos:

void	set_signals_interactive(void);
void	set_signals_child(void);
void	set_signals_ignore(void);

 3.1 set_signals_interactive: instala handler interactivo para SIGINT, ignora SIGQUIT.
 3.2 set_signals_child: instala handler de hijo para SIGINT, restaura comportamiento por defecto de SIGQUIT.
 3.3 set_signals_ignore: ignora ambas señales (útil para el proceso padre durante un pipeline).


Tarea 4 — Conectar los handlers al flujo del shell

 4.1 Llamar a set_signals_interactive al inicio del bucle principal, antes de readline.
 4.2 Llamar a set_signals_child justo después del fork, dentro del proceso padre, antes de hacer waitpid.
 4.3 En el proceso hijo, restaurar las señales a su comportamiento por defecto con SIG_DFL para que el hijo muera normalmente al recibir señales.


Tarea 5 — Actualizar exit_status según la señal
Cuando un hijo muere por una señal, el exit status debe reflejarlo. Bash usa 128 + número_de_señal.

 5.1 Después de waitpid, comprobar con WIFSIGNALED si el hijo murió por señal.
 5.2 Si murió por señal, guardar 128 + WTERMSIG(status) en mini->exit_status.


Tarea 6 — Limpiar g_signal correctamente

 6.1 Después de leer g_signal y actuar sobre ella, resetearla a 0.
 6.2 Asegurarte de que al inicio de cada iteración del bucle principal g_signal está limpia.


Tarea 7 — Pruebas

 7.1 Ctrl+C en prompt vacío → nueva línea y prompt de nuevo.
 7.2 Ctrl+C durante sleep 10 → mata el sleep, vuelve al prompt.
 7.3 Ctrl+\ en prompt → no pasa nada.
 7.4 Ctrl+\ durante sleep 10 → mata el sleep con Quit (core dumped).
 7.5 Ctrl+D en prompt vacío → sale del shell.
 7.6 Comprobar que $? después de un Ctrl+C vale 130 (128 + 2).


Una vez tengas las tareas 1-6 funcionando, las señales del heredoc serán simplemente añadir un cuarto contexto con su propio handler, reutilizando toda esta infraestructura que ya habrás construido.
