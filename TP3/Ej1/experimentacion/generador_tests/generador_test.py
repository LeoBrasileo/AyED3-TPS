import random

c = int(input("CANTIDAD DE CASOS DE TEST\n"))
nombre = input("NOMBRE DEL ARCHIVO (SIN EXTENSIÓN)\n")

with open(f"../test/{nombre}.txt", "w") as archivo:
    lineas = [f"{c}\n"]
    n_usado = []
    for i in range(c):
        N = random.randint(1, 10000)
        while N not in n_usado:
            N = random.randint(1, 10000)
            n_usado.append(N)


        #M = random.randint(1, 100000)

        k = random.randint(1, 300)
        s = random.randint(1, N)

        t = random.randint(1, N)
        while t==s:
            t = random.randint(1, N)


        lineas.append("{} {} {} {} {}\n".format(N,N,k,s,t))

        for calle in range(N):
            desde = random.randint(1, N)
            hasta = random.randint(1, N)
            longitud = random.randint(1, 1000)
            linea = "{} {} {}\n".format(desde, hasta, longitud)
            lineas.append(linea)

        for nuevas_calles in range(k):
            desde = random.randint(1, N)
            hasta = random.randint(1, N)
            longitud = random.randint(1, 1000)
            linea = "{} {} {}\n".format(desde, hasta, longitud)
            lineas.append(linea)

    archivo.writelines(lineas)
