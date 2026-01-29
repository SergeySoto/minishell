#!/bin/bash

# --- CONFIGURACIÓN ---
MINISHELL="./minishell"
VALGRIND_LOG="valgrind_out.log"
USE_VALGRIND=0 # Cambia a 1 para activar chequeo de memoria lento pero seguro

# --- COLORES ---
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

# --- LIMPIEZA INICIAL ---
rm -f $VALGRIND_LOG

# --- FUNCIÓN DE PRUEBA ---
run_test() {
    TEST_NAME="$1"
    INPUT="$2"

    echo -ne "Prueba: ${YELLOW}$TEST_NAME${RESET} -> Input: [$INPUT] ... "

    if [ $USE_VALGRIND -eq 1 ]; then
        echo "$INPUT" | valgrind --leak-check=full --show-leak-kinds=all --log-file=$VALGRIND_LOG $MINISHELL > /dev/null 2>&1
        RET=$?
        # Buscar errores en el log de valgrind
        LEAKS=$(grep "definitely lost:" $VALGRIND_LOG | grep -v "0 bytes in 0 blocks")
        ERRORS=$(grep "ERROR SUMMARY:" $VALGRIND_LOG | grep -v "0 errors")
        
        if [ $RET -eq 139 ]; then
            echo -e "${RED}[SEGFAULT]${RESET}"
        elif [ ! -z "$LEAKS" ] || [ ! -z "$ERRORS" ]; then
            echo -e "${RED}[LEAKS/ERRORS]${RESET}"
            grep "ERROR SUMMARY" $VALGRIND_LOG
        else
            echo -e "${GREEN}[OK]${RESET}"
        fi
    else
        # Ejecución normal (más rápida)
        echo "$INPUT" | $MINISHELL > /dev/null 2>&1
        RET=$?
        
        if [ $RET -eq 139 ]; then
            echo -e "${RED}[SEGFAULT]${RESET}"
        elif [ $RET -ne 0 ]; then
            echo -e "${RED}[CRASH/EXIT $RET]${RESET}"
        else
            echo -e "${GREEN}[OK]${RESET}"
        fi
    fi
}

# ==========================================
#              CASOS DE PRUEBA
# ==========================================

echo -e "${YELLOW}--- INICIANDO TESTER BASICO MINISHELL ---${RESET}"
echo "-----------------------------------------"

# 1. BASICO
run_test "Palabra simple" "ls"
run_test "Espacios" "   ls    -la   "
run_test "Tabulaciones" "	ls		-la	"
run_test "Comando vacío" ""

# 2. PIPES Y REDIRECCIONES (Tokenizer check)
run_test "Pipe simple" "ls | cat"
run_test "Pipe múltiple" "ls | grep a | wc -l"
run_test "Redirección in" "< archivo cat"
run_test "Redirección out" "ls > file"
run_test "Append" "ls >> file"
run_test "Heredoc" "cat << LIMIT"

# 3. COMILLAS (Quotes check)
run_test "Comillas dobles" "echo \"hola mundo\""
run_test "Comillas simples" "echo 'hola mundo'"
run_test "Comillas mixtas 1" "echo \"'hola'\""
run_test "Comillas mixtas 2" "echo '\"hola\"'"
run_test "Comillas sin cerrar (Debe fallar o manejarlo)" "echo \"hola"

# 4. EXPANSIONES (Expander check - LO NUEVO)
run_test "Variable simple" "echo $USER"
run_test "Variable con texto pegado" "echo valor=$USER"
run_test "Variable en comillas dobles" "echo \"Mi usuario es $USER\""
run_test "Variable en comillas simples (NO expandir)" "echo 'No expando $USER'"
run_test "Variable inexistente" "echo $VARIABLE_FALSA"
run_test "Signo dolar solo" "echo cuesta 5$"
run_test "Exit status" "echo $?"
run_test "Expansión complicada" "echo \"'$USER'\""

# 5. LISTA DE ENTORNO (Env check)
# Esto prueba si tu init_env revienta con muchas variables
run_test "Env" "env"

echo "-----------------------------------------"
echo -e "${GREEN}Test finalizado.${RESET}"