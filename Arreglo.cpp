#include <iostream>
#include <fstream>
#include <cmath>

#define MAX 200
using namespace std;

class Arreglo {
  // El arreglo "datos[]" contiene los números que se leen desde el archivo txt
  int datos[MAX];

  // El arreglo "cDatos[]" es una copia de "datos[]" pero con este se operan todos
  // los algoritmos.
  int cDatos[MAX];

  // Variable que toma el número de elementos dentro del archivo de entrada
  // es decir "n"
  int tamano;

  public:
    /****************************************************/
    /* Función:  lecturaDatos(string archivo)           */
    /* Tipo:     void                                   */
    /* Parámetros: string archivo, nombre del archivo   */
    /* txt a abrir                                      */
    /* Detalles: Función que permite leer un archivo    */
    /* txt para así llenar el arreglo público "datos",  */
    /* que es donde se guardan todos los elementos de   */
    /* entrada.                                         */
    /****************************************************/
    void lecturaDatos(string archivo){
      int i = 0;
      std::fstream myfile(archivo+".txt", std::ios_base::in);
      int a;
      myfile >> a;
      tamano = a;
      while (myfile >> a) {
        datos[i] = a;
        i++;
      }
    }

    /*****************************************************/
    /* Función:  initArray()                             */
    /* Tipo:     void                                    */
    /* Parámetros: Ninguno                               */
    /* Detalles: Función que hace una copia del arreglo  */
    /* "datos" hacia el arreglo  "cDatos", esto es para  */
    /* operar con la copia y no tocar el original, de    */
    /* este modo se tiene un respaldo y los datos están  */
    /* protegidos y seguros.                             */
    /*****************************************************/
    void initArray(){
      for (int i = 0; i < tamano; i++) {
        cDatos[i] = datos[i];
      }
    }

    /*****************************************************/
    /* Función:  endArray()                              */
    /* Tipo:     void                                    */
    /* Parámetros: Ninguno                               */
    /* Detalles: Función que hace una copia del arreglo  */
    /* para operar, "cDatos", al arreglo final "datos".  */
    /* De este modo ya se puede imprimir el arreglo      */
    /* original "datos", ya que está finalmente ordenado */
    /*****************************************************/
    void endArray(){
      for (int i = 0; i < tamano; i++) {
        datos[i] = cDatos[i];
      }
    }

    /*******************************************************/
    /* Función:  imprimeArreglo()                          */
    /* Tipo:     void                                      */
    /* Parámetros: Ninguno                                 */
    /* Detalles: Función que imprime el arreglo "datos"    */
    /* elemento por elemento, seguido de un salto de línea.*/
    /* Se puede llamar antes de aplicar algún algoritmo de */
    /* ordenamiento y ver qué datos en qué orden se leyeron*/
    /* o después para ver cómo quedó el arreglo ya ordenado*/
    /*******************************************************/
    void imprimeArreglo(){
      for (int i = 0; i < tamano; i++){
        cout << datos[i] << "\n";
      }
    }

    /*****************************************************/
    /* Función:  findMax()                               */
    /* Tipo: int                                     */
    /* Parámetros: Ninguno                               */
    /* Detalles: Esta función regresa el elemento más    */
    /* grande de los datos de entrada. No necesita       */
    /* parámetros porque lee el arreglo "cDatos".        */
    /*****************************************************/
    int findMax(){
      int max = cDatos[0];
      for (int i = 1; i < tamano; i++) {
        if (cDatos[i] > max) {
          max = cDatos[i];
        }
      }
      return max;
    }

    /****************************************************************/
    /* Función: radixSort()                                         */
    /* Tipo: void                                                   */
    /* Parámetros: Ninguno                                          */
    /* Detalles: Función que aplica el algoritmo de ordenamiento    */
    /* Radix Sort. Dentro de sí, manda llamar findMax() para        */
    /* operar "w" veces a partir del número de dígitos del máximo   */
    /* número dentro del arreglo. Igualmente llama a countingSort() */
    /* "w" veces para ordenar los valores por dígito.               */
    /****************************************************************/
    void radixSort(){
      // Se llama initArray() para hacer una copia de "datos" hacia "cDatos".
      initArray();
      int max = findMax(), digits = 0;
      // Ciclo que divide w veces al número más grande entre 10, hasta que sea 0
      // de esta manera se guarda en digits el número de dígitos que tiene "max".
      while (max > 0) {
        max /= 10;
        digits++;
      }
      // Ciclo que manda a llamar countingSort() "w" veces, para ordenar los números
      // a partir del último dígito hasta al primero.
      // Se pasa el parámetro i para saber a partir de qué dígito se va a ordenar el arreglo.
      for (int i = 0; i < digits; i++) {
        countingSort(i);
      }
      // Finalmente se llama endArray() para vaciar el arreglo ordenado "cDatos"
      // al arreglo original "datos"
      endArray();
    }

    /***************************************************************/
    /* Función: countingSort(int digitPos)                         */
    /* Tipo: void                                                  */
    /* Parámetros: int digitPos, índice del dígito correspondiente */
    /* a ordenar. Va del número de dígitos del elemento máximo a 0 */
    /* Detalles: Algoritmo que ordena elementos en un arreglo a    */
    /* partir del dígito que se pase como parámetro en "digitPos". */
    /***************************************************************/
    void countingSort(int digitPos){
      // Arreglo que registra la frecuencia en que aparece un número en
      // la línea de dígitos que se está operando. Por ejemplo, en el Arreglo
      // [11, 12, 21, 34], la frecuencia con la que se ve al 1 en la última
      // posición es 2.
      int ocurrences[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      // Arreglo que guarda los elementos ya ordenados por el dígito "digitPos"
      int orderedDatos[MAX];
      // Variable que toma el w dígito del enésimo número dentro del arreglo cDatos
      int digitSelf;
      // Ciclo que registra la frecuencia con la que aparece el dígito digitSelf
      // y lo suma +1 en su índice correspondiente dentro del arreglo ocurrences
      for (int i = 0; i < tamano; i++){
        digitSelf = (int)(cDatos[i]/(pow(10, (float)digitPos)))%10;
        ocurrences[digitSelf]++;
      }
      // Ciclo que hace una sumatoria a la derecha de ocurrencias de dígitos
      // esto es para poder colocar cada elemento de cDatos[] en su índice correspondiente
      // dentro del arreglo orderedDatos[]
      for (int i = 0; i < 9; i++) {
        ocurrences[i+1] += ocurrences[i];
      }
      // Ciclo que coloca cada elemento de cDatos[] de manera ordenada dentro de orderedDatos[]
      for (int i = tamano-1; i >= 0; i--) {
        digitSelf = (int)(cDatos[i]/(pow(10, (float)digitPos)))%10;
        orderedDatos[ocurrences[digitSelf]-1] = cDatos[i];
        ocurrences[digitSelf]--;
      }
      // Ciclo final que hace que cDatos[] sea un arreglo ordenado a partir
      // del dígito digitPos. Esto es para que en la próxima iteración
      // se ordene en el dígito digitPos+1 con un arreglo pre-ordenado.
      for (int i = 0; i < tamano; i++) {
        cDatos[i] = orderedDatos[i];
      }
    }

    /****************************************************************/
    /* Función: heapSort()                                          */
    /* Parámetros: Ninguno                                          */
    /* Tipo: void                                                   */
    /* Detalles: Algoritmo de ordenamiento bajo el esquema del uso  */
    /* de max-heaps, es decir, crear un árbol binario con todos los */
    /* elementos del arreglo y asegurarse de que se cumpla la única */
    /* condición; que los nodos padre siempre sean mayores que los  */
    /* nodos hijos.                                                 */
    /****************************************************************/
    void heapSort(){
      // Se inicializa el arreglo cDatos[] con datos[]
      initArray();
      // Ciclo que llama heapify para hacer que se cumpla la condición de
      // los max-heap y así saber cuál es el elemento más grande del arreglo
      // Se manda como parámetro i, que es la variable que dice cuántos números
      // faltan por ordenar
      for (int i = tamano; i > 0; i--) {
        heapify(i);
        imprimeArreglo();
        std::cout << "-------------" << '\n';
      }
      // Se actualiza el arreglo datos[] con cDatos[], el arreglo ya ordenado.
      endArray();
    }

    /*****************************************************************/
    /* Función: heapify(int dTamano)                                 */
    /*                                                               */
    /* Parámetros: int dTamano, es el número de elementos (n) para   */
    /* crear un árbol binario, es dTamano por dinámico tamano, ya que*/
    /* va a ser un elemento menor cada vez que se mande llamar       */
    /*                                                               */
    /* Tipo: void                                                    */
    /*                                                               */
    /* Detalles: Rutina que verifica que se cumpla la condición de   */
    /* max-heap por subárboles, no en general, mediante la lógica de */
    /* "swim", que hace que los valores del fondo del árbol suban    */
    /* siempre y cuando sean mayores que sus padres, de este modo,   */
    /* se puede encontrar el valor máximo por iteración y colocarlo  */
    /* en la última posición del arreglo para luego volver a ejecutar*/
    /* la función con n-1, así se asegura que el último valor no es  */
    /* tocado, porque se sabe que es el mayor y está en su posición  */
    /*****************************************************************/
    void heapify(int dTamano){
      // left = datos[nodo_izquierdo]
      // right = datos[nodo_derecho]
      // parent = datos[parent]
      int temp, left, right, parent;

      // Bucle que compara los nodos hijo con el padre y sube al mayor.
      // Se empieza a comparar desde el subárbol del fondo hasta el de la raíz.
      // Va de 0 a dTamano/2 porque es el número máximo de subárboles que se
      // pueden formar a partir de un arreglo de longitud dTamano
      for (int i = 0; i < dTamano/2; i++) {
        // ((dTamano/2)*2)-(i*2) = ecuación para el índice de cualquier nodo
        // izquierdo del subarbol dTamano/2
        left = cDatos[((dTamano/2)*2-1)-(i*2)];
        // La misma lógica que la de los nodos izquierdos sirve para los derechos
        // solo que sin restar un 1 a (dTamano/2)*2, eso siempre devuelve un numero par
        right = cDatos[((dTamano/2)*2)-(i*2)];
        // El índice del padre de nodos es la división del índice izquierdo / 2
        // es forzosamente la del índice izquierdo para que se haga una división entera
        parent = cDatos[(((dTamano/2)*2-1)-(i*2))/2];
        // Esta condición verifica si el árbol tiene un tamaño impar y si es la primer
        // iteración, si es el caso, el último subárbol está completo y se puede comparar izquierdo
        // con derecho, de otro modo el izquierdo se compararía con un apuntador vacío y fallaría
        if (i != 0 || (dTamano%2!=0 && i==0)) {
          // Si el valor de la izquierda es mayor que el derecho, izquierda
          // se compara con el padre, si no, derecha se compara
          if(left > right){
            // Si el número izquierdo es mayor que el padre, estos se intercambian
            if (left > parent) {
              temp = parent;
              cDatos[(((dTamano/2)*2-1)-(i*2))/2] = left;
              cDatos[((dTamano/2)*2-1)-(i*2)] = temp;
            }
          }
          else if (right > parent) {   // Si el número derecho es mayor que el padre, estos se intercambian
            temp = parent;
            cDatos[(((dTamano/2)*2-1)-(i*2))/2] = right;
            cDatos[((dTamano/2)*2)-(i*2)] = temp;
          }
        }
        else {           /* Si la condicion anterior no se cumple, sólo se compara el nodo izquierdo con su nodo padre*/
          // Si el hijo es mayor, se cambia con el padre, si no, no ocurre nada
          if (left > parent) {
            temp = parent;
            cDatos[(((dTamano/2)*2-1)-(i*2))/2] = left;
            cDatos[((dTamano/2)*2-1)-(i*2)] = temp;
          }
        }
      }
      // Cambiar la raíz (valor más grande), con el último nodo del árbol
      // para que cuando se vuelva a llamar heapify(), sea con dTamano-1
      // y no se mueva ese valor.
      temp = cDatos[0];
      cDatos[0] = cDatos[dTamano-1];
      cDatos[dTamano-1] = temp;
    }
};

int main() {
  Arreglo miArreglo;
  miArreglo.lecturaDatos("archivo");
  miArreglo.heapSort();
  //miArreglo.imprimeArreglo();
  return 0;
}
