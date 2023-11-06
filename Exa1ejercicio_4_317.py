import multiprocessing

def calcular_serie(i):
    if i % 2 == 0:
        return (i // 2 + 1) ** 2 + 1
    else:
        return i + 1

if __name__ == "__main__":
    n = 100
    pool = multiprocessing.Pool(processes=4)  # Especifica el número de hilos aquí
    argumentos=[(i,) for i in range(n)]
    resultados = pool.starmap(calcular_serie, argumentos)
    pool.close()
    pool.join()
    print(argumentos)
    for resultados in resultados:
        print(resultados)
