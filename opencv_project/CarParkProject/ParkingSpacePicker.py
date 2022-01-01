'''
标注车位的 ROIs，保存这些 ROI 的矩形坐标 作为进一步处理的 先验分析
'''

import cv2
import pickle

# 先验确定 车位的矩形框大小
width, height = 107, 48

try:
    with open('CarParkPos', 'rb') as f:
        popList = pickle.load(f)
except:
    posList = []

def mouseClick(event, x, y, flags, params):
    # 鼠标左键 添加矩形框
    if event == cv2.EVENT_LBUTTONDOWN:
        posList.append((x, y))
    elif event == cv2.EVENT_RBUTTONDOWN:
        for i, pos in enumerate(posList):
            x1, y1 = pos
            if x1 < x < x1+width and y1 < y < y1 + height:
                posList.pop(i)

    # 保存 矩形框的先验坐标
    with open('CarParkPos', 'wb') as f:
        pickle.dump(posList, f)


while True:
    img = cv2.imread('carParkImg.png')

    for pos in posList:
        cv2.rectangle(img, (pos[0], pos[1]), (pos[0] + width, pos[1] + height), (255, 0, 255), 2)
    
    cv2.imshow("Image", img)
    cv2.setMouseCallback("Image", mouseClick)
    cv2.waitKey(10)