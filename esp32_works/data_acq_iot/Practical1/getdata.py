# -*- coding: utf-8 -*-
"""
Created on Sat Feb 10 23:27:00 2024
@author: Amal Nishantha Pattividana
Plot the temperature values and ADC value
"""

import mysql.connector
from mysql.connector import Error
import matplotlib.pyplot as plt
import numpy as np

plt.close("all")
try:
    mydb = mysql.connector.connect( host="localhost", user="root", password="", database="iot" )
    if mydb.is_connected():
        mycursor = mydb.cursor()
        mycursor.execute("SELECT `referance`.`time` AS `referance_time`, `referance`.`data_val` AS `referance_value`, `referance`.`device_id` AS `referance_device`, `device`.`time` AS `device_time`, `device`.`data_val` AS `device_value`, `device`.`device_id` AS `device` FROM `sensor_data_cali` AS `referance` INNER JOIN `sensor_data_cali` AS `device` ON (`referance`.`time`=SUBTIME(`device`.`time`,1) OR `referance`.`time`=`device`.`time`) AND `referance`.`device_id`='2024abc1232' AND `device`.`device_id`='2024abc1231';")
        myresult = mycursor.fetchall()
        xpoints = np.array([row[1] for row in myresult])   # DS18B20 Value in to temperature
        ypoints = np.array([row[4] for row in myresult])   # Row ADC Value
        
        plt.plot(xpoints, ypoints)
        plt.show()
except Error as e:
    print("Error while connecting to MySQL", e)
finally:
    if mydb.is_connected():
        mycursor.close()
        mydb.close()