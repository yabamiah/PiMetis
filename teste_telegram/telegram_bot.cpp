#include "telegram_bot.hpp"

telegram_bot::telegram_bot(const std::string &token) 
    : token(token)
{
    this->url = this->url + token;

    this->chat_id = get_updates();
}

telegram_bot::telegram_bot(const std::string &token, const std::string& chat_id) 
    : token(token), chat_id(chat_id)
{
}

telegram_bot::~telegram_bot()
{
}

void telegram_bot::set_chatId(const std::string& chat_id)
{
    this->chat_id = chat_id;
}

std::string telegram_bot::get_updates() const
{
    std::string gp = "/getUpdates", chatId;
    
    cpr::Response r = cpr::Get(cpr::Url{this->url + gp});

    if (r.status_code == 200)
    {
        try 
        {
            nlohmann::json response = nlohmann::json::parse(r.text);

            if (response["ok"].get<bool>())
            {
                chatId = response["result"]["chat"]["id"];
            } 
            else
            {
                std::cerr << "Erro na resposta do Telegram: " << response.dump(4) << std::endl;
            }
        } catch (const nlohmann::json::parse_error& e) 
        {
            std::cerr << "Erro ao parsear JSON: " << e.what() << std::endl;
        }
    } 
    else
    {
        std::cerr << "Falha na requisição: " << r.status_code << std::endl;
    }

    return chatId;
}

void telegram_bot::send_text_message(const std::string& text_message)
{
    if (this->chat_id.empty())
    {
        std::cerr << "Nenhum usuário está cadastrado" << std::endl;
    } 
    else
    {
        std::string sm = "/sendMessage";

        cpr::Response r = cpr::Get(cpr::Url{this->url + sm}, 
                                   cpr::Parameters{{"chat_id", this->chat_id},
                                                   {"text", text_message}}); 

        if (r.status_code == 200)
        {
            std::cout << "Mensagem enviado com sucesso!" << std::endl;
        }
        else
        {
            std::cout << "Falha ao enviar mensagem: " << r.status_code << std::endl;
            std::cout << r.text << std::endl;
        }
    }
}

void telegram_bot::send_photo_message(const std::string& filename)
{
    if (this->chat_id.empty())
    {
        std::cerr << "Nenhum usuário está cadastrado" << std::endl;
    } 
    else
    {
        std::string sm = "/sendPhoto";
        cpr::Multipart multipart
        {
            {"chat_id", this->chat_id},
            {"photo", cpr::File{filename}}
        };

        cpr::Response r = cpr::Get(cpr::Url{this->url + sm}, multipart);

        if (r.status_code == 200)
        {
            std::cout << "Mensagem enviado com sucesso!" << std::endl;
        }
        else
        {
            std::cout << "Falha ao enviar mensagem: " << r.status_code << std::endl;
            std::cout << r.text << std::endl;
        }
    }
}

// std::vector<char> telegram_bot::read_file_to_vector(const std::string& filename) const
// {
//     std::ifstream file(filename, std::ios::binary | std::ios::ate);
//     if (!file.is_open())
//     {
//         throw std::runtime_error("Não foi possível abrir o arquivo.");
//     }

//     file.seekg(0, std::ios::end);
//     std::streamsize size = file.tellg();
//     file.seekg(0, std::ios::beg);

//     std::vector<char> buffer(size);

//     if (!file.read(buffer.data(), size)) 
//     {
//         throw std::runtime_error("Erro ao ler o arquivo.");
//     }

//     return buffer;
// }