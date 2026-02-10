# Guía Completa del Ejecutor - Minishell

## 📊 Flujograma General del Ejecutor

```
┌─────────────────────────────┐
│     execute_cmds(mini)      │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│  ¿Cuántos comandos hay?     │
│  (¿cmd->next es NULL?)      │
└──────┬──────────────┬───────┘
       │              │
   UN SOLO CMD    MÚLTIPLES CMDS
       │              │
       ▼              ▼
┌─────────────┐ ┌──────────────────┐
│ ¿Es builtin?│ │ Entrar en bucle  │
│             │ │ de pipes         │
└──┬───────┬──┘ └────────┬─────────┘
   │       │             │
  SÍ      NO             ▼
   │       │    ┌──────────────────┐
   ▼       ▼    │ Para CADA cmd:   │
┌──────┐ ┌────┐│  1. Crear pipe   │
│Eject.│ │Fork││  2. Fork         │
│en el │ │    ││  3. Redirigir    │
│PADRE │ │    ││  4. Ejecutar     │
└──────┘ └─┬──┘└────────┬─────────┘
           │            │
           ▼            ▼
    ┌─────────────────────────┐
    │  PROCESO HIJO:          │
    │  1. Configurar FDs      │
    │  2. Abrir redirecciones │
    │  3. ¿Es builtin?       │
    │     → Ejecutar builtin  │
    │     → Ejecutar execve   │
    │  4. Salir con exit()    │
    └─────────────────────────┘
           │
           ▼
    ┌─────────────────────────┐
    │  PROCESO PADRE:         │
    │  1. Cerrar FDs usados   │
    │  2. Esperar a los hijos │
    │  3. Recoger exit_status │
    └─────────────────────────┘
```

---

## 📊 Flujograma de un Comando Simple (sin pipes)

```
┌───────────────────────┐
│   Comando simple      │
│   (cmd->next == NULL) │
└───────────┬───────────┘
            │
            ▼
┌───────────────────────┐
│  ¿Es builtin?        │
│  (echo, cd, pwd,     │
│   export, unset,     │
│   env, exit)         │
└────┬────────────┬─────┘
    SÍ           NO
     │            │
     ▼            ▼
┌─────────┐  ┌─────────────────┐
│¿Tiene   │  │  fork()         │
│redireccs│  └────────┬────────┘
│?        │           │
└──┬───┬──┘     ┌─────┴─────┐
  SÍ  NO      HIJO       PADRE
   │   │       │            │
   ▼   ▼       ▼            ▼
┌──────────┐ ┌──────────┐ ┌──────────┐
│Guardar   │ │Ejecutar  │ │Abrir     │
│STDIN/OUT │ │builtin   │ │redireccs │
│Abrir FDs │ │directo   │ │Ejecutar  │
│Redirigir │ │en padre  │ │execve    │
│Ejecutar  │ └──────────┘ │exit()    │
│Restaurar │              └──────────┘
│STDIN/OUT │         ┌──────────┐
└──────────┘         │waitpid() │
                     │Guardar   │
                     │exit_status│
                     └──────────┘
```

---

## 📊 Flujograma de Pipes (múltiples comandos)

```
Ejemplo: ls -la | grep .c | wc -l
         CMD1      CMD2      CMD3

┌────────────────────────────────────────────────┐
│              ANTES DEL BUCLE                    │
│  Guardar stdin/stdout originales (backup)       │
└────────────────────┬───────────────────────────┘
                     │
     ┌───────────────┼───────────────────┐
     ▼               ▼                   ▼
  ┌──────┐      ┌──────┐           ┌──────┐
  │ CMD1 │─pipe─│ CMD2 │───pipe────│ CMD3 │
  │      │      │      │           │      │
  │IN:   │      │IN:   │           │IN:   │
  │stdin │      │lee de│           │lee de│
  │      │      │pipe1 │           │pipe2 │
  │OUT:  │      │OUT:  │           │OUT:  │
  │pipe1 │      │pipe2 │           │stdout│
  └──────┘      └──────┘           └──────┘
     │               │                │
     └───────────────┼────────────────┘
                     ▼
          ┌──────────────────┐
          │ Cerrar TODOS los │
          │ pipes en padre   │
          │ waitpid() a      │
          │ TODOS los hijos  │
          │ exit_status =    │
          │ status del ÚLTIMO│
          └──────────────────┘
```

---

## 📊 Flujograma de Redirecciones dentro de un Hijo

```
┌─────────────────────────────┐
│  DENTRO DEL PROCESO HIJO    │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│ ¿cmd->infile existe?        │
│ (redirección de entrada)    │
└──────┬──────────────┬───────┘
      SÍ             NO
       │               │
       ▼               │
┌──────────────┐       │
│ open(infile,  │       │
│   O_RDONLY)   │       │
│ ¿Falló?      │       │
│  → error msg │       │
│  → exit(1)   │       │
│ dup2(fd, 0)  │       │
│ close(fd)    │       │
└──────┬───────┘       │
       └───────┬───────┘
               │
               ▼
┌─────────────────────────────┐
│ ¿cmd->outfile existe?       │
│ (redirección de salida)     │
└──────┬──────────────┬───────┘
      SÍ             NO
       │               │
       ▼               │
┌──────────────────┐   │
│ ¿cmd->append?    │   │
│  SÍ → O_APPEND   │   │
│  NO → O_TRUNC    │   │
│ open(outfile,    │   │
│   O_WRONLY|      │   │
│   O_CREAT|flags) │   │
│ ¿Falló?          │   │
│  → error msg     │   │
│  → exit(1)       │   │
│ dup2(fd, 1)      │   │
│ close(fd)        │   │
└──────┬───────────┘   │
       └───────┬───────┘
               │
               ▼
┌─────────────────────────────┐
│ ¿Hay pipe de entrada?       │
│ (no es el primer cmd)       │
│  → dup2(prev_pipe_read, 0)  │
│                             │
│ ¿Hay pipe de salida?        │
│ (no es el último cmd)       │
│  → dup2(curr_pipe_write, 1) │
│                             │
│ Cerrar TODOS los FDs de     │
│ pipes que no uso             │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│ Ejecutar (execve o builtin) │
└─────────────────────────────┘
```

---

## 📝 Pseudocódigo

### Función Principal

```
FUNCIÓN execute_cmds(mini):
    cmd = mini->cmds
    
    SI cmd es NULL:
        RETORNAR
    
    SI cmd->next es NULL:                    // Un solo comando
        SI es_builtin(cmd->args[0]):
            SI tiene redirecciones:
                guardar_stdin_stdout(mini)
                aplicar_redirecciones(cmd)
                ejecutar_builtin(cmd, mini)
                restaurar_stdin_stdout(mini)
            SINO:
                ejecutar_builtin(cmd, mini)
        SINO:
            ejecutar_comando_simple(cmd, mini)
    SINO:                                    // Pipeline
        ejecutar_pipeline(mini)
```

### Comando Simple (no builtin, sin pipes)

```
FUNCIÓN ejecutar_comando_simple(cmd, mini):
    SI cmd->cmd_path es NULL Y cmd->args[0] no es vacío:
        imprimir error "command not found"
        mini->exit_status = 127
        RETORNAR
    
    SI cmd->cmd_path existe Y NO tiene permisos de ejecución:
        imprimir error "Permission denied"
        mini->exit_status = 126
        RETORNAR
    
    pid = fork()
    
    SI pid == 0:                         // HIJO
        aplicar_redirecciones(cmd)
        env_array = env_to_array(mini->env)
        execve(cmd->cmd_path, cmd->args, env_array)
        // Si execve retorna, hubo error
        imprimir error según errno
        liberar todo
        exit(código_apropiado)
    
    SINO SI pid > 0:                     // PADRE
        waitpid(pid, &status, 0)
        mini->exit_status = extraer_código(status)
    
    SINO:                                // Error en fork
        imprimir error
```

### Pipeline

```
FUNCIÓN ejecutar_pipeline(mini):
    cmd_actual = mini->cmds
    prev_pipe_read = -1
    
    MIENTRAS cmd_actual no sea NULL:
        SI cmd_actual->next existe:
            crear pipe(pipe_fd)          // pipe_fd[0]=lectura, pipe_fd[1]=escritura
        
        pid = fork()
        
        SI pid == 0:                     // HIJO
            // Entrada: ¿viene de un pipe anterior?
            SI prev_pipe_read != -1:
                dup2(prev_pipe_read, STDIN)
                close(prev_pipe_read)
            
            // Salida: ¿va hacia un pipe siguiente?
            SI cmd_actual->next existe:
                close(pipe_fd[0])        // El hijo no lee de SU propio pipe
                dup2(pipe_fd[1], STDOUT)
                close(pipe_fd[1])
            
            aplicar_redirecciones(cmd_actual)  // Las redirecciones tienen PRIORIDAD
            
            SI es_builtin(cmd_actual->args[0]):
                ejecutar_builtin(cmd_actual, mini)
                exit(mini->exit_status)
            SINO:
                env_array = env_to_array(mini->env)
                execve(cmd_actual->cmd_path, cmd_actual->args, env_array)
                // Error handling...
                exit(código_error)
        
        // PADRE:
        SI prev_pipe_read != -1:
            close(prev_pipe_read)        // Ya no necesitamos el pipe anterior
        
        SI cmd_actual->next existe:
            close(pipe_fd[1])            // El padre no escribe
            prev_pipe_read = pipe_fd[0]  // Guardamos lectura para el siguiente
        
        cmd_actual->pid = pid
        cmd_actual = cmd_actual->next
    
    // Esperar a TODOS los hijos
    cmd_actual = mini->cmds
    MIENTRAS cmd_actual:
        waitpid(cmd_actual->pid, &status, 0)
        cmd_actual = cmd_actual->next
    
    mini->exit_status = extraer_código(status)   // Solo del ÚLTIMO
```

---

## 🤔 Preguntas para Reflexionar

### Sobre Fork y Procesos

1. **¿Por qué los builtins `cd`, `export`, `unset` y `exit` deben ejecutarse en el proceso padre cuando son comando único, pero en un hijo cuando están en un pipeline?** Piensa qué pasa si haces `cd /tmp` en un hijo... ¿cambia el directorio del padre?

2. **¿Qué pasa si `fork()` falla?** ¿Qué valor retorna? ¿Deberías seguir intentando crear más hijos en un pipeline o detenerte?

3. **Después de `execve`, ¿se ejecuta alguna línea de código que esté debajo?** ¿Cuándo sí se ejecutan esas líneas?

### Sobre File Descriptors y Pipes

4. **Si en un pipeline de 3 comandos creas 2 pipes (4 FDs), ¿cuántos de esos FDs debe cerrar cada proceso hijo?** ¿Y el padre? Piensa en qué pasa si un hijo deja abierto el extremo de escritura de un pipe del que otro hijo está leyendo.

5. **¿Por qué las redirecciones (`< archivo`, `> archivo`) tienen prioridad sobre los pipes?** Es decir, si tienes `cat < input.txt | grep hola`, ¿de dónde lee `cat`? ¿Del pipe o del archivo?

6. **¿Qué pasa si intentas abrir un `infile` que no existe?** ¿Qué código de salida deberías usar? ¿Debería tu shell detenerse por completo o solo fallar ese comando?

7. **En tu struct `t_mini` tienes `stdin_backup` y `stdout_backup`. ¿En qué caso específico los necesitas?** Pista: piensa en un builtin sin pipes pero CON redirecciones.

### Sobre Códigos de Salida

8. **¿Cuál es la diferencia entre exit code 126 y 127?** ¿Cuándo usarías cada uno?

9. **En un pipeline como `false | true | ls`, ¿cuál es el `$?` final?** ¿El de `false`, el de `true` o el de `ls`?

10. **Las macros `WIFEXITED` y `WEXITSTATUS` sirven para extraer el código de salida real de `waitpid`. ¿Qué pasa si el hijo murió por una señal (ej: Segfault)?** ¿Qué macro usarías para detectar eso y qué código deberías reportar?

### Sobre Builtins

11. **¿Por qué `echo`, `pwd` y `env` pueden ejecutarse en un hijo sin problemas, pero `cd`, `export`, `unset` y `exit` no?** ¿Qué efecto lateral tienen estos últimos?

12. **Si el usuario escribe `export VAR=hola | echo test`, ¿debería `VAR` existir en el entorno después?** Pista: `export` está en un pipeline, así que...

### Sobre tu Código Actual

13. **En tu `executor.c`, tienes `cmd = (*mini);`. ¿Es esto correcto?** `*mini` es de tipo `t_mini`, pero `cmd` es de tipo `t_cmd *`. ¿Qué deberías asignar realmente?

14. **`is_builtin` en tu código actual no tiene paréntesis ni argumentos. ¿Es una función que necesitas crear? ¿Qué debería recibir como parámetro y qué retornar?**

15. **¿Dónde y cuándo deberías llamar a `env_to_array`?** Pista: `execve` necesita un `char **envp`. ¿Lo creas una vez antes del bucle o una vez por cada hijo?

---

## ✅ Lista de Tareas (Orden Recomendado)

### Fase 1: Infraestructura Base

- [ ] **1.1** Crear la función `is_builtin(char *cmd_name)` que retorne 1 si el comando es uno de los 7 builtins (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`), 0 si no.
- [ ] **1.2** Corregir el error de compilación en `executor.c` (revisa la pregunta 13).
- [ ] **1.3** Crear la función `apply_redirections(t_cmd *cmd)` que abra los archivos de `infile`/`outfile` y use `dup2` para redirigir `STDIN`/`STDOUT`.
- [ ] **1.4** Crear funciones `save_std_fds(t_mini *mini)` y `restore_std_fds(t_mini *mini)` para guardar/restaurar los FDs originales.

### Fase 2: Comando Simple

- [ ] **2.1** Implementar la lógica de detección: un solo comando vs pipeline.
- [ ] **2.2** Implementar ejecución de un **comando externo simple** (sin pipes): `fork` → hijo ejecuta `execve` → padre hace `waitpid`.
- [ ] **2.3** Manejar el caso donde `cmd_path` es `NULL` (comando no encontrado → exit 127).
- [ ] **2.4** Manejar el caso donde el archivo existe pero no tiene permisos (`access` con `X_OK` → exit 126).
- [ ] **2.5** Verificar que `env_to_array` se llama correctamente antes de `execve` y que se libera la memoria después.
- [ ] **2.6** Probar: `ls`, `/bin/ls`, `./minishell`, `comandoinexistente`, `""`.

### Fase 3: Redirecciones

- [ ] **3.1** Implementar `< infile` (abrir archivo, `dup2` a STDIN).
- [ ] **3.2** Implementar `> outfile` (abrir/crear archivo con `O_TRUNC`, `dup2` a STDOUT).
- [ ] **3.3** Implementar `>> outfile` (abrir/crear archivo con `O_APPEND`, `dup2` a STDOUT).
- [ ] **3.4** Manejar errores: archivo no existe, sin permisos, etc.
- [ ] **3.5** Probar: `ls > out.txt`, `cat < Makefile`, `echo hola >> out.txt`, `cat < noexiste`.

### Fase 4: Builtins (comando único)

- [ ] **4.1** Implementar `echo` (con flag `-n`).
- [ ] **4.2** Implementar `pwd`.
- [ ] **4.3** Implementar `env`.
- [ ] **4.4** Implementar `cd` (modificar el directorio del proceso padre, actualizar `PWD` y `OLDPWD` en el entorno).
- [ ] **4.5** Implementar `export` (añadir/modificar variables en `t_env`).
- [ ] **4.6** Implementar `unset` (eliminar variables de `t_env`).
- [ ] **4.7** Implementar `exit` (salir limpiamente con el código apropiado).
- [ ] **4.8** Probar cada builtin con y sin redirecciones.

### Fase 5: Pipes

- [ ] **5.1** Implementar la creación de pipes con `pipe()`.
- [ ] **5.2** Implementar el bucle de fork para múltiples comandos.
- [ ] **5.3** Implementar la lógica de `dup2` para conectar pipes entre procesos hijo.
- [ ] **5.4** Asegurar que el padre cierra TODOS los FDs de pipes que no usa.
- [ ] **5.5** Asegurar que cada hijo cierra TODOS los FDs de pipes que no usa.
- [ ] **5.6** Implementar `waitpid` para esperar a todos los hijos.
- [ ] **5.7** El `exit_status` debe ser el del **último** comando del pipeline.
- [ ] **5.8** Probar: `ls | cat`, `ls | grep .c | wc -l`, `cat < Makefile | grep NAME > out.txt`.

### Fase 6: Heredoc

- [ ] **6.1** Implementar la lectura del heredoc (leer líneas hasta encontrar el delimitador).
- [ ] **6.2** Escribir el contenido leído en un pipe o archivo temporal.
- [ ] **6.3** Conectar ese pipe/archivo como STDIN del comando.
- [ ] **6.4** Probar: `cat << EOF`.

### Fase 7: Señales

- [ ] **7.1** Implementar `SIGINT` (Ctrl+C) en modo interactivo (nueva línea de prompt).
- [ ] **7.2** Implementar `SIGQUIT` (Ctrl+\) en modo interactivo (ignorar).
- [ ] **7.3** Implementar señales durante la ejecución de un hijo (Ctrl+C mata al hijo).
- [ ] **7.4** Implementar señales durante heredoc (Ctrl+C cancela el heredoc).

### Fase 8: Testing y Limpieza

- [ ] **8.1** Ejecutar tu `tester.sh` y verificar que no hay segfaults.
- [ ] **8.2** Verificar con Valgrind que no hay leaks (usando tu `supresion.supp`).
- [ ] **8.3** Probar edge cases: `""`, `" "`, `|` solo, `> ` solo (tu pre-parser ya maneja algunos).
- [ ] **8.4** Comparar comportamiento con bash para cada caso.

---

## 💡 Consejo Final

Empieza por la **Fase 2** (comando simple sin pipes ni redirecciones). Cuando `ls` y `/bin/echo hola` funcionen correctamente, todo lo demás es construir sobre esa base.
