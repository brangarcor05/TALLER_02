#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

class Palabra {
private:
    string palabra;
    unsigned int n_linea;
public:
    Palabra(string n_palabra, unsigned int n_num) : palabra(n_palabra), n_linea(n_num) {}
    void FijarPalabra(string n_palabra) { palabra = n_palabra; }
    void FijarNumLinea(unsigned int n_num) { n_linea = n_num; }
    string ObtenerPalabra() const { return palabra; }
    unsigned int ObtenerNumLinea() const { return n_linea; }
};

class ArchivoTexto {
private:
    vector<vector<string>> lineasTexto;
public:
    void AgregarListaPals(const vector<string>& n_lista) {
        lineasTexto.push_back(n_lista);
    }
    vector<vector<string>> ObtenerListaLineas() const { return lineasTexto; }
    unsigned int ObtenerNumLineas() const { return lineasTexto.size(); }

    list<Palabra> BuscarPrincipio(const string& subcadena) {
        list<Palabra> resultado;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const auto& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena) == 0) {
                    resultado.push_back(Palabra(palabra, i + 1));
                }
            }
        }
        return resultado;
    }

    queue<Palabra> BuscarContiene(const string& subcadena) {
        queue<Palabra> resultado;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const auto& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena) != string::npos) {
                    resultado.push(Palabra(palabra, i + 1));
                }
            }
        }
        return resultado;
    }

    stack<Palabra> BuscarInvertida(const string& subcadena) {
        stack<Palabra> resultado;
        string subcadena_invertida = string(subcadena.rbegin(), subcadena.rend());
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const auto& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena_invertida) != string::npos) {
                    resultado.push(Palabra(palabra, i + 1));
                }
            }
        }
        return resultado;
    }
};

vector<string> dividirPalabras(const string& linea) {
    vector<string> palabras;
    string palabra;
    for (char c : linea) {
        if (isspace(c)) {
            if (!palabra.empty()) {
                palabras.push_back(palabra);
                palabra.clear();
            }
        } else {
            palabra += c;
        }
    }
    if (!palabra.empty()) palabras.push_back(palabra);
    return palabras;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " archivo.txt" << endl;
        return 1;
    }
    ifstream archivo(argv[1]);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    int n;
    string subcadena, linea;
    ArchivoTexto archivoTexto;
    archivo >> n;
    archivo.ignore();
    getline(archivo, subcadena);
    while (getline(archivo, linea)) {
        archivoTexto.AgregarListaPals(dividirPalabras(linea));
    }
    archivo.close();
    
    list<Palabra> resultadoPrincipio = archivoTexto.BuscarPrincipio(subcadena);
    queue<Palabra> resultadoContiene = archivoTexto.BuscarContiene(subcadena);
    stack<Palabra> resultadoInvertida = archivoTexto.BuscarInvertida(subcadena);
    
    cout << "Palabras que comienzan con '" << subcadena << "': " << resultadoPrincipio.size() << endl;
    for (const auto& palabra : resultadoPrincipio) {
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }
    
    cout << "Palabras que contienen '" << subcadena << "': " << resultadoContiene.size() << endl;
    while (!resultadoContiene.empty()) {
        Palabra palabra = resultadoContiene.front();
        resultadoContiene.pop();
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }
    
    cout << "Palabras que contienen la versión invertida de '" << subcadena << "': " << resultadoInvertida.size() << endl;
    while (!resultadoInvertida.empty()) {
        Palabra palabra = resultadoInvertida.top();
        resultadoInvertida.pop();
        cout << palabra.ObtenerPalabra() << " (Línea " << palabra.ObtenerNumLinea() << ")" << endl;
    }
    return 0;
}
