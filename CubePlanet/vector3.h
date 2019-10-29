#ifndef VECTOR3_H__
#define VECTOR3_H__
#include "define.h"
#include <cmath>

template <class T>
class Vector3 
{
public:
	Vector3(const T& x = T(), const T& y = T(), const T& z = T()); // Équivalent de mettre à 0
	~Vector3();

	T Length() const;
	// Pour avoir le vecteur de longeur 1
	void Normalize();
	// Mettre le x, y, z
	void Zero();

	// Retourne l'angle entre deux vecteurs
	T Dot(const Vector3<T>& v) const;
	// Retourne un vecteur perpendiculaire
	Vector3<T> Cross(const Vector3<T>& v) const;

	Vector3<T> operator+(const Vector3<T>& v) const;
	Vector3<T> operator-(const Vector3<T>& v) const;
	Vector3<T> operator-() const;

	Vector3<T> operator+(const T& v) const;
	Vector3<T> operator-(const T& v) const;
	Vector3<T> operator*(const T& v) const;
	Vector3<T> operator/(const T& v) const;

	Vector3<T> operator=(const Vector3<T> v);

	Vector3<T> operator+=(const Vector3<T>& v);
	Vector3<T> operator-=(const Vector3<T>& v);
	Vector3<T> operator+=(const T& v);
	Vector3<T> operator-=(const T& v);
	Vector3<T> operator*=(const T& v);
	Vector3<T> operator/=(const T& v);

	bool operator==(const Vector3<T>& v) const;
	bool operator!=(const Vector3<T>& v) const;


public:
	T x, y, z;
};

template<class T>
inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& v)
{
	out << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return out;
}

template<class T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z)
{
}

template<class T>
T Vector3<T>::Length() const
{
	// La distance qu<on va parcourir dans n'importe quelle direction
	return sqrt(x*x + y*y + z*z);
}

template<class T>
void Vector3<T>::Normalize()
{
	// On trouve la longueur du vecteur
	T n = Length();

	// On divise nos longueurs par la longueur du vecteur pour obtenir un vecteur de longueur 1.
	if (n != 0)
	{
		x /= n;
		y /= n;
		z /= n;

	}
}

template<class T>
void Vector3<T>::Zero()
{
	// Valide parce que le compilateur commence par z = 0
	x = y = z = 0;
}

template<class T>
T Vector3<T>::Dot(const Vector3<T>& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

template<class T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& v) const
{
	return Vector3<T>(y * v.z - v.y * z,
					  z * v.x - v.z * x,
				      x * v.y - v.x * y);
}

template<class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template<class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
{
	return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template<class T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3<T>(-x, -y, -z);
}

template<class T>
Vector3<T> Vector3<T>::operator+(const T & v) const
{
	return Vector3<T>(x + v, y + v, z + v);
}

template<class T>
Vector3<T> Vector3<T>::operator-(const T & v) const
{
	return Vector3<T>(x - v, y - v, z - v);
}

template<class T>
Vector3<T> Vector3<T>::operator*(const T & v) const
{
	return Vector3<T>(x * v, y * v, z * v);
}

template<class T>
Vector3<T> Vector3<T>::operator/(const T & v) const
{
	return Vector3<T>(x / v, y / v, z / v);
}

template<class T>
Vector3<T> Vector3<T>::operator=(const Vector3<T> v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator+=(const Vector3<T>& v)
{
	return (*this = *this + v);
}

template<class T>
Vector3<T> Vector3<T>::operator-=(const Vector3<T>& v)
{
	return (*this = *this - v);
}

template<class T>
Vector3<T> Vector3<T>::operator+=(const T & v)
{
	return (*this = *this + v);
}

template<class T>
Vector3<T> Vector3<T>::operator-=(const T & v)
{
	return (*this = *this - v);
}

template<class T>
Vector3<T> Vector3<T>::operator*=(const T & v)
{
	return (*this = *this * v);
}

template<class T>
Vector3<T> Vector3<T>::operator/=(const T & v)
{
	return (*this = *this / v);
}

template<class T>
bool Vector3<T>::operator==(const Vector3<T>& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

template<class T>
bool Vector3<T>::operator!=(const Vector3<T>& v) const
{
	return !(*this == v);
}

template<class T>
Vector3<T>::~Vector3()
{
}

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
#endif
