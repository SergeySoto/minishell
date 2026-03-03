# Guía Completa de Señales en Minishell

## ¿Qué es una señal?
Una señal es un mensaje que el sistema operativo envía a un proceso para notificarle de un evento.
Las dos señales que nos interesan en minishell son:
- **SIGINT** (señal 2): Se envía cuando el usuario pulsa `Ctrl+C`. Su comportamiento por defecto es **terminar** el proceso.
- **SIGQUIT** (señal 3): Se envía cuando el usuario pulsa `Ctrl+\`. Su comportamiento por defecto es **terminar** el proceso y generar un core dump.

## ¿Qué es `g_signal`?
Es una **variable global** declarada en `src/minishell.c` (línea 15) como `int g_signal;` y expuesta a todo el proyecto mediante `extern int g_signal;` en `includes/minishell.h` (línea 22).

Su propósito es almacenar el número de la última señal recibida. Se usa una variable global porque los **handlers de señales** (las funciones que se ejecutan cuando llega una señal) no pueden recibir parámetros personalizados ni acceder a estructuras locales. La variable global es el único mecanismo seguro para comunicar información desde un handler hacia el resto del programa.

---

## Archivo: `src/signal/signal.c`

### Función 1: `handler_sigint_interactive`

```c
void	handler_sigint_interactive(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
```

**¿Qué hace?** Es el manejador personalizado que se ejecuta cuando el usuario pulsa `Ctrl+C` mientras está en el **prompt interactivo** (esperando que escriba un comando).

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1 | `g_signal = signum;` | Guarda el número de la señal recibida (2, que es SIGINT) en la variable global. Esto permite que el resto del programa sepa que se recibió una señal. |
| 2 | `write(1, "\n", 1);` | Imprime un salto de línea en la terminal. Esto mueve el cursor a la línea siguiente, ya que el usuario estaba escribiendo algo cuando pulsó `Ctrl+C`. Se usa `write` en lugar de `printf` porque `write` es **async-signal-safe** (segura dentro de un handler), mientras que `printf` no lo es. |
| 3 | `rl_on_new_line();` | Función de la librería `readline`. Le dice a readline que el cursor se ha movido a una nueva línea. Sin esto, readline se confundiría sobre la posición del cursor. |
| 4 | `rl_replace_line("", 0);` | Función de `readline`. Borra lo que el usuario había escrito en la línea actual y lo sustituye por una cadena vacía `""`. Así, si el usuario había escrito `echo hol` y pulsa `Ctrl+C`, ese texto desaparece. |
| 5 | `rl_redisplay();` | Función de `readline`. Redibuja el prompt limpio (ej: `Minishell$> `) en la nueva línea. Sin esto, el prompt no aparecería. |

**Comportamiento visual en la terminal:**
```
Minishell$> echo hol   <-- El usuario estaba escribiendo aquí
                        <-- Pulsa Ctrl+C
Minishell$>             <-- Nueva línea limpia con el prompt
```

---

### Función 2: `handler_signals_child`

```c
void	handler_signals_child(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
}
```

**¿Qué hace?** Es el manejador que se ejecuta cuando el **proceso padre** recibe SIGINT mientras **espera** a que un hijo termine (ej: mientras `cat` o `sleep 100` están corriendo).

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1 | `g_signal = signum;` | Guarda la señal recibida. |
| 2 | `write(1, "\n", 1);` | Imprime un salto de línea. |

**¿Por qué NO hay `rl_redisplay`?** Porque en este momento no estamos en el prompt de `readline`. Estamos esperando a que un programa hijo termine. No necesitamos redibujar nada. Solo registramos la señal y dejamos que `waitpid` se encargue del resto.

---

### Función 3: `set_signals_interactive`

```c
void	set_signals_interactive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler_sigint_interactive;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
```

**¿Qué hace?** Configura las señales para el **modo interactivo** (cuando el usuario está en el prompt escribiendo). Este es el modo "normal" de tu shell.

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1 | `struct sigaction sa;` | Declara una estructura `sigaction`. Esta es la forma moderna (y recomendada por POSIX) de configurar señales, más segura que la antigua función `signal()`. |
| 2 | `ft_memset(&sa, 0, sizeof(sa));` | Limpia la estructura a ceros. Esto es vital para evitar que campos no inicializados contengan basura y causen comportamientos impredecibles. |
| 3 | `sa.sa_handler = &handler_sigint_interactive;` | Asigna tu función personalizada como el manejador de la señal. Cuando llegue SIGINT, el SO ejecutará `handler_sigint_interactive`. |
| 4 | `sa.sa_flags = 0;` | Sin flags especiales. Esto asegura el comportamiento estándar POSIX. |
| 5 | `sigemptyset(&sa.sa_mask);` | Inicializa la máscara de señales vacía. Esto significa que no se bloquea ninguna otra señal mientras se ejecuta el handler. |
| 6 | `sigaction(SIGINT, &sa, NULL);` | Registra la configuración para SIGINT (`Ctrl+C`). A partir de ahora, `Ctrl+C` ejecutará tu handler personalizado en vez de matar el proceso. |
| 7 | `sa.sa_handler = SIG_IGN;` | Cambia el handler a `SIG_IGN` (Ignorar). |
| 8 | `sigaction(SIGQUIT, &sa, NULL);` | Registra SIGQUIT (`Ctrl+\`) para que sea **ignorada**. En bash real, `Ctrl+\` no hace nada cuando estás en el prompt. Tu shell replica ese comportamiento. |

**Resumen del modo interactivo:**
- `Ctrl+C` → Limpia la línea y muestra un prompt nuevo.
- `Ctrl+\` → No hace nada (ignorada).

---

### Función 4: `set_signals_child`

```c
void	set_signals_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler_signals_child;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}
```

**¿Qué hace?** Configura las señales del **proceso padre** mientras **espera a un hijo único** (un solo comando sin pipes). El padre necesita un comportamiento diferente al interactivo porque no está en `readline`.

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1-5 | Inicialización | Misma limpieza y configuración que en `set_signals_interactive`. |
| 6 | `sa.sa_handler = &handler_signals_child;` | Para SIGINT: usa el handler simplificado (solo guarda señal y salta línea, sin redibujar readline). |
| 7 | `sigaction(SIGINT, &sa, NULL);` | Registra SIGINT con ese handler. |
| 8 | `sa.sa_handler = SIG_DFL;` | Para SIGQUIT: restaura el comportamiento **por defecto** del sistema (que es terminar el proceso + core dump). |
| 9-10 | Reinicialización | Limpia flags y máscara para la nueva configuración de SIGQUIT. |
| 11 | `sigaction(SIGQUIT, &sa, NULL);` | Registra SIGQUIT con comportamiento por defecto. |

**Resumen del modo child (padre esperando a un hijo):**
- `Ctrl+C` → El padre imprime `\n`. El hijo recibe SIGINT y muere.
- `Ctrl+\` → Comportamiento por defecto (el hijo muere con "Quit: core dump").

---

### Función 5: `set_signals_ignore`

```c
void	set_signals_ignore(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
```

**¿Qué hace?** Hace que el proceso padre **ignore completamente** ambas señales. Ni SIGINT ni SIGQUIT harán nada.

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1-2 | Inicialización | Limpia la estructura. |
| 3 | `sa.sa_handler = SIG_IGN;` | Handler = Ignorar. |
| 4 | `sigaction(SIGINT, &sa, NULL);` | SIGINT ignorada. |
| 5 | `sa.sa_handler = SIG_IGN;` | Handler = Ignorar. |
| 6 | `sigaction(SIGQUIT, &sa, NULL);` | SIGQUIT ignorada. |

**¿Cuándo necesitas que el padre ignore TODO?** Cuando está esperando a **múltiples hijos** (pipeline). Si el padre reaccionara a `Ctrl+C`, podría interrumpir el `waitpid` y dejar hijos huérfanos (procesos zombie).

---

### Función 6: `set_signals_default`

```c
void	set_signals_default(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}
```

**¿Qué hace?** Restaura el comportamiento **original del sistema operativo** para ambas señales.

**Línea por línea:**
| Línea | Código | Explicación |
|---|---|---|
| 1-2 | Inicialización | Limpia la estructura. |
| 3 | `sa.sa_handler = SIG_DFL;` | Handler = Defecto del SO. |
| 4 | `sigaction(SIGINT, &sa, NULL);` | SIGINT = matar proceso. |
| 5 | `sa.sa_handler = SIG_DFL;` | Handler = Defecto del SO. |
| 6 | `sigaction(SIGQUIT, &sa, NULL);` | SIGQUIT = matar proceso + core dump. |

**¿Cuándo se usa?** En los **procesos hijo** (después de `fork`). El hijo hereda los handlers del padre, pero los hijos necesitan morir normalmente cuando reciben una señal. Si el hijo heredase `SIG_IGN`, `Ctrl+C` no podría matar a `cat` o `sleep`.

---

## ¿Dónde se llaman y por qué?

### 1. `set_signals_interactive()` en `src/minishell.c` (línea 24)

```c
while (1)
{
    tokens = NULL;
    set_signals_interactive();   // <--- AQUÍ
    mini->input = readline("Minishell$> ");
```

**¿Por qué aquí?** Se llama al **inicio de cada vuelta** del bucle principal, justo antes de `readline`. Esto asegura que cada vez que el usuario vuelve al prompt (después de ejecutar un comando), las señales se reconfiguren al modo interactivo. Es necesario porque durante la ejecución del comando anterior, las señales se cambiaron a otro modo (child, ignore, o default).

---

### 2. `set_signals_default()` en `src/executor/handle_single.c` (línea 20)

```c
void	single_cmd_child_process(t_mini *mini, t_cmd *cmd)
{
    if (cmd->pid == 0)
    {
        set_signals_default();   // <--- AQUÍ (dentro del hijo)
```

**¿Por qué aquí?** Estamos dentro del **proceso hijo** (después de `fork`). El hijo heredó los handlers personalizados del padre (que redibujan readline, etc.). Eso no tiene sentido para un proceso hijo como `ls` o `cat`. Al restaurar `SIG_DFL`, el hijo se comportará como cualquier programa normal: `Ctrl+C` lo matará limpiamente.

---

### 3. `set_signals_child()` en `src/executor/handle_single.c` (línea 34)

```c
void	single_cmd_parent_wait(t_mini *mini, t_cmd *cmd)
{
    set_signals_child();   // <--- AQUÍ (padre esperando)
    waitpid(cmd->pid, &mini->exit_status, 0);
```

**¿Por qué aquí?** El **padre** está a punto de esperar (`waitpid`) a que el hijo termine. Durante esa espera, si el usuario pulsa `Ctrl+C`, el padre no debe redibujar el prompt de readline (porque no estamos en readline). Solo debe registrar la señal y saltar línea. Por eso se instala `handler_signals_child` en vez de `handler_sigint_interactive`.

---

### 4. `set_signals_default()` en `src/executor/handle_pipeline.c` (línea 40)

```c
void	pipe_child_process(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd)
{
    set_signals_default();   // <--- AQUÍ (hijo en pipeline)
```

**¿Por qué aquí?** Mismo razonamiento que el punto 2. Cada hijo dentro del pipeline necesita restaurar el comportamiento por defecto para que las señales lo maten correctamente.

---

### 5. `set_signals_ignore()` en `src/executor/handle_pipeline.c` (línea 70)

```c
void	wait_all_children(t_mini *mini)
{
    set_signals_ignore();   // <--- AQUÍ (padre esperando múltiples hijos)
    current_cmd = mini->cmds;
    while (current_cmd)
    {
        waitpid(current_cmd->pid, &mini->exit_status, 0);
```

**¿Por qué aquí?** El padre necesita esperar a **TODOS** los hijos del pipeline con `waitpid`. Si el padre reaccionara a `Ctrl+C` (como hace en `set_signals_child`), podría interrumpir el bucle de `waitpid` y dejar hijos sin recoger (zombies). Al ignorar todas las señales, el padre se asegura de limpiar todos los procesos hijos sin importar cuántas veces el usuario pulse `Ctrl+C`.

---

### 6. `set_signals_interactive()` en `src/executor/handle_pipeline.c` (línea 86)

```c
    // ... después de recoger todos los hijos ...
    set_signals_interactive();   // <--- AQUÍ (volver al prompt)
}
```

**¿Por qué aquí?** Una vez que todos los hijos han terminado y hemos recogido sus exit status, el programa va a volver al bucle principal (`shell_loop`). Restauramos el modo interactivo para que `Ctrl+C` vuelva a redibujar el prompt cuando `readline` esté activo.

---

### 7. `g_signal = 128 + WTERMSIG(...)` en `src/executor/handle_pipeline.c` (línea 81)

```c
else if (WIFSIGNALED(mini->exit_status))
{
    g_signal = 128 + WTERMSIG(mini->exit_status);
    if (WTERMSIG(mini->exit_status) == SIGINT)
        write(1, "\n", 1);
    mini->exit_status = g_signal;
}
```

**¿Por qué aquí?** Cuando un hijo muere por una señal (no por `exit()` normal), bash establece el exit status como `128 + número_de_señal`. Por ejemplo:
- Si `Ctrl+C` mata al hijo → exit status = `128 + 2 = 130`.
- Si `Ctrl+\` mata al hijo → exit status = `128 + 3 = 131`.

Esto permite que `$?` muestre el código correcto después de interrumpir un comando.

---

## Resumen Visual: Ciclo de Vida de las Señales

```
┌─────────────────────────────────────────────────┐
│              BUCLE PRINCIPAL                     │
│                                                  │
│  set_signals_interactive()                       │
│  readline("Minishell$> ")                        │
│    Ctrl+C → limpia línea, nuevo prompt           │
│    Ctrl+\ → ignorada                            │
│                                                  │
│  ┌─ COMANDO SIMPLE ──────────────────────────┐  │
│  │  fork()                                    │  │
│  │  HIJO: set_signals_default()               │  │
│  │    Ctrl+C → muere                          │  │
│  │    Ctrl+\ → muere + core dump              │  │
│  │  PADRE: set_signals_child()                │  │
│  │    Ctrl+C → guarda señal + \n              │  │
│  │    Ctrl+\ → comportamiento por defecto     │  │
│  │  waitpid(hijo)                             │  │
│  └────────────────────────────────────────────┘  │
│                                                  │
│  ┌─ PIPELINE ────────────────────────────────┐  │
│  │  fork() x N                                │  │
│  │  HIJOS: set_signals_default()              │  │
│  │    Ctrl+C → mueren                         │  │
│  │  PADRE: set_signals_ignore()               │  │
│  │    Ctrl+C → ignorada (espera a todos)      │  │
│  │  waitpid(todos)                            │  │
│  │  set_signals_interactive() (volver al prompt)│ │
│  └────────────────────────────────────────────┘  │
│                                                  │
│  Volver al inicio del bucle                      │
└─────────────────────────────────────────────────┘
```
