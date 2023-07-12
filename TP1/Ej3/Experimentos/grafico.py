import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Leer los archivos CSV sin encabezado y ordenar por la columna "N"
df1 = pd.read_csv("runtimes/ordenados.csv", header=None, names=['n', 'time_ord'])
df1 = df1.sort_values(by='n')
df2 = pd.read_csv("runtimes/desordenados.csv", header=None, names=['n', 'time_not_ord'])
df2 = df2.sort_values(by='n')

# Crear la figura y los ejes
fig, ax = plt.subplots()

# Graficar los tiempos de ejecución de las insatancias ordenadas
ax.plot(df1['n'], df1['time_ord'], color='red', label='Ordenados')

# Graficar los tiempos de ejecución de las insatancias NO ordenadas
ax.plot(df2['n'], df2['time_not_ord'], color='green', label='No Ordenados')

# Configurar etiquetas de los ejes
plt.xlabel("Cantidad de actividades")
plt.ylabel("Tiempo de Ejecución")

# Mostrar leyenda
ax.legend()

# Mostrar una cuadrícula en el gráfico
ax.grid(True)

# Mostrar el gráfico
plt.show()
