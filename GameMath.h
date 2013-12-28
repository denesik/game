#ifndef GameMath_h__
#define GameMath_h__


template <typename T>
struct Rectangle2
{
	T x, y;
	T w, h;
};

typedef Rectangle2<int>		Rectangle2i;
typedef Rectangle2<float>	Rectangle2f;
typedef Rectangle2<double>	Rectangle2d;

#endif // GameMath_h__