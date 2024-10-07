#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definición de constantes
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Definición de la estructura t_cub
/*typedef struct {
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    int **map; // Mapa 2D
    int map_width;
    int map_height;
    void *mlx; // Puntero a la estructura de MLX (para manejar gráficos)
} t_cub;

// Prototipos de funciones
void raycast(t_cub *cub);
unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY);
void my_mlx_pixel_put(void *mlx, int x, int y, unsigned int color);

// Función de inicialización del mapa
int **initialize_map(int *width, int *height) {
    *width = 5;   // Ancho del mapa
    *height = 5;  // Alto del mapa
    int **map = malloc(*height * sizeof(int *));
    
    for (int i = 0; i < *height; i++) {
        map[i] = malloc(*width * sizeof(int));
    }

    // Definir un mapa simple (0 = vacío, 1 = pared)
    int example_map[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    for (int y = 0; y < *height; y++) {
        for (int x = 0; x < *width; x++) {
            map[y][x] = example_map[y][x];
        }
    }

    return map;
}

// Implementación de funciones de textura y dibujo (solo como ejemplos)
unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY) {
    // Solo un color de ejemplo; aquí deberías acceder a tu textura real
    return (texNum * 50) + texX + texY; // Color ficticio
}

void my_mlx_pixel_put(void *mlx, int x, int y, unsigned int color) {
    // Simulación de poner un píxel; aquí deberías implementar la función real de MLX
    printf("Poniendo pixel en (%d, %d) con color %u\n", x, y, color);
}

int main() {
    t_cub cub;
    int map_width, map_height;

    // Inicialización del mapa
    cub.map = initialize_map(&map_width, &map_height);
    cub.map_width = map_width;
    cub.map_height = map_height;

    // Inicialización de la posición y dirección del jugador
    cub.posX = 2.0;
    cub.posY = 2.0;
    cub.dirX = -1.0;
    cub.dirY = 0.0;
    cub.planeX = 0.0;
    cub.planeY = 0.66;

    // Llamada a la función raycast
    raycast(&cub);

    // Liberar memoria del mapa
    for (int i = 0; i < map_height; i++) {
        free(cub.map[i]);
    }
    free(cub.map);

    return 0;
}*/
