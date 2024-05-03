import cv2

face_cascade = cv2.CascadeClassifier("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")
gun_cascade = cv2.CascadeClassifier("gun_haarcascade.xml")


imagem = cv2.imread('leo-sidearms18-lead.jpg')

imagem = cv2.resize(imagem, dsize=(500, 300))


cinza = cv2.cvtColor(imagem, cv2.COLOR_BGR2GRAY)
face = face_cascade.detectMultiScale(cinza, 1.1, minSize=(40, 40))


cinza = cv2.GaussianBlur(cinza, (21, 21), 0)
gun = gun_cascade.detectMultiScale(cinza, 1.3, 5, minSize = (100, 100))

for (x, y, w, h) in gun:
    cv2.rectangle(imagem, (x, y), (x + w, y + h), (255, 0, 0), 2)

for (x, y, w, h) in face:
    cv2.rectangle(imagem, (x, y), (x + w, y + h), (255, 255, 0), 2)

cv2.imshow('Imagem', imagem)
cv2.waitKey(0)

