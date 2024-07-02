#!/bin/bash
#                      __    /_ __
#                _(_/_(_/(__/_)(_/(_
#                 _/_
#                (/

if [ $# -eq 0 ]; then
    echo "Uso: $0 <string1> <string2> ..."
    exit 1
fi

for arg in "$@"; do
    arquivo_hpp="${arg}.hpp" # Definição de variável

    if [ -e "$arquivo_hpp" ]; then
        echo "O arquivo '$arquivo_hpp' já existe. Pulando."
    else
        echo "#ifndef ${arg^^}_HPP" > "$arquivo_hpp"
        echo "#define ${arg^^}_HPP" >> "$arquivo_hpp"
        echo "" >> "$arquivo_hpp"
        echo "// Seu código aqui..." >> "$arquivo_hpp"
        echo "" >> "$arquivo_hpp"
        echo "#endif // ${arg^^}_HPP" >> "$arquivo_hpp"

        echo "Arquivo '$arquivo_hpp' criado com sucesso."
    fi

    arquivo_cpp="${arg}.cpp"

    if [ -e "$arquivo_cpp" ]; then
        echo "O arquivo '$arquivo_cpp' já existe. Pulando."
    else
        echo "#include \"${arg}.hpp\"" > "$arquivo_cpp"
        echo "" >> "$arquivo_cpp"

        echo "Arquivo '$arquivo_cpp' criado com sucesso."
    fi
done
