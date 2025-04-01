#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// Importacion de librerias. Los archivos correspondientes deben estar en el mismo directorio que el .cpp.
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>

using namespace std;

// Struct que almacena la data de una imagen
struct Imagen{
    unsigned char* data;
    int width, height, channels;
};

// Abrir imagen desde memoria local
Imagen* load(const char* filename) {
    Imagen* img = new Imagen();
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}

// Guardar imagen en memoria local
void save(Imagen* img, const char* filename) {
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    cout << "Imagen guardada:  " << filename << "\n";
}
void Espejo(Imagen* img) {
    int ancho_total = img->width * img->channels;  // calculamos el ancho total de la imagen en pixeles
    // Recorremos cada fila de la imagen
    // y cada fila la recorremos de izquierda a derecha
    for (int pos_y = 0; pos_y < img->height; pos_y++) {
        unsigned char* fila_izq = img->data + pos_y * ancho_total; // Asignamos la fila izquierda a la posicion de la imagen
        unsigned char* fila_der = fila_izq + ancho_total - img->channels; // Asignamos la fila derecha a la posicion de la imagen menos el ancho total menos el canal
        while (fila_izq < fila_der) { // Intercambiamos los pixeles de la fila izquierda y derecha
                for (int p = 0; p < img->channels; p++) {
                    unsigned char temp = fila_izq[p];
                    fila_izq[p] = fila_der[p];
                    fila_der[p] = temp; //usamos el temp para intercambiar los pixeles y que no se vean afectados
                 }
            fila_izq += img->channels; 
            fila_der -= img->channels;
        }
    }
}

void Giro90(Imagen* img) {
    unsigned char* new_data = new unsigned char[img->width * img->height * img->channels]; // nuevo arreglo para almacenar la imagen que se rotara
    for (int x = 0; x < img->height; x++) { 
        for (int y = 0; y < img->width; y++) {
            for (int c = 0; c < img->channels; c++) {
                int pos_x = y; // La columna sera la nueva fila
                int pos_y = img->height - x - 1; // invertimos la fila en la nueva pos
                int pos_orig = (x * img->width + y) * img->channels + c; //pos de la imagen original
                int pos_nueva = (pos_x * img->height + pos_y) * img->channels + c; // pos de la imagen rotada
                new_data[pos_nueva] = img->data[pos_orig]; // asignamos el nuevo pixel a la nueva posicion
            }
        }
    }
    delete[] img->data; // liberamos la memoria de la imagen original
    img->data = new_data; // asignamos el nuevo arreglo a la imagen original
    swap(img->width, img->height); // intercambiamos el ancho y alto de la imagen
}
void Atenuar(Imagen* img) {
    float factorA;
    cout << "Ingrese el factor de atenuacion (0-1): ";
    cin >> factorA; // factor de atenuacion
    for (int i = 0; i < img->width * img->height * img->channels; i++) { // recorremos cada pixel de la imagen
        img->data[i] = img->data[i] * factorA; // atenuamos el pixel multiplicando por el factor
    }
}
void ByN(Imagen* img) {
    int Tono; // variable para almacenar el tono
    cout << "Ingrese el tono (0-255): "; // pedimos el tono al usuario
    cin >> Tono; // factor de atenuacion
    for (int i = 0; i < img->width * img->height * img->channels; i += img->channels) { // recorremos cada pixel de la imagen
        unsigned char r = img->data[i]; // asignamos el canal rojo a una variable
        unsigned char g = img->data[i + 1]; // asignamos el canal verde a una variable
        unsigned char b = img->data[i + 2]; // asignamos el canal azul a una variable
        unsigned char gris = (r + g + b) / 3; // promedio de los tres canales
        if (gris > Tono) { // si el promedio es mayor a 127, asignamos el valor 255
            gris = 255;
        } else { // si no, asignamos el valor 0
            gris = 0;
        }
        // Asignamos el nuevo valor a los tres canales
        img->data[i] = gris; // asignamos el nuevo valor al canal rojo
        img->data[i + 1] = gris; // asignamos el nuevo valor al canal verde
        img->data[i + 2] = gris; // asignamos el nuevo valor al canal azul
    }
}
int main() {
    //Cargamos la imagen
    Imagen* img = load("quilava.png");
    Espejo(img); // Llamamos a la funcion espejo
    save(img, "espejo.png"); // Guardamos la imagen
    Imagen* img2 = load("quilava.png"); // Cargamos la imagen nuevamente
    Giro90(img2);// Llamamos a la funcion girar
    save(img2, "giro90.png"); // Guardamos la imagen girada
    Imagen* img3 = load("quilava.png"); // Cargamos la imagen nuevamente
    Atenuar(img3); // Llamamos a la funcion atenuar
    save(img3, "atenuada.png"); // Guardamos la imagen atenuada
    Imagen* img4 = load("quilava.png"); // Cargamos la imagen nuevamente
    ByN(img4); // Llamamos a la funcion ByN
    save(img4, "BlancoNegro.png");
    return 0;

}