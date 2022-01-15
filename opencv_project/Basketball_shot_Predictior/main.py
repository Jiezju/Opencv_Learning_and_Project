'''
篮球命中
'''

import cv2
import cvzone
from cvzone.ColorModule import ColorFinder
import numpy as np
import math

# initialize the video
cap = cv2.VideoCapture('./Files/Videos/vid (2).mp4')

# create the color Finder object
myColorFinder = ColorFinder(False)

hsvVals = {'hmin': 8, 'smin': 96, 'vmin': 115, 'hmax': 14, 'smax': 255, 'vmax': 255}

# Variables
posListX, posListY = [], []
# x 坐标
xList = list(range(1300))

while True:
    # Grab the image
    success, img = cap.read()

    # crop ROI
    img = img[:900, :]

    # Find the Color Ball
    imgColor, mask = myColorFinder.update(img, hsvVals)

    # Find laocation of the ball
    imgContours, countours = cvzone.findContours(img, mask, minArea=500)

    if countours:
        posListX.append(countours[0]['center'][0])
        posListY.append(countours[0]['center'][1])

    if posListX:
        # Polynominal Regression 轨迹预测 y = Ax^2 + Bx + C
        # find the Coefficients
        A, B, C = np.polyfit(posListX, posListY, 2)

        for i, (posX, posY) in enumerate(zip(posListX, posListY)):
            pos = (posX, posY)
            cv2.circle(imgContours, pos, 5, (0, 255, 0), cv2.FILLED)
            if i == 0:
                cv2.line(imgContours, pos, pos, (0, 255, 0), 2)
            else:
                cv2.line(imgContours, pos, (posListX[i - 1], posListY[i - 1]), (0, 255, 0), 2)

        for x in xList:
            y = int(A * x ** 2 + B * x + C)
            cv2.circle(imgContours, (x, y), 2, (255, 0, 255), cv2.FILLED)

        # 10 帧内进行检测
        prediction = False
        if len(posListX) < 10:
            # Prediction
            # X values 330 - 430 Y 590
            a = A
            b = B
            c = C - 590
            x = int(-b - math.sqrt(b ** 2 - 4 * a * c)) / (2 * a)
            prediction = 330 < x < 430

        if prediction:
            cvzone.putTextRect(imgContours, "Basket", (50, 150), scale=7, thickness=5, colorR=(0, 255, 0))
        else:
            cvzone.putTextRect(imgContours, "No Basket", (50, 150), scale=7, thickness=5, colorR=(0, 0, 255))

    # Display
    imgContours = cv2.resize(imgContours, (0, 0), None, 0.7, 0.7)
    # cv2.imshow("Image", img)
    cv2.imshow("ImageColor", imgContours)
    cv2.waitKey(50)
