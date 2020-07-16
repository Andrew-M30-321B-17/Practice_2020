#!/usr/bin/env python
# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt
from setDataToBDFromMqtt import setData

from sys import argv

# MQTT Settings
MQTT_Broker = "iot.eclipse.org"
MQTT_Port = 1883
Keep_Alive_Interval = 45
MQTT_Topic = argv

#Subscribe to all Sensors at Base Topic
def onConnect(mosq, obj, rc):
        mqttc.subscribe(MQTT_Topic, 0)

#Save Data into DB Table
def onMessage(mosq, obj, msg):
        print("MQTT Data Received...")
        print("MQTT Topic: " + msg.topic)
        print("Data: " + msg.payload)
        setData(msg.topic, msg.payload)

def onSubscribe(mosq, obj, mid, granted_qos):
    pass

mqttc = mqtt.Client()

# Assign event callbacks
mqttc.on_message = onMessage
mqttc.on_connect = onConnect
mqttc.on_subscribe = onSubscribe

# Connect
mqttc.connect(MQTT_Broker, int(MQTT_Port), int(Keep_Alive_Interval))

# Continue the network loop
mqttc.loop_forever()
