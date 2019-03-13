CC = em++

FLAGS= -O3 -g -Wall -fpermissive -std=c++11 -DUSE_EMSCRIPTEN -s FULL_ES2=1 -s USE_GLFW=3 -s \
WASM=1 -s USE_WEBGL2=1 -s ASSERTIONS=1 --memory-init-file 0 --embed-file res -lglfw3 -lGL -s ERROR_ON_UNDEFINED_SYMBOLS=0

INC = -ISgl/libs -ISgl/include -ISgl/libs/glm -ISgl/libs/spdlog/include \
-ISgl/libs/GLFW/include -ISgl/libs/Glad/include

SRC = Sgl/src/Application.cpp Sgl/src/IndexBuffer.cpp Sgl/src/LayerStack.cpp Sgl/src/Log.cpp Sgl/src/Shader.cpp \
Sgl/src/VertexBuffer.cpp Sgl/src/GenericWindow.cpp Sgl/src/Platform/GLES2/Renderer2D_ES2.cpp Sgl/src/Graphics/ForwardRenderer.cpp \
Sgl/src/Graphics/Material.cpp Sgl/src/Graphics/Mesh.cpp Sgl/src/Graphics/Texture2D.cpp Sgl/libs/stb_image/stb_image.cpp \
Sgl/src/GenericInput.cpp Sgl/src/EventQueue.cpp Sgl/src/Layer.cpp \
Sandbox/MouseTest.cpp

Main:
	$(CC) $(SRC) $(FLAGS) $(INC) -o emscripten/mousetest/index.html