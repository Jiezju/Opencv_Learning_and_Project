import cv2
import pickle
import numpy as np

# video feed
cap = cv2.VideoCapture('carPark.mp4')

# 加载先验 矩形框坐标
with open('CarParkPos', 'rb') as f:
    posList = pickle.load(f)

width, height = 107, 48

def checkParkingSpace(img, imProc):

    SpaceCounter = 0
    font = cv2.FONT_HERSHEY_SIMPLEX  # 定义字体

    for pos in posList:
        x, y = pos

        imgCrop = imProc[y:y+height, x:x+width]
        cv2.imshow(str(x*y), imgCrop)

        # 监测车位是否空余，采用区域像素个数
        count = cv2.countNonZero(imgCrop)

        # 添加文字 图像，文字内容， 坐标 ，字体，大小，颜色，字体厚度
        imgText1 = cv2.putText(img, str(count), (x, y+height - 5), font, color=(0, 255, 255), fontScale=0.8, thickness=2)
        cv2.imshow("imgText", imgText1)

        # 依据像素个数判断
        if count < 900:
            color = (0, 255, 0)
            thickness = 5
            SpaceCounter += 1
        else:
            color = (0, 0, 255)
            thickness = 2
        
        cv2.rectangle(img, pos, (pos[0] + width, pos[1] + height), color, thickness)

    imgText2 = cv2.putText(img, f'Free: {SpaceCounter} / {len(posList)}', (100, 50), font, color=(0, 200, 0), fontScale=2, thickness=5)
    cv2.imshow("imgText", imgText2)


while True:
    # 视频 循环播放
    if cap.get(cv2.CAP_PROP_POS_FRAMES) == cap.get(cv2.CAP_PROP_FRAME_COUNT):
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

    success, img = cap.read()

    # img preprocess
    imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    imgBlur = cv2.GaussianBlur(imgGray, (3, 3), 1)
    # 阈值分割前景（车辆）和背景
    imgThreshold = cv2.adaptiveThreshold(imgBlur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 25, 16)

    # 去除斑点
    imgMedian = cv2.medianBlur(imgThreshold, 5)

    # 加粗停车区域边缘
    kernel = np.ones((3, 3), np.uint8)
    imgDilate = cv2.dilate(imgMedian, kernel, iterations=1)

    checkParkingSpace(img, imgDilate)
    for pos in posList:
        cv2.rectangle(img, pos, (pos[0] + width, pos[1] + height), (255, 0, 255), 2)
    
    cv2.imshow("Image", img)
    cv2.imshow("ImageBlur", imgBlur)
    cv2.imshow("ImageThreshold", imgThreshold)
    cv2.waitKey(10)