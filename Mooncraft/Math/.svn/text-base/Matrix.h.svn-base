#pragma once

#include "common/Types.h"
#include "MathTypes.h"

namespace phynet{
namespace math{

template <int Row, int Col>
class Matrix
{
public:
	typedef Matrix<Col,Row> TransposeType;

	Matrix()
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] = 0.0f;
	}

	Real GetElem(int i, int j) const
	{
		return m_data[i*Col+j];
	}
	
	void GetElems(Real* o_vec) const
	{
		for(int i=0; i<NUM_ELEM; ++i)
			o_vec[i] = m_data[i];
	}

	void SetElem(int i, int j, const Real i_value)
	{
		m_data[i*Col+j] = i_value;
	}

	void SetElems(Real* const i_data)
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] = i_data[i];
	}
	
	Matrix& operator*=(const Matrix& i_other)
	{
		const Matrix temp(*this);
		Mul(temp, i_other, *this);
	}
	
	Matrix& operator*=(const Real i_value)
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] *= i_value;
		return *this;
	}

	Matrix& operator/=(const Real i_value)
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] /= i_value;
		return *this;
	}

	Matrix& operator+=(const Matrix& i_other)
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] += i_other.m_data[i];
		return *this;
	}

	Matrix& operator-=(const Matrix& i_other)
	{
		for(int i=0; i<NUM_ELEM; ++i)
			m_data[i] -= i_other.m_data[i];
		return *this;
	}

	Real GetDeterminant() const;

	void Invert();
	void GetInverse(Matrix& o_inverse) const
	{
		o_inverse = *this;
		o_inverse.Invert();
	}

	void SetIdentity();

	bool IsOrtho() const;

	bool IsDiagonal() const;

	void SetDiagonal(Real* const i_data); 

	void Transpose();
	void GetTranspose(TransposeType& o_trans) const;

private:
	Real m_data[Row * Col];
	static const int NUM_ELEM = Row*Col;
};

template<int a, int b, int c>
inline void Mul(const Matrix<a,b>& i_first, const Matrix<b,c>& i_second, Matrix<a,c>& o_result)
{
	for(int i=0; i<a; ++i)
	{
		for(int j=0; j<c; ++j)
		{
			Real temp = 0.0f;
			for(int k=0; k<b; ++k)
				 temp += i_first.GetElem(i,k)*i_second.GetElem(k,j);
			o_result.SetElem(i,j,temp);
		}
	}
}

template<int a, int b, int c>
inline void Mul(const Matrix<a,b>& i_matrix, const typename Vector<b>::Type& i_vec, typename Vector<a>::Type& o_res)
{
	for(int i=0; i<a; ++i)
	{
		Real temp = 0.0f;
		for(int k=0; k<b; ++k)
			temp += i_matrix.GetElem(i,k)*i_vec.GetElem(k);
		o_res.SetElem(i,temp);
	}
}

template<int a, int b, int c>
inline const typename Vector<a>::Type operator*(const Matrix<a,b>& i_matrix, const typename Vector<b>::Type& i_vec)
{
	typename Vector<a>::Type temp;
	Mul(i_matrix, i_vec, temp);
	return temp;
}

template<int a, int b, int c>
inline const Matrix<a,c> operator*(const Matrix<a,b>& i_first, const Matrix<b,c>& i_second)
{
	Matrix<a,c> temp;
	Mul(i_first, i_second, temp);
	return temp;
}

template<int Row, int Col>
inline const Matrix<Row,Col> operator*(const Matrix<Row,Col>& i_matrix, const Real i_value)
{
	Matrix<Row,Col> temp(i_first);
	return i_first *= i_second;
}

template<int Row, int Col>
inline const Matrix<Row,Col> operator/(const Matrix<Row,Col>& i_matrix, const Real i_value)
{
	Matrix<Row,Col> temp(i_first);
	return i_first /= i_second;
}

template<int Row, int Col>
inline const Matrix<Row,Col> operator+(const Matrix<Row,Col>& i_first, const Matrix<Row,Col>& i_second)
{
	Matrix<Row,Col> temp(i_first);
	return i_first += i_second;
}

template<int Row, int Col>
inline const Matrix<Row,Col> operator-(const Matrix<Row,Col>& i_first, const Matrix<Row,Col>& i_second)
{
	Matrix<Row,Col> temp(i_first);
	return i_first -= i_second;
}

typedef Matrix<2,2> Matrix22;
typedef Matrix<2,3> Matrix23;
typedef Matrix<3,3> Matrix33;
typedef Matrix<3,4> Matrix34;

}} // namespaces

#include "Matrix.inl"

