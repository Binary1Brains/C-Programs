#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void koch(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, int depth)
  {
    if (depth == 0)
    {
        lineRGBA(renderer, x1, y1, x2, y2, 255, 255, 255, 255);
        return;
    }
    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;
    float x3 = x1 + dx;
    float y3 = y1 + dy;
    float x5 = x2 - dx;
    float y5 = y2 - dy;
    float angle = M_PI / 3.0;
    float x4 = x3 + (dx * cos(angle) - dy * sin(angle));
    float y4 = y3 + (dx * sin(angle) + dy * cos(angle));
    koch(renderer, x1, y1, x3, y3, depth - 1);
    koch(renderer, x3, y3, x4, y4, depth - 1);
    koch(renderer, x4, y4, x5, y5, depth - 1);
    koch(renderer, x5, y5, x2, y2, depth - 1);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <depth>\n", argv[0]);
        return 1;
    }
    int depth = atoi(argv[1]);
    if (depth < 0 )
    {
        fprintf(stderr, "Please enter a depth greater than 0.\n");
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Koch Snowflake",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool running = true;
    SDL_Event event;
    float x1 = 200, y1 = 400;
    float x2 = 600, y2 = 400;
    float x3 = 400, y3 = 400 - sqrt(3) * 200;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        koch(renderer, x1, y1, x2, y2, depth);
        koch(renderer, x2, y2, x3, y3, depth);
        koch(renderer, x3, y3, x1, y1, depth);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
