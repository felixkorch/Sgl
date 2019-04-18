CC = em++

FLAGS = -O3 -g -Wall -fpermissive -std=c++11 -DUSE_EMSCRIPTEN -DWEB_SOFT_FULLSCREEN -DNDEBUG

EM_FLAGS = -s FULL_ES2=1 -s USE_GLFW=3 -s \
WASM=1 -s USE_WEBGL2=1 -s --memory-init-file 0 -lglfw3 -lGL -s ERROR_ON_UNDEFINED_SYMBOLS=0

INC = -Ideps -Iinclude -Ideps/glm -Ideps/spdlog/include \
-Ideps/GLFW/include -Ideps/Glad/include -Ideps/obj_loader/include -Ideps/stb_image/include -INemu/include

TARGETS = obj/Application.o obj/IndexBuffer.o obj/LayerStack.o obj/Log.o \
obj/Shader.o obj/VertexBuffer.o obj/WebWindow.o obj/Renderer2D_ES2.o obj/GenericInput.o obj/EventQueue.o obj/Layer.o obj/Texture2D.o

nemu: lib Nemu/src/Main.cpp
	$(CC) $(FLAGS) $(EM_FLAGS) $(INC) Nemu/src/Main.cpp -L obj -l Sgl -o emscripten/nemu/index.html --shell-file emscripten/layout.html

lib: $(TARGETS)
	ar -rcs obj/Sgl.a \
	$(TARGETS)

obj/Application.o: src/Application.cpp
	$(CC) $(FLAGS) $(INC) -c src/Application.cpp -o obj/Application.o
obj/IndexBuffer.o: src/IndexBuffer.cpp
	$(CC) $(FLAGS) $(INC) -c src/IndexBuffer.cpp -o obj/IndexBuffer.o
obj/LayerStack.o: src/LayerStack.cpp
	$(CC) $(FLAGS) $(INC) -c src/LayerStack.cpp -o obj/LayerStack.o
obj/Log.o: src/Log.cpp
	$(CC) $(FLAGS) $(INC) -c src/Log.cpp -o obj/Log.o
obj/Shader.o: src/Shader.cpp
	$(CC) $(FLAGS) $(INC) -c src/Shader.cpp -o obj/Shader.o
obj/VertexBuffer.o: src/VertexBuffer.cpp
	$(CC) $(FLAGS) $(INC) -c src/VertexBuffer.cpp -o obj/VertexBuffer.o
obj/WebWindow.o: src/Platform/Web/WebWindow.cpp
	$(CC) $(FLAGS) $(INC) -c src/Platform/Web/WebWindow.cpp -o obj/WebWindow.o
obj/Renderer2D_ES2.o: src/Platform/GLES2/Renderer2D_ES2.cpp
	$(CC) $(FLAGS) $(INC) -c src/Platform/GLES2/Renderer2D_ES2.cpp -o obj/Renderer2D_ES2.o
obj/GenericInput.o: src/GenericInput.cpp
	$(CC) $(FLAGS) $(INC) -c src/GenericInput.cpp -o obj/GenericInput.o
obj/EventQueue.o: src/EventQueue.cpp
	$(CC) $(FLAGS) $(INC) -c src/EventQueue.cpp -o obj/EventQueue.o
obj/Layer.o: src/Layer.cpp
	$(CC) $(FLAGS) $(INC) -c src/Layer.cpp -o obj/Layer.o
obj/Texture2D.o: src/Graphics/Texture2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Texture2D.cpp -o obj/Texture2D.o