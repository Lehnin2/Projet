all: compile_app debug_app

safe_run: compile_app run_app

compile_app:
	gcc -D_FORTIFY_SOURCE=2 -fsanitize=address *.c -o karma $(sdl-config --libs) -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
debug_app:
	gdb ./karma
run_app:
	./karma