#pragma once

/// <summary>
///�X�v���C�g�̕`��Ɠ����蔻����s���C���^�[�t�F�[�X�ł��B
/// </summary>
class ISpriteView
{
public:
	Polygon basePolygon;
	Polygon genePolygon;
	
	///<summary>
	///�`����s���܂�
	///</summary>
	virtual void Draw(SpriteInfo&) {}
};