import random

c = int(input("Cantidad de casos de test\n"))
nombre = input("Nombre de archivo\n")

with open(f"./{nombre}.txt", "w") as archivo:
    lineas = [f"{c}\n"]

    n_usado = set()
    for i in range(c):

        while True:
            N = random.randint(1, 20000)
            if N not in n_usado:
                n_usado.add(N)
                break

        lineas.append("{}\n".format(N))

        for j in range(N):
            inicio = random.randint(1, 2*N-1)
            fin = random.randint(inicio, 2*N-1)
            lineas.append("{} {}\n".format(inicio, fin))

    archivo.writelines(lineas)