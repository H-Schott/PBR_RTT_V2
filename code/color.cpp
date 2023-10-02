#include "color.hpp"

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {

}

Color::Color(int value) {
	r = value;
	g = value;
	b = value;
}

Color::Color(float _r, float _g, float _b) {
	r = int(255. * _r);
	g = int(255. * _g);
	b = int(255. * _b);
}

Color::Color(float value) {
	r = int(255. * value);
	g = int(255. * value);
	b = int(255. * value);
}


Color Color::ToGray() const {
	return ToGray(0.3, 0.59, 0.11);
}

Color Color::ToGray(float kr, float kg, float kb) const {
	return Color(kr * r + kg * g + kb * b);
}



// EOF