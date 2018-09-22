#!/usr/bin/env python

from pymongo import MongoClient
import json, ast
import time as time_mod
import csv

client = MongoClient('localhost', 27017)

db = client.DB-NAME             # REPLACE WITH DATABASE NAME
posts = db.COLLECTION-NAME      # REPLACE WITH COLLECITON NAME
numident = 1


# outputs a CSV for each sensor in numident
for i in range(numident):
    posts_out = posts.find({'ident': str(i)})

    temps = []
    times = []
    humids = []
    for post in posts_out:
        temps.append(post["temp"])
        times.append(post["time"])
        humids.append(post["humid"])

    times_zse = [time - times[0] for time in times]

    systime = time_mod.strftime("%H:%M:%S  %d/%m/%y")

    f = "enviroment_export" + str(i) + ".csv"
    c = csv.writer(open(f,"w"))
    rows = []
    rows.append(["Generated:",systime]);
    rows.append(["Unix Epoch Time","Sec Since Start","Temp/C","Humidity/%"])
    for i in range(len(times)):
        row = []
        row.append(times[i])
        row.append(times_zse[i])
        row.append(temps[i])
        row.append(humids[i])
        rows.append(row)

    c.writerows(rows)

