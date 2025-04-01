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

// Funcion para voltear la imagen

void flip(Imagen* img) {
    for (int x = 0 ; x < img->height; x++) { // aca recorro cada fila de la imagen
        for (int y = 0; y < img->width / 2; y++) { // y aca cada columna hasta la mitad de la imagen
            for (int c = 0; c < img->channels; c++) { // recorro el canal rgb o rgba
                int pos_izq = (x * img->width + y) * img->channels + c; // Para encontrar la poscicion del pixel en la mitad izq
                int pos_der = (x * img->width + (img->width - y - 1)) * img->channels + c; // lo mismo en la mitad der
                // intercambiamos los pixeles para hacer el flip
                unsigned char temp = img->data[pos_izq];
                img->data[pos_izq] = img->data[pos_der];
                img->data[pos_der] = temp;
            }
        }
    }  
}

// Funcion para rotar la imagen

void giro(Imagen* img) {
    unsigned char* new_data = new unsigned char[img->width * img->height * img->channels]; // nuevo arreglo para almacenar la imagen que se rotara
    // Esto es lo mismo que en la funcion flip
    for (int x = 0; x < img->height; x++) { 
        for (int y = 0; y < img->width; y++) {
            for (int c = 0; c < img->channels; c++) {

                int pos_x = y; // La columna sera la nueva fila
                int pos_y = img->height - x - 1; // invertimos la fila en la nueva pos

                int pos_orig = (x * img->width + y) * img->channels + c; //pos de la imagen original
                int pos_nueva = (pos_x * img->height + pos_y) * img->channels + c; // pos de la imagen rotada

                new_data[pos_nueva] = img->data[pos_orig]; // asignamos el pixel a la nueva pos
            }
        }
    }
delete[] img->data; // liberamos memoria de la img original y asignamos la nueva imagen rotada
img->data = new_data;

}

int main() {
    //Cargamos la imagen
    Imagen* img = load("quilava.png");

   

    // Almacenamos el resultado
    save(img, "output.png");

    flip(img) ;
    save(img, "Flip.png") ; // si queri cambiarle el nombre adelante...

    //tmb hay que cambiar el pikachu.png x el quilava.png

    Imagen* img1 = load("Pikachu.png");

    //hice otro puntero para guardar la que se giro
    //hay que hacer mas punteros para las op 3 y 4 creo

    giro(img1) ;
    save(img1, "Giro.png") ;
}
