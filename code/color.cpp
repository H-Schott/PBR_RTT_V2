#include "color.hpp"

#include <algorithm>

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

Color::Color(double _r, double _g, double _b) {
	r = int(255. * _r);
	g = int(255. * _g);
	b = int(255. * _b);
}

Color::Color(double value) {
	r = int(255. * value);
	g = int(255. * value);
	b = int(255. * value);
}


Color Color::ToGray() const {
	return ToGray(0.3, 0.59, 0.11);
}

Color Color::ToGray(double kr, double kg, double kb) const {
	return Color(int(kr * r + kg * g + kb * b));
}


Color operator*(double a, const Color& color) {
	int r = std::min(255, int(a * color.r));
	int g = std::min(255, int(a * color.r));
	int b = std::min(255, int(a * color.r));
	return Color(r, g, b);
}


// EOF