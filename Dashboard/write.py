import MySQLdb
import serial


db = MySQLdb.connect("localhost","root","admin","Fi-city")

cursor = db.cursor()

arduino = serial.Serial('/dev/ttyACM0',baudrate=115200,timeout=8.0)
id = 0
while True:    
    line = arduino.readline()
    if line != '': 
       cursor.execute('''INSERT into temperature (id,data) values (%s,%s)''',(id,line))
       db.commit()
