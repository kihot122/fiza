#include <iostream>
#include <windows.h>
#include <chrono>
#include <cmath>
#include <string>

#include "render.hpp"
#include "particle.hpp"
#include "plot.hpp"

int main(int argc, char *argv[])
{
	int Size = std::stoi(argv[1]);

	double MaxEntropia = 1;
	if(Size > 100)
		MaxEntropia = Size * log(Size) - Size;
	else
	{
		int x = Size;
		while (x > 0) {
			MaxEntropia *= x;
			x--;
		}
		MaxEntropia = log(MaxEntropia);
	}

	World W(Size, 0.1); //1 argument to liczba pileczek, 2 to entropia poczatkowa (1 = max, 0 = spawn w punkcie)
	
	Renderer R(1000, 1000);
	PlotRend P(1800, 200, MaxEntropia);
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();

	while (!R.Exit && !P.Exit)
	{
		t2 = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() >= 15625000) //15625000
		{
			t1 = std::chrono::high_resolution_clock::now();
			W.Tick(1.0 / 64.0);
			R.Paint(W.Data, W.Size, 0);
			R.Event();
			P.PlotNext(ComputeEntrophy(W.Data, W.Size));
			P.Event();
		}
	}

	return 0;
}
