#pragma once
class UIData final
{
public:
	UIData();
	/// <summary>
	/// �e�L�X�g�f�[�^�ݒ�
	/// </summary>
	void TextDataInit();
	/// <summary>
	/// �X�v���C�g�t�@�C���p�X�ݒ�
	/// </summary>
	void SpriteFilePathInit();
	/// <summary>
	/// �X�e�[�g���Z�b�g
	/// </summary>
	void Reset();
	static UIData& GetInstance()
	{
		static UIData instance;
		return instance;
	}
	//���X�g�y�[�W
	enum Page {
		enPage_one,			//�y�[�W�P
		enPage_two,			//�y�[�W�Q
		enPage_three,		//�y�[�W�R
		enPage_Num			//��
	};
	//�I�v�V�����y�[�W
	enum OptionPage {
		enOptionPage_one,		//�I�v�V�����y�[�W�P
		enOptionPage_two,		//�I�v�V�����y�[�W�Q
		enOptionPage_three,		//�I�v�V�����y�[�W�R
		enOptionPage_four,		//�I�v�V�����y�[�W�S
		enOptionPage_Num		//��
	};
	//���j���[
	enum Menu {
		enMenu_list,			//���X�g
		enMenu_option,			//�I�v�V����
		enMenu_Num				//��
	};
	//���X�g���j���[
	enum ObjMenu {
		enObjMenu_obj,			//�I�u�W�F�N�g
		enObjMenu_gimmick,		//�M�~�b�N
		enObjMenu_enemy,		//�G
		enObjMenu_Num			//��
	};
	//�I�u�W�F�N�g
	enum Obj {
		enObj_mikan,			//�݂���
		enObj_coin,				//�R�C��
		enObj_star,				//�X�^�[
		enObj_Num				//��
	};
	//�M�~�b�N
	enum Gimmick {
		enGimmick_warp,			//���[�v
		enGimmick_box,			//�{�b�N�X
		enGimmick_button,		//�{�^��
		enGiimick_MoveFloor,	//������
		enGimmick_jumpFloor,	//�W�����v��
		enGimmick_Num			//��
	};
	//�G
	enum Enemy {
		enEnemy_kuribo,			//����ڂ�
		enEmemy_wingKuribo,		//�H������ڂ�
		enEnemy_kame,			//�J��
		enEnemy_Num				//��
	};
	//�I�v�V�������X�g
	enum OptionList
	{
		enOptionList_light,		//���C�g
		enOptionList_bloom,		//�u���[��
		enOptionList_Num		//��
	};
	//�u���[��
	enum Bloom
	{
		enBloom_luminance,		//�P�x
		enBloom_pow,			//����
		enBloom_init,			//������
		enBloom_Num				//��
	};
	//���C�g
	enum Light
	{
		enLight_color,			//�F
		enLight_brightness,		//���邳
		enLight_skyBrightness,	//��̖��邳
		enLight_init,			//������
		enLight_Num				//��
	};
	//���C�g�J���[
	enum LightColor
	{
		enLightColor_r,		//R
		enLightColor_g,		//G
		enLightColor_b,		//B
		enLightColor_Num		//��
	};
private:
	//���X�g�̃X�e�[�g
	Page m_pageState = static_cast<Page>(0);						//�y�[�W�X�e�[�g
	OptionPage m_optionPageState = static_cast<OptionPage>(0);	//�I�v�V�����y�[�W�X�e�[�g
	Menu m_menuState = static_cast<Menu>(0);						//���j���[�X�e�[�g
	ObjMenu m_objMenuState = static_cast<ObjMenu>(0);			//���X�g���j���[�X�e�[�g
	Obj m_objState = static_cast<Obj>(0);						//�I�u�W�F�N�g�X�e�[�g
	Gimmick m_gimmickState = static_cast<Gimmick>(0);			//�M�~�b�N�X�e�[�g
	Enemy m_enemyState = static_cast<Enemy>(0);					//�G�X�e�[�g
	OptionList m_optionListState = static_cast<OptionList>(0);	//�I�v�V�������X�g�X�e�[�g
	Bloom m_bloomState = static_cast<Bloom>(0);					//�u���[���X�e�[�g
	Light m_lightState = static_cast<Light>(0);					//���C�g�X�e�[�g
	LightColor m_lightColorState = static_cast<LightColor>(0);		//���C�g�J���[�X�e�[�g
	//�e�L�X�g�f�[�^
	wchar_t m_menutextData[enMenu_Num][256];				//���j���[�e�L�X�g
	wchar_t m_objMenutextData[enObjMenu_Num][256];			//���X�g���j���[�e�L�X�g
	wchar_t m_objTextData[enObj_Num][256];					//�I�u�W�F�N�g�e�L�X�g
	wchar_t m_gimmickTextData[enGimmick_Num][256];			//�M�~�b�N�e�L�X�g
	wchar_t m_enemyTextData[enEnemy_Num][256];				//�G�e�L�X�g
	wchar_t m_optionListTextData[enOptionList_Num][256];	//�I�v�V�������X�g�e�L�X�g
	wchar_t m_bloomTextData[enBloom_Num][256];				//�u���[���e�L�X�g
	wchar_t m_lightTextData[enLight_Num][256];				//���C�g�e�L�X�g
	wchar_t m_lightColorTextData[enLightColor_Num][256];	//���C�g�J���[�e�L�X�g�f�[�^
	//�t�@�C���p�X
	wchar_t m_objSpriteFilePath[enObj_Num][256];			//�I�u�W�F�N�g�X�v���C�g�t�@�C���p�X
	wchar_t m_gimmickSpriteFilePath[enGimmick_Num][256];	//�M�~�b�N�X�v���C�g�t�@�C���p�X
	wchar_t m_enemySpriteFilePath[enEnemy_Num][256];		//�G�X�v���C�g�t�@�C���p�X
public:
	//�e�L�X�g�f�[�^�̎擾�Q
	/// <summary>
	/// ���j���[�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetMenuTextData(int i = 0)
	{
		return &m_menutextData[i - 1][256];
	}
	/// <summary>
	/// �I�u�W�F�N�g���j���[�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetObjMenuTextData(int i = 0)
	{
		return &m_objMenutextData[i - 1][256];
	}
	/// <summary>
	/// �I�u�W�F�N�g�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetObjTextData(int i = 0)
	{
		return &m_objTextData[i - 1][256];
	}
	/// <summary>
	/// �M�~�b�N�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetGimmickTextData(int i = 0)
	{
		return &m_gimmickTextData[i - 1][256];
	}
	/// <summary>
	/// �G�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetEnemyTextData(int i = 0)
	{
		return &m_enemyTextData[i - 1][256];
	}
	/// <summary>
	/// �I�v�V�������X�g�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetOptionListTextData(int i = 0)
	{
		return &m_optionListTextData[i - 1][256];
	}
	/// <summary>
	/// �u���[���e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetBloomTextData(int i = 0)
	{
		return &m_bloomTextData[i - 1][256];
	}
	/// <summary>
	/// ���C�g�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetLightTextData(int i = 0)
	{
		return &m_lightTextData[i - 1][256];
	}
	/// <summary>
	/// ���C�g�J���[�e�L�X�g�f�[�^�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃e�L�X�g���w��</param>
	/// <returns>�w�肵���Ԗڂ̃e�L�X�g</returns>
	wchar_t* GetLightColorTextData(int i = 0)
	{
		return &m_lightColorTextData[i - 1][256];
	}
public:
	//�t�@�C���p�X�擾�Q
	/// <summary>
	/// �I�u�W�F�N�g�X�v���C�g�t�@�C���p�X�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃t�@�C���p�X���w��</param>
	/// <returns>�w�肵���Ԗڂ̃t�@�C���p�X</returns>
	wchar_t* GetObjSpriteFilePath(int i = 0)
	{
		return &m_objSpriteFilePath[i - 1][256];
	}
	/// <summary>
	/// �M�~�b�N�X�v���C�g�t�@�C���p�X�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃t�@�C���p�X���w��</param>
	/// <returns>�w�肵���Ԗڂ̃t�@�C���p�X</returns>
	wchar_t* GetGimmickSpriteFilePath(int i = 0)
	{
		return &m_gimmickSpriteFilePath[i - 1][256];
	}
	/// <summary>
	/// �G�X�v���C�g�t�@�C���p�X�̎擾
	/// </summary>
	/// <param name="i">���Ԗڂ̃t�@�C���p�X���w��</param>
	/// <returns>�w�肵���Ԗڂ̃t�@�C���p�X</returns>
	wchar_t* GetEnemySpriteFilePath(int i = 0)
	{
		return &m_enemySpriteFilePath[i - 1][256];
	}
public:
	//�X�e�[�g���Z�b�g�Q
	/// <summary>
	/// �I�u�W�F�N�g���j���[�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetObjMenuState()
	{
		m_objMenuState = static_cast<ObjMenu>(0);
	}
	/// <summary>
	/// �I�u�W�F�N�g�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetObjState()
	{
		m_objState = static_cast<Obj>(0);
	}
	/// <summary>
	/// �M�~�b�N�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetGimmickState()
	{
		m_gimmickState = static_cast<Gimmick>(0);
	}
	/// <summary>
	/// �G�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetEnemyState()
	{
		m_enemyState = static_cast<Enemy>(0);
	}
	/// <summary>
	/// �I�v�V�������X�g�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetOptionListState()
	{
		m_optionListState = static_cast<OptionList>(0);
	}
	/// <summary>
	/// �u���[���X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetBloomState()
	{
		m_bloomState = static_cast<Bloom>(0);
	}
	/// <summary>
	/// ���C�g�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetLightState()
	{
		m_lightState = static_cast<Light>(0);
	}
	/// <summary>
	/// ���C�g�J���[�X�e�[�g�̃��Z�b�g
	/// </summary>
	void ResetLightColor()
	{
		m_lightColorState = static_cast<LightColor>(0);
	}
public:
	//�X�e�[�g�̉��Z���Z�Q
	/// <summary>
	/// �y�[�W�X�e�[�g�̉��Z
	/// </summary>
	void PageStatePlus()
	{
		m_pageState = static_cast<Page>(m_pageState + 1);
		if (m_pageState >= enPage_Num) {
			m_pageState = static_cast<Page>(enPage_Num - 1);
		}
	}
	/// <summary>
	/// �y�[�W�X�e�[�g�̌��Z
	/// </summary>
	void PageStateMinus()
	{
		m_pageState = static_cast<Page>(m_pageState - 1);
		if (m_pageState <= 0) {
			m_pageState = static_cast<Page>(0);
		}
	}
	/// <summary>
	/// �I�v�V�����y�[�W�X�e�[�g�̉��Z
	/// </summary>
	void OptionPageStatePlus()
	{
		m_optionPageState = static_cast<OptionPage>(m_optionPageState + 1);
		if (m_optionPageState >= enOptionPage_Num) {
			m_optionPageState = static_cast<OptionPage>(enOptionPage_Num - 1);
		}
	}
	/// <summary>
	/// �I�v�V�����y�[�W�X�e�[�g�̌��Z
	/// </summary>
	void OptionPageStateMinus()
	{
		m_optionPageState = static_cast<OptionPage>(m_optionPageState - 1);
		if (m_optionPageState <= 0) {
			m_optionPageState = static_cast<OptionPage>(0);
		}
	}
	/// <summary>
	/// ���j���[�X�e�[�g�̉��Z
	/// </summary>
	void MenuStatePlus()
	{
		m_menuState = static_cast<Menu>(m_menuState + 1);
		if (m_menuState >= enMenu_Num) {
			m_menuState = static_cast<Menu>(enMenu_Num - 1);
		}
	}
	/// <summary>
	/// ���j���[�X�e�[�g�̌��Z
	/// </summary>
	void MenuStateMinus()
	{
		m_menuState = static_cast<Menu>(m_menuState - 1);
		if (m_menuState <= 0) {
			m_menuState = static_cast<Menu>(0);
		}
	}
	/// <summary>
	/// �I�u�W�F�N�g���j���[�X�e�[�g�̉��Z
	/// </summary>
	void ObjMenuStatePlus()
	{
		m_objMenuState = static_cast<ObjMenu>(m_objMenuState + 1);
		if (m_objMenuState >= enObjMenu_Num) {
			m_objMenuState = static_cast<ObjMenu>(enObjMenu_Num - 1);
		}
	}
	/// <summary>
	/// �I�u�W�F�N�g���j���[�X�e�[�g�̌��Z
	/// </summary>
	void ObjMenuStateMinus()
	{
		m_objMenuState = static_cast<ObjMenu>(m_objMenuState - 1);
		if (m_objMenuState <= 0) {
			m_objMenuState = static_cast<ObjMenu>(0);
		}
	}
	/// <summary>
	/// �I�u�W�F�N�g�X�e�[�g�̉��Z
	/// </summary>
	void ObjStatePlus()
	{
		m_objState = static_cast<Obj>(m_objState + 1);
		if (m_objState >= enObj_Num) {
			m_objState = static_cast<Obj>(enObj_Num - 1);
		}

	}
	/// <summary>
	/// �I�u�W�F�N�g�X�e�[�g�̌��Z
	/// </summary>
	void ObjStateMinus()
	{
		m_objState = static_cast<Obj>(m_objState - 1);
		if (m_objState <= 0) {
			m_objState = static_cast<Obj>(0);
		}
	}
	/// <summary>
	/// �M�~�b�N�X�e�[�g�̉��Z
	/// </summary>
	void GimmickStatePlus()
	{
		m_gimmickState = static_cast<Gimmick>(m_gimmickState + 1);
		if (m_gimmickState >= enGimmick_Num) {
			m_gimmickState = static_cast<Gimmick>(enGimmick_Num - 1);
		}
	}
	/// <summary>
	/// �M�~�b�N�X�e�[�g�̌��Z
	/// </summary>
	void GimmickStateMinus()
	{
		m_gimmickState = static_cast<Gimmick>(m_gimmickState - 1);
		if (m_gimmickState <= 0) {
			m_gimmickState = static_cast<Gimmick>(0);
		}
	}
	/// <summary>
	/// �G�X�e�[�g�̉��Z
	/// </summary>
	void EnemyStatePlus()
	{
		m_enemyState = static_cast<Enemy>(m_enemyState + 1);
		if (m_enemyState >= enEnemy_Num) {
			m_enemyState = static_cast<Enemy>(enEnemy_Num - 1);
		}
	}
	/// <summary>
	/// �G�X�e�[�g�̌��Z
	/// </summary>
	void EnemyStateMinus()
	{
		m_enemyState = static_cast<Enemy>(m_enemyState - 1);
		if (m_enemyState <= 0) {
			m_enemyState = static_cast<Enemy>(0);
		}
	}
	/// <summary>
	/// �I�v�V�������X�g�X�e�[�g�̉��Z
	/// </summary>
	void OptionListStatePlus()
	{
		m_optionListState = static_cast<OptionList>(m_optionListState + 1);
		if (m_optionListState >= enOptionList_Num) {
			m_optionListState = static_cast<OptionList>(enOptionList_Num - 1);
		}
	}
	/// <summary>
	/// �I�v�V�������X�g�X�e�[�g�̌��Z
	/// </summary>
	void OptionListStateMinus()
	{
		m_optionListState = static_cast<OptionList>(m_optionListState - 1);
		if (m_optionListState <= 0) {
			m_optionListState = static_cast<OptionList>(0);
		}
	}
	/// <summary>
	/// �u���[���X�e�[�g�̉��Z
	/// </summary>
	void BloomStatePlus()
	{
		m_bloomState = static_cast<Bloom>(m_bloomState + 1);
		if (m_bloomState >= enBloom_Num) {
			m_bloomState = static_cast<Bloom>(enBloom_Num - 1);
		}
	}
	/// <summary>
	/// �u���[���X�e�[�g�̌��Z
	/// </summary>
	void BloomStateMinus()
	{
		m_bloomState = static_cast<Bloom>(m_bloomState - 1);
		if (m_bloomState <= 0) {
			m_bloomState = static_cast<Bloom>(0);
		}
	}
	/// <summary>
	/// ���C�g�X�e�[�g�̉��Z
	/// </summary>
	void LightStatePlus()
	{
		m_lightState = static_cast<Light>(m_lightState + 1);
		if (m_lightState >= enLight_Num) {
			m_lightState = static_cast<Light>(enLight_Num - 1);
		}
	}
	/// <summary>
	/// ���C�g�X�e�[�g�̌��Z
	/// </summary>
	void LightStateMinus()
	{
		m_lightState = static_cast<Light>(m_lightState - 1);
		if (m_lightState <= 0) {
			m_lightState = static_cast<Light>(0);
		}
	}
	/// <summary>
	/// ���C�g�J���[�X�e�[�g�̉��Z
	/// </summary>
	void LightColorStatePlus()
	{
		m_lightColorState = static_cast<LightColor>(m_lightColorState + 1);
		if (m_lightColorState >= enLightColor_Num) {
			m_lightColorState = static_cast<LightColor>(enLightColor_Num - 1);
		}
	}
	/// <summary>
	/// ���C�g�J���[�X�e�[�g�̌��Z
	/// </summary>
	void LightColorStateMinus()
	{
		m_lightColorState = static_cast<LightColor>(m_lightColorState - 1);
		if (m_lightColorState <= 0) {
			m_lightColorState = static_cast<LightColor>(0);
		}
	}
public:
	//�X�e�[�g�擾�Q
	/// <summary>
	/// �y�[�W�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�y�[�W�X�e�[�g</returns>
	Page GetPageState() const
	{
		return m_pageState;
	}
	/// <summary>
	/// �I�v�V�����y�[�W�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�I�v�V�����y�[�W�X�e�[�g</returns>
	OptionPage GetOptionPageState() const
	{
		return m_optionPageState;
	}
	/// <summary>
	/// ���j���[�X�e�[�g�̎擾
	/// </summary>
	/// <returns>���j���[�X�e�[�g</returns>
	Menu GetMenuState() const
	{
		return m_menuState;
	}
	/// <summary>
	/// �I�u�W�F�N�g���j���[�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g���j���[�X�e�[�g</returns>
	ObjMenu GetObjMenuState() const
	{
		return m_objMenuState;
	}
	/// <summary>
	/// �I�u�W�F�N�g�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�X�e�[�g</returns>
	Obj GetObjState() const
	{
		return m_objState;
	}
	/// <summary>
	/// �M�~�b�N�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�M�~�b�N�X�e�[�g</returns>
	Gimmick GetGimmickState() const
	{
		return m_gimmickState;
	}
	/// <summary>
	/// �G�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�G�X�e�[�g</returns>
	Enemy GetEnemyState() const
	{
		return m_enemyState;
	}
	/// <summary>
	/// �I�v�V�������X�g�X�e�[�g�̎擾
	/// </summary>
	/// <returns>�I�v�V�������X�g�X�e�[�g</returns>
	OptionList GetOptionListState() const
	{
		return m_optionListState;
	}
	/// <summary>
	/// �u���[���X�e�[�g�̎擾
	/// </summary>
	/// <returns>�u���[���X�e�[�g</returns>
	Bloom GetBloomState() const
	{
		return m_bloomState;
	}
	/// <summary>
	/// ���C�g�X�e�[�g�̎擾
	/// </summary>
	/// <returns>���C�g�X�e�[�g</returns>
	Light GetLightState() const
	{
		return m_lightState;
	}
	/// <summary>
	/// ���C�g�J���[�X�e�[�g�̎擾
	/// </summary>
	/// <returns>���C�g�J���[�X�e�[�g</returns>
	LightColor GetLightColorState() const
	{
		return m_lightColorState;
	}
};

static inline UIData& GetUIData()
{
	return UIData::GetInstance();
}
