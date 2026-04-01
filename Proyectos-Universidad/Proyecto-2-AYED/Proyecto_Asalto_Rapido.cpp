#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#define masa 10
#define gravedad 9.81
#define epsilon 1e-6

// Funciones de calculo

double distancia3D(double x1, double y1, double z1, double x2, double y2, double z2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

double EGravitacional(double Zinicial, double Zfinal){
    return masa * gravedad * (Zinicial - Zfinal);
}

double Wfriccion(double u, double desplazamiento){
    return u * masa * gravedad * desplazamiento;
}

double EFinal(double Einicial, double EG, double WF){
    return Einicial + EG - WF;

}

// Estructuras de datos

struct Datos{
    int nodoOrigen;
    int nodoDestino;
    double energiaInicial;
};

class Nodo{
    public:
       int ID;
       double x, y, z;
};

class Arista{
    public:
        int destino;
        double friccion;
        Arista* siguiente;
};

// estructuras para la cola de prioridad

struct NodoArbol{
    int id; // id del nodo
    double energia; // contador de energia acumulada
    double distancia; // distancia acumulada desde el nodo origen
    double cambioAltura; // cambio de altura acumulado desde el nodo origen
    NodoArbol* nodoDerecho; // puntero para poner los mejores nodos a la derecha
    NodoArbol* nodoIzquierdo; // puntero para poner los peores nodos a la izquierda
};

NodoArbol* crearNodoArbol(int id, double energia, double distanacia, double cambioAltura){

    NodoArbol* newNodo = new NodoArbol(); // creamos un puntero de tipo NodoArbol llamado newNodo

    newNodo -> id = id; // le asignamos el id
    newNodo ->energia = energia; // le asignamos la energia
    newNodo -> distancia = distanacia; // le asignamos la distancia
    newNodo -> cambioAltura = cambioAltura; // le asignamos el cambio de Altura
    newNodo -> nodoDerecho= NULL; // declaramos el nodoDerecho como Null
    newNodo -> nodoIzquierdo= NULL; // y lo mismo con el izquierdo

    return newNodo; // retornamos el nodo
}

class ColaPrioridad{
    public:
      NodoArbol* raiz; // raiz del arbol

      ColaPrioridad(){
        raiz = NULL;
      }

    void insertar(NodoArbol *&arbol, int id, double energia,double distancia, double cambioAltura){

        if(arbol == NULL){ 
            arbol = crearNodoArbol(id, energia, distancia, cambioAltura);
            return;
        }

        if(energia < arbol->energia - epsilon){

            insertar(arbol->nodoIzquierdo, id, energia, distancia, cambioAltura);

        } else if(energia > arbol->energia + epsilon){


            insertar(arbol->nodoDerecho, id, energia, distancia, cambioAltura);

        } else {

            if(distancia < arbol->distancia - epsilon){

                insertar(arbol->nodoDerecho, id, energia, distancia, cambioAltura);

            } else if(distancia > arbol->distancia + epsilon) {

                insertar(arbol->nodoIzquierdo, id, energia, distancia, cambioAltura);

            } else {


                if(cambioAltura < arbol->cambioAltura - epsilon){

                    insertar(arbol->nodoDerecho, id, energia, distancia, cambioAltura);

                } else {

                    insertar(arbol->nodoIzquierdo, id, energia, distancia, cambioAltura);
                }
            }
        }
    }

    NodoArbol* sacarMejor(NodoArbol *&arbol){

        if(arbol->nodoDerecho != NULL){
            return sacarMejor(arbol->nodoDerecho);
        } else {

            NodoArbol* mejor = arbol;
            arbol = arbol->nodoIzquierdo;
            return mejor;
        }
    }
};

// función para escribir el archivo de salida y función para escribir todas las energias con dos decimales

string to_TwoDecimal(double valor){
    long long valorRedondeado = round(valor * 100.0); 

    long long parteEntera = valorRedondeado / 100;
    long long parteDecimal = valorRedondeado % 100;

    string res= to_string(parteEntera) + ".";

    if(parteDecimal < 10){
        res += "0";
    }

    res += to_string(parteDecimal);

    return res;
}

void generarPath(int origen, int destino, double libreta1Energias[], int libreta2Caminos[], int numMision, int CV){
    
    string path = "path" + to_string(numMision) + ".out";

    ofstream archivo(path);

    if(!archivo.is_open()){
        cout << "Error al crear el archivo" << endl;
        return;
    }

    if(origen == destino) {
        
        archivo << origen << " " << destino << " " << to_TwoDecimal(libreta1Energias[origen]) << endl;
        archivo.close();
        return; 
    }

    if(libreta2Caminos[destino] != -1){

        archivo << to_TwoDecimal(libreta1Energias[destino]) << endl;
        int* caminoRecorrido = new int[CV + 1];
        int count = 0;
        int nodoActual = destino;

        while(nodoActual != -1){
            caminoRecorrido[count] = nodoActual;
            count++;
            nodoActual = libreta2Caminos[nodoActual];
        }

        for(int i = count -1; i > 0; i--){
            int nodoOrigen = caminoRecorrido[i];
            int nodoDestino = caminoRecorrido[i-1];

            archivo << nodoOrigen << " " << nodoDestino << " " << to_TwoDecimal(libreta1Energias[nodoOrigen]) << " " << to_TwoDecimal(libreta1Energias[nodoDestino]) << endl;

        }
        delete[] caminoRecorrido;

    } else {
        archivo << "-1" <<endl;
    }

    archivo.close(); 

}

//Mapa Umaril
class MapaUmaril{

    private:
        int CV;
        Nodo* nodos;
        Arista** caminos;

    public:

    MapaUmaril(int CV){

        this->CV = CV;
        nodos = new Nodo[CV+1];
        caminos = new Arista*[CV+1];
        
        for(int i = 0; i <= CV; i++){
            caminos[i] = nullptr;
        }
    }

    ~MapaUmaril(){
        
        for(int i = 0; i <= CV; i++){ // Recorremos cada conexión
            Arista* actual = caminos[i]; // Nos paramos en una
            while(actual != nullptr){ // Si no esta vacia
                Arista* lineaBorrar = actual; // guardamos ese valor en una variable temporal
                actual = actual->siguiente; // movemos actual a la siguiente conexión 
                delete lineaBorrar; // borramos el valor de actual
            }
        }

        delete[] caminos;
        delete[] nodos;
    }

    void setNodos(int ID, double x, double y, double z){ // para guardar los datos del nodo
        nodos[ID].ID = ID;
        nodos[ID].x = x;
        nodos[ID].y = y;
        nodos[ID].z = z; 
    }

    void agregarCamino(int origen, int destino, double friccion){

        Arista* nuevoCamino = new Arista();
        nuevoCamino->destino = destino; // al nuevo camino le asigno su nuevo destino
        nuevoCamino->friccion = friccion; // al nuevo camino le asigno su nueva fricción
        nuevoCamino->siguiente = caminos[origen]; // aqui insertamos el nuevo camino de primero 
        caminos[origen] = nuevoCamino;
    }

    void exploracion(ColaPrioridad& explorador, double libreta1Energias[], int libreta2Caminos[], int destino){
        
        while(explorador.raiz != nullptr){

            NodoArbol* arbolActual = explorador.sacarMejor(explorador.raiz);

            int id = arbolActual->id;
            double energia = arbolActual->energia;
            double distancia = arbolActual->distancia;
            double camAltura = arbolActual->cambioAltura;

            delete arbolActual;

            Arista* caminoActual = caminos[id];

            while(caminoActual != nullptr){
                int idVecino = caminoActual->destino;

                double disEntreNodos = distancia3D(nodos[id].x,nodos[id].y,nodos[id].z,nodos[idVecino].x, nodos[idVecino].y,nodos[idVecino].z);

                double egGravitacional = EGravitacional(nodos[id].z, nodos[idVecino].z);
                double wFriccion = Wfriccion(caminoActual->friccion,disEntreNodos);
                double energiaActual = EFinal(energia,egGravitacional,wFriccion); 

                if(energiaActual >= -epsilon && energiaActual > libreta1Energias[idVecino]){

                    if(fabs(energiaActual) < 1e-6) {
                       energiaActual = 0.0;
                    }

                    libreta1Energias[idVecino] = energiaActual;
                    libreta2Caminos[idVecino] = id;

                    double nuevaDistancia = distancia + 1;

                    double camAltuNew = camAltura;

                    if(nodos[id].z != nodos[idVecino].z){
                        camAltuNew++;
                    }
                    
                    explorador.insertar(explorador.raiz,idVecino,energiaActual,nuevaDistancia,camAltuNew);

                }

                caminoActual = caminoActual->siguiente;

            }
        }

    }

    void iniciarMision(int origen, int destino, double energia, int numMision){

        double* libreta1Energias = new double[CV + 1];
        int* libreta2Caminos = new int[CV + 1];

        for(int i = 0; i <=CV; i++){
            libreta1Energias[i] = -1;
            libreta2Caminos[i] = -1;
        }

        libreta1Energias[origen] = energia;

        if(origen == destino){
            
            generarPath(origen,destino, libreta1Energias, libreta2Caminos, numMision, CV);
            delete[] libreta1Energias;
            delete[] libreta2Caminos;
            return; 
        }

        ColaPrioridad explorador;

        explorador.insertar(explorador.raiz,origen,energia,0,0);

        exploracion(explorador, libreta1Energias, libreta2Caminos, destino);

        generarPath(origen, destino, libreta1Energias, libreta2Caminos, numMision, CV);

        delete[] libreta1Energias;
        delete[] libreta2Caminos;
    }
  
};

// función para leer y crear el mapa

MapaUmaril* cargarDatos(string nombreArchivo, Datos &mision){

    ifstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return nullptr; 
    }

    archivo >> mision.energiaInicial;
    archivo >> mision.nodoOrigen >> mision.nodoDestino;

    int CV, CA;
    archivo >> CV >> CA;

    MapaUmaril* mapa = new MapaUmaril(CV);

    int id;
    double x,y,z;

    for(int i = 0; i < CV; i++){
        archivo >> id >> x >> y >> z;
        mapa ->setNodos(id,x,y,z);
    }

    int origen, destino;
    double friccion;

    for(int i = 0; i < CA; i++){

        archivo>> origen >> destino >> friccion;
        mapa->agregarCamino(origen, destino, friccion);
        
    }

    archivo.close();
    return mapa;
}

int main(){

    int numMision;
    cin >> numMision;

    Datos mision;
    MapaUmaril* umaril = cargarDatos("data" + to_string(numMision) + ".in", mision);

    if(umaril != nullptr){

        umaril->iniciarMision(mision.nodoOrigen,mision.nodoDestino,mision.energiaInicial,numMision);

        delete umaril;

    }

    return 0;
}