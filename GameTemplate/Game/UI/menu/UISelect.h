#pragma once
#include "IUIObject.h"
class UISelect final : public IUIObject
{
public:
	UISelect();
	~UISelect();
	/*
	* @brief �X�V
	*/
	void Update() override;
};

