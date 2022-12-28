import serial
import time

arduino = serial.Serial(port='COM10', baudrate=115200, timeout=.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8')) # gửi data đến arduino
    time.sleep(0.05)
    data = arduino.readline() # nhận data từ arduino
    return data

while True:
    num = input("Enter a number: ")
    value = write_read(num)
    print(value)