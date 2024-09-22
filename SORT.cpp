#include <iostream>
#include <fstream> // para leer el archivo
#include <string> // para manejar las palabras
#include <vector> // para crear el vector de palabras a ordenar
#include <algorithm> // para usar la funcion 'sort'
#include <ctime> // para encontrar el tiempo de ejecucion

using namespace std;

int letras = 27; //
int lineas =  10000; // numero de lineas a leer del archivo

// Función para obtener el índice del bucket basado en la letra
int getBucketIndex(char c) {
    // Convertir a minúsculas para uniformidad
    c = tolower(c);

    // Si es una letra normal, usar su posición en el alfabeto
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }

    // Para cualquier otro carácter, usar el último índice
    return letras - 1;  // Para caracteres no contemplados
}

// Función para imprimir el vector
void imprimirVector(const vector<string>& vec) {
    for (const auto& elemento : vec) {
        cout << elemento << endl;
    }
}

// Función de ordenación por bucket
void bucketSort(vector<string>& palabras) {
    vector<vector<string>> buckets(letras);

    // Distribuir las palabras en los buckets basándose en la primera letra
    for (const auto& palabra : palabras) {
        int index = getBucketIndex(palabra[0]);
        buckets[index].push_back(palabra);
    }

    // Ordenar cada bucket individualmente
    for (int i = 0; i < letras; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Concatenar los resultados de todos los buckets
    palabras.clear();
    for (const auto& bucket : buckets) {
        for (const auto& palabra : bucket) {
            palabras.push_back(palabra);
        }
    }
}

// Función de ordenación por burbuja (bubble sort)
void bubbleSort(vector<string>& palabras) {
    int lineas = palabras.size();
    for (int i = 0; i < lineas - 1; i++) {
        for (int j = 0; j < lineas - i - 1; j++) {
            if (palabras[j] > palabras[j + 1]) {
                swap(palabras[j], palabras[j + 1]);
            }
        }
    }
}

int main() {
    // Nombre del archivo a leer
    string nombreArchivo = "palabras.es";

    // Crear un objeto ifstream para leer el archivo
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1; // Salir con un error
    }

    // Variable para almacenar cada palabra leída
    string palabra;
    vector<string> palabras;

    int contador = 0;
    // Leer palabras del archivo, una por línea
    while (getline(archivo, palabra) && contador < lineas) {
        palabras.push_back(palabra);
        contador++;
    }

    // Cerrar el archivo
    archivo.close();

    // Medir el tiempo de ejecución de la ordenación
    clock_t inicio = clock();

    // Ordenar usando Bucket Sort o Bubble Sort
    //bucketSort(palabras);
    bubbleSort(palabras);

    clock_t fin = clock();
    double duracion = double(fin - inicio) / CLOCKS_PER_SEC;

    // Imprimir el tiempo de ejecución
    cout << "Tiempo de ejecucion: " << duracion << " segundos" << endl;

    // Imprimir el vector ordenado
    //imprimirVector(arreglo);

    return 0;
}
