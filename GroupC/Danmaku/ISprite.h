#pragma once
#include"SpriteManager.h"
#include"SpriteInfo.h"
#include"ISpriteView.h"

class SpriteManager;

/// <summary>
///�X�v���C�g�{�̂̃C���^�[�t�F�[�X�ł��B
/// </summary>
class ISprite
{
public:
	enum SpriteEvent
	{
		Damage
	};

	ISprite() {}

	ISprite& operator=(const ISprite& other)
	{
		this->View = other.View;
		this->Info = other.Info;
		this->IsInit = other.IsInit;

		return *this;
	}

	/// <summary>
	/// <para>�X�v���C�g�̕`����s���܂�</para>
	/// <para>(�f�t�H���g��View��Draw()���Ăяo���܂�)</para>
	/// </summary>
	virtual void Draw();
	
	/// <summary>
	/// ���߂�Update���ĂԒ��O�ɌĂ΂��֐�
	/// </summary>
	virtual void Start();

	/// <summary>
	/// ���t���[���ɌĂ΂��֐�
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �X�v���C�g�̃C�x���g�n���h��
	/// </summary>
	/// <param name="e">�C�x���g�̓��e</param>
	/// <param name="e">�C�x���g�̓��e(���l)</param>
	virtual void DoEvent(const SpriteEvent e,const int value);

	/// <summary>
	/// �X�v���C�g�Ƃ̓����蔻����s���܂�
	/// </summary>
	/// <param name="sp">���肷��X�v���C�g</param>
	/// <returns>�������Ă����true�A�������Ă��Ȃ����false</returns>
	virtual bool IsHit(const std::shared_ptr<ISprite>);

	/// <summary>
	/// �X�v���C�g�Ƃ̓����蔻����s���܂�
	/// </summary>
	/// <param name="sp">�X�v���C�g�̊Ǘ��ԍ�</param>
	/// <returns>�������Ă����true�A�������Ă��Ȃ����false</returns>
	virtual bool IsHit(unsigned int);

	/// <summary>
	/// �������Ă���X�v���C�g��1�Ԃ��܂�
	/// </summary>
	/// <returns>�X�v���C�g�̊Ǘ��ԍ�</returns>
	virtual std::shared_ptr<ISprite> GetHitSp();
	/// <summary>
	/// �����ɊY�����A�������Ă���X�v���C�g��1�Ԃ��܂�
	/// </summary>
	/// <param name="tag">�i�荞�ޏ���</param>
	/// <returns>�X�v���C�g�̊Ǘ��ԍ�</returns>
	virtual std::shared_ptr<ISprite> GetHitSp(const String tag);
	
	bool IsInWindow();
	bool IsInWindow(int x, int y);

	int HitArea;
	ISpriteView* View = nullptr;
	SpriteInfo Info = SpriteInfo();
	SpriteManager* Manager = nullptr;
	String Tag;
	bool IsInit = false;
};