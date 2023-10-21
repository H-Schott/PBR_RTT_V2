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
	Color(double _r, double _g, double _b);
	Color(double value);

	Color ToGray() const;
	Color ToGray(double kr, double kg, double kb) const;

	static Color Red()    { return Color(255, 0  , 0);   };
	static Color Green()  { return Color(0  , 255, 0);   };
	static Color Blue()   { return Color(0  , 0  , 255); };
	static Color White()  { return Color(255, 255, 255); };
	static Color Black()  { return Color(0  , 0  , 0);   };
};


Color operator*(double a, const Color& color);


#endif