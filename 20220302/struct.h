#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length() const { return static_cast<float>(sqrt(static_cast<double>(x) * static_cast<double>(x) + static_cast<double>(y) * static_cast<double>(y))); } // 빗변
	Vec2& _abs() 
	{ 
		if (x < 0)
			x *= -1;
		
		if (y < 0)
			y *= -1;

		return *this;
	}
	bool IsZero()
	{
		if (0.f == x && 0.f == y)
			return true;
		return false;
	}

	Vec2& Normalize()
	{
		float fLen = Length();

//		assert(fLen != 0.f); // 분모가 0이면 inf되니까 예외처리
		x /= fLen;
		y /= fLen;

		return *this;
	}

	Vec2 operator +(Vec2 _vOther)
	{
		return(Vec2(x + _vOther.x , y + _vOther.y));
	}
	Vec2 operator += (Vec2 _vOther)
	{
		(*this).x += _vOther.x;
		(*this).y += _vOther.y;

		return *this;
	}
	Vec2 operator -= (Vec2 _vOther)
	{
		(*this).x -= _vOther.x;
		(*this).y -= _vOther.y;

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
	Vec2 operator *(double _i)
	{
		return(Vec2(x * (float)_i, y * (float)_i));
	}

	Vec2 operator *(float _f)
	{
		return(Vec2(x * _f, y * _f));
	}
	Vec2 operator -()
	{;
		return Vec2(-(*this).x, -(*this).y);
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
	Vec2 operator *= (float _f)
	{
		(*this).x *= _f;
		(*this).y *= _f;

		return *this;
	}

	Vec2 Rotate(int _iValue)
	{
		Vec2 vTemp = *this;
		vTemp.x = vTemp.x * static_cast<float>(cos(_iValue * PI / 180)) + vTemp.y * static_cast<float>(sin(_iValue * PI / 180));
		vTemp.y = -vTemp.x * static_cast<float>(sin(_iValue * PI / 180)) + vTemp.y * static_cast<float>(cos(_iValue * PI / 180));

		return vTemp;
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

/** 게임 캐릭터와 아이템들의 스펙 */
struct Stat
{
	int			m_iMaxHP;
	int			m_iHP;
	int			m_iDmg;
	float		m_fSpeed;
	float		m_fShotSpeed;
	float		m_fRange;
	float		m_fRate;

public:
	Stat operator += (Stat _vOther)
	{
		(*this).m_iMaxHP += _vOther.m_iMaxHP;
		(*this).m_iHP += _vOther.m_iHP;
		(*this).m_iDmg += _vOther.m_iDmg;
		(*this).m_fSpeed += _vOther.m_fSpeed;
		(*this).m_fShotSpeed += _vOther.m_fShotSpeed;
		(*this).m_fRange += _vOther.m_fRange;
		(*this).m_fRate += _vOther.m_fRate;

		return *this;
	}

public:

	void Heal(UINT _iValue)
	{
		if (m_iHP == m_iMaxHP - 1)
		{
			(*this).m_iHP += 1;
		}
		else 
			(*this).m_iHP += _iValue;
	}
	/** DestStat에 캐릭터 데미지만큼 피해를 입힙니다. */
	void InflictDamage(int _iDmg)
	{
		m_iHP -= _iDmg;
	}
};

/** 플레이어의 Pickup 개수를 담는 구조체*/
struct Pickup
{
	UINT		m_iCoin;
	UINT		m_iBomb;
	UINT		m_iKey;

public:
	void SetCoin(int _iValue)
	{
		m_iCoin += _iValue;
	}
	void SetBomb(int _iValue)
	{
		m_iBomb += _iValue;
	}
	void SetKey(int _iValue)
	{
		m_iKey += _iValue;
	}
	Pickup operator += (Pickup _vOther)
	{
		(*this).m_iCoin += _vOther.m_iCoin;
		(*this).m_iKey += _vOther.m_iKey;
		(*this).m_iBomb += _vOther.m_iBomb;

		return *this;
	}

};