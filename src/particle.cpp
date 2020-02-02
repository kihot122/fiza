#include <chrono>
#include <random>
#include <iostream>
#include <cmath>
#include "particle.hpp"

World::World(int Count, double Entropy)
{
    Size = Count;
    Data = new Particle[Size];
    Old = new Point[Size];

    std::ranlux24_base rand;
    rand.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 0; i < Size; i++)
    {
        Data[i].Vel.X = ((double)(rand() % 2000000) - 1000000) / 10000000;
        Data[i].Vel.Y = ((double)(rand() % 2000000) - 1000000) / 10000000;
        Data[i].Pos.X = (double)(rand() % (int)(Entropy * 1000000)) / 1000000;
        //Data[i].Pos.Y = (double)(rand() % (int)(Entropy * 1000000)) / 1000000;
        Data[i].Pos.Y = (double)(rand() % (int)(1000000)) / 1000000;
    }
}

World::World(int Count, Particle *_Data)
{
    Size = Count;
    Data = new Particle[Size];
    Old = new Point[Size];
    Data = _Data;
}

double Dot(Point A, Point B)
{
    return A.X * B.X + A.Y * B.Y;
}

double LenSq(Point A)
{
    return A.X * A.X + A.Y * A.Y;
}

void World::Tick(double Mult)
{
    for (int i = 0; i < Size; i++)
    {
        Old[i].X = Data[i].Pos.X;
        Old[i].Y = Data[i].Pos.Y;
        Data[i].Pos.X += Data[i].Vel.X * Mult;
        Data[i].Pos.Y += Data[i].Vel.Y * Mult;
    }

    for (int x = 0; x < Size; x++)
        for (int y = x + 1; y < Size; y++)
        {
            double dist = std::sqrt(std::pow(Data[x].Pos.X - Data[y].Pos.X, 2) + std::pow(Data[x].Pos.Y - Data[y].Pos.Y, 2));
            if (dist <= thresold)
            {
                double delta = std::sqrt(std::pow(Old[x].X - Old[y].X, 2) + std::pow(Old[x].Y - Old[y].Y, 2));
                if (delta > dist)
                {
                    //old stuff
                    //std::swap(Data[x].Vel.X, Data[y].Vel.X);
                    //std::swap(Data[x].Vel.Y, Data[y].Vel.Y);

                    //new shiny stuff
                    
                    double A = LenSq(Data[x].Pos - Data[y].Pos);
                    double B = LenSq(Data[y].Pos - Data[x].Pos); 

                    if(A == 0 || B == 0)
                        continue;
                    
                    Point TempX, TempY;
                    
                    TempX = Data[x].Vel - (Data[x].Pos - Data[y].Pos) * (Dot(Data[x].Vel - Data[y].Vel, Data[x].Pos - Data[y].Pos) / A);
                    TempY = Data[y].Vel - (Data[y].Pos - Data[x].Pos) * (Dot(Data[y].Vel - Data[x].Vel, Data[y].Pos - Data[x].Pos) / B);
                
                    Data[x].Vel = TempX;
                    Data[y].Vel = TempY;
                }
            }
        }
    for (int i = 0; i < Size; i++)
    {
        if ((Data[i].Pos.X >= 1 && Data[i].Pos.Y >= 1) || (Data[i].Pos.X >= 1 && Data[i].Pos.Y < 0) || (Data[i].Pos.X < 0 && Data[i].Pos.Y >= 1) || (Data[i].Pos.X < 0 && Data[i].Pos.Y < 0))
        {
            Data[i].Vel.X = -Data[i].Vel.X;
            Data[i].Vel.Y = -Data[i].Vel.Y;
        }

        else if (Data[i].Pos.X >= 1 || Data[i].Pos.X < 0)
            Data[i].Vel.X = -Data[i].Vel.X;

        else if (Data[i].Pos.Y >= 1 || Data[i].Pos.Y < 0)
            Data[i].Vel.Y = -Data[i].Vel.Y;
    }
    /*
    printf("DEBUG\n");
    for(int i=0; i<Size; i++)
    {
        printf("%g %g\n", Data[i].Vel.X, Data[i].Vel.Y);
    }
    printf("DEBUG\n");
    */
}
