#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length() const { return static_cast<float>(sqrt(static_cast<double>(x) * static_cast<double>(x) + static_cast<double>(y) * static_cast<double>(y))); } // 빗변
	bool IsZero()
	{
		if (0.f == x && 0.f == y)
			return true;
		return false;
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f); // 분모가 0이면 inf되니까 예외처리
		x /= fLen;
		y /= fLen;

		return *this;
	}

	Vec2 operator +(Vec2 _vOther)
	{
		return(Vec2(x + _vOther.x, y + _vOther.y));
	}
	Vec2 operator += (Vec2 _vOther)
	{
		(*this).x += _vOther.x;
		(*this).y += _vOther.y;

		return *this;
	}
	Vec2 operator -(Vec2 _vOther)
	{
		return(Vec2(x - _vOther.x, y - _vOther.y));
	}
	Vec2 operator *(Vec2 _vOther)
	{
		return(Vec2(x * _vOther.x, y * _vOther.y));
	}
	Vec2 operator *(int _i)
	{
		return(Vec2(x * (float)_i, y * (float)_i));
	}
	Vec2 operator *(float _f)
	{
		return(Vec2(x * _f, y * _f));
	}


	Vec2 operator /(Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return(Vec2(x / _f, y / _f));
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}
	Vec2(const Vec2& _vec)
		: x((float)_vec.x)
		, y((float)_vec.y)
	{}



};