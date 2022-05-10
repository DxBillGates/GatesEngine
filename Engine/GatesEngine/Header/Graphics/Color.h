#pragma once

namespace GE
{
	struct Color
	{
		float r, g, b, a;

		Color();
		Color(float r,float g,float b,float a);
		Color(float rgb, float a);
		Color(float rgba);

		void SetAlpha(float value);

		static Color Red();
		static Color Green();
		static Color Blue();
		static Color White();
		static Color Black();
	};
}
