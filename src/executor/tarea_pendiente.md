🎯 ¿Qué hace unset?
unset elimina una o más variables del entorno. Es lo opuesto a export.

export NOMBRE=Juan    # Crea la variable
echo $NOMBRE          # Imprime: Juan
unset NOMBRE          # La elimina
echo $NOMBRE          # Imprime: (nada)

📋 Comportamiento esperado
Entrada	                                 Resultado
unset VAR	                             Elimina VAR del entorno
unset VAR1 VAR2 VAR3	                 Elimina múltiples variables
unset VAR_QUE_NO_EXISTE	                 No hace nada, no es error
unset (sin argumentos)	                 No hace nada, retorna 0
unset PATH	                             Elimina PATH (válido, aunque peligroso)

Código de retorno: Siempre 0 (en la versión básica de minishell).

🧩 Tareas para implementar unset
Tarea 1: Entender tu lista enlazada
Tu entorno es una lista enlazada (t_env). Para eliminar un nodo de una lista enlazada necesitas:

1. Encontrar el nodo con la key que coincide
2. "Saltar" ese nodo conectando el anterior con el siguiente
3. Liberar la memoria del nodo eliminado

Pregunta para ti: ¿Qué pasa si el nodo a eliminar es el primero de la lista? ¿Y si es el último?

Tarea 2: Iterar sobre los argumentos
unset puede recibir múltiples argumentos: unset VAR1 VAR2 VAR3

Recuerda que cmd->args es un array:

args[0] = "unset"
args[1] = "VAR1"
args[2] = "VAR2"
...
Pregunta para ti: ¿Desde qué índice deberías empezar a procesar? ¿Cuándo paras?

Tarea 3: Buscar la variable en la lista
Para cada argumento, debes recorrer tu lista mini->env buscando un nodo donde node->key sea igual al argumento.

Pregunta para ti: ¿Qué función de tu libft puedes usar para comparar strings?

Tarea 4: Eliminar el nodo
Eliminar un nodo de una lista enlazada tiene 3 casos:

Caso	Situación	               Acción
1	    El nodo es el primero	   El inicio de la lista (mini->env) debe apuntar al siguiente
2	    El nodo está en el medio   El nodo anterior debe apuntar al siguiente del actual
3	    El nodo es el último	   El nodo anterior debe apuntar a NULL

Pregunta para ti: ¿Por qué necesitas guardar una referencia al nodo anterior mientras recorres la lista?

Tarea 5: Actualizar env_array
Tu estructura t_mini tiene env_array (un char** que usas para execve). Si eliminas una variable de la lista enlazada, también debes actualizar este array.

Opciones:

· Regenerar env_array completo después de cada unset
· O actualizar el array directamente (más complejo)

Pregunta para ti: ¿Tienes ya una función que convierta tu lista t_env a char**? Si es así, ¿podrías reutilizarla?

📝Pseudocodigo
FUNCIÓN builtin_unset(mini, cmd):
    
    índice = 1  // Empezamos desde args[1], args[0] es "unset"
    
    MIENTRAS cmd->args[índice] NO sea NULL:
        
        nombre_variable = cmd->args[índice]
        
        // Buscar y eliminar de la lista enlazada
        eliminar_variable_de_lista(mini->env, nombre_variable)
        
        índice = índice + 1
    
    // Actualizar el array para execve
    regenerar_env_array(mini)
    
    RETORNAR 0


FUNCIÓN eliminar_variable_de_lista(env, nombre):
    
    actual = env
    anterior = NULL
    
    MIENTRAS actual NO sea NULL:
        
        SI actual->key ES IGUAL A nombre:
            
            SI anterior ES NULL:
                // Es el primer nodo
                env = actual->next
            SINO:
                // Está en medio o al final
                anterior->next = actual->next
            
            liberar(actual->key)
            liberar(actual->value)
            liberar(actual)
            RETORNAR
        
        anterior = actual
        actual = actual->next

❓ Preguntas de autoevaluación
1. Memoria: Cuando eliminas un nodo, ¿qué sucede si solo liberas el nodo pero no key y value? (Pista: memory leak)

2. Punteros: Si el nodo a eliminar es el primero, necesitas modificar mini->env directamente. ¿Cómo pasarías env a la función para poder modificar el puntero original? (Pista: doble puntero **)

3. Edge case: ¿Qué pasa si args[1] es NULL? (El usuario solo escribió unset)

4. Validación opcional: En bash real, unset 123VAR da error porque los nombres de variables no pueden empezar con número. ¿Tu minishell debe validar esto?

⚠️ Aclaraciones importantes
· No es error si la variable no existe: unset VARIABLE_INEXISTENTE simplemente no hace nada.
· Orden de liberación: Siempre libera key y value antes de liberar el nodo.
· Variables especiales: En tu minishell básico, no necesitas proteger variables especiales. unset PATH es válido aunque rompa la ejecución de comandos externos.

🔍 Siguiente paso sugerido
Empieza por dibujar en papel cómo se ve tu lista enlazada con 3-4 nodos y simula manualmente qué punteros cambian cuando eliminas:

1. El primer nodo
2. Un nodo del medio
3. El último nodo
