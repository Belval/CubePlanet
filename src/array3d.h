#ifndef Array3d_H__
#define Array3d_H__

#include "define.h"

template <class T>
class Array3d
{
public:
    Array3d(int x, int y, int z);
    ~Array3d();
    Array3d(const Array3d& array);

    void Set(int x, int y, int z, T type);
    T Get(int x, int y, int z) const;

    void Reset(T type);

private:
    int m_x, m_y, m_z;
    T* m_blocs;

    T& GetElement(int x, int y, int z);
    const T& GetElement(int x, int y, int z) const;
};
template <class T>
Array3d<T>::Array3d(int x, int y, int z) : m_x(x), m_y(y), m_z(z), m_blocs(new T[m_x * m_y * m_z])
{
	Reset(BTYPE_AIR);
}
template <class T>
Array3d<T>::~Array3d()
{
}
template <class T>
Array3d<T>::Array3d(const Array3d& array)
{
	m_x = array.m_x;
	m_y = array.m_y;
	m_z = array.m_z;

	m_blocs = new T[m_x * m_y * m_z];
	for (int i = 0; i < m_x * m_y * m_z; ++i)
		m_blocs[i] = array.m_blocs[i];
}
template <class T>
void Array3d<T>::Set(int x, int y, int z, T type)
{
	GetElement(x, y, z) = type;
}
template <class T>
T Array3d<T>::Get(int x, int y, int z) const
{
	return GetElement(x, y, z);
}
template <class T>
void Array3d<T>::Reset(T type)
{
	for (int i = 0; i < m_x * m_y * m_z; ++i)
		m_blocs[i] = type;
}
template <class T>
T& Array3d<T>::GetElement(int x, int y, int z)
{
	return m_blocs[x + (z * m_x) + (y * m_z * m_x)];
}
template <class T>
const T& Array3d<T>::GetElement(int x, int y, int z) const
{
	return m_blocs[x + (z * m_x) + (y * m_z * m_x)];
}
#endif // Array3d_H__
