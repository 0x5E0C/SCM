import sensor, image, time
from pyb import *

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(10)
sensor.set_auto_exposure(False)
sensor.set_auto_whitebal(False,(-6.317097, -6.02073, -6.774588))
sensor.set_brightness(-3)

uart=UART(3,115200,timeout_char=1000)

red_threshold=(51, 9, 15, 88, -16, 66)#(82, 18, 40, 90, 3, 51)
yellow_threshold=(82, 13, -29, 55, 26, 68) #(82, 36, 2, 53, 29, 71)
blue_threshold=(68, 24, -34, 9, -59, 3)#(64, 19, -7, 28, -60, -26)
area=3500
time_out=120*1000


servo1 = Servo(1)
servo2 = Servo(2)

def send_finish_flag():
    uart.writechar(0xFF)
    delay(1)
    uart.writechar(0x46)
    delay(1)
    uart.writechar(0x23)
    delay(1)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

def open():
    servo1.angle(90)

def pick():
    servo1.angle(50)

def back():
    servo1.angle(-20)

def paddle_left():
    servo2.angle(50)

def paddle_right():
    servo2.angle(-20)

def paddle_middle():
    servo2.angle(0)

red_count=0
blue_count=0
yellow_count=0

open()
paddle_left()

while(uart.any()==0):
    img = sensor.snapshot()
sbuf=uart.read(3)

#sbuf=[0xff,0x02,0x23]
pick()
if(sbuf[0]==0xff and sbuf[2]==0x23):
    start=millis()
    if(sbuf[1]==0x01):
        while True:
            img = sensor.snapshot()
            red_blobs = img.find_blobs([red_threshold],area_threshold=area)
            if(red_blobs):
                back()
                paddle_left()
                delay(200)
                pick()
                red_count=red_count+1
                delay(200)
            if(red_count==10 or elapsed_millis(start)>time_out):
                break
    if(sbuf[1]==0x02):
        while True:
            img = sensor.snapshot()
            blue_blobs = img.find_blobs([blue_threshold],area_threshold=area)
            if(blue_blobs):
                back()
                paddle_left()
                delay(200)
                pick()
                blue_count=blue_count+1
                delay(200)
            if(blue_count==10 or elapsed_millis(start)>time_out):
                break
open()
delay(1000)
send_finish_flag()

