#!/usr/bin/env python

from pymongo import MongoClient
import json, ast
import time as time_mod
from bokeh.plotting import figure, output_file, show
from bokeh.models import  LinearAxis, Range1d
import numpy as np

client = MongoClient('localhost', 27017)

db = client.DB-NAME             # SET THIS WITH YOUR DATABASE NAME
posts = db.COLLECTION-NAME      # SET THIS WITH YOUR COLLECTION NAME
posts_out = posts.find({'ident': '1'})  # SENSOR IDENT VAL TO PLOT

temps = []
times = []
humids = []
for post in posts_out:
    temps.append(post["temp"])
    times.append(post["time"])
    humids.append(post["humid"])
    print(post["time"])

spacefact = 0.3
mintemp = (np.floor(float(str(min(temps)))))
maxtemp = (np.ceil(float(str(max(temps)))))
tempdelta = maxtemp-mintemp
mintemp = int(mintemp-tempdelta*spacefact)
maxtemp = int(maxtemp+tempdelta*spacefact)

minhumid = (np.floor(float(str(min(humids)))))
maxhumid = (np.ceil(float(str(max(humids)))))
humiddelta = maxhumid-minhumid
minhumid = int(minhumid-humiddelta*spacefact)
maxhumid = int(maxhumid+humiddelta*spacefact)

print(mintemp)
print(maxtemp)

times_zse = [time - times[0] for time in times]

systime = time_mod.strftime("%H:%M:%S  %d/%m/%y")

# Begin BOKEH plotting code
output_file("test.html")

# Generate Figure
titlestr = "Enviromental Condition Plot, Generated: " + systime
p = figure(plot_width=800,plot_height=400,title=titlestr)

# Plotting Code
p.y_range=Range1d(mintemp,maxtemp)
p.line(times,temps, line_width=2, legend="Temperature", line_color="navy")

p.extra_y_ranges = {"humidrng": Range1d(start=minhumid, end=maxhumid)}
p.add_layout(LinearAxis(y_range_name="humidrng"), 'right')
p.line(times,humids, line_width=2, legend="Humidity", y_range_name="humidrng", line_color="olive")

p.xaxis.axis_label = "Unix Epoch Time"

show(p)
