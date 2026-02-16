#### Paso 3: El Pipeline (exec_pipeline) — LA JOYA DE LA CORONA
Esta es la parte más compleja. Necesitas crear una función nueva.

#### Prototipo:

Antes de escribir código, responde estas preguntas:

Si tienes ls | grep .c | wc -l (3 comandos), ¿cuántos pipes necesitas crear? ¿Cuántos fork() necesitas?

En el pseudocódigo de tu guía, aparece una variable prev_pipe_read. ¿Para qué sirve? Imagina que estás procesando grep .c (el segundo comando). ¿De dónde lee su entrada? ¿Del teclado o del pipe que creó ls?

¿Por qué el padre debe cerrar pipe_fd[1] (el extremo de escritura) inmediatamente después de hacer fork? Pista: Si el padre deja abierto el extremo de escritura, el hijo que lee de ese pipe nunca recibirá EOF y se quedará colgado esperando.

¿Por qué hay que esperar a TODOS los hijos al final y no uno por uno dentro del bucle?

Pseudocódigo detallado:

FUNCIÓN exec_pipeline(mini):
    cmd_actual = mini->cmds
    prev_pipe_read = -1
    
    MIENTRAS cmd_actual no sea NULL:
        
        // 1. ¿Necesito un pipe nuevo?
        SI cmd_actual->next existe:
            crear pipe(pipe_fd)
            SI pipe falla:
                imprimir error, RETORNAR
        
        // 2. Crear hijo
        pid = fork()
        SI pid falla:
            imprimir error, limpiar pipes, RETORNAR
        
        SI pid == 0:  // HIJO
            // a) ¿Tengo entrada de un pipe anterior?
            SI prev_pipe_read != -1:
                dup2(prev_pipe_read, STDIN)
                close(prev_pipe_read)
            
            // b) ¿Tengo salida hacia un pipe siguiente?
            SI cmd_actual->next existe:
                close(pipe_fd[0])    // No leo de mi propio pipe
                dup2(pipe_fd[1], STDOUT)
                close(pipe_fd[1])
            
            // c) Aplicar redirecciones (tienen PRIORIDAD sobre pipes)
            apply_redirections(cmd_actual)
            
            // d) Ejecutar
            SI es_builtin(cmd_actual->args[0]):
                run_builtin(mini, cmd_actual)
                exit(exit_status)
            SINO:
                env = env_to_array(mini->env)
                execve(cmd_actual->cmd_path, cmd_actual->args, env)
                // Si llega aquí, execve falló
                imprimir error
                exit(código_error)
        
        // PADRE:
        // e) Cerrar el pipe anterior (ya no lo necesito)
        SI prev_pipe_read != -1:
            close(prev_pipe_read)
        
        // f) Preparar para el siguiente comando
        SI cmd_actual->next existe:
            close(pipe_fd[1])             // No escribo
            prev_pipe_read = pipe_fd[0]   // Guardo lectura para el siguiente
        
        // g) Guardar el pid del hijo
        cmd_actual->pid = pid
        cmd_actual = cmd_actual->next
    
    // 3. Esperar a TODOS los hijos
    cmd_actual = mini->cmds
    MIENTRAS cmd_actual:
        waitpid(cmd_actual->pid, &status, 0)
        cmd_actual = cmd_actual->next
    
    // 4. Exit status = el del ÚLTIMO comando
    mini->exit_status = WEXITSTATUS(status)

