#pragma once

#include "kotek_component_allocator.h"

#include <kotek.core.defines_dependent.ecs/include/kotek_core_defines_dependent_ecs.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_GAME
KOTEK_BEGIN_NAMESPACE_ECS
KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND

class ktkComponentHandleCamera
{
	KOTEK_COMPONENT(ktkComponentHandleCamera)

public:
	ktkComponentHandleCamera(void) {}
	~ktkComponentHandleCamera(void) {}
};

class ktkComponentHandleInput
{
	KOTEK_COMPONENT(ktkComponentHandleInput)

public:
	ktkComponentHandleInput(void) {}
	~ktkComponentHandleInput(void) {}
};

class ktkComponentHandleModel
{
	KOTEK_COMPONENT(ktkComponentHandleModel)

public:
	ktkComponentHandleModel(void) {}
	~ktkComponentHandleModel(void) {}
};

class ktkComponentHandleTransform
{
	KOTEK_COMPONENT(ktkComponentHandleTransform)

public:
	ktkComponentHandleTransform(void) {}
	~ktkComponentHandleTransform(void) {}
};

class ktkComponentHandleVisibility
{
	KOTEK_COMPONENT(ktkComponentHandleVisibility)

public:
	ktkComponentHandleVisibility(void) {}
	~ktkComponentHandleVisibility(void) {}
};

class ktkComponentHandleActor
{
	KOTEK_COMPONENT(ktkComponentHandleActor)

public:
	ktkComponentHandleActor(void) {}
	~ktkComponentHandleActor(void) {}
};

KOTEK_END_NAMESPACE_ECS_FRONTEND
KOTEK_END_NAMESPACE_ECS
KOTEK_END_NAMESPACE_GAME
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_ECS(ktkMainManager* p_manager);
bool SerializeModule_Core_ECS(ktkMainManager* p_manager);
bool DeserializeModule_Core_ECS(ktkMainManager* p_manager);
bool ShutdownModule_Core_ECS(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK