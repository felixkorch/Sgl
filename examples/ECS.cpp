#include <Sgl.h>
#include <memory>
#include <stack>
#include <numeric>
#include <string>
#include <iostream>

#define SPRITE_C 0
#define POSITION_C 1
#define VELOCITY_C 2
#define BLUE_C 3
#define COMPONENT_COUNT 4
#define RESERVED_ENTITY_COUNT 100
#define MAX_ENTITY_COUNT 1000
#define INITIAL_ENTITY_CAP 8

struct SpriteComponent {
	sgl::Sprite spr;
};

struct PositionComponent {
	float x;
	float y;
};

struct VelocityComponent {
	float x;
	float y;
};

struct BlueComponent {
};

struct ComponentLayout {
	SpriteComponent sprite; // 0
	PositionComponent position; // 1
	VelocityComponent velocity; // 2
	BlueComponent blue; // 3
};

constexpr int sizeArray[] { // Stores the size of each component.
		sizeof(SpriteComponent), // 0
		sizeof(PositionComponent), // 1
		sizeof(VelocityComponent), // 2
		sizeof(BlueComponent) }; // 3

template <size_t Size>
constexpr int AggregateArray(const int(&arr)[Size], int offset)
{
	int ret = 0;
	for (int i = 0; i < offset; ++i)
		ret += arr[i];
	return ret;
}

constexpr std::array<int, COMPONENT_COUNT> offsetArray { // Stores the offset of each component.
	AggregateArray(sizeArray, 0),
	AggregateArray(sizeArray, 1),
	AggregateArray(sizeArray, 2),
	AggregateArray(sizeArray, 3)
};

template <class T>
int GetComponentID() {}
template <> constexpr int GetComponentID<SpriteComponent>() { return SPRITE_C; }
template <> constexpr int GetComponentID<PositionComponent>() { return POSITION_C; }
template <> constexpr int GetComponentID<VelocityComponent>() { return VELOCITY_C; }
template <> constexpr int GetComponentID<BlueComponent>() { return BLUE_C; }

template <class T>
int GetComponentOffset() {}
template <> constexpr int GetComponentOffset<SpriteComponent>() { return offsetArray[SPRITE_C]; }
template <> constexpr int GetComponentOffset<PositionComponent>() { return offsetArray[POSITION_C]; }
template <> constexpr int GetComponentOffset<VelocityComponent>() { return offsetArray[VELOCITY_C]; }
template <> constexpr int GetComponentOffset<BlueComponent>() { return offsetArray[BLUE_C]; }

typedef int Entity; // An entity just an integer ID

struct QueryResult {
	int count;
	std::vector<Entity> result;

	QueryResult(int initialEntityCount, int maxEntityCount) :
		result(initialEntityCount)
	{
		result.reserve(maxEntityCount);
	}

	void Resize(int newSize)
	{
		result.resize(newSize);
	}

	void Push(Entity ent)
	{
		result[count++] = ent;
	}

	void Clear() { count = 0; }
};

class ECS {

	struct EntityLayout {
		ComponentLayout componentData = {}; // Data that each entity stores.
		std::int32_t componentMask = 0; // Tells which components this entity has.
		bool alive = false;
	};

	// Stores the data of all entities. Each index represent an entity ID.
	// Starts at size INITIAL_ENTITY_CAP and grows if needed.
	// The size is critical since the query will loop through every entity, hence recycling is used.
	std::vector<EntityLayout> entityStore;

	// Re-use slots of entities that have been killed.
	std::stack<int> recycledSlots;

	QueryResult queryResult;
	int entityCap;
	Entity nextID;

private:
	void SetAlive(Entity ent)
	{
		entityStore[ent].alive = true;
	}

	void IncreaseEntityCap()
	{
		entityCap *= 2;
		entityStore.resize(entityCap);
		queryResult.Resize(entityCap);
	}

public:
	ECS() :
		entityStore(INITIAL_ENTITY_CAP),
		entityCap(INITIAL_ENTITY_CAP),
		queryResult(INITIAL_ENTITY_CAP, MAX_ENTITY_COUNT),
		nextID(0)
	{
		entityStore.reserve(MAX_ENTITY_COUNT);
	}

	Entity Create()
	{
		Entity newID;
		if (!recycledSlots.empty()) {
			newID = recycledSlots.top();
			recycledSlots.pop();
		}
		else {
			newID = nextID++;
		}
		
		if (newID == entityCap)
			IncreaseEntityCap();

		sgl::SGL_TRACE("NEW ENTITY WITH ID {}", newID);

		SetAlive(newID);
		return newID;
	}

	// O(1)
	void* GetComponentData(const Entity ent, int componentID)
	{
		return &entityStore[ent].componentData + offsetArray[componentID];
	}

	template <class T>
	T* GetComponentData(const Entity ent)
	{
		return (T*)&entityStore[ent].componentData + GetComponentOffset<T>();
	}

	// O(1)
	void AddComponentToEntity(Entity ent, int componentID, void* data)
	{
		void* insertPos = GetComponentData(ent, componentID);
		std::memcpy(insertPos, data, sizeArray[componentID]);
		entityStore[ent].componentMask |= (1 << componentID);
	}

	template <class T>
	void AddComponentToEntity(Entity ent, const T& data)
	{
		T* insertPos = GetComponentData<T>(ent);
		*insertPos = data;
		entityStore[ent].componentMask |= (1 << GetComponentID<T>());
	}

	void RemoveComponentFromEntity(const Entity* ent, int componentID)
	{

	}

	bool EntityHasComponent(const Entity* ent, int componentID)
	{
	}

	// O(n), n = entityCap
	QueryResult* QueryEntities(int n, ...)
	{
		queryResult.Clear();

		// Create appropriate component mask.
		va_list args;
		int mask = 0;
		va_start(args, n);
		for (int i = 0; i < n; i++)
			mask |= (1 << va_arg(args, int));
		va_end(args);

		// Find entities based on mask.
		for (Entity id = 0; id < entityStore.size(); id++) {
			if (entityStore[id].alive && mask == (entityStore[id].componentMask & mask))
				queryResult.Push(id);
		}
		return &queryResult;
	}

};

Entity CreateSnakeHead(ECS& ecs, int x, int y)
{
	sgl::Sprite spr;
	auto tiles = std::make_shared<sgl::Texture2D>(512, 512);
	spr.FromTexture(tiles);

	SpriteComponent snakeHeadSprite = { spr };
	PositionComponent snakeHeadPosition = { x, y };
	Entity snakeHead = ecs.Create();
	ecs.AddComponentToEntity<SpriteComponent>(snakeHead, snakeHeadSprite);
	ecs.AddComponentToEntity<PositionComponent>(snakeHead, snakeHeadPosition);
	return snakeHead;
}


class SnakeLayer : public sgl::Layer {
private:
	sgl::BatchRenderer renderer;
	ECS ecs;
	float mouseX, mouseY;
public:

	SnakeLayer() :
		Layer("Snake Layer"),
		renderer(512, 512)
	{
		for (int i = 0; i < 1; i++) {
			Entity s2 = CreateSnakeHead(ecs, i * 32, 0);
		}
	}

	void System_Draw()
	{
		QueryResult* qr = ecs.QueryEntities(2, SPRITE_C, POSITION_C);
		for (int i = 0; i < qr->count; i++) {
			SpriteComponent* sprite_component = ecs.GetComponentData<SpriteComponent>(qr->result[i]);
			PositionComponent* pos_component = ecs.GetComponentData<PositionComponent>(qr->result[i]);
			renderer.Submit(sprite_component->spr, glm::vec2(pos_component->x, pos_component->y));
		}
	}

	void System_Velocity()
	{
		QueryResult* qr = ecs.QueryEntities(1, VELOCITY_C);
		for (int i = 0; i < qr->count; i++) {
			PositionComponent* pos = ecs.GetComponentData<PositionComponent>(qr->result[i]);
			VelocityComponent* vel = ecs.GetComponentData<VelocityComponent>(qr->result[i]);
			pos->x += vel->x;
			pos->y += vel->y;
		}
	}

	void AddVelocity()
	{
		QueryResult* qr = ecs.QueryEntities(1, POSITION_C);
		for (int i = 0; i < qr->count; i++) {
			const Entity ent = qr->result[i];
			ecs.AddComponentToEntity<VelocityComponent>(ent, { 0, 1 });
		}
	}

	void OnUpdate() override
	{
		//System_Position();
		System_Velocity();

		renderer.Begin();

		System_Draw();

		renderer.End();
	}

	void OnEvent(sgl::Event& e) override
	{
		if (e.GetEventType() == sgl::EventType::KeyPressed) {
			sgl::KeyPressedEvent& keyEv = (sgl::KeyPressedEvent&)e;
			int keyCode = keyEv.GetKeyCode();
			if (keyCode == SGL_KEY_UP || keyCode == SGL_KEY_DOWN || keyCode == SGL_KEY_LEFT || keyCode == SGL_KEY_LEFT) {
				//ChangeDirection(keyCode, snakeEnt);
			}
		}
		else if (e.GetEventType() == sgl::EventType::MouseMoved) {
			sgl::MouseMovedEvent& mouseEv = (sgl::MouseMovedEvent&)e;
			mouseX = mouseEv.GetXPos();
			mouseY = 512 - mouseEv.GetYPos();
		}
		else if (e.GetEventType() == sgl::EventType::MouseButtonReleased) {
			sgl::MouseButtonReleased& mouseEv = (sgl::MouseButtonReleased&)e;
			AddVelocity();
		}
	}
};

const sgl::WindowProperties props{
		512,         // WindowWidth
		512,         // WindowHeight
		false,       // Resizable
		"ECS",		 // Title
};

class ECSApp : public sgl::Application {
private:

public:

	ECSApp()
		: sgl::Application(props)
	{
		PushLayer(new SnakeLayer);
	}

	~ECSApp()
	{
	}

};

sgl::Application* sgl::CreateApplication()
{
	return new ECSApp;
}
