CC = em++

FLAGS = -g4 -Wall -fpermissive -std=c++11 -D SGL_PLATFORM_WEB -D SGL_SOFT_FULLSCREEN

EM_FLAGS = -s FULL_ES3=1 -s USE_GLFW=3 -s DEMANGLE_SUPPORT=1 \
-s WASM=1 -s USE_WEBGL2=1 -lglfw3 -lGL
# -s DEMANGLE_SUPPORT=1 -s ASSERTIONS \
-s ALLOW_MEMORY_GROWTH=1 -s --memory-init-file 0 -s ERROR_ON_UNDEFINED_SYMBOLS=0

INC = -Ideps -Iinclude -Ideps/glm -Ideps/spdlog/include \
-Ideps/GLFW/include -Ideps/obj_loader/include -Ideps/stb_image/include -INemu/include -Ideps/imgui

TARGETS = obj/Application.o obj/IndexBuffer.o obj/LayerStack.o obj/Log.o obj/VertexArray.o \
obj/Shader.o obj/VertexBuffer.o obj/WebWindow.o obj/Renderer2D.o obj/BaseInput.o obj/EventQueue.o obj/Layer.o obj/Texture2D.o \
obj/Main.o obj/ImGuiLayer.o obj/ImGuiRenderer.o obj/imgui.o obj/imgui_demo.o obj/imgui_draw.o obj/imgui_widgets.o \
obj/Camera2D.o obj/Group.o obj/Renderable2D.o obj/FrameBuffer2D.o

nemu: $(TARGETS)
	$(CC) $(FLAGS) $(EM_FLAGS) $(INC) $(TARGETS) obj/Main.o -o emscripten/nemu/index.html --shell-file emscripten/layout.html

obj/Main.o: Nemu/src/Main.cpp
	$(CC) $(FLAGS) $(EM_FLAGS) $(INC) -c Nemu/src/Main.cpp -o obj/Main.o


obj/FrameBuffer2D.o: src/Graphics/FrameBuffer2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/FrameBuffer2D.cpp -o obj/FrameBuffer2D.o
obj/Renderable2D.o: src/Graphics/Renderable2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Renderable2D.cpp -o obj/Renderable2D.o
obj/Camera2D.o: src/Graphics/Camera2D.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Camera2D.cpp -o obj/Camera2D.o
obj/Group.o: src/Graphics/Group.cpp
	$(CC) $(FLAGS) $(INC) -c src/Graphics/Group.cpp -o obj/Group.o
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
obj/VertexArray.o: src/VertexArray.cpp
	$(CC) $(FLAGS) $(INC) -c src/VertexArray.cpp -o obj/VertexArray.o
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
obj/ImGuiLayer.o: src/ImGui/ImGuiLayer.cpp
	$(CC) $(FLAGS) $(INC) -c src/ImGui/ImGuiLayer.cpp -o obj/ImGuiLayer.o
obj/ImGuiRenderer.o: src/ImGui/ImGuiRenderer.cpp
	$(CC) $(FLAGS) $(INC) -c src/ImGui/ImGuiRenderer.cpp -o obj/ImGuiRenderer.o
obj/imgui.o: deps/imgui/imgui.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui.cpp -o obj/imgui.o
obj/imgui_demo.o: deps/imgui/imgui_demo.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_demo.cpp -o obj/imgui_demo.o
obj/imgui_draw.o: deps/imgui/imgui_draw.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_draw.cpp -o obj/imgui_draw.o
obj/imgui_widgets.o: deps/imgui/imgui_widgets.cpp
	$(CC) $(FLAGS) $(INC) -c deps/imgui/imgui_widgets.cpp -o obj/imgui_widgets.o