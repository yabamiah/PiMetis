// #include <iostream>
// #include <fstream>
// #include <array>
// #include <memory>
// #include <regex>
// #include <unistd.h>

// // Função para criar o servidor ngrok
// void create_ngrok_server() {
//     printf("Olá");
//     system("ngrok http 5000 --log ngrok.log &");
    
    
//     // std::ifstream file("ngrok.log");
//     // std::string line;
//     // while (std::getline(file, line))
//     // {
//     //     if (line.find("url=") != std::string::npos)
//     //     {
//     //         std::string url = line.substr(line.find("url=") + 4, 66);
//     //         std::ofstream out("../servidor_link.txt");
//     //         out << url;
//     //         out.close();
//     //         std::cout << " * Link do servidor ngrok: \"" << url << "\" -> \"http://127.0.0.1:5000\"" << std::endl;        }
//     //         break;
//     // }

//     // file.close();   
// }

// void catch_server_link()
// {
//     printf("Catch_server_link");
//     std::ifstream file("ngrok.log");
//     std::string line;
//     while (std::getline(file, line))
//     {
//         if (line.find("url=") != std::string::npos)
//         {
//             std::string url = line.substr(line.find("url=") + 4, 66);
//             std::ofstream out("../servidor_link.txt");
//             out << url;
//             out.close();
//             std::cout << " * Link do servidor ngrok: \"" << url << "\" -> \"http://127.0.0.1:5000\"" << std::endl;        }
//             break;
//     }

//     file.close();  
// }

// int main() {

//     pid_t pid = fork();

//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0)
//     {
//         sleep(3);
//         catch_server_link();   
//     }
//     else
//     {
//         try 
//         {
//             create_ngrok_server();
//         } 
//         catch (const std::exception& ex) 
//         {
//             std::cerr << "Erro: " << ex.what() << std::endl;
//             return -1;
//         }
//     }   
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <regex>
#include <unistd.h>

// Função para criar o servidor ngrok
void create_ngrok_server() {
    std::cout << "Iniciando ngrok..." << std::endl;
    system("ngrok http 5000 --log=stdout > ngrok.log &");
    printf("PID = %d\n", getpid());
}

void catch_server_link() {
    std::cout << "Capturando link do servidor..." << std::endl;
    std::ifstream file;
    std::string line;
    std::regex url_regex(R"(https://[a-zA-Z0-9\-]+\.ngrok-free\.app)");
    std::smatch url_match;
    bool url_found = false;

    // Esperar até que o URL esteja disponível no arquivo de log
    while (!url_found) {
        file.open("ngrok.log");
        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (std::regex_search(line, url_match, url_regex)) {
                    std::string url = url_match[0];
                    std::ofstream out("../servidor_link.txt");
                    out << url;
                    out.close();
                    std::cout << " * Link do servidor ngrok: \"" << url << "\" -> \"http://127.0.0.1:5000\"" << std::endl;
                    url_found = true;
                    break;
                }
            }
            file.close();
        }
        break;
    }
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo filho: esperar e capturar o link do servidor
        sleep(5);  // Ajuste o tempo de espera conforme necessário
        catch_server_link();

        exit(EXIT_SUCCESS);
    } else {
        // Processo pai: iniciar o ngrok
        try {
            create_ngrok_server();
        } catch (const std::exception& ex) {
            std::cerr << "Erro: " << ex.what() << std::endl;
            return -1;
        }
    }
    return 0;
}
