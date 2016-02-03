#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  arduino.py
#
#  Copyright 2013 Antonio A. Scolari <scolari@ascolari.com>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#

import os
from prettytable import PrettyTable
#import serial
import pymysql

from socket import *
import time
address = ('10.221.21.109', 5000)
client_socket = socket(AF_INET, SOCK_DGRAM)
client_socket.settimeout(3)

def connectDB():
    global DB
    DB = pymysql.connect(host='localhost',
                        user='arduino',
                        password='arduino',
                        db='arduinodb')
    return

def disconnectDB():
    if DB:
        DB.close()
        return


def dbRackUpdate(RackName, RackStatus):
    try:
        connectDB()
        with DB.cursor() as cursor:
            sql = """UPDATE arduinodb.bioterio_01 SET RackStatus = %s
                    WHERE RackName = %s"""
            cursor.execute(sql, (RackStatus, RackName))
            DB.commit()
            sql = """UPDATE arduinodb.bioterio_01 SET ConnectionStatus = 1
                    WHERE RackName = %s"""
            cursor.execute(sql, (RackName))
            DB.commit()
            disconnectDB()
    finally:
        True


def ConStatUpdate(RackName, Node, Status):
    connectDB()
    if (RackName != "NULL"):
        try:
            with DB.cursor() as cursor:
                sql = """UPDATE arduinodb.bioterio_01 SET
                        ConnectionStatus = %s WHERE RackName = %s"""
                cursor.execute(sql, (Status, RackName))
                DB.commit()
                disconnectDB()
        finally:
            True
    elif (Node != "NULL"):
        try:
            with DB.cursor() as cursor:
                sql = """UPDATE arduinodb.bioterio_01 SET
                        ConnectionStatus = %s WHERE NodeNumber = %s"""
                cursor.execute(sql, (Status, Node))
                DB.commit()
                sql = """UPDATE arduinodb.bioterio_01 SET
                        RackStatus = 'UNKNOWN' WHERE NodeNumber = %s"""
                cursor.execute(sql, (Node))
                DB.commit()
                disconnectDB()
        finally:
            clearTable(Node)
            True


def clearTable(Node):
    connectDB()
    with DB.cursor() as cursor:
        try:
            sql = """SELECT RackName from arduinodb.bioterio_01 WHERE
                    NodeNumber = %s"""
            cursor.execute(sql, (Node))
            result = cursor.fetchone()
            sql = "update arduinodb." + result[0]
            sql += " set BinStatusBit = 3, BinStatus = 'UNKNOWN' where id>0"
            cursor.execute(sql)
            DB.commit()
            disconnectDB()
        finally:
            True


def AITUpdate(RackName, dStat):
    connectDB()
    try:
        with DB.cursor() as cursor:
            sql = "SELECT BinStatusBit from arduinodb."
            sql += RackName
            cursor.execute(sql)
            result = cursor.fetchall()
            i = 0
            while i <= 15:
                if (result[i][0] != dStat[i]):
                    if (dStat[i] == "0"):
                        BS = "CLEAR"
                    elif (dStat[i] == "1"):
                        BS = "ALARMED"
                    elif (dStat[i] == "2"):
                        BS = "ACKNOWLEDGE"
                    sql = "UPDATE arduinodb." + RackName
                    sql += """ SET BinStatusBit= %s, BinStatus = %s
                            WHERE AnalogInput = %s"""
                    cursor.execute(sql, (int(dStat[i]), BS, i))
                    DB.commit()
                i += 1
            disconnectDB()
            '''
            ###########################################################
            sql = "Select arduinodb." + Rackname
            sql += "_01 SET ConnectionStatus = %s WHERE RackName = %s"
            cursor.execute(sql, (Status,RackName))
            DB.commit()'''
    finally:
        #print("DataBase Updated")
        True


def dbprint(DB_Name):
    connectDB()
    try:
        with DB.cursor() as cursor:
            sql = "select * from arduinodb." + DB_Name
            cursor.execute(sql)
            rows = cursor.fetchall()
            columns = cursor.description
            desc = []
            for item in columns:
                desc.append(item[0])
            T = PrettyTable(desc)
            for row in rows:
                T.add_row([item for item in row])
            disconnectDB()
            print("\n\t\t\t")
            print(DB_Name)
            print(T)
            indexUpdate()
    finally:
        #DB.close()
        #return
        True

def indexUpdate():
    connectDB()
    try:
        with DB.cursor() as cursor:
            sql = "select * from arduinodb.bioterio_01"
            cursor.execute(sql)
            rows = cursor.fetchall()
            columns = cursor.description
            desc = []
            for item in columns:
                desc.append(item[0])
            T1 = PrettyTable(desc)
            for row in rows:
                T1.add_row([item for item in row])
            sql = "select * from arduinodb.B01R01"
            cursor.execute(sql)
            rows = cursor.fetchall()
            columns = cursor.description
            desc = []
            for item in columns:
                desc.append(item[0])
            T2 = PrettyTable(desc)
            for row in rows:
                T2.add_row([item for item in row])
        with open(os.path.join('templates', 'index.html'),'w') as f:
            f.write(T1.get_html_string())
            f.write("<p> </p>")
            f.write(T2.get_html_string())

            f.close()
        disconnectDB()
    finally:
        #DB.close()
        #return
        True


def main():
    #dbtest()
    #COM.flushInput()
    while (1):
        data = ""
        os.system("cls")
        dbprint("Bioterio_01")
        dbprint("B01R01")
        #data = COM.readline()
        RE = "Request"
        client_socket.sendto(RE.encode(), address)
        try:
            rec_data, addr = client_socket.recvfrom(2048)
            data = rec_data.decode()
            #print ("data= ",data)
            #time.sleep(3)
        except:
            #pass
            ConStatUpdate("NULL", 9, 0)
        if (data[0:2] == 'RE' and data[3] != 'a'):
            if (("1" in data[10:])):
                #print("ALARMED FROM DATA")
                #print(data[10:])
                #time.sleep(2)
                RackName = data[3:9]
                RackStatus = "ALARMED"
                dbRackUpdate(RackName, RackStatus)
                AITUpdate(RackName, data[10:])

            elif (("2" in data[10:]) and
                ("1" not in data[10:])):
                #print("ACKNOWLEDGE FROM DATA")
                #print(data[10:])
                #time.sleep(2)
                RackName = data[3:9]
                RackStatus = "ACKNOLEDGE"
                dbRackUpdate(RackName, RackStatus)
                AITUpdate(RackName, data[10:])

            elif (("1" not in data[10:]) and
                ("2" not in data[10:])):
                #print("CLEARED FROM DATA")
                #print(data[10:])
                #time.sleep(2)
                RackName = data[3:9]
                RackStatus = "CLEAR"
                dbRackUpdate(RackName, RackStatus)
                AITUpdate(RackName, data[10:])
        else:
            print(data)
            #time.sleep(2)
        #time.sleep(2)
    DB.close()
'''
        elif (data[7:-2] == b'ALARM TRIGGERED'):
            RackName = data[0:6].decode(encoding='UTF-8')
            RackStatus = "ALARMED"
            dbRackUpdate(RackName,RackStatus)'''
'''
        elif (data[7:-2] == b'CONNECTED'):
            #print(data[0:6].decode("utf-8"))
            #print(data[7:-2].decode("utf-8"))
            RackName = data[0:6].decode("utf-8")
            ConStatUpdate(RackName, "NULL", 1)
        elif (data[0:4] == b'Node'):
            Node = int(data[4:7].decode("utf-8"))
            #print(data[0:4].decode("utf-8"), " ", Node)
            #print(data[7:-2].decode("utf-8"))
            ConStatUpdate("NULL", Node, 0)
        else:
            print(data)
            time.sleep(2)
    DB.close()'''


if __name__ == '__main__':
    main()
