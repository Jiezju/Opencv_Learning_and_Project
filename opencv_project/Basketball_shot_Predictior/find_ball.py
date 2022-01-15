'''
基于 HSV 空间 查找 篮球位置
'''

import cv2
import cvzone
from cvzone.ColorModule import ColorFinder

# initialize the video
cap = cv2.VideoCapture('./Files/Videos/vid (1).mp4')

# create the color Finder object
myColorFinder = ColorFinder(True)
# best val {'hmin': 0, 'smin': 105, 'vmin': 0, 'hmax': 15, 'smax': 255, 'vmax': 255}
hsvVals = {'hmin': 8, 'smin': 124, 'vmin': 13, 'hmax': 24, 'smax': 255, 'vmax': 255}

while True:
    # Grab the image
    img = cv2.imread('Files/Ball.png')

    # crop ROI
    img = img[:900, :]

    # Find the Color Ball
    imgColor, mask = myColorFinder.update(img, hsvVals)
    
    # Display
    img = cv2.resize(img, (0,0), None, 0.7, 0.7)
    cv2.imshow("Image", img)
    cv2.imshow("ImageColor", imgColor)
    cv2.waitKey(50)