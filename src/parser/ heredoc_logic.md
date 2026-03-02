### handle_redirection(t_token **tokens, t_cmd *cmd) - parser_redirections_Chicken.c
Función principal para manejar cualquier tipo de redirección.
- Obtiene el tipo de redirección del token
- Verifica que haya un filename válido
- Llama a handle_redirection_mid() con el tipo y filename
- *Retorna:* 1 si éxito, 0 si error

### handle_heredoc(char *delimiter) - parser_redirections_little_chickens3.c
Maneja la redirección heredoc (<<).
- Crea un archivo temporal /tmp/heredoc
- Lee líneas con readline("> ") en un bucle
- Escribe cada línea en el archivo hasta encontrar el delimitador
- Cierra y reabre el archivo en modo lectura
- *Retorna:* File descriptor del archivo temporal para usarse como stdin

### handle_input_redirection(char *filename) - parser_redirections_little_chickens3.c
Maneja la redirección de entrada (<).
- Abre el archivo en modo solo lectura (O_RDONLY)
- Si hay error (archivo no existe, sin permisos), muestra error
- *Retorna:* File descriptor para usarse como stdin, o -1 si error

### handle_output_redirection(char *filename) - parser_redirections_little_chickens3.c
Maneja la redirección de salida (>).
- Abre/crea el archivo en modo escritura
- Usa O_TRUNC para truncar (vaciar) el archivo si existe
- Permisos: 0644 (rw-r--r--)
- *Retorna:* File descriptor para usarse como stdout

### handle_append_redirection(char *filename) - parser_redirections_little_chickens3.c
Maneja la redirección de salida en modo append (>>).
- Abre/crea el archivo en modo escritura
- Usa O_APPEND en lugar de O_TRUNC
- Añade contenido al final sin borrar lo existente
- *Retorna:* File descriptor para usarse como stdout