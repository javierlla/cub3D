# cub3D

cub3D es una implementación básica de un motor gráfico en 3D basado en raycasting, similar al que se utilizó en juegos clásicos como **Wolfenstein 3D**. Este proyecto introduce conceptos fundamentales de gráficos 3D, manejo de eventos, lectura de archivos y renderizado en tiempo real utilizando la biblioteca **MiniLibX**.

## 🧠 Objetivos del Proyecto

- Aprender sobre raycasting y cómo simular un entorno 3D a partir de un mapa 2D.
- Profundizar en el manejo de eventos gráficos (teclado, movimiento, ventanas).
- Trabajar con estructuras complejas en C.
- Crear un pequeño juego con visualización 3D.

## 🖥️ Requisitos

- Sistema operativo: Linux
- Compilador: `gcc`
- Librería gráfica: [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
- Mapa de entrada válido en formato `.cub`

## ⚙️ Compilación

```bash
make

Esto generará un ejecutable llamado cub3D.
🚀 Ejecución

./cub3D maps/mapa.cub

    Asegúrate de tener un archivo .cub válido con texturas y configuración del mapa.

📦 Estructura del Proyecto

cub3D/
│
├── mandatory/         # Código fuente
├── includes/          # Archivos de cabecera
├── libft/             # Librería propia Libft
├── mlx/               # Librería mlx
├── maps/              # Mapas de prueba en formato .cub
├── textures/          # Texturas para las paredes
├── Makefile
└── README.md

🧱 Formato del archivo .cub

El archivo .cub debe contener:

    Rutas a las texturas para cada dirección (NO, SO, WE, EA)

    Color del piso y techo en RGB

    Mapa del mundo (solo caracteres válidos: 0, 1, N, S, E, W, espacio)

Ejemplo:

NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
111111

🎮 Controles

    W / S: Avanzar / Retroceder

    A / D: Moverse lateralmente

    ← / →: Girar la cámara

    ESC: Salir del juego

🛠️ Funcionalidades Implementadas

    ✅ Motor de raycasting con DDA

    ✅ Renderizado de paredes en 3D

    ✅ Soporte para múltiples texturas

    ✅ Colisiones básicas

    ✅ Lectura y validación del mapa

    ✅ Manejo de eventos de teclado

🧪 Bonus 

    🔦 Minimapa en 2D
