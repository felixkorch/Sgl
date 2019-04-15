CC = em++

FLAGS= -O3 -g -Wall -fpermissive -std=c++11 -DUSE_EMSCRIPTEN -s FULL_ES2=1 -s USE_GLFW=3 -s \
WASM=1 -s USE_WEBGL2=1 -s ASSERTIONS=1 --memory-init-file 0 --embed-file res -lglfw3 -lGL -s ERROR_ON_UNDEFINED_SYMBOLS=0 -DWEB_SOFT_FULLSCREEN

INC = -Ideps -Iinclude -Ideps/glm -Ideps/spdlog/include \
-Ideps/GLFW/include -Ideps/Glad/include -Ideps/obj_loader/include -Ideps/stb_image/include -INemu/include

SRC = src/Application.cpp src/IndexBuffer.cpp src/LayerStack.cpp src/Log.cpp src/Shader.cpp \
src/VertexBuffer.cpp src/Platform/Web/WebWindow.cpp src/Platform/GLES2/Renderer2D_ES2.cpp \
src/Graphics/Texture2D.cpp deps/stb_image/src/stb_image.cpp \
src/GenericInput.cpp src/EventQueue.cpp src/Layer.cpp \
Nemu/src/Main.cpp

Main:
	$(CC) $(SRC) $(FLAGS) $(INC) -o emscripten/nemu/index.html --shell-file emscripten/layout.html