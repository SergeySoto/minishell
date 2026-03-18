#!/bin/bash

# **************************************************************************** #
#                              COLORES                                         #
# **************************************************************************** #
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
RESET='\033[0m'
SUPP_FILE="$(cd "$(dirname "$0")" && pwd)/supresion.supp"
# **************************************************************************** #
#                              FUNCIONES                                       #
# **************************************************************************** #

print_header() {
    clear
    echo -e "${MAGENTA}"
    echo "╔══════════════════════════════════════════════════════════════════════════╗"
    echo "║                                                                          ║"
    echo "║   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗         ║"
    echo "║   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║         ║"
    echo "║   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║         ║"
    echo "║   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║         ║"
    echo "║   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████║    ║"
    echo "║   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝    ║"
    echo "║                                                                          ║"
    echo "╚══════════════════════════════════════════════════════════════════════════╝"
    echo -e "${RESET}"
}

print_menu() {
    echo -e "${CYAN}══════════════════════ MENÚ DE COMPILACIÓN ══════════════════════${RESET}"
    echo ""
    echo -e "  ${GREEN}[1]${RESET} make          ${WHITE}→${RESET} Compilar y ejecutar"
    echo -e "  ${GREEN}[2]${RESET} make re       ${WHITE}→${RESET} Recompilar y ejecutar"
    echo -e "  ${GREEN}[3]${RESET} make clean    ${WHITE}→${RESET} Limpiar objetos"
    echo -e "  ${GREEN}[4]${RESET} make fclean   ${WHITE}→${RESET} Limpiar todo"
    echo ""
    echo -e "${CYAN}═══════════════════════ CON VALGRIND ════════════════════════════${RESET}"
    echo ""
    echo -e "  ${YELLOW}[5]${RESET} make          ${WHITE}→${RESET} Compilar + Valgrind"
    echo -e "  ${YELLOW}[6]${RESET} make re       ${WHITE}→${RESET} Recompilar + Valgrind"
    echo -e "  ${YELLOW}[7]${RESET} make          ${WHITE}→${RESET} Compilar + Valgrind (sin supresiones)"
    echo ""
    echo -e "${CYAN}═══════════════════════════ OTROS ═══════════════════════════════${RESET}"
    echo ""
    echo -e "  ${BLUE}[8]${RESET} norminette    ${WHITE}→${RESET} Verificar norma"
    echo -e "  ${BLUE}[9]${RESET} tester        ${WHITE}→${RESET} Ejecutar tester.sh"
    echo ""
    echo -e "  ${RED}[0]${RESET} Salir"
    echo ""
    echo -e "${CYAN}═════════════════════════════════════════════════════════════════${RESET}"
}

print_separator() {
    echo -e "${BLUE}────────────────────────────────────────────────────────────────${RESET}"
}

run_command() {
    echo -e "${YELLOW}▶ Ejecutando:${RESET} $1"
    print_separator
    eval $1
    local status=$?
    print_separator
    if [ $status -eq 0 ]; then
        echo -e "${GREEN}✓ Comando completado exitosamente${RESET}"
    else
        echo -e "${RED}✗ El comando terminó con código: $status${RESET}"
    fi
    return $status
}

compile_and_run() {
    run_command "make"
    if [ $? -eq 0 ]; then
        echo ""
        echo -e "${GREEN}▶ Ejecutando minishell...${RESET}"
        print_separator
        ./minishell
    fi
}

recompile_and_run() {
    run_command "make re"
    if [ $? -eq 0 ]; then
        echo ""
        echo -e "${GREEN}▶ Ejecutando minishell...${RESET}"
        print_separator
        ./minishell
    fi
}

compile_valgrind() {
    run_command "make"
    if [ $? -eq 0 ]; then
        echo ""
        echo -e "${YELLOW}▶ Ejecutando con Valgrind (con supresiones)...${RESET}"
        print_separator
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions="$SUPP_FILE" ./minishell
    fi
}

recompile_valgrind() {
    run_command "make re"
    if [ $? -eq 0 ]; then
        echo ""
        echo -e "${YELLOW}▶ Ejecutando con Valgrind (con supresiones)...${RESET}"
        print_separator
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions="$SUPP_FILE" ./minishell
    fi
}

compile_valgrind_raw() {
    run_command "make"
    if [ $? -eq 0 ]; then
        echo ""
        echo -e "${YELLOW}▶ Ejecutando con Valgrind (SIN supresiones)...${RESET}"
        print_separator
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./minishell
    fi
}

run_norminette() {
    echo -e "${BLUE}▶ Ejecutando norminette...${RESET}"
    print_separator
    norminette src/ includes/ libft/
    print_separator
}

run_tester() {
    if [ -f "tester.sh" ]; then
        echo -e "${BLUE}▶ Ejecutando tester.sh...${RESET}"
        print_separator
        bash tester.sh
    else
        echo -e "${RED}✗ No se encontró tester.sh${RESET}"
    fi
}

wait_for_key() {
    echo ""
    echo -e "${WHITE}Presiona ENTER para continuar...${RESET}"
    read
}

# **************************************************************************** #
#                              MAIN                                            #
# **************************************************************************** #

while true; do
    print_header
    print_menu
    echo -ne "${WHITE}Selecciona una opción: ${RESET}"
    read option

    case $option in
        1)
            compile_and_run
            wait_for_key
            ;;
        2)
            recompile_and_run
            wait_for_key
            ;;
        3)
            run_command "make clean"
            wait_for_key
            ;;
        4)
            run_command "make fclean"
            wait_for_key
            ;;
        5)
            compile_valgrind
            wait_for_key
            ;;
        6)
            recompile_valgrind
            wait_for_key
            ;;
        7)
            compile_valgrind_raw
            wait_for_key
            ;;
        8)
            run_norminette
            wait_for_key
            ;;
        9)
            run_tester
            wait_for_key
            ;;
        0)
            echo -e "${GREEN}¡Hasta luego!${RESET}"
            exit 0
            ;;
        *)
            echo -e "${RED}Opción no válida${RESET}"
            sleep 1
            ;;
    esac
done
