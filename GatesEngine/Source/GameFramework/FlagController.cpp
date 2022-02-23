#include "..\..\Header\GameFramework\FlagController.h"

GE::FlagController::FlagController()
	: flag(false)
	, elapsedTime(0)
	, preElapsedTime(0)
	, PROPERTY_MAX_TIME(1)
{
}

GE::FlagController::~FlagController()
{
}

void GE::FlagController::Initialize()
{
	flag = false;
	preElapsedTime = 0;
	elapsedTime = 0;
	PROPERTY_MAX_TIME = 1;
}

void GE::FlagController::Update(float deltaTime)
{
	if (!flag)return;

	preElapsedTime = elapsedTime;
	float addValue = deltaTime / PROPERTY_MAX_TIME;
	elapsedTime += addValue;
}

bool GE::FlagController::GetOverTimeTrigger()
{
	if (preElapsedTime < 1 && elapsedTime >= 1)
	{
		return true;
	}
	return false;
}

bool GE::FlagController::GetFlag()
{
	return flag;
}

float GE::FlagController::GetTime()
{
	return elapsedTime;
}

float GE::FlagController::GetMaxTimeProperty()
{
	return PROPERTY_MAX_TIME;
}

void GE::FlagController::SetFlag(bool setFlag)
{
	flag = setFlag;
}

void GE::FlagController::SetTime(float setValue)
{
	elapsedTime = setValue;
}

void GE::FlagController::SetMaxTimeProperty(const float value)
{
	PROPERTY_MAX_TIME = value;
}

bool GE::FlagController::IsOverTime(float value)
{
	return (elapsedTime >= value);
}

bool GE::FlagController::IsUnderTime(float value)
{
	return (elapsedTime <= value);
}
