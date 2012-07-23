namespace phynet{
namespace math{

template<>
inline Real Matrix<2,2>::GetDeterminant() const
{
	return m_data[0]*m_data[3] - m_data[1]*m_data[2];
}

template<>
inline Real Matrix<3,3>::GetDeterminant() const
{
	return 
		m_data[0]*m_data[4]*m_data[8] +
		m_data[1]*m_data[5]*m_data[6] +
		m_data[2]*m_data[3]*m_data[7] -
		m_data[0]*m_data[5]*m_data[7] -
		m_data[1]*m_data[3]*m_data[8] -
		m_data[2]*m_data[4]*m_data[6];
}

template<int Dim>
inline Real Determinant(const Matrix<Dim,Dim>& i_marix)
{
	//TODO
	return 0.0f;
}

template<int Row, int Col>
inline Real Matrix<Row,Col>::GetDeterminant() const
{
	return Determinant(*this);
}

template<int Dim>
inline const Matrix<Dim,Dim> InvertMatrix(const Matrix<Dim,Dim>& i_matrix)
{
	//TODO
	return 	i_matrix;
}

template<>
inline void Matrix<2,2>::Invert()
{
	std::swap(m_data[0],m_data[3]);

	m_data[1] = -m_data[1];
	m_data[2] = -m_data[2]; 
}

template<>
inline void Matrix<3,3>::Invert()
{
	Matrix<3,3> temp(*this);

	m_data[0] = temp.m_data[4]*temp.m_data[8] - temp.m_data[5]*temp.m_data[7];
	m_data[1] = temp.m_data[2]*temp.m_data[7] - temp.m_data[1]*temp.m_data[8];
	m_data[2] = temp.m_data[1]*temp.m_data[5] - temp.m_data[2]*temp.m_data[4];
	m_data[3] = temp.m_data[5]*temp.m_data[6] - temp.m_data[3]*temp.m_data[8];
	m_data[4] = temp.m_data[8]*temp.m_data[0] - temp.m_data[2]*temp.m_data[6];
	m_data[5] = temp.m_data[2]*temp.m_data[3] - temp.m_data[0]*temp.m_data[5];
	m_data[6] = temp.m_data[3]*temp.m_data[7] - temp.m_data[4]*temp.m_data[6];
	m_data[7] = temp.m_data[1]*temp.m_data[6] - temp.m_data[0]*temp.m_data[7];
	m_data[8] = temp.m_data[0]*temp.m_data[4] - temp.m_data[1]*temp.m_data[3];

	*this /= temp.GetDeterminant();
}

template<int Row, int Col>
inline void Matrix<Row,Col>::Invert()
{
	*this = InvertMatrix(*this);
}

template<int Dim>
inline const Matrix<Dim,Dim> TransposeMatrix(const Matrix<Dim,Dim>& i_matrix)
{
	//inefficient
	Matrix<Dim,Dim> temp(i_matrix);
	i_matrix.GetTranspose(temp);
	return temp;
}

template<>
inline void Matrix<2,2>::Transpose()
{
	std::swap(m_data[1],m_data[2]);
}

template<>
inline void Matrix<3,3>::Transpose()
{
	std::swap(m_data[1],m_data[3]);
	std::swap(m_data[6],m_data[2]);
	std::swap(m_data[5],m_data[7]);
}

template<int Row, int Col>
inline void Matrix<Row,Col>::Transpose()
{
	*this = TransposeMatrix(*this);
}

template<int Row, int Col>
inline void Matrix<Row,Col>::SetIdentity()
{
	//static_assert(Row==Col);
	for (int i=0; i<Row; ++i)
		for (int j=0; i<Col; ++i)
			m_data[i*Row + j] = (i==j ? 1.0f : 0.0f);
}

template<int Row, int Col>
inline bool Matrix<Row,Col>::IsOrtho() const
{
	Matrix<Row,Col> inverse;
	GetInverse(inverse);
	Matrix<Row,Col> transpose;
	GetTranspose(transpose);
	for (int i=0; i<Row*Col; ++i)
		if (!AreEqual(inverse.m_data[i], transpose.m_data[i]))
			return false;
	return true;
}

template<int Row, int Col>
inline bool Matrix<Row,Col>::IsDiagonal() const
{
	//static_assert(Row==Col);
	for (int i=0; i<Row; ++i)
		for (int j=0; i<Col; ++i)
			if((i!=j) && (!AreEqual(m_data[i*Row + j], 0.0f))) 
				return false;
	return true;
}

template<int Row, int Col>
inline void Matrix<Row,Col>::SetDiagonal(Real* const i_data)
{
	//static_assert(Row==Col);
	for (int i=0; i<Row; ++i)
		for (int j=0; i<Col; ++i)
			m_data[i*Row + j] = (i==j ? i_data[i] : 0.0f);
}

template<int Row, int Col>
inline void Matrix<Row,Col>::GetTranspose(TransposeType& o_trans) const
{
	for(int i=0; i<Row; ++i)
		for(int j=0; j<Col; ++j)
			o_trans.SetElem(j,i, m_data[i*Col+j]);
}

}} // namespaces
