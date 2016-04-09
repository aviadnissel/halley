#include "test_stage.h"
#include <gen/cpp/systems/test_system.h>
#include <gen/cpp/systems/render_system.h>

using namespace Halley;

void TestStage::init()
{
	world.addSystem(std::make_unique<TestSystem>(), TimeLine::FixedUpdate);
	world.addSystem(std::make_unique<RenderSystem>(), TimeLine::Render);

	id0 = world.createEntity()
		.addComponent(new TestComponent())
		.addComponent(new FooComponent())
		.addComponent(new BarComponent())
		.getEntityId();
}

void TestStage::deInit()
{
	std::cout << "Final bar: " << world.getEntity(id0).getComponent<BarComponent>()->bar << std::endl;
}

void TestStage::onVariableUpdate(Time)
{
}

void TestStage::onFixedUpdate(Time time)
{
	if (i == 20) {
		world.createEntity()
			.addComponent(new TestComponent())
			.addComponent(new FooComponent());
	}
	if (i == 40) {
		id2 = world.createEntity()
			.addComponent(new TestComponent())
			.addComponent(new BarComponent())
			.getEntityId();
	}
	if (i == 60) {
		world.getEntity(id2).removeComponent<TestComponent>();
	}
	if (i == 80) {
		world.destroyEntity(id2);
	}

	world.step(TimeLine::FixedUpdate, time);
	i++;

	if (i == 100) {
		//getAPI().core->quit();
	}
}

void TestStage::onRender(Painter& painter) const
{
	painter.clear(Colour(0.2f, 0.2f, 0.3f));
	world.render(painter);

	auto texture = getResource<Texture>("sprites/test.png");
	auto material = *getResource<Material>("shaders/sprite.yaml");
	material["tex0"] = texture;
	painter.drawSprite(material, Vector2f(100, 100));
}
