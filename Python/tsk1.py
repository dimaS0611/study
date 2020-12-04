import numpy as np
import statistics as st
import matplotlib as plt
import random
import pylab
from datetime import datetime, timedelta

fig = pylab.gcf()
fig.canvas.set_window_title('Мой город')

for i in range(1,6):
    height = [random.random(),random.random(),random.random(),random.random(),random.random()]
    bars = ["Экол","Трансп","Образов","Энергет","Мед"]
    y_pos = np.arange(len(bars))

    pylab.subplot (2, 3, i)
    plt.pyplot.bar(y_pos, height)
    plt.pyplot.xticks(y_pos, bars)

    now = datetime.now() - timedelta(days = i-1)
    str = datetime.strftime(now, "%d.%m.%Y")
    plt.pyplot.title('Состояние на ' + str)

mng = plt.pyplot.get_current_fig_manager()
mng.resize(*mng.window.maxsize())
plt.pyplot.show()