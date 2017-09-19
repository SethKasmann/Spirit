#include <array>
#include <iostream>
#include <iomanip>
#include <cmath>

namespace spirit {

	#define PI 3.14159265358979323846

	static const int identity    = 0;
	static const int translation = 1;
	static const int scaling     = 2;

	static const size_t mat_size  = 16;
	static const size_t mat_width = 4;

	inline int cmajor(int row, int col)
	{
		return row + col * mat_width;
	}

	inline float cot(float x)
	{
		return (1 / tan(x));
	}

	class vec3;

	class mat4
	{
	public:
		mat4();
		mat4(float value);
		float& at(int row, int col);
		float at(int row, int col) const;
		void operator*=(const mat4& mat);
		float* operator*();
		void orthographic(float l, float r, float b, float t, float n, float f);
		void perspective(float fovy, float aspect, float n, float f);
		void translation(const vec3& vec);
		void scaling(const vec3& vec);
		void rotation(float degrees, const vec3& vec);
		friend std::ostream& operator<<(std::ostream& o, const mat4& m);
	private:
		std::array<float, mat_size> _elements;
	};

}