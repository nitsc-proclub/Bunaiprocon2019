#pragma once
#include<Siv3D.hpp>

/// <summary>
/// �v���O���X�o�[
/// </summary>
class ProgressBar
{
public:
	Color BackColor = Color(L"#dddddd");
	Color BarColor = Color(L"#4b85e5");
	int Width = 200;
	int Height = 20;
	int Value;
	int Max;
	/// <summary>
	/// �v���O���X�o�[�̃R���X�g���N�^�[
	/// </summary>
	/// <param name="val">0~Max�̒l</param>
	/// <param name="max">�ő�l</param>
	ProgressBar(int val, int max)
	{
		Value = val; Max = max;
	}
	/// <summary>
	/// �v���O���X�o�[�̃R���X�g���N�^�[
	/// </summary>
	/// <param name="val">0~Max�̒l</param>
	/// <param name="max">�ő�l</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	ProgressBar(int val, int max, int width, int height)
	{
		Value = val; Max = max; Width = width; Height = height;
	}
	/// <summary>
	/// �v���O���X�o�[�̃R���X�g���N�^�[
	/// </summary>
	/// <param name="val">0~Max�̒l</param>
	/// <param name="max">�ő�l</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <param name="backcol">�w�i�F</param>
	/// <param name="barcol">�o�[�̐F</param>
	ProgressBar(int val, int max, int width, int height,Color& backcol,Color& barcol)
	{
		Value = val; Max = max; Width = width; Height = height; BackColor = backcol; BarColor = barcol;
	}
	/// <summary>
	/// �v���O���X�o�[�̕`��
	/// </summary>
	/// <param name="x">�����X���W</param>
	/// <param name="y">�����Y���W</param>
	void Draw(int x, int y)
	{
		//�w�i
		Rect(x,y,Width, Height).draw(BackColor);
		//�o�[
		Rect(x,y,Width*Value/Max, Height).draw(BarColor);
	}
};