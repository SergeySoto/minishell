# Minishell

*This project has been created as part of the 42 curriculum by ssoto-su, carmegon.*

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
