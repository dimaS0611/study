from pillow import Image
from pygame import mixer
from datetime import datetime
from datetime import date

mixer.init()
X1 = [0.00, 0.01, 0.07, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]
X2 = [0.00, 0.41, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]
X3 = [0.00, 0.01, 0.00, 0.00, 0.07, 0.58, 0.65, 0.27, 0.00, 0.00]
V = ['норма', 'возгорание' ,'пожар']
max = -1
iter = 0
sost = V[0]

print ("******************************************")
print ("* Система наблюдения за реликтовой рощей *")
print ("******************************************")

def Date():
       today = date.today()
       print('Сегодня:', today)

Date()
now = datetime.now()

print ("Проверено : ", datetime.strftime(datetime.now(), "%Y.%m.%d %H:%M:%S"))

while True:
    var = int(input("Введите вариант развития события(1 2 3 (0 для выхода))"+"\n"))

    if var == 1:        
        for i,ii in enumerate(X1):
            if X1[i]>max:
                max = X1[i]
                iter = i 
        img = Image.open('ptkRel1.jpg')

        if max >=0.00 and max <= 0.35: 
            mixer.music.load('looking.mp3')           

        if max >=0.36 and max <= 0.60:
            sost = V[1]
            mixer.music.load('BPLA.mp3')

        if max >=0.61 and max <= 1.00:
            sost = V[2]            
            mixer.music.load('Fireman.mp3')            
        print("Состояние: ",sost)
        img.show()
        mixer.music.play()
    max = -1

    if var == 2:
        for i,ii in enumerate(X2):
            if X2[i]>max:
                max = X2[i]
                iter = i
        img = Image.open('ptkRel2.jpg')

        if max >=0.00 and max <= 0.35:
            mixer.music.load('looking.mp3')        

        if max >=0.36 and max <= 0.60:
            sost = V[1]
            mixer.music.load('BPLA.mp3')

        if max >=0.61 and max <= 1.00:
            sost = V[2]
            mixer.music.load('Fireman.mp3')
        print("Состояние: ",sost)
        img.show()
        mixer.music.play()
    max = -1    

    if var == 3:
        for i,ii in enumerate(X3):
            if X3[i]>max:
                max = X3[i]
                iter = i
        img = Image.open('ptkRel3.jpg')  

        if max >=0.00 and max <= 0.35:
            mixer.music.load('looking.mp3')        

        if max >=0.36 and max <= 0.60:
            sost = V[1]
            mixer.music.load('BPLA.mp3')

        if max >=0.61 and max <= 1.00:
            sost = V[2]
            mixer.music.load('Fireman.mp3')
        print("Состояние: ",sost)    
        max = -1
        img.show()
        mixer.music.play()

    if(var == 0):
        break    

    if(var != 1 and var != 2 and var != 3):
        print("Неверные данные")

print("Работа завершена")