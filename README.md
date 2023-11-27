# Proyecto2Grafica

## Configuración Inicial

- **`#define SDL_MAIN_HANDLED`**: Se utiliza para evitar que SDL defina su propio punto de entrada `main`, ya que el programa proporciona el suyo.
- **`#include <SDL.h>` y otras inclusiones**: Importan las bibliotecas necesarias de SDL y otras dependencias.
- Se define una variable global `hasWon` para rastrear si el jugador ha ganado el juego.

## Funciones Básicas

### `clear`

- Establece el color de fondo del renderizador y lo limpia.

### `welcomeScreen`

- Muestra una pantalla de bienvenida con una imagen hasta que se presiona la barra espaciadora o se cierra la ventana.

### `draw_floor`

- Dibuja el suelo en el renderizador con colores dados.

## Función `loadMapAndRunGame`

- Carga el mapa desde un archivo proporcionado y ejecuta el bucle principal del juego.
- Registra eventos de teclado para controlar el movimiento y la rotación del jugador.
- Llama a funciones para limpiar la pantalla, dibujar el suelo y renderizar la escena.

## Función Principal `main`

- Inicializa SDL y crea la ventana y el renderizador.
- Carga imágenes necesarias para el juego, como texturas de paredes y fondos.
- Crea un objeto `Raycaster` y muestra una pantalla de bienvenida.
- En el bucle principal, espera la selección del nivel por parte del jugador y carga el mapa correspondiente.
- Inicia el bucle principal del juego, que maneja eventos, actualiza la escena y renderiza.

## Bucle Principal del Juego

- Maneja eventos de teclado para seleccionar el nivel y salir del juego.
- Muestra la pantalla de selección de nivel hasta que el jugador selecciona uno.
- Carga el mapa del nivel seleccionado y ejecuta el bucle principal del juego.
- Dentro del bucle, actualiza la escena y muestra estadísticas de FPS.


##Video:
https://youtu.be/oumWbsTV8Eo
