from datetime import datetime
import requests
import time

link_server_path = "../servidor_link.txt"
TOKEN = "7132288406:AAGr8jjVtgQbD1VptDYure0pTn98EcohxBQ"
chat_id_jm = "1172156831"
chat_id_vn = "835554428"

link = ''
with open(link_server_path, 'r') as file :
    link = file.read()
img = open("wallhaven-2y9x5m.jpg", 'rb')

data_atual = time.strftime("%d/%m/%Y")
horario_atual = datetime.now().strftime("%H:%M:%S")
message = f"Data: {data_atual}\n\nHorário: {horario_atual}\n\nLink da transmissão: {link}"

# video = open("video.mp4", 'rb')

url1 = f"https://api.telegram.org/bot{TOKEN}/getUpdates"
url2 = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={chat_id_vn}&text={message}"
url3 = f"https://api.telegram.org/bot{TOKEN}/sendPhoto?chat_id={chat_id_vn}"

print(requests.get(url1).json())
# print(requests.post(url3, files={'photo': img}).json())