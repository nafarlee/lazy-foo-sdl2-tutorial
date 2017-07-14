#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

bool init(SDL_Window**, SDL_Surface**);
bool load_media(SDL_Surface*[]);
void terminate(SDL_Window**, SDL_Surface**);
SDL_Surface* load_surface(char[]);

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;


SDL_Surface* load_surface(char path[]) {
  SDL_Surface* loaded_surface = SDL_LoadBMP(path);

  if (loaded_surface == NULL)
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());

  return loaded_surface;
}


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


bool load_media(SDL_Surface *surface_container[]) {
  surface_container[KEY_PRESS_SURFACE_DEFAULT] = load_surface("./default.bmp");
  if (surface_container[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("%s\n", "Failed to load DEFAULT image");
    return false;
  }

  surface_container[KEY_PRESS_SURFACE_UP] = load_surface("./up.bmp");
  if (surface_container[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("%s\n", "Failed to load UP image");
    return false;
  }

  surface_container[KEY_PRESS_SURFACE_DOWN] = load_surface("./down.bmp");
  if (surface_container[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("%s\n", "Failed to load DOWN image");
    return false;
  }

  surface_container[KEY_PRESS_SURFACE_LEFT] = load_surface("./left.bmp");
  if (surface_container[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("%s\n", "Failed to load LEFT image");
    return false;
  }

  surface_container[KEY_PRESS_SURFACE_RIGHT] = load_surface("./right.bmp");
  if (surface_container[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("%s\n", "Failed to load RIGHT image");
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
  SDL_Surface* current_surface = NULL;

  if (!init(&window, &screen_surface)) return 1;
  if (!load_media(&current_surface)) return 1;

  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) quit = true;
    }
    SDL_BlitSurface(current_surface, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);
  }

  terminate(&window, &current_surface);
  return 0;
}
