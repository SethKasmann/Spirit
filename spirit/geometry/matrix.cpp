#include "matrix.h"
#include "vec.h"

namespace spirit {

	mat4::mat4()
	: _elements{0}
	{}

	mat4::mat4(float value)
	: _elements{0}
	{
		_elements[cmajor(0, 0)]  = value;
		_elements[cmajor(1, 1)]  = value;
		_elements[cmajor(2, 2)]  = value;
		_elements[cmajor(3, 3)] = value;
	}

	float& mat4::at(int row, int col)
	{
		return _elements[cmajor(row, col)];
	}

	float mat4::at(int row, int col) const
	{
		return _elements[cmajor(row, col)];
	}

	void mat4::operator*=(const mat4& mat)
	{
		std::array<float, mat_size> temp = {};
		for (int i = 0; i < mat_width; ++i)
		{
			for (int j = 0; j < mat_width; ++j)
			{
				for (int k = 0; k < mat_width; ++k)
				{
					temp[cmajor(i, j)] += _elements[cmajor(i, k)] * mat.at(k, j);
				}
			}
		}
		_elements = temp;
	}

	float* mat4::operator*()
	{
		return &_elements[0];
	}

	void mat4::orthographic(float l, float r, float b, float t, float n, float f)
	{
		_elements[cmajor(0, 0)] = 2.0 / (r - l);
		_elements[cmajor(1, 1)] = 2.0 / (t - b);
		_elements[cmajor(2, 2)] = -2.0 / (f - n);
		_elements[cmajor(3, 0)] = -(r + l) / (r - l);
		_elements[cmajor(3, 1)] = -(t + b) / (t - b);
		_elements[cmajor(3, 2)] = -(f + n) / (f - n);
	}

	void mat4::perspective(float fovy, float aspect, float n, float f)
	{
		_elements[cmajor(0, 0)] = cot(fovy / 2.0) / aspect;
		_elements[cmajor(1, 1)] = cot(fovy / 2.0);
		_elements[cmajor(2, 2)] = (n + f) / (n - f);
		_elements[cmajor(2, 3)] = (2.0 * n * f) / (n - f);
		_elements[cmajor(3, 2)] = -1.0;
		_elements[cmajor(3, 3)] = 0;
	}

	void mat4::translation(const vec3& vec)
	{
		_elements[cmajor(0, 3)] = vec.x;
		_elements[cmajor(1, 3)] = vec.y;
		_elements[cmajor(2, 3)] = vec.z;
	}

	void mat4::scaling(const vec3& vec)
	{
		_elements[cmajor(0, 0)] = vec.x;
		_elements[cmajor(1, 1)] = vec.y;
		_elements[cmajor(2, 2)] = vec.z;
	}

	void mat4::rotation(float degrees, const vec3& vec)
	{
		float radians = degrees * PI / 180.0;
		float c = cos(radians);
		float s = sin(radians);
		float t = 1.0 - c;

		_elements[cmajor(0, 0)] = t * vec.x * vec.x + c;
		_elements[cmajor(0, 1)] = t * vec.x * vec.y - s * vec.z;
		_elements[cmajor(0, 2)] = t * vec.x * vec.z + s * vec.y;
		_elements[cmajor(1, 0)] = t * vec.y * vec.x + s * vec.z;
		_elements[cmajor(1, 1)] = t * vec.y * vec.y + c;
		_elements[cmajor(1, 2)] = t * vec.y * vec.z - s * vec.x;
		_elements[cmajor(2, 0)] = t * vec.x * vec.z - s * vec.y;
		_elements[cmajor(2, 1)] = t * vec.y * vec.z + s * vec.x;
		_elements[cmajor(2, 2)] = t * vec.z * vec.z + c;
	}

	std::ostream& operator<<(std::ostream& o, const mat4& mat)
	{
		o << "<mat4 " << &mat;
		for (int row = 0; row < mat_width; ++row)
		{
			o << '\n';
			for (int col = 0; col < mat_width; ++col)
				o << '[' << std::setw(5) << mat.at(row, col) << ']';
		}
		o << "\n>";
		return o;
	}
}