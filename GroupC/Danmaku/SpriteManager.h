#pragma once
#include<Siv3D.hpp>
#include"ISprite.h"

class ISprite;

/// <summary>
///�X�v���C�g���Ǘ�����N���X�ł��B
/// </summary>
class SpriteManager
{
public:
	SpriteManager(int width, int height)
	{
		Width = width;
		Height = height;
	}
	/// <summary>
	/// �Ǘ����Ă���X�v���C�g���ׂĂ�Draw()�����s���܂�
	/// </summary>
	/// <param name="X">X���W</param>
	/// <param name="Y">Y���W</param>
	/// <param name="Rot180">180�x��]</param>
	virtual void DrawAll(double X, double Y, bool Rot180);
	/// <summary>
	/// �Ǘ����Ă���X�v���C�g���ׂĂ�Update()�����s���܂�
	/// </summary>
	virtual void UpdateAll();
	/// <summary>
	/// �������g�̃X�v���C�g���Ǘ�����O���܂�(�X�v���C�g��Draw(),Update()����̌Ăяo���ɑ΂��ėL��)
	/// </summary>
	virtual void DestroyMe();
	/// <summary>
	/// �Ǘ�����X�v���C�g��ǉ����܂�
	/// </summary>
	/// <param name="sp">�X�v���C�g�̎Q��</param>
	virtual void Add(ISprite*);
	/// <summary>
	/// ���ׂẴX�v���C�g���Ǘ�����O���܂�
	/// </summary>
	virtual void Clear();
	/// <summary>
	/// �w�肵���ԍ��̃X�v���C�g���Ǘ�����O���܂�
	/// </summary>
	/// <param name="index">�X�v���C�g�̔ԍ�</param>
	void RemoveAt(unsigned int index);
	/// <summary>
	/// �w�肵���^�O�����X�v���C�g���擾���܂�
	/// </summary>
	/// <param name="tag">��������^�O</param>
	/// <returns>�X�v���C�g�̎Q��(������Ȃ��Ƃ���nullptr)</returns>
	std::shared_ptr<ISprite> FindTag(const String Tag);

	Array<std::shared_ptr<ISprite>> Sprites;
	unsigned int Call_i;
	bool Calling = false;
	double Width, Height;
	double OffsetX, OffsetY;
	bool Rot180;
};