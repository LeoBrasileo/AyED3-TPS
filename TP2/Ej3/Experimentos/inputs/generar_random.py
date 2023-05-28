import random

# Límite para x,y fijo en 10.000
# R fijo <= 10.000
# 

in_txt = input("nombre del txt\n")

U = input("Escribí el U\n")
while (int(U) > 10):
    U = input("U tiene que ser menor igual a 10. Probá otra vez\n")

V = input(f"Escribí el V, tiene que ser mayor igual a {U}\n")
while (int(V) < int(U) or int(V) > 10):
    V = input(f"V tiene que ser mayor igual a {U} y menor igual que 10. Probá otra vez\n")

R = input(f"Escribí el R\n")
while (int(R) > 10000):
    R = input(f"R tiene que ser menor igual que 10000. Probá otra vez\n")

file = open(f"{in_txt}.txt", "w")

C = input("Cuantos casos de test queres?\n")

file.write(f"{C}\n")


def generar_pares_unicos(n):
    pares = []

    while len(pares) < n:
        num1 = random.randint(0, n * 10)
        num2 = random.randint(0, n * 10)

        if [num1, num2] not in pares and [num2, num1] not in pares:
            pares.append([num1, num2])
            file.write(f"{num1} {num2}\n")


def generar_test(n, w):
    line = f"{n} {R} {w} {U} {V}\n"
    file.write(line)
    generar_pares_unicos(n)
    
elegidos = []

for i in range(int(C)):
    n = random.randint(0, 1000)
    # no repetimos numeros
    while (n in elegidos):
        n = random.randint(0, 1000)
    w = random.randint(0, n-1)
    #w = n-1
    elegidos.append(n)
    generar_test(n, w)

# while n < 1000:
#     w = 0
#     while w < n:
#         line = f"{n} {R} {w} {U} {V}\n"
#         file.write(line)
#         generar_pares_unicos(n)
#         w += 10
#     n += 10
