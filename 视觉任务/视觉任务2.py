import cv2
import numpy as np

# 1. 打开视频
cap = cv2.VideoCapture('test.mp4')

while True:
    # 2. 读取每一帧
    ret, frame = cap.read()
    if not ret:
        break

    # 3. 识别绿色
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, np.array([30, 30, 30]), np.array([90, 255, 255]))

    # 4. 只显示绿色部分
    result = cv2.bitwise_and(frame, frame, mask=mask)

    # 5. 显示结果
    cv2.imshow('Green Only', result)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()