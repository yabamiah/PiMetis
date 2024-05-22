import cv2, os

face_cascade = cv2.CascadeClassifier("/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt2.xml")
profile_face_cascade = cv2.CascadeClassifier("/usr/share/opencv4/haarcascades/haarcascade_profileface.xml")

# Inicializar webcam
cap = cv2.VideoCapture(0)

# Loop para leitura do conteúdo
while(not cv2.waitKey(20) & 0xFF == ord('q')):
        ret, frame = cap.read()

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        faces_frontal = face_cascade.detectMultiScale(gray, 1.1, minSize=(40, 40))
        print(len(faces_frontal))
        
        for x, y, w, h in faces_frontal:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0))

        # Visualizar
        cv2.imshow('frame',frame)

# Desligar a webcam
cap.release()

#Fechar janela do vídeo
cv2.destroyAllWindows()
cv2.waitKey(1)