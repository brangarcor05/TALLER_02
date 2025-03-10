# Procesador de Texto con Búsqueda Avanzada

## Descripción
Este proyecto implementa un sistema para analizar archivos de texto y buscar palabras según tres criterios:
1. Palabras que comienzan con una subcadena específica.
2. Palabras que contienen una subcadena en cualquier parte.
3. Palabras que contienen la versión invertida de una subcadena.

El código utiliza estructuras de datos eficientes como listas, colas y pilas para almacenar y organizar los resultados de la búsqueda, optimizando la recuperación de información en archivos de texto.

## Características
- Lectura y procesamiento de archivos de texto línea por línea.
- Almacenamiento estructurado en una matriz de palabras.
- Búsqueda eficiente utilizando listas, colas y pilas.
- Implementación modular basada en un Tipo Abstracto de Datos (TAD).

## Instalación y Ejecución
### Requisitos
- Compilador C++ (GCC, Clang o MSVC)
- Sistema operativo Windows, Linux o macOS

### Compilación
```sh
g++ -o procesador main.cpp ArchivoTexto.cpp Palabra.cpp dividirPalabras.cpp
```

### Ejecución
```sh
./procesador archivo.txt
```
El programa requiere un archivo de texto como entrada, que debe contener:
1. Un número entero `n` indicando el número de líneas a leer.
2. Una subcadena a buscar.
3. `n` líneas de texto.

### Ejemplo de Entrada (archivo.txt)
```
3
pal
palabra ejemplo
texto palabras claves
otra oración aquí
```

### Ejemplo de Salida
```
Palabras que comienzan con 'pal': 2
palabra (Línea 1)
palabras (Línea 2)

Palabras que contienen 'pal': 2
palabra (Línea 1)
palabras (Línea 2)

Palabras que contienen la versión invertida de 'pal': 0
```

## Licencia
Este proyecto es de código abierto bajo la licencia MIT.

