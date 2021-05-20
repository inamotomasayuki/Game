#pragma once
#include "RenderTarget.h"
#include "../graphics/2D/Sprite.h"
#include "postEffect/PostEffect.h"
#include "effect/EffectEngine.h"

/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Silhouette,		//�V���G�b�g�`��B
	enRenderMode_Sky,
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};


/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice() const
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext() const
	{
		return m_pd3dDeviceContext;
	}

	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
	/// <summary>
/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
/// </summary>
/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// �`��
	/// </summary>
	void GameDraw();
	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���쐬
	/// </summary>
	void CreateMainRenderTarget();
	/// <summary>
/// ���C�������_�����O�^�[�Q�b�g���擾�B
/// </summary>
/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	/// <summary>
/// �J������Ԃł̐[�x�l����������ł��郌���_�����O�^�[�Q�b�g���擾�B
/// </summary>
/// <returns></returns>
	RenderTarget* GetDepthInViewRenderTarget()
	{
		return &m_depthRenderTarget;
	}
	/// <summary>
	/// �����������̃u�����h�X�e�[�g��������
	/// </summary>
	void InitTranslucentBlendState();
	/// <summary>
	/// �����������̃u�����h�X�e�[�g��ݒ�
	/// </summary>
	void SetBlendState();
	/// <summary>
	/// �X�v���C�g�o�b�`�̎擾
	/// </summary>
	/// <returns>�X�v���C�g�o�b�`</returns>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}
	/// <summary>
	/// �X�v���C�g�t�H���g�̎擾
	/// </summary>
	/// <returns>�X�v���C�g�t�H���g</returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spriteFont.get();
	}
	/// <summary>
	/// �t���[���o�b�t�@�̃r���[�|�[�g�̎擾
	/// </summary>
	/// <returns>�t���[���o�b�t�@�̃r���[�|�[�g</returns>
	const D3D11_VIEWPORT& GetFrameBufferViewport() const
	{
		return m_frameBufferViewports;
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B

	PostEffect m_postEffect;
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B	
	RenderTarget m_depthRenderTarget;		//�[�x�l�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

	//��`�B
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;     //���ꂪ��
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;		//�������
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��