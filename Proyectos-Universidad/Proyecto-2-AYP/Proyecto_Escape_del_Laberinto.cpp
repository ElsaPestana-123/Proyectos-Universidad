// PRIMER PROYECTO DE ALGORITMO Y PROGRAMACION "ESCAPE DEL LABERINTO"

#include <iostream>
using namespace std;

char tipo1, tipo2, tipo3, tipo4, tipo5, tipo6, tipo7, tipo8, tipo9, tipo10, tipo11, tipo12, tipo13, tipo14, tipo15, tipo16, tipo17, tipo18, tipo19, tipo20;
char tipo21, tipo22, tipo23, tipo24, tipo25, tipo26, tipo27, tipo28, tipo29, tipo30, tipo31, tipo32, tipo33, tipo34, tipo35, tipo36, tipo37, tipo38, tipo39; 
char tipo40, tipo41, tipo42;

int x1_1, y1_1, x2_1, y2_1;  // Estas variables junto a las que estan arriba sirven para almacenar todos los datos que el usuario ingrese.
int x1_2, y1_2, x2_2, y2_2;  // Son 42 ya que segun las especificaciones del proyecto solo pueden haber 10 de cada tipo de datos (Portales, Muros, Tesoros, Trampas)
int x1_3, y1_3, x2_3, y2_3;  // y solo una entrada y una salida.
int x1_4, y1_4, x2_4, y2_4;
int x1_5, y1_5, x2_5, y2_5;
int x1_6, y1_6, x2_6, y2_6;
int x1_7, y1_7, x2_7, y2_7;
int x1_8, y1_8, x2_8, y2_8;
int x1_9, y1_9, x2_9, y2_9;
int x1_10, y1_10, x2_10, y2_10;
int x1_11, y1_11, x2_11, y2_11;
int x1_12, y1_12, x2_12, y2_12;
int x1_13, y1_13, x2_13, y2_13;
int x1_14, y1_14, x2_14, y2_14;
int x1_15, y1_15, x2_15, y2_15;
int x1_16, y1_16, x2_16, y2_16;
int x1_17, y1_17, x2_17, y2_17;
int x1_18, y1_18, x2_18, y2_18;
int x1_19, y1_19, x2_19, y2_19;
int x1_20, y1_20, x2_20, y2_20;
int x1_21, y1_21, x2_21, y2_21;
int x1_22, y1_22, x2_22, y2_22;
int x1_23, y1_23, x2_23, y2_23;
int x1_24, y1_24, x2_24, y2_24;
int x1_25, y1_25, x2_25, y2_25;
int x1_26, y1_26, x2_26, y2_26;
int x1_27, y1_27, x2_27, y2_27;
int x1_28, y1_28, x2_28, y2_28;
int x1_29, y1_29, x2_29, y2_29;
int x1_30, y1_30, x2_30, y2_30;
int x1_31, y1_31, x2_31, y2_31;
int x1_32, y1_32, x2_32, y2_32;
int x1_33, y1_33, x2_33, y2_33;
int x1_34, y1_34, x2_34, y2_34;
int x1_35, y1_35, x2_35, y2_35;
int x1_36, y1_36, x2_36, y2_36;
int x1_37, y1_37, x2_37, y2_37;
int x1_38, y1_38, x2_38, y2_38;
int x1_39, y1_39, x2_39, y2_39;
int x1_40, y1_40, x2_40, y2_40;
int x1_41, y1_41, x2_41, y2_41;
int x1_42, y1_42, x2_42, y2_42;

int muro_cont = 0;     // estas variables que estan aqui sirven para llevar un conteo de cuantos objetos de cada tipo hay en el laberinto
int tesoro_cont = 0;   // y evitar que excedan el numero establecido en el enunciado del proyecto.
int trampa_cont = 0;
int portal_cont = 0;
int entrada_cont = 0;
int salida_cont = 0;

void procesarElementos(int index, int &entrada_x, int &entrada_y){ // esta funcion sirve para procesar los elementos que el usuario ingrese y almacenarlos en las variables

    char tipo;
    int x1, y1, x2 = 0, y2 = 0;

    cin >> tipo;

    if (tipo == 'P'){
        cin >> x1 >> y1 >> x2 >> y2;
        //cout<<tipo<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

    } else if (tipo == '#' || tipo == 'E' || tipo == 'S' || tipo == 'T'|| tipo == 'X' || tipo == '.'){
        cin >> x1 >> y1;
        //cout<<tipo<<" "<<x1<<" "<<y1<<endl;                             
    }

    if (tipo == 'E'){
        entrada_x = x1;
        entrada_y = y1;
    }

    if (tipo != '#' && tipo != 'E' && tipo != 'S' && tipo != 'T' && tipo != 'X' && tipo != '.' && tipo != 'P'){ // aqui se verifica que los datos ingresados por el usuario sean validos
       // cout<<"Tipo de objeto no valido"<<endl;
        return;
    }

    if(tipo == '#'){    // aqui se verifica que no se exceda el numero de objetos de cada tipo
        muro_cont++;
        if(muro_cont > 10){
            //cout<<"No se pueden tener mas de 10 muros"<<endl;
            return;
        }

    } else if(tipo == 'T'){
        tesoro_cont++;
        if(tesoro_cont > 10){
           // cout<<"No se pueden tener mas de 10 tesoros"<<endl;
            return;
        }
    } else if(tipo == 'X'){
        trampa_cont++;
        if(trampa_cont > 10){
            //cout<<"No se pueden tener mas de 10 trampas"<<endl;
            return;
        }
    } else if(tipo == 'P'){
        portal_cont++;
        if(portal_cont > 10){
            //cout<<"No se pueden tener mas de 10 portales"<<endl;
            return;
        }
    } else if(tipo == 'E'){
        entrada_cont++;
        if(entrada_cont > 1){
            //cout<<"Solo puede haber una entrada"<<endl;
            return;
        }
    } else if(tipo == 'S'){
        salida_cont++;
        if(salida_cont > 1){
            //cout<<"Solo puede haber una salida"<<endl;
            return;
        }
    }

    switch (index) // aqui se almacenan los datos en las variables correspondientes
    {
    case 0:
        tipo1 = tipo; x1_1 = x1; y1_1 = y1; x2_1 = x2; y2_1 = y2;
        break;
    case 1:
        tipo2 = tipo; x1_2 = x1; y1_2 = y1; x2_2 = x2; y2_2 = y2;
        break;
    case 2:
        tipo3 = tipo; x1_3 = x1; y1_3 = y1; x2_3 = x2; y2_3 = y2;
        break; 
    case 3: 
        tipo4 = tipo; x1_4 = x1; y1_4 = y1; x2_4 = x2; y2_4 = y2;
        break;
    case 4:     
        tipo5 = tipo; x1_5 = x1; y1_5 = y1; x2_5 = x2; y2_5 = y2;
        break;
    case 5:
        tipo6 = tipo; x1_6 = x1; y1_6 = y1; x2_6 = x2; y2_6 = y2;
        break;
    case 6: 
        tipo7 = tipo; x1_7 = x1; y1_7 = y1; x2_7 = x2; y2_7 = y2;
        break;
    case 7: 
        tipo8 = tipo; x1_8 = x1; y1_8 = y1; x2_8 = x2; y2_8 = y2;
        break;
    case 8: 
        tipo9 = tipo; x1_9 = x1; y1_9 = y1; x2_9 = x2; y2_9 = y2;
        break;
    case 9: 
        tipo10 = tipo; x1_10 = x1; y1_10 = y1; x2_10 = x2; y2_10 = y2;
        break;   
    case 10: 
        tipo11 = tipo; x1_11 = x1; y1_11 = y1; x2_11 = x2; y2_11 = y2;
        break;
    case 11:
        tipo12 = tipo; x1_12 = x1; y1_12 = y1; x2_12 = x2; y2_12 = y2;
        break;
    case 12:
        tipo13 = tipo; x1_13 = x1; y1_13 = y1; x2_13 = x2; y2_13 = y2;
        break;
    case 13:
        tipo14 = tipo; x1_14 = x1; y1_14 = y1; x2_14 = x2; y2_14 = y2;
        break;
    case 14:
        tipo15 = tipo; x1_15 = x1; y1_15 = y1; x2_15 = x2; y2_15 = y2;
        break;
    case 15:
        tipo16 = tipo; x1_16 = x1; y1_16 = y1; x2_16 = x2; y2_16 = y2;
        break;
    case 16:
        tipo17 = tipo; x1_17 = x1; y1_17 = y1; x2_17 = x2; y2_17 = y2;
        break;
    case 17:
        tipo18 = tipo; x1_18 = x1; y1_18 = y1; x2_18 = x2; y2_18 = y2;
        break;
    case 18:
        tipo19 = tipo; x1_19 = x1; y1_19 = y1; x2_19 = x2; y2_19 = y2;
        break;
    case 19:
        tipo20 = tipo; x1_20 = x1; y1_20 = y1; x2_20 = x2; y2_20 = y2;
        break;
    case 20:
        tipo21 = tipo; x1_21 = x1; y1_21 = y1; x2_21 = x2; y2_21 = y2;
        break;
    case 21:
        tipo22 = tipo; x1_22 = x1; y1_22 = y1; x2_22 = x2; y2_22 = y2;
        break;
    case 22:
        tipo23 = tipo; x1_23 = x1; y1_23 = y1; x2_23 = x2; y2_23 = y2;
        break;
    case 23:
        tipo24 = tipo; x1_24 = x1; y1_24 = y1; x2_24 = x2; y2_24 = y2;
        break;
    case 24:
        tipo25 = tipo; x1_25 = x1; y1_25 = y1; x2_25 = x2; y2_25 = y2;
        break;
    case 25:
        tipo26 = tipo; x1_26 = x1; y1_26 = y1; x2_26 = x2; y2_26 = y2;
        break;
    case 26:
        tipo27 = tipo; x1_27 = x1; y1_27 = y1; x2_27 = x2; y2_27 = y2;
        break;
    case 27:
        tipo28 = tipo; x1_28 = x1; y1_28 = y1; x2_28 = x2; y2_28 = y2;
        break;
    case 28:
        tipo29 = tipo; x1_29 = x1; y1_29 = y1; x2_29 = x2; y2_29 = y2;
        break;
    case 29:
        tipo30 = tipo; x1_30 = x1; y1_30 = y1; x2_30 = x2; y2_30 = y2;
        break;
    case 30:
        tipo31 = tipo; x1_31 = x1; y1_31 = y1; x2_31 = x2; y2_31 = y2;
        break;
    case 31:
        tipo32 = tipo; x1_32 = x1; y1_32 = y1; x2_32 = x2; y2_32 = y2;
        break;
    case 32:
        tipo33 = tipo; x1_33 = x1; y1_33 = y1; x2_33 = x2; y2_33 = y2;
        break;
    case 33:
        tipo34 = tipo; x1_34 = x1; y1_34 = y1; x2_34 = x2; y2_34 = y2;
        break;
    case 34:
        tipo35 = tipo; x1_35 = x1; y1_35 = y1; x2_35 = x2; y2_35 = y2;
        break;
    case 35:
        tipo36 = tipo; x1_36 = x1; y1_36 = y1; x2_36 = x2; y2_36 = y2;
        break;
    case 36:
        tipo37 = tipo; x1_37 = x1; y1_37 = y1; x2_37 = x2; y2_37 = y2;
        break;
    case 37:
        tipo38 = tipo; x1_38 = x1; y1_38 = y1; x2_38 = x2; y2_38 = y2;
        break;
    case 38:
        tipo39 = tipo; x1_39 = x1; y1_39 = y1; x2_39 = x2; y2_39 = y2;
        break;
    case 39:
        tipo40 = tipo; x1_40 = x1; y1_40 = y1; x2_40 = x2; y2_40 = y2;
        break;
    case 40:
        tipo41 = tipo; x1_41 = x1; y1_41 = y1; x2_41 = x2; y2_41 = y2;
        break;
    case 41:
        tipo42 = tipo; x1_42 = x1; y1_42 = y1; x2_42 = x2; y2_42 = y2;
        break;                            
    }
}

bool recorrer_lab(char tipo_buscar, int x, int y){ // esta funcion sirve para recorrer el laberinto y verificar si el jugador se encuentra en una posicion valida, regresa un valor de true o false

    if (tipo1 == tipo_buscar && x1_1 == x && y1_1 == y){
        return true;
    } else if(tipo2 == tipo_buscar && x1_2 == x && y1_2 == y){
        return true;
    } else if (tipo3 == tipo_buscar && x1_3 == x && y1_3 == y) {
        return true;
    } else if (tipo4 == tipo_buscar && x1_4 == x && y1_4 == y) {
        return true;
    } else if (tipo5 == tipo_buscar && x1_5 == x && y1_5 == y) {
        return true;
    } else if (tipo6 == tipo_buscar && x1_6 == x && y1_6 == y) {
        return true;
    } else if (tipo7 == tipo_buscar && x1_7 == x && y1_7 == y) {
        return true;
    } else if (tipo8 == tipo_buscar && x1_8 == x && y1_8 == y) {
        return true;
    } else if (tipo9 == tipo_buscar && x1_9 == x && y1_9 == y) {
        return true;
    } else if (tipo10 == tipo_buscar && x1_10 == x && y1_10 == y) {
        return true;
    } else if (tipo11 == tipo_buscar && x1_11 == x && y1_11 == y) {
        return true;
    } else if (tipo12 == tipo_buscar && x1_12 == x && y1_12 == y) {
        return true;
    } else if (tipo13 == tipo_buscar && x1_13 == x && y1_13 == y) {
        return true;
    } else if (tipo14 == tipo_buscar && x1_14 == x && y1_14 == y) {
        return true;
    } else if (tipo15 == tipo_buscar && x1_15 == x && y1_15 == y) {
        return true;
    } else if (tipo16 == tipo_buscar && x1_16 == x && y1_16 == y) {
        return true;
    } else if (tipo17 == tipo_buscar && x1_17 == x && y1_17 == y) {
        return true;
    } else if (tipo18 == tipo_buscar && x1_18 == x && y1_18 == y) {
        return true;
    } else if (tipo19 == tipo_buscar && x1_19 == x && y1_19 == y) {
        return true;
    } else if (tipo20 == tipo_buscar && x1_20 == x && y1_20 == y) {
        return true;
    } else if (tipo21 == tipo_buscar && x1_21 == x && y1_21 == y) {
        return true;
    } else if (tipo22 == tipo_buscar && x1_22 == x && y1_22 == y) {
        return true;
    } else if (tipo23 == tipo_buscar && x1_23 == x && y1_23 == y) {
        return true;
    } else if (tipo24 == tipo_buscar && x1_24 == x && y1_24 == y) {
        return true;
    } else if (tipo25 == tipo_buscar && x1_25 == x && y1_25 == y) {
        return true;
    } else if (tipo26 == tipo_buscar && x1_26 == x && y1_26 == y) {
        return true;
    } else if (tipo27 == tipo_buscar && x1_27 == x && y1_27 == y) {
        return true;
    } else if (tipo28 == tipo_buscar && x1_28 == x && y1_28 == y) {
        return true;
    } else if (tipo29 == tipo_buscar && x1_29 == x && y1_29 == y) {
        return true;
    } else if (tipo30 == tipo_buscar && x1_30 == x && y1_30 == y) {
        return true;
    } else if (tipo31 == tipo_buscar && x1_31 == x && y1_31 == y) {
        return true;
    } else if (tipo32 == tipo_buscar && x1_32 == x && y1_32 == y) {
        return true;
    } else if (tipo33 == tipo_buscar && x1_33 == x && y1_33 == y) {
        return true;
    } else if (tipo34 == tipo_buscar && x1_34 == x && y1_34 == y) {
        return true;
    } else if (tipo35 == tipo_buscar && x1_35 == x && y1_35 == y) {
        return true;
    } else if (tipo36 == tipo_buscar && x1_36 == x && y1_36 == y) {
        return true;
    } else if (tipo37 == tipo_buscar && x1_37 == x && y1_37 == y) {
        return true;
    } else if (tipo38 == tipo_buscar && x1_38 == x && y1_38 == y) {
        return true;
    } else if (tipo39 == tipo_buscar && x1_39 == x && y1_39 == y) {
        return true;
    } else if (tipo40 == tipo_buscar && x1_40 == x && y1_40 == y) {
        return true;
    } else if (tipo41 == tipo_buscar && x1_41 == x && y1_41 == y) {
        return true;
    } else if (tipo42 == tipo_buscar && x1_42 == x && y1_42 == y) {
        return true;
    }
    return false;
}

void moviento_del_jugador(int &x_jugador, int &y_jugador, int N, int M, char movimiento){ // esta funcion sive para mover al jugador en el laberinto

          if(movimiento == 'w'){  // como el laberinto solamente puede estar conformado de numeros positivos con estas condiciones se verifica que el jugador no se salga del laberinto
                                  // ademas de cumplir con la w, a, s, d que son las teclas que el usuario puede usar para moverse y que se muevan en la direccion correcta
            if(y_jugador > 0){    
            y_jugador--;
            }

          } else if(movimiento == 'a'){
           
            if(x_jugador > 0){
            x_jugador--;
            }

          } else if(movimiento == 's'){
            
            if(y_jugador < M-1){
            y_jugador++;
            } 

         } else if(movimiento == 'd'){

            if(x_jugador < N-1){
            x_jugador++;
            }

         }

         
}

int main(){
    
    int objetosL;
    int L, N, M;
    char movimiento;
    int cantidad_de_movimientos;

    //cout<<"Indique su cantidad de puntos de vida:"; 
    cin>>L;

   // cout<<"Indique su valor de coordenadas (x,y), en este caso solo el del eje x:"; 
    cin>> N; cin>> M;
    //cout<<"Indique su valor de coordenadas (x,y), en este caso solo el del eje y:"; 

    //cout<<"ingrese el numero de objetos que van a estar presentes en el laberinto"<<endl;
    cin>> objetosL;

    int entrada_x;
    int entrada_y;
    int Z = L;

         objetosL = objetosL - 1;

    for (int i = 0; i < objetosL; i++){ // bucle que llama la funcion procesar elementos para almacenar los datos que el usuario ingrese

       //cout<<"ingrese un objeto"<<i+1<<endl;
       procesarElementos(i,entrada_x,entrada_y);

    } 

    int x = entrada_x; // esta variable sirve para que agarre como punto de inicio la entrada del laberinto en x
    int y = entrada_y; // esta variable sirve para que agarre como punto de inicio la entrada del laberinto en y

    if (recorrer_lab('E', x,y)){
       // cout<<"entrada encontrada"<<endl;
    } else {
       // cout<<"entrada no encontrada"<<endl;
        return 1;
    }

    //cout<<"ingrese la cantidad de movimientos que desea realizar"<<endl;
    cin>> cantidad_de_movimientos;

    int acum_tesoros = 0; // contar los tesoro que se han tomado
    int acum_trampas = 0; // contar las trampas que se han pisado

    bool tesoro_tomado = false; // variable que sirve para verificar si el tesoro ya fue tomado

    while (cantidad_de_movimientos > 0) { // bucle que se encarga de mover al jugador en el laberinto

     //cout<<"Ingrese el movimiento que desea realizar (W, A, S, D): ";
     cin >> movimiento;

     moviento_del_jugador(x, y, N, M, movimiento);

     //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

     cantidad_de_movimientos--;

     if (recorrer_lab('T', x, y) && !tesoro_tomado){ // aqui se verifica si el jugador se encuentra en una posicion valida y se le suma puntos de vida
        Z += 20;
        acum_tesoros++; 
        //cout<<"Tienes 20 puntos de vida mas"<<endl;
        tesoro_tomado = true; // se cambia el valor de la variable para que no se sumen mas puntos de vida

     } else if (recorrer_lab('X', x, y)){ // aqui se verifica si el jugador se encuentra en una posicion valida y se le resta puntos de vida 
        Z -= 10;
        acum_trampas++;
        //cout<<"Perdiste 10 puntos de vida"<<endl;

     } else if (recorrer_lab('P', x, y)){ // aqui se verifica si el jugador encontro un portal, y lo mueve de sitio dependiendo de cual de las dos posiciones del portal se ha encontrado
        //cout<<"Has encontrado un portal"<<endl;
         if (x == x1_1 && y == y1_1) {
          x = x2_1;
          y = y2_1;
          //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_1 && y == y2_1) {
         x = x1_1;
         y = y1_1;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_2 && y == y1_2) {
         x = x2_2;
         y = y2_2;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_2 && y == y2_2) {
         x = x1_2;
         y = y1_2;
          //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_3 && y == y1_3) {
         x = x2_3;
         y = y2_3;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_3 && y == y2_3) {
         x = x1_3;
         y = y1_3;
        // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_4 && y == y1_4) {
         x = x2_4;
         y = y2_4;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_4 && y == y2_4) {
         x = x1_4;
          y = y1_4;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_5 && y == y1_5) {
         x = x2_5;
         y = y2_5;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_5 && y == y2_5) {
         x = x1_5;
         y = y1_5;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_6 && y == y1_6) {
         x = x2_6;
         y = y2_6;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_6 && y == y2_6) {
         x = x1_6;
          y = y1_6;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_7 && y == y1_7) {
         x = x2_7;
         y = y2_7;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_7 && y == y2_7) {
         x = x1_7;
         y = y1_7;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_8 && y == y1_8) {
         x = x2_8;
         y = y2_8;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_8 && y == y2_8) {
         x = x1_8;
         y = y1_8;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_9 && y == y1_9) {
         x = x2_9;
         y = y2_9;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_9 && y == y2_9) {
         x = x1_9;
         y = y1_9;
         // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_10 && y == y1_10) {
         x = x2_10;
         y = y2_10;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_10 && y == y2_10) {
          x = x1_10;
         y = y1_10;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_11 && y == y1_11) {
         x = x2_11;
         y = y2_11;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_11 && y == y2_11) {
         x = x1_11;
         y = y1_11;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_12 && y == y1_12) {
         x = x2_12;
         y = y2_12;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_12 && y == y2_12) {
         x = x1_12;
         y = y1_12;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_13 && y == y1_13) {
         x = x2_13;
         y = y2_13;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_13 && y == y2_13) {
         x = x1_13;
         y = y1_13;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_14 && y == y1_14) {
         x = x2_14;
         y = y2_14;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_14 && y == y2_14) {
         x = x1_14;
         y = y1_14;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_15 && y == y1_15) {
         x = x2_15;
         y = y2_15;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_15 && y == y2_15) {
         x = x1_15;
         y = y1_15;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_16 && y == y1_16) {
         x = x2_16;
         y = y2_16;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_16 && y == y2_16) {
         x = x1_16;
         y = y1_16;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_17 && y == y1_17) {
         x = x2_17;
         y = y2_17;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_17 && y == y2_17) {
         x = x1_17;
         y = y1_17;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_18 && y == y1_18) {
         x = x2_18;
         y = y2_18;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_18 && y == y2_18) {
         x = x1_18;
         y = y1_18;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_19 && y == y1_19) {
         x = x2_19;
         y = y2_19;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_19 && y == y2_19) {
         x = x1_19;
         y = y1_19;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_20 && y == y1_20) {
         x = x2_20;
         y = y2_20;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_20 && y == y2_20) {
         x = x1_20;
         y = y1_20;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_21 && y == y1_21) {
         x = x2_21;
         y = y2_21;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_21 && y == y2_21) {
         x = x1_21;
         y = y1_21;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_22 && y == y1_22) {
         x = x2_22;
         y = y2_22;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_22 && y == y2_22) {
         x = x1_22;
         y = y1_22;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_23 && y == y1_23) {
         x = x2_23;
         y = y2_23;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_23 && y == y2_23) {
         x = x1_23;
         y = y1_23;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_24 && y == y1_24) {
         x = x2_24;
         y = y2_24;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_24 && y == y2_24) {
         x = x1_24;
         y = y1_24;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_25 && y == y1_25) {
         x = x2_25;
         y = y2_25;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_25 && y == y2_25) {
         x = x1_25;
         y = y1_25;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_26 && y == y1_26) {
         x = x2_26;
         y = y2_26;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_26 && y == y2_26) {
         x = x1_26;
         y = y1_26;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_27 && y == y1_27) {
         x = x2_27;
         y = y2_27;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_27 && y == y2_27) {
         x = x1_27;
         y = y1_27;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_28 && y == y1_28) {
         x = x2_28;
         y = y2_28;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_28 && y == y2_28) {
         x = x1_28;
         y = y1_28;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_29 && y == y1_29) {
         x = x2_29;
         y = y2_29;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_29 && y == y2_29) {
         x = x1_29;
         y = y1_29;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_30 && y == y1_30) {
         x = x2_30;
         y = y2_30;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_30 && y == y2_30) {
          x = x1_30;
         y = y1_30;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_31 && y == y1_31) {
         x = x2_31;
         y = y2_31;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_31 && y == y2_31) {
         x = x1_31;
         y = y1_31;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_32 && y == y1_32) {
         x = x2_32;
         y = y2_32;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_32 && y == y2_32) {
         x = x1_32;
         y = y1_32;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_33 && y == y1_33) {
         x = x2_33;
         y = y2_33;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_33 && y == y2_33) {
         x = x1_33;
         y = y1_33;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_34 && y == y1_34) {
         x = x2_34;
         y = y2_34;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_34 && y == y2_34) {
         x = x1_34;
         y = y1_34;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_35 && y == y1_35) {
         x = x2_35;
         y = y2_35;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_35 && y == y2_35) {
         x = x1_35;
         y = y1_35;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_36 && y == y1_36) {
         x = x2_36;
         y = y2_36;
         //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x2_36 && y == y2_36){
            x = x1_36;
            y = y1_36;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x1_37 && y == y1_37){
            x = x2_37;
            y = y2_37;
           // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x2_37 && y == y2_37){
            x = x1_37;
            y = y1_37;
           // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x1_38 && y == y1_38){
            x = x2_38;
            y = y2_38;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;
         } else if(x == x2_38 && y == y2_38){
            x = x1_38;
            y = y1_38;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x1_39 && y == y1_39){
            x = x2_39;
            y = y2_39;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x2_39 && y == y2_39){
            x = x1_39;
            y = y1_39;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x1_40 && y == y1_40){
            x = x2_40;
            y = y2_40;
           // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if( x == x2_40 && y == y2_40){
            x = x1_40;
            y = y1_40;
           // cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x1_41 && y == y1_41){
            x = x2_41;
            y = y2_41;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x2_41 && y == y2_41){
            x = x1_41;
            y = y1_41;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if (x == x1_42 && y == y1_42){
            x = x2_42;
            y = y2_42;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;

         } else if(x == x2_42 && y == y2_42){
            x = x1_42;
            y = y1_42;
            //cout << "Nueva posición del jugador: (" << x << ", " << y << ")" << endl;
         }


     } else if (recorrer_lab('#', x, y)){ // aqui verifica si el jugador se ha chocado contra un muro
        cout<<"Has encontrado un muro"<<endl;

     } else if (recorrer_lab('S', x, y)){ // aqui se verifica si el jugador a encontrado la salida del laberinto y sale del bucle
        //cout<<"Felicidades, has salido del laberinto"<<endl;
        return 0;
     }

    }

    if (Z > 0 && acum_tesoros == tesoro_cont){
    cout<<"TESOROS:"<<acum_tesoros<<endl;
    cout<<"TRAMPAS:"<<acum_trampas<<endl;
    cout<<"VIDA:"<<Z<<endl;
    cout<<"SORPRENDENTE"<<endl;
    } else if (Z > 0){
    cout<<"TESOROS:"<<acum_tesoros<<endl;
    cout<<"TRAMPAS:"<<acum_trampas<<endl;
    cout<<"VIDA:"<<Z<<endl;
    cout<<"LOGRADO"<<endl;
    } else if (Z == 0){
    cout<<"MUERTOS"<<endl;
    } if (N == 0 && M == 0){
    cout<<"ATRAPADOS"<<endl;
    }

    return 0;
}