#include<iostream>
#include "SDL.h"

#define DisplayWidth 500
#define DisplayHeight 500


struct Vector2
{
	float x;
	float y;
};

Vector2 point1;
Vector2 point2;
Vector2 point3;
Vector2 point4;


// Here if t = 0.0 then point 1 is drawn
// Here if t = 1.0 then point 4 is drawn
Vector2 CalculateCurve(float t) {

	float tt = t * t;
	float ttt = tt * t;
	float u = 1.0f - t;
	float uu = u * u;
	float uuu = uu * u;

	Vector2 point;

	point.x = (uuu * point1.x) + (3 * uu*t * point2.x) + (3 * u*tt * point3.x) + (ttt * point4.x);
	point.y = (uuu * point1.y) + (3 * uu*t * point2.y) + (3 * u*tt * point3.y) + (ttt * point4.y);

	return point;
}

int main(int argc, char* argv[])
{
	point1.x = 0;
	point1.y = 25.0f;

	std::cout << "Enter Start Point " << std::endl;
	std::cin >> point1.x;
	std::cin >> point1.y;

	std::cout << "Enter End Point " << std::endl;
	std::cin >> point4.x;
	std::cin >> point4.y;

	std::cout << "w a s d for control point 1" << std::endl;
	std::cout << "up down left right buttons for control point 2" << std::endl;
	std::cout << "Now , Click the Render Display" << std::endl;
	
	point3.x = 250.0f;
	point3.y = 250.0f;

	point2.x = 378.0f;
	point2.y = 125.0f;

	
	Vector2 Curvepoint;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(DisplayWidth, DisplayHeight,0, &window, &renderer) == 0) {
			SDL_bool isRunning = SDL_FALSE;

			while (!isRunning) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
				for (float i = 0.0 ;i < 1.0; i= i + 0.005) {
					Curvepoint = CalculateCurve(i);
					SDL_RenderDrawPoint(renderer, Curvepoint.x , Curvepoint.y);
				}
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_Rect startpoint = { point2.x + 10.0, point2.y + 10.0,4,4 };
				SDL_Rect endpoint = { point3.x + 10.0, point3.y + 10.0,4,4 };
				SDL_RenderFillRect(renderer, &startpoint);
				SDL_RenderFillRect(renderer, &endpoint);


				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						isRunning = SDL_TRUE;
					}
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_w :
							point2.y -= 2.0;
							
							break;
						case SDLK_a:
							point2.x -= 2.0;
							
							break;
						case SDLK_s:
							point2.y += 2.0;
							
							break;
						case SDLK_d:
							point2.x += 2.0;
							
							break;
						case SDLK_UP:
							point3.y -= 2.0;
							
							break;
						case SDLK_LEFT:
							point3.x -= 2.0;
							
							break;
						case SDLK_DOWN:
							point3.y += 2.0;
							
							break;
						case SDLK_RIGHT:
							point3.x += 2.0;
							
							break;

						}
					}
					if ( event.type == SDL_MOUSEMOTION) {
						if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT)) {
							//std::cout <<"Button Coordinates"<< event.button.x << " " << event.button.y << std::endl;
							//std::cout << "point Coordinates" << point2.x << " " << point2.y << std::endl;
							if (
								event.button.x > point2.x - 10.0
								&& event.button.x < point2.x + 10.0
								&&event.button.y > point2.y - 10.0
								&& event.button.y < point2.y + 10.0
								) {
								//std::cout << "Button Coordinates" << event.button.x << " " << event.button.y << std::endl;
								point2.x = event.button.x;
								point2.y = event.button.y;
							}
							if (
								event.button.x > point3.x - 10.0
								&& event.button.x < point3.x + 10.0
								&&event.button.y > point3.y - 10.0
								&& event.button.y < point3.y + 10.0
								) {
								//std::cout << "Button Coordinates" << event.button.x << " " << event.button.y << std::endl;
								point3.x = event.button.x;
								point3.y = event.button.y;
							}
						}
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}