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

void flip(Imagen* img) {
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

int main() {
    //Cargamos la imagen
    Imagen* img = load("Pikachu.png");

    //Modificamos un par de pixeles en el borde superior de la imagen como ejemplo
    img->data[101] = 0;
    img->data[102] = 0;
    img->data[103] = 0;
    img->data[104] = 0;
    img->data[105] = 0;
    img->data[106] = 0;

    // Almacenamos el resultado
    save(img, "output.png");

    // Rudolf no se si influya en que lo haga con la misma direccion con la cual trabajamos el main, asi q lo dejo asi mientras.
    // Igual despues le podemos hacer con la direccion de otro puntero que apunte a la direccion de la imagen.
    // tambien hay que cambiarle el nombre a la img a quilava.png.

    flip(img) ;
    save(img, "ImagenFlip.png") ;
}
