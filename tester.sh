#!/bin/bash

# --- CONFIGURACIÓN ---
MINISHELL="./minishell"
VALGRIND_LOG="valgrind_out.log"
OUTPUT_MINI="out_mini.txt"
OUTPUT_BASH="out_bash.txt"
DIFF_FILE="diff.txt"

# --- COLORES ---
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"
BOLD="\033[1m"

# --- LIMPIEZA INICIAL ---
rm -f $VALGRIND_LOG $OUTPUT_MINI $OUTPUT_BASH $DIFF_FILE

# --- FUNCIÓN DE EJECUCIÓN ---
run_test() {
    TEST_DESC="$1"
    CMD="$2"

    echo -ne "Test: ${BLUE}$TEST_DESC${RESET} -> [ ${BOLD}$CMD${RESET} ] ... "

    # 1. Ejecutar en BASH (Referencia)
    # Usamos bash -c para replicar comportamiento de shell
    echo "$CMD" | bash > $OUTPUT_BASH 2>&1
    EXIT_BASH=$?

    # 2. Ejecutar en MINISHELL
    # Valgrind opcional (puedes activarlo descomentando o pasando flag)
    # echo "$CMD" | valgrind --leak-check=full --quiet --log-file=$VALGRIND_LOG $MINISHELL > $OUTPUT_MINI 2>&1
    
    # Ejecución normal para comparar output
    # OJO: Minishell imprime el prompt en stdout, hay que filtrarlo
    echo "$CMD" | $MINISHELL > $OUTPUT_MINI 2>&1
    EXIT_MINI=$?

    # Filtrar el prompt "Minishell$>" del output de minishell
    # Esto es necesario porque tu shell imprime el prompt
    grep -v "Minishell\$> " $OUTPUT_MINI > "${OUTPUT_MINI}.tmp" && mv "${OUTPUT_MINI}.tmp" $OUTPUT_MINI
    grep -v "exit" $OUTPUT_MINI > "${OUTPUT_MINI}.tmp" && mv "${OUTPUT_MINI}.tmp" $OUTPUT_MINI
    
    # Eliminar líneas vacías al inicio/final si es necesario (ajustar según tu minishell)
    sed -i '/^$/d' $OUTPUT_MINI 
    sed -i '/^$/d' $OUTPUT_BASH

    # 3. Comparar Salidas
    diff -w -B $OUTPUT_BASH $OUTPUT_MINI > $DIFF_FILE
    DIFF_RET=$?

    # 4. Mostrar Resultados
    if [ $DIFF_RET -eq 0 ]; then
        echo -e "${GREEN}[OK]${RESET}"
    else
        echo -e "${RED}[KO]${RESET}"
        echo -e "${YELLOW}--- Diferencias encontradas ---${RESET}"
        #cat $DIFF_FILE
        #echo -e "${YELLOW}--------------------------------${RESET}"
        echo -e "Esperado (Bash):\n----------"
        cat $OUTPUT_BASH
        echo -e "----------\nObtenido (Minishell):\n----------"
        cat $OUTPUT_MINI
        echo "----------"
    fi
}

echo -e "${BOLD}--- INICIANDO TESTER MEJORADO MINISHELL ---${RESET}"
echo "-------------------------------------------"

# Obtener rutas absolutas de binarios comunes
ls_path=$(which ls)
echo_path=$(which echo)
cat_path=$(which cat)
grep_path=$(which grep)
wc_path=$(which wc)
pwd_path=$(which pwd)
cd_path=$(which cd)

if [ -z "$ls_path" ] || [ -z "$echo_path" ]; then
    echo -e "${RED}Error: no se encontraron binarios básicos (ls, echo).${RESET}"
    exit 1
fi

echo -e "${YELLOW}[ BLOQUE 1: Rutas Absolutas (Sin Builtins) ]${RESET}"

# Test 1: ls simple
run_test "LS Simple" "$ls_path"

# Test 2: ls con flags
run_test "LS Long Format" "$ls_path -l"

# Test 3: echo simple (usando binary)
run_test "ECHO Simple" "$echo_path hola mundo"

# Test 4: argumentos con espacios
run_test "ECHO Espacios" "$echo_path 'hola      mundo'"

# Test 5: cat de archivo existente
run_test "CAT Archivo" "$cat_path Makefile"

echo -e "\n${YELLOW}[ BLOQUE 2: Nuevas Pruebas (PWD y CD) ]${RESET}"

# Test PWD
if [ -n "$pwd_path" ]; then
    run_test "PWD Absoluto" "$pwd_path"
    run_test "PWD en Pipe" "$pwd_path | $grep_path Documents"
else
    echo -e "${RED}No se encontró binario para 'pwd'. Saltando test.${RESET}"
fi


# Test CD: CD NO TIENE BINARIO ABSOLUTO.
# Como no tienes builtins, 'cd' fallará (command not found) en tu minishell.
# Bash sí lo ejecutará. Por tanto, este test dará KO si la salida de error difiere.
echo -e "${BLUE}Nota sobre CD: Como 'cd' es un builtin, necesitas implementarlo primero. Aquí probamos si se detecta (fallará si no existe).${RESET}"
run_test "CD intento (relativo)" "$cd_path /src"


echo -e "\n${YELLOW}[ BLOQUE 3: Pipes con Rutas Absolutas ]${RESET}"

# Test 6: pipe simple
run_test "Pipe Simple (ls | wc)" "$ls_path | $wc_path -l"

# Test 7: pipe doble
run_test "Pipe Doble (ls | grep | wc)" "$ls_path | $grep_path a | $wc_path -l"

# Test 8: pipe cat | grep
run_test "Cat | Grep" "$cat_path Makefile | $grep_path minishell"


echo -e "\n${YELLOW}[ BLOQUE 4: Errores y Casos Borde ]${RESET}"

# Test 9: comando no encontrado
run_test "Comando Inexistente" "/bin/cmd_fake"

# --- LIMPIEZA FINAL ---
rm -f $OUTPUT_MINI $OUTPUT_BASH $DIFF_FILE $VALGRIND_LOG

echo "-------------------------------------------"
echo -e "${GREEN}Test finalizado.${RESET}"
