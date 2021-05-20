/*!
 *@brief	�t���X�^���J�����O�����B
 */
#pragma once
#include "ObjectCulling.h"
#include "Aabb.h"
 /*!
	  *@brief	�t���X�^���J�����O�����B
	  *@details
	  * �I�u�W�F�N�g������AABB���\������8���_���J�����ɉf��Ȃ��ꍇ�ɃJ�����O����܂��B
	  */
class ObjectFrustumCulling final : public IObjectCulling {
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	ObjectFrustumCulling();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~ObjectFrustumCulling();
	/*!
	 *@brief	�J�����O�A���S���Y���̎��s�B
	 *@param[in]	box	�J�����O���s�������I�u�W�F�N�g���o�E���f�B���O�{�b�N�X�B
	 */
	void Execute(const Aabb& aabb) override;
};