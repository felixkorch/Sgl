CC = em++

FLAGS = -O3 -g -Wall -fpermissive -std=c++11 -D PLATFORM_WEB -D WEB_SOFT_FULLSCREEN -D NDEBUG

EM_FLAGS = -s FULL_ES2=1 -s USE_GLFW=3 -s \
WASM=1 -s USE_WEBGL2=1 -s --memory-init-file 0 -lglfw3 -lGL -s ERROR_ON_UNDEFINED_SYMBOLS=0

INC = -Ideps -Iinclude -Ideps/glm -Ideps/spdlog/include \
-Ideps/GLFW/include -Ideps/Glad/include -Ideps/obj_loader/include -Ideps/stb_image/include -INemu/include \
-Ideps/imgui

TARGETS = obj/Application.o obj/IndexBuffer.o obj/LayerStack.o obj/Log.o \
obj/Shader.o obj/VertexBuffer.o obj/WebWindow.o obj/Renderer2D.o obj/BaseInput.o obj/EventQueue.o obj/Layer.o obj/Texture2D.o \
obj/Main.o obj/ImGuiLayer.o obj/ImGuiRenderer.o obj/imgui.o obj/imgui_demo.o obj/imgui_draw.o obj/imgui_widgets.o

nemu: $(TARGETS)
	$(CC) $(FLAGS) $(EM_FLAGS) $(INC) $(TARGETS) obj/Main.o -o emscripten/nemu/index.html --shell-file emscripten/layout.html

obj/Main.o: Nemu/src/Main.cpp
	$(CC) $(FLAGS) $(INC) -c Nemu/src/Main.cpp -o obj/Main.o

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
obj/Renderer2D.o: src/Graphics/Renderer2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Renderer2D.cpp -o obj/Renderer2D.o
obj/BaseInput.o: src/BaseInput.cpp
	$(CC) $(FLAGS) $(INC) -c src/BaseInput.cpp -o obj/BaseInput.o
obj/EventQueue.o: src/EventQueue.cpp
	$(CC) $(FLAGS) $(INC) -c src/EventQueue.cpp -o obj/EventQueue.o
obj/Layer.o: src/Layer.cpp
	$(CC) $(FLAGS) $(INC) -c src/Layer.cpp -o obj/Layer.o
obj/Texture2D.o: src/Graphics/Texture2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Texture2D.cpp -o obj/Texture2D.o
obj/ImGuiLayer.o: src/ImGuiLayer.cpp
	$(CC) $(FLAGS) $(INC) -c src/ImGuiLayer.cpp -o obj/ImGuiLayer.o
obj/ImGuiRenderer.o: src/ImGuiRenderer.cpp
	$(CC) $(FLAGS) $(INC) -c src/ImGuiRenderer.cpp -o obj/ImGuiRenderer.o
obj/imgui.o: deps/imgui/imgui.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui.cpp -o obj/imgui.o
obj/imgui_demo.o: deps/imgui/imgui_demo.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_demo.cpp -o obj/imgui_demo.o
obj/imgui_draw.o: deps/imgui/imgui_draw.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_draw.cpp -o obj/imgui_draw.o
obj/imgui_widgets.o: deps/imgui/imgui_widgets.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_widgets.cpp -o obj/imgui_widgets.o