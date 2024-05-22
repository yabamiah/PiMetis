from flask import Flask, render_template, Response, request
import cv2
from pyngrok import ngrok
import threading

app = Flask(__name__)
video = cv2.VideoCapture(0)

@app.route('/')
def index():
    return render_template('index.html')

def gen():
    while True:
        _, frame = video.read()
        cv2.imwrite('t.jpg', frame)
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + open('t.jpg', 'rb').read() + b'\r\n')


@app.route('/video_feed')
def video_feed():
    return Response(gen(),mimetype='multipart/x-mixed-replace; boundary=frame')

def create_ngrok_server():
    http_tunnel = ngrok.connect(proto="http", addr="5000")
    with open("../servidor_link.txt", '+w') as file:
        file.write(http_tunnel.public_url)
    print(" * Link do servidor ngrok: \"{}\" -> \"http://127.0.0.1\"".format(http_tunnel.public_url))

if __name__ == '__main__':
    t1 = threading.Thread(target=create_ngrok_server)
    t1.start()
    t1.join()

    app.run()
    app.debug = True