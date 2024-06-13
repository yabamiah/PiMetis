import cv2 as cv

Conf_threshold = 0.4
NMS_threshold = 0.4
COLORS = [(0, 255, 0), (0, 0, 255), (255, 0, 0),
          (255, 255, 0), (255, 0, 255), (0, 255, 255)]

nomes = []
with open('pimetis.names', 'r') as file:
    nomes = [nome.strip() for nome in file.readlines()]

net = cv.dnn.readNet('yolov4-tiny.weights', 'yolov4-tiny.cfg')

model = cv.dnn_DetectionModel(net)
model.setInputParams(size=(416, 416), scale=1/255, swapRB=True)

cap = cv.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if ret == False:
        break

    classes, scores, boxes = model.detect(frame, Conf_threshold, NMS_threshold)
    for (classid, score, box) in zip(classes, scores, boxes):
        color = COLORS[int(classid) % len(COLORS)]
        label = "%s : %f" % (nomes[classid], score)

        print(len(boxes))

        if nomes[classid] != "hide":
            cv.rectangle(frame, box, color, 1)
            cv.putText(frame, label, (box[0], box[1]-10),
                           cv.FONT_HERSHEY_COMPLEX, 0.3, color, 1)
        
    cv.imshow('frame', frame)
    key = cv.waitKey(1)
    if key == ord('q'):
        break
    
cap.release()
cv.destroyAllWindows()
