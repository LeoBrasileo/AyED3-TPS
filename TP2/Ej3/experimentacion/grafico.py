import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Leer los archivos CSV sin encabezado y ordenar por la columna "N"
df1 = pd.read_csv("runtime_denso.csv", header=None, names=['n', 'time_algo_denso'])
df1 = df1.sort_values(by='n')
df2 = pd.read_csv("runtime_ralo.csv", header=None, names=['n', 'time_algo_ralo'])
df2 = df2.sort_values(by='n')

# Crear la figura y los ejes
fig, ax = plt.subplots()

# Graficar los tiempos de ejecución del algoritmo 1 en rojo
ax.plot(df1['n'], df1['time_algo_denso'], color='red', label='Algoritmo Denso')

# Graficar los tiempos de ejecución del algoritmo 2 en azul
ax.plot(df2['n'], df2['time_algo_ralo'], color='blue', label='Algoritmo Ralo')

# Configurar etiquetas de los ejes
plt.xlabel("N")
plt.ylabel("Tiempo de Ejecución")

# Mostrar leyenda
ax.legend()

# Mostrar una cuadrícula en el gráfico
ax.grid(True)

# Mostrar el gráfico
plt.show()
