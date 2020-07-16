#!/usr/bin/env python
# -*- coding: utf-8 -*-
from clickhouse_driver import Client
import json

client = Client('localhost')

def paramPtime(jsonData, FVNPnum):
        #Parse Data
        json_Dict = json.loads(jsonData)
        param = json_Dict['param']
        ptime = json_Dict['ptime']

        ptQuery = '%s %d %s %f %s' % ('INSERT INTO Practice.condition (param, ptime) VALUES (', param, ', ', ptime, ')')

        client.execute(ptQuery)

def setData(Topic, jsonData, FVNPnum):
        paramPtime(jsonData, FVNPnum)
