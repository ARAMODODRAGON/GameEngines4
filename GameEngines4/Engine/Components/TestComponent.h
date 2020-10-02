#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H
#include "../Rendering/3D/GameObject.h"

class TestComponent1 : public Component {

public:

	TestComponent1();
	virtual ~TestComponent1();

	virtual void OnCreate() override;
	virtual void Update(const float& delta) override;
	virtual void OnDestroy() override;

};

class TestComponent2 : public TestComponent1 {

public:

	TestComponent2();
	~TestComponent2();

	virtual void OnCreate() override;
	virtual void Update(const float& delta) override;
	virtual void OnDestroy() override;

};


#endif // !TEST_COMPONENT_H