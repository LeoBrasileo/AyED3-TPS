import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Leer los archivos CSV sin encabezado y ordenar por la columna "N"
df1 = pd.read_csv("runtime_basic.csv", header=None, names=['n', 'time_basic'])
df1 = df1.sort_values(by='n')
df2 = pd.read_csv("runtime_fibonacci.csv", header=None, names=['n', 'time_fibo'])
df2 = df2.sort_values(by='n')
df3 = pd.read_csv("runtime_minheap.csv", header=None, names=['n', 'time_heap'])
df3 = df3.sort_values(by='n')

# Crear la figura y los ejes
fig, ax = plt.subplots()

# Graficar los tiempos de ejecución del algoritmo 2 en azul
ax.plot(df2['n'], df2['time_fibo'], color='blue', label='Fibonacci Heap')

# Graficar los tiempos de ejecución del algoritmo 3 en verde
ax.plot(df3['n'], df3['time_heap'], color='green', label='Min Heap')

# Configurar etiquetas de los ejes
plt.xlabel("Cantidad de aristas (calles)")
plt.ylabel("Tiempo de Ejecución")

# Mostrar leyenda
ax.legend()

# Mostrar una cuadrícula en el gráfico
ax.grid(True)

# Mostrar el gráfico
plt.show()
