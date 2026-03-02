Perfecto, tienes ya la estructura base. Te doy las tareas claras para cada función:

Funciones Permitidas (Subject 42)
Categoría	Funciones
Señales	signal, sigaction, kill
Readline	rl_on_new_line, rl_replace_line, rl_redisplay
Wait	wait, waitpid, WIFSIGNALED, WTERMSIG
I/O	write (la única segura dentro de handlers)
### TAREA 1: Variable global ✅ (ya hecha)
Tienes int g_signal; declarado y extern int g_signal; en el header.

Corrección necesaria: Elimina la línea 6 g_signal = 0; — no puedes asignar fuera de una función.

### TAREA 2: handler_sigint_interactive
Qué debe hacer:

Guardar el número de señal en g_signal
Imprimir una nueva línea con write(1, "\n", 1)
Decirle a readline que estás en nueva línea: rl_on_new_line()
Limpiar el buffer de readline: rl_replace_line("", 0)
Redibujar el prompt: rl_redisplay()
Funciones a usar:

write(1, "\n", 1) — imprime salto de línea
rl_on_new_line() — notifica nueva línea
rl_replace_line("", 0) — limpia el input actual
rl_redisplay() — redibuja el prompt

### TAREA 3: Crear handler_sigint_child
Qué debe hacer:

Guardar el número de señal en g_signal
Imprimir nueva línea: write(1, "\n", 1)
NO usar readline aquí — el hijo está ejecutando un comando.

### TAREA 4: Crear set_signals_interactive
Qué debe hacer:

Declarar una variable struct sigaction sa
Configurar sa.sa_handler con tu handler interactivo
Inicializar sa.sa_flags = 0
Vaciar la máscara: sigemptyset(&sa.sa_mask)
Instalar para SIGINT: sigaction(SIGINT, &sa, NULL)
Ignorar SIGQUIT: sa.sa_handler = SIG_IGN y luego sigaction(SIGQUIT, &sa, NULL)
Funciones a usar:

sigaction(señal, &config, NULL)
sigemptyset(&sa.sa_mask)
SIG_IGN — constante para ignorar

### TAREA 5: Crear set_signals_child
Qué debe hacer:

Configurar sa.sa_handler con tu handler de hijo para SIGINT
Instalar con sigaction(SIGINT, &sa, NULL)
Restaurar SIGQUIT a comportamiento default: sa.sa_handler = SIG_DFL
Instalar con sigaction(SIGQUIT, &sa, NULL)
Funciones a usar:

sigaction
SIG_DFL — comportamiento por defecto

### TAREA 6: Crear set_signals_ignore
Qué debe hacer:

Poner sa.sa_handler = SIG_IGN para ambas señales
Instalar para SIGINT y SIGQUIT
### TAREA 7: Crear set_signals_default (para los hijos después del fork)
Qué debe hacer:

Restaurar SIGINT y SIGQUIT a SIG_DFL