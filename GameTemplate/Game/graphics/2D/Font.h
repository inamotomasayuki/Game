#pragma once

class Font
{
public:
	Font();
	~Font();
	/// <summary>
	/// �`��A���W���X�N���[�����W�Ŏw��
	/// </summary>
	/// <param name="text">����</param>
	/// <param name="pos">���W</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="pivot">�s�{�b�g</param>
	/// <param name="rotation">��]</param>
	/// <param name="effects">�f�t�H���g��DirectX::SpriteEffects_None</param>
	void DrawScreenPos(
		wchar_t const* text,
		const CVector2& pos,
		const CVector4& color = CVector4::White(),
		const CVector2& scale = CVector2::One(),
		const CVector2& pivot = CVector2::Zero(),
		float rotation = 0.0f,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None
	);
private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//�ӂ����
	CVector2 m_screenSize;								//��ʃT�C�Y
};

