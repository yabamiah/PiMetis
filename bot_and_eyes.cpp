#include "teste_ia/pi_metis_eyes.hpp"
#include "teste_telegram/pi_metis_bot.hpp"

int main()
{
    telegram_bot tgbot("7132288406:AAGr8jjVtgQbD1VptDYure0pTn98EcohxBQ", "835554428");
    pi_metis_eyes pime;

    while (1)
    {
        std::cout << std::endl;
        if (person_counter >= 2)
        {   
            tgbot.send_warning();
        }

        if (object_counter != 0)
        {
            tgbot.send_text_message("Arma arma, perigo!!\n");
        }
    }
}