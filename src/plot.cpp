#include "plot.hpp"
#include <cmath>

double ComputeEntrophy(Particle* Data, int Size)
{
	
	double entropia = 1;

	if (Size > 100)
		entropia = Size * log(Size) - Size;
	else
	{
		int x = Size;
		while (x > 0) {
			entropia *= x;
			x--;
		}
		entropia = log(entropia);
	}

	int T[10][10][10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				for (int l = 0; l < 10; l++)
				{
					T[i][j][k][l] = 0;
				}
			}
		}
	}

	int X, Y, velX, velY;

	for (int i = 0; i < Size; i++)
	{
		if (Data[i].Pos.X * 10 >= 10)
			X = 9;
		else
			X = (int)(Data[i].Pos.X * 10);

		if (Data[i].Pos.Y * 10 >= 10)
			Y = 9;
		else
			Y = (int)(Data[i].Pos.Y * 10);

		if ((Data[i].Vel.X + 0.1 )* 5 >= 10)
			velX = 9;
		else
			velX = (int)((Data[i].Vel.X + 0.1)*5);

		if ((Data[i].Vel.Y + 0.1) * 5 >= 10)
			velY = 9;
		else
			velY = (int)((Data[i].Vel.Y + 0.1) * 5);

		T[X][Y][velX][velY]++;
	}
	double liczba = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				for (int l = 0; l < 10; l++)
				{
					while (T[i][j][k][l] > 0)
					{
						liczba = liczba * T[i][j][k][l];
						T[i][j][k][l]--;
					}
					entropia -= log(liczba);
					liczba = 1;
				}
			}
		}
	}

	return entropia;
}


/*
<-0.1;0.1> | + 0.1
<0.0;0.2> | * 5
<0.0;1.0>
*/