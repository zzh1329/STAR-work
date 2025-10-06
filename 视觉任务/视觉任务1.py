import cv2
import numpy as np

# 1. 读取图片
img = cv2.imread('test.jpg')

# 2. 转换颜色空间
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

# 3. 设置绿色范围
lower_green = np.array([30, 30, 30])
upper_green = np.array([90, 255, 255])

# 4. 创建绿色掩模
mask = cv2.inRange(hsv, lower_green, upper_green)

# 5. 找轮廓并计算重心
contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
for cnt in contours:
    M = cv2.moments(cnt)
    if M["m00"] != 0:
        cx = int(M["m10"] / M["m00"])
        cy = int(M["m01"] / M["m00"])
        print(f"重心: ({cx}, {cy})")
        cv2.circle(img, (cx, cy), 5, (0, 0, 255), -1)

# 6. 显示结果
cv2.imshow('Result', img)
cv2.waitKey(0)
cv2.destroyAllWindows()