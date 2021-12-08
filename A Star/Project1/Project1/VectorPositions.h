//////////
//////////Vector 2 files
//////////Written by Tanapat Somrid 
/////////Starting 01/12/2021
//////// Most Recent Update 07/12/2021

#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <iostream>
template <typename T> class Vector2 {
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	Vector2() {};
	/// <summary>
	/// Individual Coordinate Constructor
	/// </summary>
	Vector2(T x, T y) : Vector2() { this->x = x; this->y = y; }
	/// <summary>
/// Assignment with different typename
/// </summary>
	template <typename U> explicit Vector2(const Vector2<U>& difPrimitive) {
		x = difPrimitive.x; y = difPrimitive.y;
	}
	//Copy Constructor
	Vector2(const Vector2& rhs) { x = rhs.x; y = rhs.y; }//Required for assignment and required for below operatorr//	Vector2<int> dif = position;
	Vector2& operator =(const Vector2& copy) { x = copy.x; y = copy.y; return *this; }//So this will copy/assign//		Node* endNode = new Node(endPos);





	T x, y;

	T Magnitude() {
		return (T)(sqrt((x * x) + (y * y)));
	}
	static T Magnitude(Vector2<T>& vector) {
		return (T)(sqrt((vector.x * vector.x) +(vector.y * vector.y)));
	}
	/// <summary>
/// The EUCLIDEAN distance from this vector and the given coordinates (x and y)
/// </summary>
/// <returns>EUCLIDEAN DISTANCE</returns>
	int DistanceFrom(T x, T y) { return sqrt(((x - this->x) * (x - this->x)) + ((y - this->y) * (y - this->y))); }
	/// <summary>
	/// The EUCLIDEAN distance from this vector and the given vector
	/// </summary>
	/// <returns>EUCLIDEAN DISTANCE</returns>
	int DistanceFrom(const Vector2<T>& pos) {
		int x = pos.x - x; int y = pos.y - y;
		int sq = sqrt((x * x) + (y * y));
		return sq;
	}
	/// <summary>
	/// The EUCLIDEAN distance between two given vectors
	/// <para> From vector A to vector B</para>
	/// </summary>
	/// <param name="Vector A"></param>
	/// <param name="Vector B"></param>
	/// <returns>EUCLIDEAN DISTANCE</returns>
	static int DistanceBetween(const Vector2& a, const Vector2& b) {
		int x = b.x - a.x; int y = b.y - a.y;
		int sq = sqrt((x * x) + (y * y));
		return sq;
	}

};

/*
///Not called?
//template <typename T> Vector2<T> operator +(const Vector2<T>& rhs) {
//	this.x += rhs.x;
//	this.y += rhs.y;
//	return this;
//
//	//Vector2<T> newVector;
//	//newVector.x = lhs.x + rhs.x;
//	//newVector.y = lhs.y + rhs.y;
//	//return newVector;
//}
	////bool operator <(const Vector2<T>* a) {
	////	return (Magnitude() < a->Magnitude());
	////}
	////bool operator >(const Vector2<T>* a) {
	////	return (Magnitude() > a->Magnitude());
	////}

	////constexpr Vector2<T>& operator ()(const Vector2<T>& copy) {
	////	lhs->x = x + rhs->x;
	////	lhs->y = y + rhs->y;
	////	return lhs;
	////}
	//// Vector2<T>& operator -(const Vector2<T>& rhs) { //messy
	////	//x = x - rhs.x;
	////	//y = y - rhs.y;
	////	//return *this;
	////	std::shared_ptr<Vector2<T>> newVector(new Vector2<T>);
	////	newVector->x = x - rhs.x;
	////	newVector->y = y - rhs.y;
	////	return *newVector;
	////}	 
	//// Vector2<T> operator +(const Vector2<T>& rhs) { //messy
	////	 std::shared_ptr<Vector2<T>> newVector(new Vector2<T>);
	////	 newVector->x = x + rhs.x;
	////	 newVector->y = y + rhs.y;
	////	 return *newVector;
	////}
	*/

/// <summary>
/// This works
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
template <typename T> Vector2<T> operator +(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>((lhs.x + rhs.x), (lhs.y + rhs.y));
}
template <typename T> Vector2<T> operator -(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>((lhs.x - rhs.x), (lhs.y - rhs.y));
}


template <typename T> Vector2<T>& operator +=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	//lhs.x = lhs.x + rhs.x;
	//lhs.y = lhs.y + rhs.y;
	//return *lhs;
	Vector2<T> newVector;
	newVector.x = lhs.x + rhs.x;
	newVector.y = lhs.y + rhs.y;
	return newVector;
}
//template <typename T> Vector2<T>& operator -(const Vector2<T>& lhs, const Vector2<T>& rhs) {
//	//lhs.x = lhs.x - rhs.x;
//	//lhs.y = lhs.y - rhs.y;
//	//return *lhs;
//	Vector2<T> newVector;
//	newVector.x = lhs.x - rhs.x;
//	newVector.y = lhs.y - rhs.y;
//	return newVector;
//}
template <typename T> Vector2<T>& operator -=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	//lhs.x = lhs.x - rhs.x;
	//lhs.y = lhs.y - rhs.y;
	//return *lhs;
	Vector2<T> newVector;
	newVector.x = lhs.x - rhs.x;
	newVector.y = lhs.y - rhs.y;
	return newVector;
}
template <typename T> bool operator ==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}
template <typename T> bool operator !=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

template <typename T> bool operator >(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return (lhs.Magnitude() > rhs.Magnitude());
}
template <typename T> bool operator <(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return (lhs.Magnitude() < rhs.Magnitude());
}

template<typename T> std::ostream& operator<<(std::ostream& stream, Vector2<T> const& vector)
{
	return stream << "X:" << vector.x << " Y:" << vector.y;
}
#endif // !VECTOR2_H
