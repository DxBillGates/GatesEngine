#include "..\..\Header\Graphics\Color.h"
#include "..\..\Header\Util\Math\Math.h"

GE::Color::Color()
	: Color(0,0,0,0)
{
}

GE::Color::Color(float r, float g, float b, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{
	if ((r + g + b + a) / 4 > 1)
	{
		r /= 255.0f;
		g /= 255.0f;
		b /= 255.0f;
		a /= 255.0f;
	}
}

GE::Color::Color(float rgb, float a)
	: Color(rgb,rgb,rgb,a)
{
}

GE::Color::Color(float rgba)
	: Color(rgba, rgba, rgba, rgba)
{
}

void GE::Color::SetAlpha(float value)
{
	a = value;
}

GE::Color GE::Color::Red()
{
	return Color(1,0,0,1);
}

GE::Color GE::Color::Green()
{
	return Color(0,1,0,1);
}

GE::Color GE::Color::Blue()
{
	return Color(0,0,1,1);
}

GE::Color GE::Color::White()
{
	return Color(1);
}

GE::Color GE::Color::Black()
{
	return Color(0,0,0,1);
}
