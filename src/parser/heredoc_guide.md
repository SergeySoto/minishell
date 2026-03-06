# Guía Completa del Heredoc en Minishell

## ¿Qué es un heredoc?

Un heredoc (`<<`) es una redirección de entrada especial. En vez de leer de un archivo, lee líneas directamente del usuario hasta que escribe una palabra delimitadora.

```bash
cat << EOF
hola
mundo
EOF
```
Esto envía `"hola\nmundo\n"` como stdin de `cat`, como si fuera un archivo.

---

## ¿Cuándo se ejecuta el heredoc en bash?

**MUY IMPORTANTE:** En bash real, los heredocs se resuelven **ANTES de ejecutar ningún comando**. Es decir, durante el **parseo**, no durante la ejecución.

```bash
cat << EOF | grep hola
hola
mundo
EOF
```
Bash primero lee todas las líneas del heredoc, las guarda, y luego ejecuta el pipeline.

---

## Estado actual de tu código

### Lo que ya tienes:

1. **Tokenizer** → Ya reconoce `<<` como tipo `HEREDOC` (valor 4 en `e_type`)
2. **`set_redirects()`** en [parser_utils.c](parser_utils.c) → Ya tiene la rama `HEREDOC`, pero está vacía:
   ```c
   else if ((*token)->type == HEREDOC)
   {
       //cmd->fd_in = ; //Aqui va la logica del heredoc
   }
   ```
3. **`t_cmd`** → Ya tiene `fd_in` donde guardar el file descriptor del heredoc
4. **`setup_redirections()`** en [../executor/handle_redirections.c](../executor/handle_redirections.c) → Ya sabe hacer `dup2(cmd->fd_in, STDIN_FILENO)` cuando `cmd->infile` existe, pero para heredoc usaremos `fd_in` directamente

### Lo que necesitas implementar:

Una función que lea líneas del usuario, las escriba en un archivo temporal (o pipe), y devuelva un file descriptor para usarlo como stdin.

---

## Flujograma General

```
┌─────────────────────────────────────────────────────────────────┐
│                    ENTRADA DEL USUARIO                          │
│              cat << EOF | grep hola                             │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│                   TOKENIZER (ya existe)                          │
│  Genera tokens: [cat] [<<] [EOF] [|] [grep] [hola]             │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│               init_cmd() → handler_redirects()                   │
│               → set_redirects() (ya existe)                      │
│                                                                  │
│  Detecta token tipo HEREDOC                                      │
│  El SIGUIENTE token ("EOF") es el delimitador                    │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│              handle_heredoc(delimiter, mini)                     │
│                   *** NUEVA FUNCIÓN ***                           │
│                                                                  │
│  1. Comprobar si el delimitador tenía comillas                   │
│     - "EOF" o 'EOF' → NO expandir variables                     │
│     - EOF (sin comillas) → SÍ expandir variables                │
│                                                                  │
│  2. Crear archivo temporal con open()                            │
│     - Ruta: "/tmp/minishell_heredoc"                             │
│     - Flags: O_CREAT | O_WRONLY | O_TRUNC                       │
│     - Permisos: 0600                                             │
│                                                                  │
│  3. Configurar señales para heredoc                              │
│     - SIGINT (Ctrl+C) → cancelar heredoc, limpiar               │
│     - SIGQUIT (Ctrl+\) → ignorar                                │
│                                                                  │
│  4. Bucle de lectura (ver detalle abajo)                         │
│                                                                  │
│  5. Cerrar archivo temporal                                      │
│                                                                  │
│  6. Reabrir en modo lectura (O_RDONLY)                           │
│                                                                  │
│  7. Borrar el archivo con unlink()                               │
│     (el fd sigue válido aunque el archivo desaparezca)           │
│                                                                  │
│  8. Restaurar señales                                            │
│                                                                  │
│  9. Retornar el fd                                               │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│                   BUCLE DE LECTURA                               │
│                                                                  │
│  MIENTRAS (verdadero):                                           │
│  │                                                               │
│  │  línea = readline("> ")                                       │
│  │                                                               │
│  │  ┌─ ¿línea es NULL? ────────────────────────┐                │
│  │  │  (Ctrl+D o error)                         │                │
│  │  │  SÍ → imprimir warning, romper bucle      │                │
│  │  └──────────────────────────────────────────┘                │
│  │                                                               │
│  │  ┌─ ¿g_signal != 0? ───────────────────────┐                │
│  │  │  (Ctrl+C fue pulsado)                     │                │
│  │  │  SÍ → liberar línea, cerrar fd,           │                │
│  │  │       retornar -1 (heredoc cancelado)      │                │
│  │  └──────────────────────────────────────────┘                │
│  │                                                               │
│  │  ┌─ ¿línea == delimitador? ─────────────────┐                │
│  │  │  SÍ → liberar línea, romper bucle         │                │
│  │  │  (heredoc completado con éxito)            │                │
│  │  └──────────────────────────────────────────┘                │
│  │                                                               │
│  │  (Opcional) Expandir variables $VAR en la línea               │
│  │  si el delimitador NO tenía comillas                          │
│  │                                                               │
│  │  Escribir línea en el archivo temporal:                       │
│  │    write(fd, línea, strlen(línea))                            │
│  │    write(fd, "\n", 1)                                         │
│  │                                                               │
│  │  Liberar línea                                                │
│  │                                                               │
│  └─ Volver al inicio del bucle                                   │
└──────────────────────────────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│            VUELTA A set_redirects()                              │
│                                                                  │
│  cmd->fd_in = fd retornado por handle_heredoc()                  │
│                                                                  │
│  Si fd == -1 → heredoc fue cancelado (Ctrl+C)                   │
│  Si fd >= 0  → fd válido, listo para usar como stdin            │
└──────────────────────────────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────────┐
│               EJECUCIÓN (ya existe)                              │
│                                                                  │
│  setup_redirections() detecta fd_in != 0                         │
│  → dup2(cmd->fd_in, STDIN_FILENO)                               │
│  → close(cmd->fd_in)                                             │
│  El comando lee de ese fd como si fuera un archivo               │
└──────────────────────────────────────────────────────────────────┘
```

---

## Funciones Necesarias (solo prototipos y explicación)

### 1. `int handle_heredoc(char *delimiter, t_mini *mini)`

**Propósito:** Función principal del heredoc. Orquesta todo el proceso: crear archivo temporal, leer líneas del usuario, guardarlas, y devolver un fd listo para usar como stdin.

**Parámetros:**
- `delimiter` → La palabra que marca el fin del heredoc (ej: "EOF")
- `mini` → Estructura principal, necesaria para expandir variables y para `g_signal`

**Retorna:**
- `fd >= 0` → File descriptor válido con el contenido del heredoc
- `-1` → El heredoc fue cancelado (Ctrl+C) o hubo un error

**¿Por qué necesita `mini`?** Para acceder a las variables de entorno si hay que expandir `$VAR` dentro del heredoc, y para poder marcar `exit_status = 130` si se cancela con Ctrl+C.

---

### 2. `void set_signals_heredoc(void)`

**Propósito:** Configura las señales del proceso padre mientras está leyendo el heredoc con `readline("> ")`.

**Comportamiento deseado:**

| Señal | Acción |
|-------|--------|
| SIGINT (Ctrl+C) | Guardar en `g_signal`, cerrar readline con `rl_done = 1` o `close(STDIN_FILENO)` |
| SIGQUIT (Ctrl+\\) | Ignorar (`SIG_IGN`) — bash la ignora durante heredoc |

**¿Por qué es necesaria?** Porque el comportamiento del heredoc ante señales es diferente al interactivo:
- En modo interactivo, Ctrl+C limpia la línea y muestra un nuevo prompt
- En heredoc, Ctrl+C debe **cancelar todo el heredoc**, devolver al prompt principal, y poner `$? = 130`

---

### 3. `void handler_sigint_heredoc(int signum)`

**Propósito:** Handler que se ejecuta cuando el usuario pulsa Ctrl+C durante la lectura del heredoc.

**Qué debe hacer:**
1. Guardar `signum` en `g_signal`
2. Escribir `"\n"` con `write(1, "\n", 1)`
3. Forzar a `readline` a terminar — hay varias formas:
   - Usar `rl_done = 1` (variable global de readline que le dice que pare)
   - O usar `close(STDIN_FILENO)` para que readline reciba EOF (más agresivo, necesitas restaurar stdin después)
   - O `ioctl(STDIN_FILENO, TIOCSTI, "\n")` para simular Enter (no portable)

**¿Por qué no reutilizar `handler_sigint_interactive`?** Porque ese handler llama a `rl_replace_line` y `rl_redisplay`, que redibujan el prompt de minishell. En heredoc queremos cancelar la lectura, no redibujar.

---

### 4. `char *expand_heredoc_line(char *line, t_mini *mini)`

**Propósito:** Expande las variables `$VAR` y `$?` dentro de una línea del heredoc.

**Parámetros:**
- `line` → La línea leída del usuario
- `mini` → Para acceder a las variables de entorno

**Retorna:** Una nueva cadena con las variables expandidas.

**¿Cuándo se usa?** Solo cuando el delimitador NO tenía comillas:
- `<< EOF` → SÍ expandir (`$HOME` se convierte en `/home/user`)
- `<< "EOF"` → NO expandir (`$HOME` se queda como `$HOME`)
- `<< 'EOF'` → NO expandir

**¿Por qué es necesaria?** Podrías reutilizar tu lógica de expansión del expander, pero necesitas una versión que trabaje con un `char *` suelto en lugar de un `t_token *`. Puedes crear una función auxiliar o adaptar `perform_expansion`.

---

### 5. `int check_delimiter_quoted(char *delimiter)`

**Propósito:** Comprueba si el delimitador tenía comillas en el input original.

**Retorna:**
- `1` → El delimitador tenía comillas (no expandir variables)
- `0` → El delimitador NO tenía comillas (sí expandir variables)

**¿Por qué es necesaria?** Porque para cuando llegas a `set_redirects()`, el tokenizer ya ha eliminado las comillas del token. Necesitas saber si las tenía **antes** de quitarlas. Hay dos opciones:
- Guardar esa información en el token (campo `expand` o uno nuevo)
- O comprobar en el input original del usuario

---

## Pseudocódigo Detallado

### Función principal: `handle_heredoc`

```
FUNCIÓN handle_heredoc(delimiter, mini) → fd
    
    // Paso 1: Determinar si hay que expandir variables
    expandir = comprobar si delimiter NO tenía comillas
    
    // Paso 2: Quitar comillas del delimiter si las tiene
    delimiter_limpio = quitar_comillas(delimiter)
    
    // Paso 3: Crear archivo temporal
    fd_escritura = open("/tmp/minishell_heredoc", ESCRITURA | CREAR | TRUNCAR, 0600)
    SI fd_escritura == -1
        imprimir error
        retornar -1
    
    // Paso 4: Configurar señales para heredoc
    g_signal = 0
    configurar_señales_heredoc()
    
    // Paso 5: Bucle de lectura
    MIENTRAS verdadero:
        línea = readline("> ")
        
        // Ctrl+D (EOF) sin cerrar heredoc
        SI línea == NULL
            imprimir "warning: here-document delimited by end-of-file"
            ROMPER bucle
        
        // Ctrl+C fue pulsado
        SI g_signal != 0
            liberar(línea)
            cerrar(fd_escritura)
            borrar_archivo("/tmp/minishell_heredoc")
            mini->exit_status = 130
            restaurar_señales_interactivas()
            retornar -1
        
        // Se encontró el delimitador
        SI strcmp(línea, delimiter_limpio) == 0
            liberar(línea)
            ROMPER bucle
        
        // Expandir variables si corresponde
        SI expandir == verdadero
            línea_expandida = expandir_variables(línea, mini)
            liberar(línea)
            línea = línea_expandida
        
        // Escribir línea en archivo temporal
        write(fd_escritura, línea, strlen(línea))
        write(fd_escritura, "\n", 1)
        
        liberar(línea)
    
    FIN MIENTRAS
    
    // Paso 6: Cerrar escritura, abrir lectura
    cerrar(fd_escritura)
    fd_lectura = open("/tmp/minishell_heredoc", SOLO_LECTURA)
    
    // Paso 7: Borrar archivo (fd sigue válido)
    unlink("/tmp/minishell_heredoc")
    
    // Paso 8: Restaurar señales
    restaurar_señales_interactivas()
    
    retornar fd_lectura
FIN FUNCIÓN
```

### Integración: Cambio en `set_redirects`

```
FUNCIÓN set_redirects(token, cmd)
    ...
    SI token->tipo == HEREDOC
        delimiter = token->siguiente->contenido
        fd = handle_heredoc(delimiter, mini)  // ← NECESITAS pasar mini
        SI fd == -1
            // Heredoc cancelado, marcar error
            cmd->fd_in = -1
        SINO
            cmd->fd_in = fd
    ...
FIN FUNCIÓN
```

### Integración: Cambio en `setup_redirections`

```
FUNCIÓN setup_redirections(cmd)
    // Heredoc: fd_in ya tiene un fd válido (no un archivo para abrir)
    SI cmd->fd_in > 0     // ← Antes era: SI cmd->infile
        dup2(cmd->fd_in, STDIN_FILENO)
        cerrar(cmd->fd_in)
    
    // Infile normal: abrir el archivo
    SI cmd->infile
        fd = open(cmd->infile, SOLO_LECTURA)
        dup2(fd, STDIN_FILENO)
        cerrar(fd)
    ...
FIN FUNCIÓN
```

---

## Flujo de Señales durante Heredoc

```
┌──────────────────────────────────────────────────────────┐
│                  HEREDOC ACTIVO                           │
│              readline("> ") esperando input               │
│                                                          │
│  Ctrl+C ──────────────────────────────────────────────── │
│  │                                                       │
│  ▼                                                       │
│  handler_sigint_heredoc()                                │
│  │  1. g_signal = 2                                      │
│  │  2. write(1, "\n", 1)                                 │
│  │  3. rl_done = 1  (forzar que readline termine)        │
│  │                                                       │
│  ▼                                                       │
│  readline retorna la línea actual (o "")                  │
│  │                                                       │
│  ▼                                                       │
│  El bucle detecta g_signal != 0                          │
│  │  1. Liberar línea                                     │
│  │  2. Cerrar fd temporal                                │
│  │  3. Borrar archivo temporal                           │
│  │  4. mini->exit_status = 130                           │
│  │  5. Restaurar señales interactivas                    │
│  │  6. Retornar -1                                       │
│  │                                                       │
│  ▼                                                       │
│  set_redirects() recibe -1                               │
│  cmd->fd_in = -1                                         │
│  │                                                       │
│  ▼                                                       │
│  init_cmd() debe detectar fd_in == -1                    │
│  y ABORTAR el parseo de este comando                     │
│  │                                                       │
│  ▼                                                       │
│  Volver al prompt:  Minishell$>                          │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│  Ctrl+\ → IGNORADA (SIG_IGN)                            │
│  No hace nada. Bash ignora SIGQUIT en heredoc.           │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│  Ctrl+D → readline retorna NULL                          │
│  │                                                       │
│  ▼                                                       │
│  Imprimir warning:                                       │
│  "bash: warning: here-document delimited by              │
│   end-of-file (wanted 'EOF')"                            │
│  │                                                       │
│  ▼                                                       │
│  ROMPER bucle y continuar normalmente                    │
│  (NO es un error, el heredoc se usa con lo que haya)     │
└──────────────────────────────────────────────────────────┘
```

---

## Caso Especial: Múltiples heredocs

```bash
cat << EOF1 << EOF2
hola
EOF1
mundo
EOF2
```

En bash, **el último heredoc gana** (sobrescribe `fd_in`). Tu bucle en `set_redirects()` ya maneja esto naturalmente: cada vez que encuentra un `HEREDOC`, sobrescribe `cmd->fd_in`. Solo asegúrate de **cerrar el fd anterior** antes de sobrescribirlo:

```
SI cmd->fd_in > 2   // hay un heredoc anterior
    cerrar(cmd->fd_in)
cmd->fd_in = handle_heredoc(delimiter, mini)
```

---

## Caso Especial: Heredoc con pipes

```bash
cat << EOF | grep hola
hola
mundo
EOF
```

Los heredocs se resuelven en el **parseo** (en `init_cmd`/`set_redirects`), ANTES de que el executor cree los pipes. Así que cuando el executor llama a `setup_redirections()`, el `fd_in` ya contiene un fd válido con el contenido del heredoc. No hay conflicto con los pipes.

---

## Archivos que necesitas modificar

| Archivo | Qué cambiar |
|---------|-------------|
| [parser_utils.c](parser_utils.c) | Completar la rama `HEREDOC` en `set_redirects()` para llamar a `handle_heredoc()`. Necesitas que `set_redirects` reciba `t_mini *mini` como parámetro adicional. |
| [parser.c](parser.c) | Propagar `mini` hasta `set_redirects()` a través de `handler_redirects()`. |
| [../executor/handle_redirections.c](../executor/handle_redirections.c) | Modificar `setup_redirections()` para manejar `fd_in > 0` (heredoc) además de `cmd->infile` (redirección normal). |
| [../signal/signal.c](../signal/signal.c) | Añadir `handler_sigint_heredoc()` y `set_signals_heredoc()`. |
| [../../includes/signals.h](../../includes/signals.h) | Declarar los nuevos prototipos. |
| [../../includes/parser.h](../../includes/parser.h) | Declarar `handle_heredoc()`. Actualizar firma de `set_redirects()`. |

## Archivos nuevos que necesitas crear

| Archivo | Contenido |
|---------|-----------|
| `src/parser/heredoc.c` | `handle_heredoc()`, `expand_heredoc_line()`, `check_delimiter_quoted()` |

---

## Orden de implementación recomendado

```
Paso 1 → handle_heredoc() básico (sin expansión, sin señales)
         Solo readline + archivo temporal + devolver fd
         Probar con: cat << EOF

Paso 2 → Integrar en set_redirects() y setup_redirections()
         Probar que el contenido llega al comando

Paso 3 → Señales: handler_sigint_heredoc + set_signals_heredoc
         Probar con: cat << EOF + Ctrl+C

Paso 4 → Expansión de variables ($VAR dentro del heredoc)
         Probar con: cat << EOF → $HOME → debe mostrar /home/user

Paso 5 → Comillas en delimitador
         Probar con: cat << "EOF" → $HOME → debe mostrar $HOME literal

Paso 6 → Múltiples heredocs
         Probar con: cat << A << B

Paso 7 → Heredoc con pipes
         Probar con: cat << EOF | grep hola
```
--------------------------------------------------------------

Basándome en la guía y el estado actual de tu código:

Lista de tareas para implementar el heredoc
Fase 1 — Preparar la base
Crear el archivo src/parser/heredoc.c — aquí irá toda la lógica del heredoc
Actualizar el Makefile — añadir src/parser/heredoc.c a las fuentes compiladas
Cambiar la firma de set_redirects() — actualmente recibe (t_token **token, t_cmd *cmd), necesita recibir también t_mini *mini
Cambiar la firma de handler_redirects() en parser.c — para que propague mini hasta set_redirects()
Actualizar parser.h — actualizar el prototipo de set_redirects() con el nuevo parámetro
Fase 2 — Heredoc básico (sin señales, sin expansión)
Escribir handle_heredoc(char *delimiter, t_mini *mini) — versión básica: abrir archivo temporal, bucle con readline("> "), comparar con delimitador, escribir líneas, cerrar, reabrir en lectura, unlink, retornar fd
Completar la rama HEREDOC en set_redirects() — llamar a handle_heredoc() y guardar el fd en cmd->fd_in
Modificar setup_redirections() en handle_redirections.c — añadir lógica para fd_in > 0 (heredoc) antes de la lógica de infile
Declarar handle_heredoc() en parser.h
Compilar y probar con cat << EOF
Fase 3 — Señales del heredoc
Escribir handler_sigint_heredoc(int signum) en signal.c — guardar en g_signal, escribir \n, poner rl_done = 1
Escribir set_signals_heredoc(void) en signal.c — SIGINT con el handler nuevo, SIGQUIT con SIG_IGN
Declarar ambas funciones en signals.h
Integrar señales en handle_heredoc() — llamar set_signals_heredoc() antes del bucle, comprobar g_signal != 0 tras cada readline, restaurar con set_signals_interactive() al salir
Compilar y probar con cat << EOF + Ctrl+C (debe volver al prompt con $? = 130)
Fase 4 — Ctrl+D (EOF sin delimitador)
Manejar readline retornando NULL — imprimir el warning "minishell: warning: here-document delimited by end-of-file (wanted 'DELIMITADOR')" y romper el bucle (no es error, el heredoc se usa con lo que haya)
Compilar y probar con cat << EOF + Ctrl+D sin escribir EOF
Fase 5 — Propagación del error de heredoc
Manejar fd_in == -1 en init_cmd() — si handle_heredoc devolvió -1 (Ctrl+C), abortar el parseo del comando actual y no ejecutar nada
Compilar y probar que tras Ctrl+C no se ejecuta el comando
Fase 6 — Expansión de variables
Escribir expand_heredoc_line(char *line, t_mini *mini) en heredoc.c — expandir $VAR y $? dentro de cada línea leída
Integrar en el bucle de handle_heredoc() — llamar a expand_heredoc_line antes de escribir cada línea en el archivo temporal
Compilar y probar con cat << EOF → escribir $HOME → debe mostrar /home/usuario
Fase 7 — Comillas en delimitador
Escribir check_delimiter_quoted(char *delimiter) en heredoc.c — comprobar si el delimitador tiene comillas (simples o dobles)
Escribir lógica para quitar comillas del delimitador — "EOF" → EOF para la comparación
Condicionar la expansión — si el delimitador tenía comillas, NO expandir variables
Compilar y probar con cat << "EOF" → escribir $HOME → debe mostrar $HOME literal
Fase 8 — Casos especiales
Múltiples heredocs — en set_redirects(), si cmd->fd_in > 2, cerrar el fd anterior antes de sobrescribirlo con el nuevo heredoc
Probar con cat << A << B
Probar heredoc con pipes — cat << EOF | grep hola
Probar heredoc con otras redirecciones — cat << EOF > salida.txt
Fase 9 — Limpieza
Verificar leaks con valgrind — comprobar que readline, líneas temporales y fds se liberan/cierran correctamente
Comprobar que $? se actualiza correctamente en todos los casos (0 éxito, 130 Ctrl+C)