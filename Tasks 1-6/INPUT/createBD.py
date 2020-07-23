#!/usr/bin/env python
#/usr/bin/python3
import  subprocess
from clickhouse_driver import Client

from sys import argv

fvnpnum, topic = argv

client = Client('localhost')

client.execute('DROP TABLE IF EXISTS Practice.condition')

client.execute('CREATE TABLE IF NOT EXISTS Practice.condition (param UInt64, ptime Float64) ENGINE = Memory')

subprocess.Popen(['python3', '/home/andrew/Practice_29-06-2020/mqttGetData.py', topic])#Отвечает считывание данных из mqtt и запись из в базу данных

#Дропаем таблицу в начале, а не в конце, так как она может понадобиться другим процессам
