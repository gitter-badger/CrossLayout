//
// Created by Dawid Drozd aka Gelldur on 8/17/16.
//

#pragma once

#include <string>
#include <stdexcept>
#include <limits>
#include <type_traits>

namespace CrossLayout
{

template<class T>
class Point
{
public:
	T x;
	T y;

	constexpr Point(T x = 0, T y = 0)
			: x(x)
			, y(y)
	{
	}

	template<class From>
	constexpr Point(const From& from)
			: x(from.x)
			, y(from.y)
	{
	}

	constexpr Point(Point<T>&& other)
			: x(other.x)
			, y(other.y)
	{
	}

	Point& operator=(Point<T>&& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	Point& operator=(const Point<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	constexpr Point(const Point<T>& other)
			: x(other.x)
			, y(other.y)
	{
	}

	//Ctor for other signs eg. unsigned and signed types
	template<typename F
			, typename std::enable_if<
					std::is_unsigned<T>::value != std::is_unsigned<F>::value
					&& std::is_unsigned<F>::value, F
			>::type* = nullptr>
	Point(const Point<F>& point)
			:x(static_cast<T>(point.x))
			, y(static_cast<T>(point.y))
	{
		using Bigger = typename std::conditional<sizeof(T) >= sizeof(F), T, F>::type;
		if (point.x > static_cast<F>(std::numeric_limits<T>::max()))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (point.y > static_cast<F>(std::numeric_limits<T>::max()))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (static_cast<Bigger>(x) != static_cast<Bigger>(point.x))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (static_cast<Bigger>(y) != static_cast<Bigger>(point.y))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
	}

	//Ctor for other signs eg. unsigned and signed types
	template<typename F
			, typename std::enable_if<
					std::is_unsigned<T>::value != std::is_unsigned<F>::value
					&& std::is_signed<F>::value, F
			>::type* = nullptr>
	Point(const Point<F>& point)
			:x(static_cast<T>(point.x))
			, y(static_cast<T>(point.y))
	{
		using Bigger = typename std::conditional<sizeof(T) >= sizeof(F), T, F>::type;
		if (point.x < 0)
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (point.y < 0)
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (static_cast<Bigger>(x) != static_cast<Bigger>(point.x))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (static_cast<Bigger>(y) != static_cast<Bigger>(point.y))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
	}

	//Ctor for the same sign
	template<typename F
			, typename std::enable_if<std::is_unsigned<T>::value == std::is_unsigned<F>::value, F
			>::type* = nullptr>
	Point(const Point<F>& point)
			:x(static_cast<T>(point.x))
			, y(static_cast<T>(point.y))
	{
		using Bigger = typename std::conditional<sizeof(T) >= sizeof(F), T, F>::type;

		if (static_cast<Bigger>(x) != static_cast<Bigger>(point.x))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
		if (static_cast<Bigger>(y) != static_cast<Bigger>(point.y))
		{
			throw std::runtime_error("Can't convert. Data will be loosed or incorrect");
		}
	}

	Point<T> operator-(const Point<T>& right) const
	{
		return {x - right.x, y - right.y};
	}

	Point<T> operator+(const Point<T>& right) const
	{
		return {x + right.x, y + right.y};
	}

	Point& operator+=(const Point& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	std::string toString() const;
};

template<class T>
std::string Point<T>::toString() const
{
	return std::string("{") + std::to_string(x) + "," + std::to_string(y) + "}";
}

template<class T>
bool operator!=(const CrossLayout::Point<T>& left, const CrossLayout::Point<T>& right)
{
	return left.x != right.x || left.y != right.y;
}

template<class T>
bool operator<(const CrossLayout::Point<T>& left, const CrossLayout::Point<T>& right)
{
	return left.x < right.x || (left.x == right.x && left.y < right.y);
}

template<class T>
bool operator==(const CrossLayout::Point<T>& left, const CrossLayout::Point<T>& right)
{
	return left.x == right.x && left.y == right.y;
}
}
