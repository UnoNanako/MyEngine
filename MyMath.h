#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

//ベクトル
struct Vector2 {
	float x, y;
};
struct Vector3 {
	float x, y, z;
};
struct Vector4 {
	float x, y, z, w;
};

//行列
struct Matrix3x3 {
	float m[3][3];
};
struct Matrix4x4 {
	float m[4][4];
};

//球
struct Sphere {
	Vector3 center; //中心
	float radius; //半径
};

//3次元ベクトル関数
//加算
inline Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 ret;
	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return ret;
}
//減算
inline Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 ret;
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return ret;
}
//スカラー倍
inline Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 ret;
	ret.x = scalar * v.x;
	ret.y = scalar * v.y;
	ret.z = scalar * v.z;
	return ret;
}
//内積
inline float Dot(const Vector3& v1, const Vector3& v2) {
	float ret;
	ret = v1.x * v2.x + v1.y * v2.y;
	return ret;
}
//長さ(ノルム)
inline float Length(const Vector3& v) {
	float ret;
	ret = sqrtf(v.x * v.x + v.y * v.y);
	return ret;
}
//正規化
inline Vector3 Normalize(const Vector3& v) {
	Vector3 ret;
	float length = Length(v);
	if (length >= 0.0001f) { //0除算を防ぐため
		ret.x = v.x / length;
		ret.y = v.y / length;
		ret.z = v.z / length;
	}
	return ret;
}

//4x4行列関数
//1.行列の加法
inline Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 ret;
	ret.m[0][0] = m1.m[0][0] + m2.m[0][0];
	ret.m[0][1] = m1.m[0][1] + m2.m[0][1];
	ret.m[0][2] = m1.m[0][2] + m2.m[0][2];
	ret.m[0][3] = m1.m[0][3] + m2.m[0][3];
	ret.m[1][0] = m1.m[1][0] + m2.m[1][0];
	ret.m[1][1] = m1.m[1][1] + m2.m[1][1];
	ret.m[1][2] = m1.m[1][2] + m2.m[1][2];
	ret.m[1][3] = m1.m[1][3] + m2.m[1][3];
	ret.m[2][0] = m1.m[2][0] + m2.m[2][0];
	ret.m[2][1] = m1.m[2][1] + m2.m[2][1];
	ret.m[2][2] = m1.m[2][2] + m2.m[2][2];
	ret.m[2][3] = m1.m[2][3] + m2.m[2][3];
	ret.m[3][0] = m1.m[3][0] + m2.m[3][0];
	ret.m[3][1] = m1.m[3][1] + m2.m[3][1];
	ret.m[3][2] = m1.m[3][2] + m2.m[3][2];
	ret.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return ret;
}

//2.行列の減法
inline Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 ret;
	ret.m[0][0] = m1.m[0][0] - m2.m[0][0];
	ret.m[0][1] = m1.m[0][1] - m2.m[0][1];
	ret.m[0][2] = m1.m[0][2] - m2.m[0][2];
	ret.m[0][3] = m1.m[0][3] - m2.m[0][3];
	ret.m[1][0] = m1.m[1][0] - m2.m[1][0];
	ret.m[1][1] = m1.m[1][1] - m2.m[1][1];
	ret.m[1][2] = m1.m[1][2] - m2.m[1][2];
	ret.m[1][3] = m1.m[1][3] - m2.m[1][3];
	ret.m[2][0] = m1.m[2][0] - m2.m[2][0];
	ret.m[2][1] = m1.m[2][1] - m2.m[2][1];
	ret.m[2][2] = m1.m[2][2] - m2.m[2][2];
	ret.m[2][3] = m1.m[2][3] - m2.m[2][3];
	ret.m[3][0] = m1.m[3][0] - m2.m[3][0];
	ret.m[3][1] = m1.m[3][1] - m2.m[3][1];
	ret.m[3][2] = m1.m[3][2] - m2.m[3][2];
	ret.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return ret;
}

//3.行列の積
inline Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 ret;
	ret.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	ret.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	ret.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	ret.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	ret.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	ret.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	ret.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	ret.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	ret.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	ret.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	ret.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	ret.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	ret.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	ret.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	ret.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	ret.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return ret;
}

//4.逆行列
inline Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 ret;
	ret.m[0][0] = m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1];
	ret.m[0][1] = m.m[0][1] * m.m[2][3] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2];
	ret.m[0][2] = m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][3] * m.m[1][2] * m.m[3][1];
	ret.m[0][3] = m.m[0][1] * m.m[1][3] * m.m[2][2] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2];

	ret.m[1][0] = m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2];
	ret.m[1][1] = m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][3] * m.m[2][2] * m.m[3][0];
	ret.m[1][2] = m.m[0][0] * m.m[1][3] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2];
	ret.m[1][3] = m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][3] * m.m[1][2] * m.m[2][0];

	ret.m[2][0] = m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0];
	ret.m[2][1] = m.m[0][0] * m.m[2][3] * m.m[3][1] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1];
	ret.m[2][2] = m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][3] * m.m[1][1] * m.m[3][0];
	ret.m[2][3] = m.m[0][0] * m.m[1][3] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1];

	ret.m[3][0] = m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1];
	ret.m[3][1] = m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][2] * m.m[2][1] * m.m[3][0];
	ret.m[3][2] = m.m[0][0] * m.m[1][2] * m.m[3][1] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1];
	ret.m[3][3] = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[1][1] * m.m[2][0];
	return ret;
}

//5.転置行列
inline Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 ret;
	ret.m[0][0] = m.m[0][0];
	ret.m[0][1] = m.m[1][0];
	ret.m[0][2] = m.m[2][0];
	ret.m[0][3] = m.m[3][0];
	ret.m[1][0] = m.m[0][1];
	ret.m[1][1] = m.m[1][1];
	ret.m[1][2] = m.m[2][1];
	ret.m[1][3] = m.m[3][1];
	ret.m[2][0] = m.m[0][2];
	ret.m[2][1] = m.m[1][2];
	ret.m[2][2] = m.m[2][2];
	ret.m[2][3] = m.m[3][2];
	ret.m[3][0] = m.m[0][3];
	ret.m[3][1] = m.m[1][3];
	ret.m[3][2] = m.m[2][3];
	ret.m[3][3] = m.m[3][3];
	return ret;
}

//6.単位行列の生成
inline Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 ret;
	ret.m[0][0] = 1.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

//7.平行移動行列
inline Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 ret;
	ret.m[0][0] = 1.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = translate.x;
	ret.m[3][1] = translate.y;
	ret.m[3][2] = translate.z;
	ret.m[3][3] = 1.0f;
	return ret;
}

//8. 拡大縮小行列
inline Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 ret;
	ret.m[0][0] = scale.x;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = scale.y;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = scale.z;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

//9. 座標変換
inline Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
	Vector3 ret;
	ret.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	ret.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	ret.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	return ret;
}

//10. x軸回転行列
inline Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = 1.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = std::cos(radian);
	ret.m[1][2] = std::sin(radian);
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = -std::sin(radian);
	ret.m[2][2] = std::cos(radian);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

//11. y軸回転行列
inline Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = std::cos(radian);
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = -std::sin(radian);
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = std::sin(radian);
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = std::cos(radian);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

//12. z軸回転行列
inline Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = std::cos(radian);
	ret.m[0][1] = std::sin(radian);
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = -std::sin(radian);
	ret.m[1][1] = std::cos(radian);
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

//13. 3次元アフィン変換行列
inline Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 ret;
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	ret = Multiply(scaleMatrix, rotateXMatrix);
	ret = Multiply(ret, rotateYMatrix);
	ret = Multiply(ret, rotateZMatrix);
	ret = Multiply(ret, translateMatrix);
	return ret;
}

//14. 透視投影行列
inline Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 ret;
	float dot = farClip * nearClip;
	float tan = std::tan(fovY / 2.0f);
	ret.m[0][0] = 1.0f / aspectRatio * tan;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = tan;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = nearClip / (nearClip - farClip);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = -dot / (nearClip - farClip);
	ret.m[3][3] = 0.0f;
	return ret;
}

//15. 正射影行列(平行投影行列)
inline Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 ret;
	ret.m[0][0] = 2.0f / (right - 1.0f);
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 2.0f / (top - bottom);
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f / (farClip - nearClip);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = (left + right) / (left - right);
	ret.m[3][1] = (top + bottom) / (bottom - top);
	ret.m[3][2] = nearClip / (nearClip - farClip);
	ret.m[3][3] = 1.0f;
	return ret;
}

//16. ビューポート変換行列
inline Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 ret;
	ret.m[0][0] = width / 2.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = -(height / 2.0f);
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = maxDepth - minDepth;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = left + width / 2.0f;
	ret.m[3][1] = top + height / 2.0f;
	ret.m[3][2] = minDepth;
	ret.m[3][3] = 1.0f;
	return ret;
}
