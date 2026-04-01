def entrada():
    import sys
    input = sys.stdin

    primera_linea = input.readline()
    N, M = map(int, primera_linea.strip().split())

    segunda_linea = input.readline()
    T = int(segunda_linea.strip())

    tercera_linea = input.readline()
    P = int(tercera_linea.strip())

    MatrizAdyacencia = []
    for i in range(N + 1):
        fila = [False] * (N + 1)
        MatrizAdyacencia.append(fila)

    Grados = []
    for i in range(N + 1):
        Grados.append(0)

    for i in range(M):
        linea_puente = input.readline()
        U, V = map(int, linea_puente.strip().split())
        MatrizAdyacencia[U][V] = True
        MatrizAdyacencia[V][U] = True
        Grados[U] += 1
        Grados[V] += 1

    return N, M, T, P, MatrizAdyacencia, Grados    

def grados (Grados, N):
    for i in range(1, N + 1):
        if Grados[i] % 2 != 0:
            return False
    return True

def conexos(MatrizAdyacencia, N):
    visitados = [False] * (N + 1)
   
    inicio = 1
    while inicio <= N and sum(MatrizAdyacencia[inicio]) == 0:
        inicio += 1
    if inicio > N:
        return False
    
    visitados[inicio] = True
    cambios = True

    while cambios:

        cambios = False

        for j in range(1, N + 1):
            if visitados[j]:
                for k in range(1, N + 1):
                    if MatrizAdyacencia[j][k] and not visitados[k]:
                        visitados[k] = True
                        cambios = True

    for i in range(1, N + 1):
        if sum(MatrizAdyacencia[i]) > 0 and not visitados[i]:
            return False
        
    return True

def puntes_faltantes(Grados, N, MatrizAdyacencia):

    impares = []

    for i in range(1, N + 1):
        if Grados[i] % 2 != 0:
            impares.append(i)

    pares_necesarios = len(impares) // 2

    posibles = 0

    emparejados = set()

    
    for i in impares:
        if i in emparejados:
            continue
        for j in impares:
            if i != j and j not in emparejados and MatrizAdyacencia[i][j]:
                posibles += 1
                emparejados.add(i)
                emparejados.add(j)
                break

    return pares_necesarios, posibles

def salida(Grados, N, MatrizAdyacencia, T, P):

    if grados(Grados, N) and conexos(MatrizAdyacencia, N):

        print("No es necesario hacer cambios")

    else:

        pares_necesarios, posibles = puntes_faltantes(Grados, N, MatrizAdyacencia)
        
        if pares_necesarios <= posibles and pares_necesarios * P <= T:
           
            if conexos(MatrizAdyacencia, N):

                print("Es posible modificar la ciudad")

            else:

                print("Debo presentar mi renuncia")

        else:

            print("Debo presentar mi renuncia")

if __name__ == "__main__":
    
    N, M, T, P, MatrizAdyacencia, Grados = entrada()
    salida(Grados, N, MatrizAdyacencia, T, P)