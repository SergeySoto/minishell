# Minishell

*Este proyecto ha sido creado como parte del currículo de 42 por ssoto-su, carmegon.*

*This project has been created as part of the 42 curriculum by ssoto-su, carmegon.*

---

## 🇪🇸 Español

---

### Descripción

Minishell es un proyecto de la escuela 42 cuyo objetivo es implementar una shell funcional en C, similar a Bash. El programa debe ser capaz de leer comandos del usuario, interpretarlos correctamente y ejecutarlos, gestionando redirecciones, pipes, variables de entorno, señales y comandos integrados (builtins).

El proyecto reproduce el comportamiento esencial de una shell UNIX: desde que el usuario escribe un comando y pulsa Enter, hasta que el resultado aparece en pantalla. Esto implica implementar desde cero el ciclo completo de lectura → validación → tokenización → expansión → parseo → ejecución, respetando las reglas de comportamiento de Bash.

**Características principales:**
- Prompt interactivo con historial de comandos (readline)
- Pipes (`|`) encadenando cualquier número de comandos
- Redirecciones de entrada (`<`), salida (`>`), append (`>>`) y heredoc (`<<`)
- Expansión de variables de entorno (`$VAR`, `$?`)
- Gestión correcta de comillas simples y dobles
- Manejo de señales (`SIGINT`, `SIGQUIT`) en todos los contextos
- 7 builtins implementados: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

---

### División del trabajo

El proyecto se dividió en dos grandes bloques funcionales:

**Pre-parseo, Lexer, Tokenizador, Parser y Builtins**
Antes de procesar nada, se valida que el input del usuario sea sintácticamente correcto: comillas no cerradas, pipes al inicio o al final, operadores de redirección sin argumento, caracteres prohibidos (`\`, `;`) y dobles operadores inválidos (`||`, `&&`). El input validado se divide en tokens individuales respetando comillas y operadores de shell. Cada fragmento se convierte en un nodo `t_token` de una lista enlazada con su tipo asignado. Esta lista se transforma después en una lista enlazada de `t_cmd`, donde cada nodo representa un comando con sus argumentos, rutas de archivos y file descriptors. Los siete builtins de bash se implementan desde cero con su comportamiento exacto.

**Heredoc, Expander, Executor y Señales**
Después de tokenizar, la lista de tokens se recorre en busca de referencias a variables (`$VAR`, `$?`) y se sustituyen por sus valores. La redirección `<<` crea un archivo temporal, lee líneas hasta encontrar el delimitador y devuelve un file descriptor al contenido. El executor distingue entre comandos únicos y pipelines: los builtins que modifican el estado del shell se ejecutan en el proceso padre; el resto se forkea. Para pipelines, se crea un proceso hijo por comando conectados mediante pipes POSIX. Las señales `SIGINT` y `SIGQUIT` se gestionan de forma diferente según el contexto: prompt, hijo único, pipeline o heredoc.

---

### Instrucciones

**Requisitos del sistema:**
- Sistema operativo Linux o macOS
- Compilador `gcc` o `clang`
- Librería `readline` instalada
- `make`

**Instalación de readline (si no está instalada):**
```bash
# Ubuntu / Debian
sudo apt-get install libreadline-dev

# macOS (Homebrew)
brew install readline
```

**Compilación:**
```bash
git clone <url-del-repositorio>
cd minishell
make
```

**Ejecución:**
```bash
./minishell
```

**Modo no interactivo (pipe de entrada):**
```bash
echo "ls -la" | ./minishell
```

**Limpieza:**
```bash
make clean    # elimina objetos
make fclean   # elimina objetos y binario
make re       # recompila desde cero
```

---

### Ejemplos de uso y pruebas por builtin

#### `echo`
```bash
echo Hola mundo
echo -n Sin salto de linea
echo "Variable HOME: $HOME"
echo -nnn Multiples flags n
echo '$USER no se expande entre comillas simples'
echo ""
```

#### `cd`
```bash
cd /tmp
cd ..
cd
cd $HOME
cd /ruta/que/no/existe
cd /tmp && pwd
```

#### `pwd`
```bash
pwd
cd /tmp && pwd
cd .. && pwd
export PWD=/fake && pwd
pwd | cat
```

#### `export`
```bash
export
export MI_VAR=hola
export MI_VAR=hola OTRA=mundo
export SINVALOR
export 1INVALIDO=fallo
export MI_VAR= && echo $MI_VAR
```

#### `unset`
```bash
unset MI_VAR
unset HOME && cd
unset PATH && ls
unset MI_VAR OTRA
unset _
unset INEXISTENTE
```

#### `env`
```bash
env
env | grep HOME
env | grep PATH
env | wc -l
unset PATH && env
```

#### `exit`
```bash
exit
exit 0
exit 42
exit 300
exit abc
exit 1 2 3
```

---

### Recursos

**Documentación oficial:**
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — referencia completa del comportamiento de Bash
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentación de la librería readline
- [POSIX.1-2017 — Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/) — estándar POSIX para shells

**Llamadas al sistema clave:**
- `man 2 fork` — creación de procesos hijo
- `man 2 execve` — sustitución del proceso por un ejecutable
- `man 2 pipe` — creación de pipes POSIX
- `man 2 dup2` — duplicación y redirección de file descriptors
- `man 2 waitpid` — espera de procesos hijo
- `man 2 sigaction` — gestión avanzada de señales

**Artículos y tutoriales:**
- [Writing a Unix Shell](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/) — serie de artículos sobre implementación de shells
- [Stephen Brennan's Tutorial Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/) — tutorial clásico de shell en C
- [Unix Processes and Signals](https://cs.usfca.edu/~galles/visualization/Processes.html) — visualización de procesos y señales

**Uso de Inteligencia Artificial:**
Durante el desarrollo de este proyecto se ha utilizado IA (Claude de Anthropic) y Gemini Pro como herramienta de apoyo en las siguientes tareas:
- Generación de documentación Doxygen para todas las funciones del proyecto
- Resolución de dudas conceptuales sobre el comportamiento de pipes, fork/exec y señales POSIX
- Generación de la guía técnica de arquitectura del proyecto (diagramas de flujo, explicaciones del executor y pipelines)
- Apoyo en la comprensión del código implementado por el compañero de proyecto
- Generación de este archivo README

La IA **no** ha generado código fuente del proyecto. Todo el código C ha sido escrito íntegramente por los autores.

---
---

## 🇬🇧 English

---

### Description

Minishell is a 42 school project whose goal is to implement a functional shell in C, similar to Bash. The program must be able to read user commands, interpret them correctly and execute them, handling redirections, pipes, environment variables, signals and built-in commands.

The project reproduces the essential behaviour of a UNIX shell: from the moment the user types a command and presses Enter, to the result appearing on screen. This means implementing from scratch the full cycle of reading → validation → tokenization → expansion → parsing → execution, following Bash's behavioural rules.

**Main features:**
- Interactive prompt with command history (readline)
- Pipes (`|`) chaining any number of commands
- Input (`<`), output (`>`), append (`>>`) and heredoc (`<<`) redirections
- Environment variable expansion (`$VAR`, `$?`)
- Correct handling of single and double quotes
- Signal management (`SIGINT`, `SIGQUIT`) across all contexts
- 7 implemented builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

---

### Division of work

The project was split into two main functional blocks:

**Pre-parsing, Lexer, Tokenizer, Parser and Builtins**
Before processing anything, the user's input is validated for correct syntax: unclosed quotes, pipes at the start or end of the line, redirection operators with no argument, forbidden characters (`\`, `;`) and invalid double operators (`||`, `&&`). The validated input is split into individual tokens while respecting quotes and shell operators. Each fragment becomes a `t_token` node in a linked list with its assigned type. This list is then transformed into a linked list of `t_cmd` nodes, where each node represents a command with its arguments, file paths and file descriptors. The seven bash builtins are implemented from scratch with their exact behaviour.

**Heredoc, Expander, Executor and Signals**
After tokenizing, the token list is traversed looking for variable references (`$VAR`, `$?`) which are replaced with their values. The `<<` redirection creates a temporary file, reads lines until the delimiter is found and returns a file descriptor to the content. The executor distinguishes between single commands and pipelines: builtins that modify shell state run in the parent process; everything else is forked. For pipelines, one child process is created per command, all connected through POSIX pipes. `SIGINT` and `SIGQUIT` signals are handled differently depending on context: prompt, single child, pipeline or heredoc.

---

### Instructions

**System requirements:**
- Linux or macOS operating system
- `gcc` or `clang` compiler
- `readline` library installed
- `make`

**Installing readline (if not already installed):**
```bash
# Ubuntu / Debian
sudo apt-get install libreadline-dev

# macOS (Homebrew)
brew install readline
```

**Build:**
```bash
git clone <repository-url>
cd minishell
make
```

**Run:**
```bash
./minishell
```

**Non-interactive mode (piped input):**
```bash
echo "ls -la" | ./minishell
```

**Cleanup:**
```bash
make clean    # removes object files
make fclean   # removes objects and binary
make re       # full recompile from scratch
```

---

### Usage examples and builtin tests

#### `echo`
```bash
echo Hello world
echo -n No newline at end
echo "HOME variable: $HOME"
echo -nnn Multiple n flags
echo '$USER is not expanded in single quotes'
echo ""
```

#### `cd`
```bash
cd /tmp
cd ..
cd
cd $HOME
cd /path/that/does/not/exist
cd /tmp && pwd
```

#### `pwd`
```bash
pwd
cd /tmp && pwd
cd .. && pwd
export PWD=/fake && pwd
pwd | cat
```

#### `export`
```bash
export
export MY_VAR=hello
export MY_VAR=hello OTHER=world
export NOVALUE
export 1INVALID=fail
export MY_VAR= && echo $MY_VAR
```

#### `unset`
```bash
unset MY_VAR
unset HOME && cd
unset PATH && ls
unset MY_VAR OTHER
unset _
unset NONEXISTENT
```

#### `env`
```bash
env
env | grep HOME
env | grep PATH
env | wc -l
unset PATH && env
```

#### `exit`
```bash
exit
exit 0
exit 42
exit 300
exit abc
exit 1 2 3
```

---

### Resources

**Official documentation:**
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — full reference for Bash behaviour
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — readline library documentation
- [POSIX.1-2017 — Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/) — POSIX standard for shells

**Key system calls:**
- `man 2 fork` — child process creation
- `man 2 execve` — replacing the process with an executable
- `man 2 pipe` — POSIX pipe creation
- `man 2 dup2` — file descriptor duplication and redirection
- `man 2 waitpid` — waiting for child processes
- `man 2 sigaction` — advanced signal management

**Articles and tutorials:**
- [Writing a Unix Shell](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/) — article series on shell implementation
- [Stephen Brennan's Tutorial Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/) — classic shell-in-C tutorial
- [Unix Processes and Signals](https://cs.usfca.edu/~galles/visualization/Processes.html) — process and signal visualisation

**Use of Artificial Intelligence:**
During the development of this project, AI (Claude by Anthropic) was used as a support tool for the following tasks:
- Generating Doxygen documentation for all project functions
- Answering conceptual questions about pipes, fork/exec and POSIX signal behaviour
- Generating the project's technical architecture guide (flow diagrams, executor and pipeline explanations)
- Supporting understanding of code implemented by the project partner
- Generating this README file

The AI **did not** generate any source code for the project. All C code was written entirely by the authors.
