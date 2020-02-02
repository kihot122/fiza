#include "render.hpp"

Renderer::Renderer(int W, int H)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	Window = SDL_CreateWindow("Symulacja pileczek :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	Rend = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Ball[0] = IMG_LoadTexture(Rend, "../data/particle_blue.png");
	Ball[1] = IMG_LoadTexture(Rend, "../data/particle_red.png");

	Width = W;
	Height = H;
}

void Renderer::Paint(Particle *Data, int Size, int Color)
{
	SDL_RenderClear(Rend);
	SDL_SetRenderDrawColor(Rend, 255, 255, 255, 255);
	SDL_RenderFillRect(Rend, NULL);
	//SDL_RenderCopy(Rend, Ball[0], NULL, NULL);
	for (int i = 0; i < Size; i++)
	{
		SDL_Rect T;
		T.x = (int)(Data[i].Pos.X * Width + 8);
		T.y = (int)(Height - Data[i].Pos.Y * Height + 8);
		T.w = 16;
		T.h = 16;
		SDL_RenderCopy(Rend, Ball[Color], NULL, &T);
	}

	SDL_RenderPresent(Rend);
}

void Renderer::Event()
{
	while (SDL_PollEvent(&E))
		if (E.type == SDL_WINDOWEVENT && E.window.event == SDL_WINDOWEVENT_CLOSE)
			Exit = true;
}

PlotRend::PlotRend(double W, double H, double max)
{
	SDL_Init(SDL_INIT_VIDEO);

	Window = SDL_CreateWindow("Wykresik", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	Rend = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(Rend, 255, 255, 255, 255);
	SDL_RenderFillRect(Rend, NULL);

	Points = new double[(int)W];
	Width = W;
	Height = H;
	Max = max;
}

void PlotRend::PlotNext(double Val)
{
	if (Current == 0)
	{
		SDL_SetRenderDrawColor(Rend, 255, 255, 255, 255);
		SDL_RenderFillRect(Rend, NULL);
	}
	Points[Current] = Val;
	SDL_SetRenderDrawColor(Rend, 0, 0, 0, 255);
	SDL_RenderDrawPoint(Rend, Current, (int)(Height - (Height * Points[Current] / Max)));
	SDL_RenderPresent(Rend);
	if (Current++ == Width)
		Current = 0;
}

void PlotRend::Event()
{
	while (SDL_PollEvent(&E))
		if (E.type == SDL_WINDOWEVENT && E.window.event == SDL_WINDOWEVENT_CLOSE)
			Exit = true;
}