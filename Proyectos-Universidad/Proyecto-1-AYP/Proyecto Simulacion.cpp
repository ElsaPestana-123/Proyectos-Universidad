#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string> 
using namespace std;
#define MAX 100

// Estructuras para el mapa y los semáforos

struct Mapa {
    int N,M,K; // N: Filas, M: Columnas, K tiempo de la simulación
    char Mapa[MAX][MAX]; // Mapa de la ciudad 
};

struct Semaforo {
    int i, j; // Posición del semáforo
    int N; // Cantidad del patrón (0: rojo, 1: verde)
    int inicio; // inicio del patron
    int Rn[MAX]; // Patrón del Semáforo (0: rojo, 1: verde)
    int Semaforo_actual; // Semáforo actual (índice del patrón)
};

// Clase Vehiculo que representa los vehículos en la simulación
class Vehiculo{

public:

    // Atributos de la clase Vehiculo

    int id; // Identificador del vehículo
    char tipo; // Tipo de vehículo ('A' para auto, 'M' para moto)
    int posicion_i, posicion_j; // Posición del vehículo en el mapa
    bool direccion_A; // Direccion de los autos (true: izquierda, false: derecha)
    bool direccion_M; // Direccion de las motos (true: arriba, false: abajo)
    int tiempo_Movimiento_A = 0; // Tiempo de movimiento del auto
    int tiempo_Movimiento_M = 0; // Tiempo de movimiento de la moto
    int tiempo_espera_A = 0; // Tiempo de espera del auto
    int tiempo_espera_M = 0; // Tiempo de espera de la moto
    int cambios_direccion_A = 0; // Contador de cambios de dirección del auto
    int cambios_direccion_M = 0; // Contador de cambios de dirección de la moto
    bool activo = true; // Verifica si el vehiculo esta activo o no
    int turno_choque = 0; // turno donde se produjo la colisión 

public:

    // Constructores de la clase.
   
    Vehiculo(int id, char tipo, int posicion_i, int posicion_j) {
        this->id = id;
        this->tipo = tipo;
        this->posicion_i = posicion_i;
        this->posicion_j = posicion_j;
        this->direccion_A = false;
        this->direccion_M = false;
        this->tiempo_Movimiento_A = 0;
        this->tiempo_Movimiento_M = 0;
        this->tiempo_espera_A = 0;
        this->tiempo_espera_M = 0;
        this->cambios_direccion_A = 0;
        this->cambios_direccion_M = 0;
        this->activo = true;
        this->turno_choque = 0;
        if (tipo == 'A') {
            direccion_A = true; // Auto: izquierda
        } else {
            direccion_M = true; // Moto: arriba
        }
    }

    Vehiculo() {
        id = 0;
        tipo = ' ';
        posicion_i = 0;
        posicion_j = 0;
        direccion_A = false;
        direccion_M = false;
        tiempo_Movimiento_A = 0;
        tiempo_Movimiento_M = 0;
        tiempo_espera_A = 0;
        tiempo_espera_M = 0;
        cambios_direccion_A = 0;
        cambios_direccion_M = 0;
        activo = true;
        turno_choque = 0;
        if (tipo == 'A') {
           direccion_A = true; // Auto: izquierda
        } else {
           direccion_M = true; // Moto: arriba
        } 
    }

    // Métodos de la clase Vehiculo

    void moverAuto(Mapa &mapa, Semaforo semaforos[], int num_semaforos, int turno, Vehiculo vehiculos[], int num_vehiculos) {

    if (!activo) return;

    int nueva_j;  // calcular la nueva posicion j (los autos se mueven en j/columna)

    if (direccion_A) {
        nueva_j = posicion_j - 1;
    } else {
        nueva_j = posicion_j + 1;
    }

    // Caso 1: Límites del mapa
    if (nueva_j < 0 || nueva_j >= mapa.M) {

        direccion_A = !direccion_A; 
        cambios_direccion_A++; 
        tiempo_espera_A++;

        return;
    }

    // Caso 2: Edificio enfrente
    if (mapa.Mapa[posicion_i][nueva_j] == 'E') {

        direccion_A = !direccion_A; 
        cambios_direccion_A++; 
        tiempo_espera_A++;

        return;
    }

    // Caso 3: Semáforo enfrente

    for (int i = 0; i < num_semaforos; i++) { // recorrer semaforos y ver si hay uno enfrente

        if (semaforos[i].i == posicion_i && semaforos[i].j == nueva_j) {

            int idx = semaforos[i].Semaforo_actual; // índice del patrón actual

            if (semaforos[i].Rn[idx] == 0) { // rojo

                tiempo_espera_A++;
                return;

            } else { // verde

                int occ = -1; // indice del vehiculo que ocupa la celda destino (si es -1 está libre)

                for (int j = 0; j < num_vehiculos; j++){

                    if (vehiculos[j].posicion_i == posicion_i && vehiculos[j].posicion_j == nueva_j) {
                        occ = j; // celda ocupada por el vehiculo j
                        break;
                    }
                }

                if (occ != -1) { // Celda ocupada

                    if (vehiculos[occ].tipo == 'M') {

                        // Colisión contra MOTO (activa o inactiva)
                        activo = false;

                        if (turno_choque == 0) {
                            turno_choque = turno + 1;
                        }

                        if (vehiculos[occ].activo) {
                            vehiculos[occ].activo = false;
                        }

                        if (vehiculos[occ].turno_choque == 0) {
                            vehiculos[occ].turno_choque = turno + 1;
                        }

                        tiempo_espera_A++;
                        vehiculos[occ].tiempo_espera_M++;

                        return;

                    } else { // Si son del mismo tipo, entonces el otro auto se convierte en un obstáculo

                        direccion_A = !direccion_A;
                        cambios_direccion_A++;
                        tiempo_espera_A++;
                        return;
                    }
                }
                // Celda libre
                posicion_j = nueva_j;
                tiempo_Movimiento_A++;
                return;
            }
        }
    }

    // Caso 4: No hay semáforo, verificar que la celda destino esté libre
    int occ = -1;

    for (int j = 0; j < num_vehiculos; j++){
        if (vehiculos[j].posicion_i == posicion_i && vehiculos[j].posicion_j == nueva_j) {
            occ = j;
            break;
        }
    }

    if (occ != -1) {

        if (vehiculos[occ].tipo == 'M') { // Colisión contra MOTO (activa o inactiva)

            activo = false;

            if (turno_choque == 0) {
                turno_choque = turno + 1;
            }

            if (vehiculos[occ].activo) {
                vehiculos[occ].activo = false;
            }

            if (vehiculos[occ].turno_choque == 0) {
                vehiculos[occ].turno_choque = turno + 1;
            }

            tiempo_espera_A++;
            vehiculos[occ].tiempo_espera_M++;

            return;

        } else {  // Si son del mismo tipo, entonces el otro auto se convierte en un obstáculo

            direccion_A = !direccion_A;
            cambios_direccion_A++;
            tiempo_espera_A++;

            return;
        }
    }

    // Caso 5: Celda libre
    posicion_j = nueva_j; tiempo_Movimiento_A++;
}

void moverMoto(Mapa &mapa, Semaforo semaforos[], int num_semaforos, int turno, Vehiculo vehiculos[], int num_vehiculos) {

    if (!activo) return;

    int nueva_i; // calcular la nueva posicion i (los autos se mueven en i/fila)

    if (direccion_M) {
        nueva_i = posicion_i - 1;
    } else {
        nueva_i = posicion_i + 1;
    }

    // Caso 1: Límites del mapa
    if (nueva_i < 0 || nueva_i >= mapa.N) {
        
        direccion_M = !direccion_M; 
        cambios_direccion_M++; 
        tiempo_espera_M++;

        return;
    }

    // Caso 2: Edificio enfrente

    if (mapa.Mapa[nueva_i][posicion_j] == 'E') {

        direccion_M = !direccion_M; 
        cambios_direccion_M++; 
        tiempo_espera_M++;

        return;
    }

    // Caso 3: Semáforo enfrente
    for (int i = 0; i < num_semaforos; i++) {

        if (semaforos[i].i == nueva_i && semaforos[i].j == posicion_j) {

            int idx = semaforos[i].Semaforo_actual; // índice del patrón actual

            if (semaforos[i].Rn[idx] == 0) { // rojo
                tiempo_espera_M++;
                return;
                
            } else { // verde

                int occ = -1; // indice del vehiculo que ocupa la celda destino (si es -1 está libre)

                for (int j = 0; j < num_vehiculos; j++) {
                    if (vehiculos[j].posicion_i == nueva_i && vehiculos[j].posicion_j == posicion_j) {
                        occ = j;
                        break;
                    }
                }

                if (occ != -1) {

                    if (vehiculos[occ].tipo == 'A') {
                        // Colisión contra AUTO (activo o inactivo)
                        activo = false;

                        if (turno_choque == 0) {
                            turno_choque = turno + 1;
                        }

                        if (vehiculos[occ].activo) {
                            vehiculos[occ].activo = false;
                        }

                        if (vehiculos[occ].turno_choque == 0) {
                            vehiculos[occ].turno_choque = turno + 1;
                        }
                        
                        tiempo_espera_M++;
                        vehiculos[occ].tiempo_espera_A++;

                        return;
                    } else { // Si son del mismo tipo, entonces la otra moto se convierte en un obstáculo
                        
                        direccion_M = !direccion_M; 
                        cambios_direccion_M++; 
                        tiempo_espera_M++;
                        return;
                    }
                }
                // Celda libre
                posicion_i = nueva_i; tiempo_Movimiento_M++;
                return;
            }
        }
    }

    // Caso 4: No hay semáforo, verificar que la celda destino esté libre
    int occ = -1;

    for (int j = 0; j < num_vehiculos; j++) {
        if (vehiculos[j].posicion_i == nueva_i && vehiculos[j].posicion_j == posicion_j) {
            occ = j;
            break;
        }
    }

    if (occ != -1) {
        if (vehiculos[occ].tipo == 'A') { // Colisión contra AUTO (activo o inactivo)
            activo = false;

            if (turno_choque == 0) {
                turno_choque = turno + 1;
            }

            if (vehiculos[occ].activo) {
                vehiculos[occ].activo = false;
            }

            if (vehiculos[occ].turno_choque == 0) {
                vehiculos[occ].turno_choque = turno + 1;
            }

            tiempo_espera_M++;
            vehiculos[occ].tiempo_espera_A++;
            return;

        } else { // Si son del mismo tipo, entonces la otra moto se convierte en un obstáculo

            direccion_M = !direccion_M; 
            cambios_direccion_M++; 
            tiempo_espera_M++;

            return;
        }
    }

    // Caso 5: Celda libre
    posicion_i = nueva_i; tiempo_Movimiento_M++;
  }

};

// Funciones de lectura y guardado de archivos

void leer_mapa(string mapa_archivo, Mapa &mapa) {

    ifstream archivo(mapa_archivo); // Abrir el archivo en modo lectura

    if (!archivo) { // Verificar si el archivo se abrió correctamente
        cerr << "Error al abrir el archivo del mapa." << endl;
        exit(EXIT_FAILURE);
    }
    
    archivo >> mapa.N >> mapa.M >> mapa.K; // Leer las dimensiones del mapa y el tiempo de simulación

    for (int i = 0; i < mapa.N; i++) {
        for (int j = 0; j < mapa.M; j++) {
            archivo >> mapa.Mapa[i][j]; // Leer el contenido del mapa y almacenarlo en una matriz de tipo mapa
        }
    }
   
    archivo.close();
}

void leer_semaforos(string semaforos_archivo, Semaforo semaforos[], int &num_semaforos){

    ifstream archivo(semaforos_archivo);
    if(!archivo) {
        cerr << "Error al abrir el archivo de semáforos." << endl;
        exit(EXIT_FAILURE);
    }

    num_semaforos = 0;

    while (archivo >> semaforos[num_semaforos].i
                   >> semaforos[num_semaforos].j
                   >> semaforos[num_semaforos].N
                   >> semaforos[num_semaforos].inicio) {

        for (int i = 0; i < semaforos[num_semaforos].N; ++i){
            archivo >> semaforos[num_semaforos].Rn[i];
        }

        int N = semaforos[num_semaforos].N; // Número de estados del semáforo
        int ini = semaforos[num_semaforos].inicio; // Valor inicial 
        semaforos[num_semaforos].inicio = ini - 1; 
        semaforos[num_semaforos].Semaforo_actual = semaforos[num_semaforos].inicio;

        num_semaforos++;
    }
}

void salida_mapa(Mapa &mapa){

    ofstream archivo("log_simulacion.out");

    if (!archivo) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return;
    }

    for (int i = 0; i < mapa.N; i++) {
        for (int j = 0; j < mapa.M; j++) {
            archivo << mapa.Mapa[i][j] << " ";
        }
        archivo << endl;
    }

    archivo.close();
}

void salida_estadisticas(Vehiculo vehiculos[], int num_vehiculos) {

    ofstream archivo("estadisticas.out");

    if (!archivo) {
        cerr << "Error al abrir el archivo de estadísticas." << endl;
        return;
    }

    for (int i = 0; i < num_vehiculos; i++) {

        archivo << vehiculos[i].id << " ";

        if (vehiculos[i].tipo == 'A') {
            
            archivo << "Auto ";
            archivo << vehiculos[i].tiempo_Movimiento_A << " ";
            archivo << vehiculos[i].tiempo_espera_A << " ";
            archivo << vehiculos[i].cambios_direccion_A << " ";
            archivo << vehiculos[i].turno_choque << endl;
            
        } else if (vehiculos[i].tipo == 'M') {

            archivo << "Moto ";
            archivo << vehiculos[i].tiempo_Movimiento_M << " ";
            archivo << vehiculos[i].tiempo_espera_M << " ";
            archivo << vehiculos[i].cambios_direccion_M << " ";
            archivo << vehiculos[i].turno_choque << endl;
        }
    }

    archivo.close();

}

// Funcion para hacer la simulacion

void simulacion(Mapa &mapa, Semaforo semaforos[], int num_semaforos, Vehiculo vehiculos[], int num_vehiculos) {

    char mapa_original[MAX][MAX]; // Mapa original 

    for (int i = 0; i < mapa.N; i++){ // Guardar el mapa original
        for (int j = 0; j < mapa.M; j++){
            mapa_original[i][j] = mapa.Mapa[i][j]; 
        }
    }

    // Simulación por K turnos
    for (int turno = 0; turno < mapa.K; turno++) {

        // Estado semáforos por turno
        for (int sem = 0; sem < num_semaforos; sem++){
            semaforos[sem].Semaforo_actual = (semaforos[sem].inicio + turno + semaforos[sem].N - 1) % semaforos[sem].N;
        }

        // Restaurar mapa base
        for (int i = 0; i < mapa.N; i++){
            for (int j = 0; j < mapa.M; j++){
                mapa.Mapa[i][j] = mapa_original[i][j];
            }
        }

        // Mover vehiculos activos
        for (int veh = 0; veh < num_vehiculos; veh++) {

            if (!vehiculos[veh].activo) 
            continue;

            if (vehiculos[veh].tipo == 'A')
                vehiculos[veh].moverAuto(mapa, semaforos, num_semaforos, turno, vehiculos, num_vehiculos);
            else
                vehiculos[veh].moverMoto(mapa, semaforos, num_semaforos, turno, vehiculos, num_vehiculos);
        }

        // Colisión simultánea (dos vehiculos activos terminan en misma celda en este turno)

        for (int i = 0; i < num_vehiculos; i++) {

            if (!vehiculos[i].activo) 
            continue;

            for (int j = i + 1; j < num_vehiculos; j++) {

                if (!vehiculos[j].activo) 
                continue;

                if (vehiculos[i].posicion_i == vehiculos[j].posicion_i && vehiculos[i].posicion_j == vehiculos[j].posicion_j) {

                    if ((vehiculos[i].tipo == 'A' && vehiculos[j].tipo == 'M') || (vehiculos[i].tipo == 'M' && vehiculos[j].tipo == 'A')) {

                        vehiculos[i].activo = false;
                        vehiculos[j].activo = false;

                        if (vehiculos[i].turno_choque == 0) 
                        vehiculos[i].turno_choque = turno + 1;

                        if (vehiculos[j].turno_choque == 0) 
                        vehiculos[j].turno_choque = turno + 1;

                        if (vehiculos[i].tipo == 'A') 
                        vehiculos[i].tiempo_espera_A++; 

                        else 
                        vehiculos[i].tiempo_espera_M++;

                        if (vehiculos[j].tipo == 'A') 
                        vehiculos[j].tiempo_espera_A++;

                        else 
                        vehiculos[j].tiempo_espera_M++;
                    }
                }
            }
        }

        // Acumular espera de inactivos desde el turno siguiente al choque
        for (int veh = 0; veh < num_vehiculos; veh++) {
            if (!vehiculos[veh].activo && vehiculos[veh].turno_choque > 0 && (turno + 1) > vehiculos[veh].turno_choque) {

                if (vehiculos[veh].tipo == 'A') 
                vehiculos[veh].tiempo_espera_A++;
                else                           
                vehiculos[veh].tiempo_espera_M++;
            }
        }

        // Pintar vehículos (activos e inactivos)
        for (int i = 0; i < num_vehiculos; i++) {
              
            bool esSemaforo = false;

            for (int j = 0; j < num_semaforos; j++) {

                if (semaforos[j].i == vehiculos[i].posicion_i && semaforos[j].j == vehiculos[i].posicion_j) { 
                    esSemaforo = true;
                    break; 
                }
                mapa.Mapa[vehiculos[i].posicion_i][vehiculos[i].posicion_j] = esSemaforo ? 'S' : vehiculos[i].tipo;
            }
        } 
    }

    salida_mapa(mapa);
    salida_estadisticas(vehiculos, num_vehiculos);
}

int main() {

    Mapa mapa;

    Semaforo semaforos[MAX];

    int totalSemaforos = 0;

    string archivo_mapa, archivo_semaforos;

    archivo_mapa = "mapa.in"; // Ruta del archivo del mapa
    leer_mapa(archivo_mapa, mapa);

    archivo_semaforos = "config_semaforos.in"; // Ruta del archivo de semáforos
    leer_semaforos(archivo_semaforos, semaforos, totalSemaforos);

    Vehiculo vehiculos[MAX];

    int num_vehiculos = 0;

    int id = 1; 

    for (int i = 0; i < mapa.N; i++) {
        for (int j = 0; j < mapa.M; j++) {

            if (mapa.Mapa[i][j] == 'A' || mapa.Mapa[i][j] == 'M') {

               vehiculos[num_vehiculos] = Vehiculo(id++, mapa.Mapa[i][j], i, j);

               mapa.Mapa[i][j] = 'C';

               num_vehiculos++;
           }
        }
    }

    simulacion(mapa, semaforos, totalSemaforos, vehiculos, num_vehiculos);

    return 0;
}