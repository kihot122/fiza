g++ -O3 -march=native -c "./src/main.cpp" -o "./obj/main.obj"
g++ -O3 -march=native -c "./src/particle.cpp" -o "./obj/particle.obj"
g++ -O3 -march=native -c "./src/plot.cpp" -o "./obj/plot.obj"
g++ -O3 -march=native -c "./src/render.cpp" -o "./obj/render.obj"

g++ "./obj/main.obj" "./obj/particle.obj" "./obj/plot.obj" "./obj/render.obj" -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o "./bin/program.exe"