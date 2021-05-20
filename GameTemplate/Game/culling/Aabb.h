/*!
 *@brief	AABB
 */
#pragma once
 /*!
  *@brief	Aabb
  */
class Aabb final {
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Aabb();
	/*!
	 *@brief	�������B
	 */
	void Init(const CVector3& halfSize);
	/*!
	 *@brief	�X�V�B
	 *@param[in]	worldMatrix�B
	 */
	void Update(const CMatrix& worldMatrix);
	/*!
	*@brief	�o�E���f�B���O�{�b�N�X���\������8���_�̍��W���擾�B
	*@param[in]	vertNo	���_�ԍ��B0�`7�̔ԍ���n���Ă��������B
	*/
	const CVector3& GetVertexPosition(unsigned int vertNo) const
	{
		return m_vertexPosition[vertNo];
	}

private:
	CVector3	m_halfSize = CVector3::Zero();		//!<�n�[�t�T�C�Y�B
	CVector3	m_vertexPosition[8];				//!<�o�E���f�B���O�{�b�N�X���\������8���_�̍��W�B
};