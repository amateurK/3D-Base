
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ‹î(piece)‚ÌƒNƒ‰ƒX
// 
// »ìÒ	: amateurK
// ì¬“ú	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Piece.h"

namespace Piece {

	Piece::Piece(
		Shader::Shader* const shader
		, std::wstring name
		, std::wstring fileName
	)
		: AK_Base::ModelActor(shader, name, fileName)
		, m_Value(0)
	{
		auto scale = 0.03f;
		m_Scale.x = scale;
		m_Scale.y = scale;
		m_Scale.z = scale;
	}

	//--------------------------------------------------------------------------------------
	Piece::~Piece()
	{

	}

	//--------------------------------------------------------------------------------------
	void Piece::Move(const double& totalTime, const float& elapsedTime)
	{
		m_Rotation += elapsedTime;

		AK_Base::ModelActor::Move(totalTime, elapsedTime);
	}

	//--------------------------------------------------------------------------------------
	void Piece::Render(const double& totalTime, const float& elapsedTime)
	{
		AK_Base::ModelActor::Render(totalTime, elapsedTime);
	}
}