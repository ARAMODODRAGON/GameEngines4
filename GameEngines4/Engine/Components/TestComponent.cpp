#include "TestComponent.h"

TestComponent1::TestComponent1() { }

TestComponent1::~TestComponent1() { }

void TestComponent1::OnCreate() {
	DEBUG_INFO("I am a test component #1");
}

void TestComponent1::Update(const float& delta) { }

void TestComponent1::OnDestroy() { }



TestComponent2::TestComponent2() { }

TestComponent2::~TestComponent2() { }

void TestComponent2::OnCreate() {
	DEBUG_INFO("I am a test component #2");
}

void TestComponent2::Update(const float& delta) { }

void TestComponent2::OnDestroy() { }
