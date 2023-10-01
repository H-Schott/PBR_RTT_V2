#ifndef __COLOR_HPP__
#define __COLOR_HPP__

class Color {
public:

	int r;
	int g;
	int b;

	Color();
	Color(int _r, int _g, int _b);
	Color(int value);
	Color(float _r, float _g, float _b);
	Color(float value);

	Color ToGray();
	Color ToGray(float kr, float kg, float kb);
};

#endif