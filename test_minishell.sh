#!/bin/bash

# Fichier de test pour minishell

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compteurs
total_tests=0
failed_tests=0

# Fonction pour nettoyer la sortie du minishell
clean_output() {
    # Supprime le prompt et les lignes vides
    echo "$1" | sed 's/^minisHell-1\.0\$ //g' | sed '/^$/d'
}

# Fonction pour exécuter une commande et vérifier le résultat
run_test() {
    local description="$1"
    local command="$2"

    ((total_tests++))

    # Exécution dans minishell
    minishell_output=$(echo "$command" | ./minishell 2>&1)
    minishell_exit_code=$?
    
    # Nettoyage de la sortie du minishell
    cleaned_minishell_output=$(clean_output "$minishell_output")

    # Exécution dans bash
    bash_output=$(echo "$command" | bash 2>&1)
    bash_exit_code=$?

    # Comparaison plus flexible
    if ! diff <(echo "$cleaned_minishell_output") <(echo "$bash_output") >/dev/null 2>&1 || [ $minishell_exit_code -ne $bash_exit_code ]; then
        ((failed_tests++))
        echo -e "${RED}Test échoué: $description${NC}"
        echo "Commande: $command"
        echo "Sortie minishell (nettoyée):"
        echo "$cleaned_minishell_output"
        echo "Sortie bash:"
        echo "$bash_output"
        echo "Code de sortie minishell: $minishell_exit_code"
        echo "Code de sortie bash: $bash_exit_code"
        echo "-------------------"
    fi
}

# Tests de commandes simples
run_test "Echo simple" "echo Hello"
run_test "ls" "ls -l"
run_test "pwd" "pwd"
run_test "whoami" "whoami"
run_test "date" "date"
run_test "uname" "uname -a"

# Tests de variables d'environnement
run_test "Echo HOME" "echo \$HOME"
run_test "Echo PATH" "echo \$PATH"
run_test "Echo USER" "echo \$USER"
run_test "Export et echo" "export TEST=42 && echo \$TEST"
run_test "Multiple export" "export X=abc Y=123 && echo \$X \$Y"
run_test "Unset" "export TEST=42 && unset TEST && echo \$TEST"

# Tests de redirections
run_test "Redirection >" "echo test > tmp.txt && cat tmp.txt"
run_test "Redirection <" "echo 'Hello' > tmp.txt && cat < tmp.txt"
run_test "Redirection >>" "echo A > tmp.txt && echo B >> tmp.txt && cat tmp.txt"
run_test "Redirection 2>" "ls fichier_inexistant 2> tmp.txt && cat tmp.txt"
run_test "Redirection 2>&1" "ls fichier_inexistant > tmp.txt 2>&1 && cat tmp.txt"

# Tests de pipes
run_test "Pipe simple" "echo hello | tr a-z A-Z"
run_test "Double pipe" "echo hello | tr a-z A-Z | rev"
run_test "Pipe avec grep" "ls -l | grep .txt"
run_test "Pipe avec wc" "echo 'one two three' | wc -w"

# Tests de built-ins
run_test "cd et pwd" "cd /tmp && pwd"
run_test "cd -" "cd - && pwd"
run_test "cd ~" "cd ~ && pwd"
run_test "echo avec option -n" "echo -n test"
run_test "export sans argument" "export"
run_test "unset" "export TEST=42 && unset TEST && echo \$TEST"

# Tests d'erreurs
run_test "Commande inexistante" "commande_inexistante"
run_test "Fichier inexistant" "cat fichier_inexistant"
run_test "Permission denied" "touch tmp.txt && chmod 000 tmp.txt && ./tmp.txt"
run_test "cd dossier inexistant" "cd dossier_inexistant"

# Tests de quotes
run_test "Double quotes" "echo \"Hello World\""
run_test "Single quotes" "echo 'Hello World'"
run_test "Quotes mixtes" "echo \"L'apostrophe fonctionne\""
run_test "Quotes dans quotes" "echo 'Les \"guillemets\" fonctionnent'"

# Tests d'expansions
run_test "Expansion *" "echo *"
run_test "Expansion ~" "echo ~"
run_test "Expansion arithmétique" "echo \$((2 + 2))"
run_test "Expansion de commande" "echo \$(ls)"

# Tests de contrôle de flux
run_test "AND logique" "true && echo success"
run_test "OR logique" "false || echo failure"
run_test "Séquence" "echo A ; echo B"

# Tests de wildcards
run_test "Wildcard *" "touch a.txt b.txt && ls *.txt"
run_test "Wildcard ?" "touch a.txt ab.txt && ls a?.txt"
run_test "Wildcard []" "touch a.txt b.txt c.txt && ls [ab].txt"

# Tests de variables spéciales
run_test "Variable \$?" "false && echo \$?"
run_test "Variable \$0" "echo \$0"

# Tests de commandes avec arguments
run_test "mkdir et ls" "mkdir test_dir && ls -d test_dir"
run_test "touch et chmod" "touch test_file && chmod 755 test_file && ls -l test_file | cut -d' ' -f1"
run_test "rm" "touch test_file && rm test_file && ls test_file"

# Tests avancés
run_test "Pipe et redirection" "echo hello | tr a-z A-Z > tmp.txt && cat tmp.txt"
run_test "Multiples pipes" "echo hello | tr a-z A-Z | rev | tr A-Z a-z"
run_test "Redirection complexe" "echo error 2>&1 1>/dev/null | cat"
run_test "Expansion dans quotes" "echo \"Home is \$HOME\""
run_test "Commande entre parenthèses" "(echo A && echo B) | tr a-z A-Z"

# Tests supplémentaires potentiellement problématiques
run_test "Commande très longue" "echo $(printf 'A%.0s' {1..10000})"
run_test "Beaucoup de pipes" "echo hello | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
run_test "Redirection circulaire" "cat < <(cat < <(echo 'test'))"
run_test "Expansion de variables imbriquées" "A=1; B=A; C=B; echo \${!C}"
run_test "Commande avec caractères spéciaux" "echo \$'\\x41\\x42\\x43'"
run_test "Expansion de commande imbriquée" "echo \$(echo \$(echo \$(echo test)))"
run_test "Beaucoup de parenthèses" "( ( ( ( ( echo nested ) ) ) ) )"
run_test "Redirection multiple" "echo test > file1 > file2 > file3 && cat file3"
run_test "Heredoc avec expansion" "cat << EOF\n\$HOME\nEOF"
run_test "Commande avec beaucoup d'arguments" "echo $(printf 'arg%d ' {1..1000})"

# Tests avec beaucoup de pipes
run_test "Pipe long 1" "echo hello | rev | tr a-z A-Z | rev | tr A-Z a-z | wc -c | tr -d ' '"
run_test "Pipe long 2" "ls -l | grep . | sort | head -n 3 | tail -n 1 | awk '{print \$9}'"
run_test "Pipe long 3" "cat /etc/passwd | grep /home | cut -d: -f1 | sort | uniq -c | sort -nr | head -n 5"
run_test "Pipe très long" "echo 'test' | cat | grep t | sed 's/t/T/' | tr T t | rev | tr t T | sed 's/T/t/' | grep t | cat | wc -c"
run_test "Pipe avec commandes variées" "ls -l | grep '^d' | awk '{print \$9}' | sort -r | head -n 3 | xargs -I {} echo 'Directory: {}'"

# Nettoyage final
cleanup() {
    rm -f tmp.txt test_file a.txt b.txt c.txt ab.txt file1 file2 file3
    rm -rf test_dir
    # Supprimer tous les fichiers temporaires créés pendant les tests
    find . -maxdepth 1 -type f -name "tmp*" -delete
    find . -maxdepth 1 -type f -name "test*" -delete
}

# Exécuter le nettoyage à la fin du script et en cas d'interruption
trap cleanup EXIT INT TERM

# Affichage du résultat final
echo -e "${GREEN}Tests terminés.${NC}"
echo "Total des tests: $total_tests"
echo "Tests échoués: $failed_tests"

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}Tous les tests ont réussi !${NC}"
    exit 0
else
    echo -e "${RED}Certains tests ont échoué.${NC}"
    exit 1
fi