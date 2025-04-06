#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// Importacion de librerias. Los archivos correspondientes deben estar en el mismo directorio que el .cpp.
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <fstream>

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

// Funcion para voltear la imagen

void operacion_1(Imagen* img) {
    for (int x = 0 ; x < img->height; x++) {
        for (int y = 0; y < img->width / 2; y++) {
            for (int c = 0; c < img->channels; c++) {
                int pos_izq = (x * img->width + y) * img->channels + c;
                int pos_der = (x * img->width + (img->width - y - 1)) * img->channels + c;

                unsigned char temp = img->data[pos_izq];
                img->data[pos_izq] = img->data[pos_der];
                img->data[pos_der] = temp;
            }
        }
    }  
}

// Funcion para rotar la imagen 90 grados

void operacion_2(Imagen* img) {
    unsigned char* new_data = new unsigned char[img->width * img->height * img->channels];

    for (int x = 0; x < img->height; x++) {
        for (int y = 0; y < img->width; y++) {
            for (int c = 0; c < img->channels; c++) {

                int pos_x = y;
                int pos_y = img->height - x - 1;

                int pos_orig = (x * img->width + y) * img->channels + c;
                int pos_nueva = (pos_x * img->height + pos_y) * img->channels + c;

                new_data[pos_nueva] = img->data[pos_orig];
            }
        }
    }
delete[] img->data;
img->data = new_data;
}

void operacion_3(Imagen* img) {
    float factorA;
    cout << "Ingrese el factor de atenuacion (0-1): ";
    cin >> factorA;
    for (int i = 0; i < img->width * img->height * img->channels; i++) {
        img->data[i] = 255 - (255 - img->data[i]) * factorA;
    }
}

void operacion_4(Imagen* img) {
    int Tono; // variable para almacenar el tono
    cout << "Ingrese el tono (0-255): "; // pedimos el tono al usuario
    cin >> Tono;
    for (int i = 0; i < img->width * img->height * img->channels; i += img->channels) { // recorremos cada pixel de la imagen
        unsigned char r = img->data[i]; // asignamos el canal rojo a una variable
        unsigned char g = img->data[i + 1]; // asignamos el canal verde a una variable
        unsigned char b = img->data[i + 2]; // asignamos el canal azul a una variable
        unsigned char gris = (r + g + b) / 3; // promedio de los tres canales
        if (gris > Tono) { // si el promedio es mayor al tono, asignamos el valor 255
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
    Imagen* img = load("Pikachu.png");

    operacion_1(img) ;
    save(img, "Flip.png") ;

    Imagen* img1 = load("Pikachu.png");

    operacion_2(img1) ;
    save(img1, "Giro.png") ;

    Imagen* img2 = load("Pikachu.png");

    operacion_3(img2) ;
    save(img2, "Atenuar.png") ;

    Imagen* img3 = load("Pikachu.png"); 

    operacion_4(img3) ;
    save(img3, "BlancoNegro.png") ;
}
