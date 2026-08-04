import serial
import time

# send time since epoch to arduino as string roughly every hour to sync the clock

ser = serial.Serial('COM4', 9600)
while True:
    ser.write(str(int(time.time())).encode('utf-8'))
    ser.write(b'\n')
    ser.flush()
    print("Sent time to Arduino:", str(int(time.time())))
    time.sleep(60*60)
