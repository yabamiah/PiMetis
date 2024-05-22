#!/bin/bash
#                      __    /_ __
#                _(_/_(_/(__/_)(_/(_
#                 _/_
#                (/

# Verifica se foram fornecidos argumentos
if [ $# -eq 0 ]; then
    echo "Uso: $0 <string1> <string2> ..."
    exit 1
fi

# Loop pelos argumentos fornecidos
for arg in "$@"; do
    # Define o nome do arquivo .hpp
    arquivo_hpp="${arg}.hpp" # Definição de variável

    # Verifica se o arquivo .hpp já existe
    if [ -e "$arquivo_hpp" ]; then
        echo "O arquivo '$arquivo_hpp' já existe. Pulando."
    else
        # Escreve o conteúdo no arquivo .hpp
        echo "#ifndef ${arg^^}_HPP" > "$arquivo_hpp"
        echo "#define ${arg^^}_HPP" >> "$arquivo_hpp"
        echo "" >> "$arquivo_hpp"
        echo "// Seu código aqui..." >> "$arquivo_hpp"
        echo "" >> "$arquivo_hpp"
        echo "#endif // ${arg^^}_HPP" >> "$arquivo_hpp"

        echo "Arquivo '$arquivo_hpp' criado com sucesso."
    fi

    # Define o nome do arquivo .cpp
    arquivo_cpp="${arg}.cpp"

    # Verifica se o arquivo .cpp já existe
    if [ -e "$arquivo_cpp" ]; then
        echo "O arquivo '$arquivo_cpp' já existe. Pulando."
    else
        # Escreve o conteúdo no arquivo .cpp
        echo "#include \"${arg}.hpp\"" > "$arquivo_cpp"
        echo "" >> "$arquivo_cpp"

        echo "Arquivo '$arquivo_cpp' criado com sucesso."
    fi
done
