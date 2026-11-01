# Tarea 1 INF134 – Procesamiento de imágenes en C++

Proyecto de procesamiento de imágenes RGB en C++. Carga una imagen PNG, aplica distintas operaciones sobre sus píxeles y genera nuevas imágenes, además de una versión en arte ASCII de la imagen original.

## Contenido

Todo el trabajo está en la carpeta `tarea 1/`.

| Archivo | Descripción |
|---|---|
| `Tarea1.cpp` | Programa principal. Contiene las cuatro operaciones de imagen, la conversión a ASCII y la función `main`. |
| `R01.cpp` | Versión de trabajo con espejo, rotación, atenuación y blanco y negro con umbral ingresado por el usuario. |
| `001.cpp` | Primer borrador con las operaciones de volteo y rotación. |
| `stb_image.h`, `stb_image_write.h` | Librerías de un solo archivo (stb) para leer y escribir imágenes. |
| `quilava.png` | Imagen de entrada usada por el programa principal. |
| `operacion_1.png` … `operacion_4.png` | Resultados generados por `Tarea1.cpp`. |
| `ascii.txt` | Arte ASCII generado a partir de `quilava.png`. |
| `TEORICAS.txt` | Respuestas a las preguntas teóricas de la tarea, con sus fuentes. |
| `Tarea1-Bravo-Palma.zip` | Entrega comprimida. |
| `Tarea1.exe`, `R01.exe`, `001.exe` | Ejecutables compilados para Windows. |

## Operaciones implementadas

El programa principal (`Tarea1.cpp`) realiza las siguientes operaciones:

1. **Volteo horizontal** (`operacion_1`): invierte cada fila intercambiando el píxel izquierdo con el derecho.
2. **Rotación de 90°** (`operacion_2`): crea un nuevo arreglo y reubica cada píxel en su posición girada.
3. **Aclarado** (`operacion_3`): aplica `255 - (255 - valor) * factor` a cada canal, con factor 0.37.
4. **Escala de grises con umbral** (`operacion_4`): calcula el promedio de R, G y B, y lo convierte en blanco (255) si supera el umbral 127, o en negro (0) si no.
5. **Arte ASCII** (`ascii.txt`): convierte cada píxel a luminancia con la fórmula `0.299 R + 0.587 G + 0.114 B` y la asigna a un carácter de una escala de 70 símbolos.

`R01.cpp` además incluye `Espejo`, `Giro90`, `Atenuar` y `ByN`, que son versiones con parámetros ingresados por el usuario, como el factor de atenuación (0 a 1) o el tono del blanco y negro (0 a 255).

## Cómo compilar y ejecutar

Los archivos `stb_image.h` y `stb_image_write.h` deben estar en el mismo directorio que el `.cpp`.

```bash
cd "tarea 1"
g++ Tarea1.cpp -o tarea1 -Wall
./tarea1
```

Al ejecutarlo se generan `operacion_1.png`, `operacion_2.png`, `operacion_3.png`, `operacion_4.png` y `ascii.txt`.

En Windows también se puede compilar con g++ de MSYS2 (UCRT64).

## Estado actual

- `Tarea1.cpp` genera las cuatro imágenes y el archivo ASCII a partir de `quilava.png`.
- `TEORICAS.txt` responde las preguntas sobre el uso de `unsigned char`, la comparación de memoria con `unsigned int`, el índice del canal azul en un arreglo unidimensional y las formas de convertir RGB a escala de grises.
- `R01.cpp` y `001.cpp` son versiones anteriores o exploratorias; el programa que genera las entregas es `Tarea1.cpp`.
- El `README.txt` original indica compilar `tareal.cpp`, pero el nombre real del archivo es `Tarea1.cpp`.
- La configuración de VS Code (`.vscode/tasks.json`) usa rutas de Windows (`C:\msys64\...`).

## Autor

Integrantes:
R. Palma j. Bravo
Repositorio: `r-pt/tarea1-in134`
