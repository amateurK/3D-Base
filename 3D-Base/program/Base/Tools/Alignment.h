#pragma once

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A���C�������g�Ɋւ���֐�
// 
// �����	: amateurK
// �쐬��	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Tools {

	/// @brief �A���C�������g������Ă��邩���`�F�b�N����
	/// @tparam T ���ׂ�I�u�W�F�N�g�̌^
	/// @param ptr ���ׂ�I�u�W�F�N�g�̃|�C���^
	/// @param alignment ��byte�ɃA���C�������g���邩
	/// @details XMVECTOR�Ȃǂ��g���ۂ̓R���X�g���N�^�ł��̊֐����Ăт������Ƃ𐄏�
	template<typename T>
	inline void CheckAlignment(T* ptr, size_t alignment = alignof(T)) {
#ifdef _DEBUG
		if (reinterpret_cast<uintptr_t>(ptr) % alignment != 0) {
			throw std::runtime_error("���̃I�u�W�F�N�g�̓A���C�������g����Ă��܂���B");
		}
#endif
	}
}