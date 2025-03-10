#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Clase que representa una palabra junto con la línea en la que aparece en un archivo
class Palabra {
private:
    string palabra;        // Almacena la palabra
    unsigned int n_linea;  // Almacena el número de línea donde se encontró la palabra

public:
    // Constructor que inicializa la palabra y el número de línea
    Palabra(string n_palabra, unsigned int n_num) : palabra(n_palabra), n_linea(n_num) {}

    // Métodos para modificar los atributos
    void FijarPalabra(string n_palabra) { palabra = n_palabra; }
    void FijarNumLinea(unsigned int n_num) { n_linea = n_num; }

    // Métodos para obtener los valores de los atributos
    string ObtenerPalabra() const { return palabra; }
    unsigned int ObtenerNumLinea() const { return n_linea; }
};

// Clase que representa el contenido de un archivo de texto y permite búsquedas en él
class ArchivoTexto {
private:
    vector<vector<string>> lineasTexto; // Almacena el archivo como una lista de líneas, donde cada línea es un vector de palabras

public:
    // Agrega una nueva línea de palabras al almacenamiento
    void AgregarListaPals(const vector<string>& n_lista) {
        lineasTexto.push_back(n_lista);
    }

    // Devuelve todas las líneas almacenadas en forma de lista de listas
    vector<vector<string>> ObtenerListaLineas() const { return lineasTexto; }

    // Devuelve la cantidad de líneas almacenadas en el archivo
    unsigned int ObtenerNumLineas() const { return lineasTexto.size(); }

    // Busca palabras que comiencen con la subcadena dada y devuelve una lista con los resultados
    list<Palabra> BuscarPrincipio(const string& subcadena) {
        list<Palabra> resultado;
        for (size_t i = 0; i < lineasTexto.size(); i++) { // Recorre cada línea
            for (const auto& palabra : lineasTexto[i]) {  // Recorre cada palabra en la línea
                if (palabra.find(subcadena) == 0) { // Si la palabra empieza con la subcadena
                    resultado.push_back(Palabra(palabra, i + 1)); // Se guarda en la lista
                }
            }
        }
        return resultado;
    }

    // Busca palabras que contengan la subcadena dada y devuelve una cola con los resultados
    queue<Palabra> BuscarContiene(const string& subcadena) {
        queue<Palabra> resultado;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const auto& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena) != string::npos) { // Si la subcadena está en la palabra
                    resultado.push(Palabra(palabra, i + 1)); // Se agrega a la cola
                }
            }
        }
        return resultado;
    }

    // Busca palabras que contengan la versión invertida de la subcadena dada y devuelve una pila con los resultados
    stack<Palabra> BuscarInvertida(const string& subcadena) {
        stack<Palabra> resultado;
        string subcadena_invertida = string(subcadena.rbegin(), subcadena.rend()); // Invertimos la subcadena
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const auto& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena_invertida) != string::npos) { // Si la palabra contiene la versión invertida
                    resultado.push(Palabra(palabra, i + 1)); // Se agrega a la pila
                }
            }
        }
        return resultado;
    }
};

// Función auxiliar que divide una línea de texto en palabras y las almacena en un vector
vector<string> dividirPalabras(const string& linea) {
    vector<string> palabras;
    string palabra;
    for (char c : linea) { // Recorre cada carácter de la línea
        if (isspace(c)) {  // Si se encuentra un espacio o salto de línea
            if (!palabra.empty()) {  // Si hay una palabra acumulada
                palabras.push_back(palabra); // Se guarda en el vector
                palabra.clear(); // Se limpia para la siguiente palabra
            }
        } else {
            palabra += c; // Se acumula el carácter en la palabra
        }
    }
    if (!palabra.empty()) palabras.push_back(palabra); // Añadir la última palabra si existe
    return palabras;
}

// Función principal
int main(int argc, char* argv[]) {
    // Verifica que el usuario proporcione un archivo de entrada
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " archivo.txt" << endl;
        return 1;
    }

    // Intenta abrir el archivo
    ifstream archivo(argv[1]);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    int n;
    string subcadena, linea;
    ArchivoTexto archivoTexto;

    // Leer el número de líneas a analizar
    archivo >> n;
    archivo.ignore(); // Ignorar el salto de línea tras leer el número

    // Leer la subcadena a buscar
    getline(archivo, subcadena);

    // Leer el archivo línea por línea y procesar cada una
    while (getline(archivo, linea)) {
        archivoTexto.AgregarListaPals(dividirPalabras(linea));
    }

    archivo.close(); // Cerrar el archivo

    // Realizar las búsquedas en el texto cargado
    list<Palabra> resultadoPrincipio = archivoTexto.BuscarPrincipio(subcadena);
    queue<Palabra> resultadoContiene = archivoTexto.BuscarContiene(subcadena);
    stack<Palabra> resultadoInvertida = archivoTexto.BuscarInvertida(subcadena);

    // Mostrar resultados de palabras que comienzan con la subcadena
    cout << "Palabras que comienzan con '" << subcadena << "': " << resultadoPrincipio.size() << endl;
    for (const auto& palabra : resultadoPrincipio) {
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }

    // Mostrar resultados de palabras que contienen la subcadena
    cout << "Palabras que contienen '" << subcadena << "': " << resultadoContiene.size() << endl;
    while (!resultadoContiene.empty()) {
        Palabra palabra = resultadoContiene.front();
        resultadoContiene.pop();
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }

    // Mostrar resultados de palabras que contienen la subcadena invertida
    cout << "Palabras que contienen la versión invertida de '" << subcadena << "': " << resultadoInvertida.size() << endl;
    while (!resultadoInvertida.empty()) {
        Palabra palabra = resultadoInvertida.top();
        resultadoInvertida.pop();
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }

    return 0;
}
