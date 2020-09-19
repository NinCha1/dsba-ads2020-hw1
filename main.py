import pandas as pb
import matplotlib.pyplot as plt
import csv

t = []
a = []
b = []
c = []

with open('table.csv', newline='') as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
        t.append(int(row[0]))
        a.append(float(row[1]))
        b.append(float(row[2]))
        c.append(float(row[3]))

plt.plot(t, a, label='GSM')
plt.plot(t, b, label='DaC')
plt.plot(t, c, label='Karatsuba')
plt.title('Comparison of GSM, DaC and Karatsuba')
plt.legend()
plt.show()
