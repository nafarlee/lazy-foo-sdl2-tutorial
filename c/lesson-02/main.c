#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

bool init(SDL_Window**, SDL_Surface**);
bool load_media(SDL_Surface**);
void terminate(SDL_Window**, SDL_Surface**);

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;


bool init(SDL_Window** window, SDL_Surface** screen_surface) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  } 

  *window = SDL_CreateWindow("SDL Tutorial!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (*window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  *screen_surface = SDL_GetWindowSurface(*window);
  return true;
}


bool load_media(SDL_Surface** surface) {
  *surface = SDL_LoadBMP("lena_gray.bmp");

  if (*surface == NULL) {
    printf("Image could not be loaded! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}


void terminate(SDL_Window** window, SDL_Surface** surface) {
  SDL_FreeSurface(*surface);
  *surface = NULL;

  SDL_DestroyWindow(*window);
  *window =  NULL;

  SDL_Quit();
}


int main () {
  SDL_Window* window = NULL;
  SDL_Surface* screen_surface = NULL;
  SDL_Surface* lena = NULL;

  if (!init(&window, &screen_surface)) return 1;
  if (!load_media(&lena)) return 1;

  SDL_BlitSurface(lena, NULL, screen_surface, NULL);
  SDL_UpdateWindowSurface(window);

  SDL_Delay(2 * 1000);

  terminate(&window, &lena);
  return 0;
}
