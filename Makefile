CC = em++

FLAGS= -O3 -g -Wall -fpermissive -std=c++11 -DUSE_EMSCRIPTEN -s FULL_ES3=1 -s USE_GLFW=3 -s \
WASM=1 -s USE_WEBGL2=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 --memory-init-file 0 --embed-file res -lglfw3 -lGL

INC = -ISgl/libs -ISgl/include -ISgl/libs/glm -ISgl/libs/Glad/include -ISgl/libs/spdlog/include \
-ISgl/libs/GLFW/include

SRC = Sgl/src/Application.cpp Sgl/src/IndexBuffer.cpp Sgl/src/Input.cpp Sgl/src/LayerStack.cpp Sgl/src/Log.cpp Sgl/src/Shader.cpp \
Sgl/src/VertexArray.cpp Sgl/src/VertexBuffer.cpp Sgl/src/Window.cpp Sgl/src/Graphics/BatchRenderer.cpp Sgl/src/Graphics/ForwardRenderer.cpp \
Sgl/src/Graphics/Material.cpp Sgl/src/Graphics/Mesh.cpp Sgl/src/Graphics/Texture.cpp Sandbox/MouseTest.cpp

OBJDIR = emscripten/obj

Main:
	$(CC) $(SRC) $(FLAGS) $(INC) -o emscripten/index.html