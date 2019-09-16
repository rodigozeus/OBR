import cv2
import numpy as np

direita = cv2.imread("direita.jpg")

#a função shape mostra a altura, largura e quantidade de cores de uma imagem
print (direita.shape)

#a função item lê um pixel específico (y, x) e diz o nível de cada cor 0 = blue, 1 = green, 2 = red
print (direita.item(0, 0, 1)) 

direita.itemset((0, 0, 2), 255)
direita.itemset((0, 0, 1), 0)
direita.itemset((0, 0, 0), 0)

bola = direita[180:250, 250:315]
cv2.imwrite("bola.jpg", bola)
direita[130:200, 200:265] = bola

cv2.imwrite("soccer3.jpg", direita)
