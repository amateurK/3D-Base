#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// enum class��bit���Z���g����悤�ɂ���}�N��
// 
// �����	: amateurK
// �쐬��	: 2025/05/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// ������enum class������ƁA����enum�Ȃ���bit���Z��������悤�ɂȂ�B
#define ENABLE_ENUM_CLASS_BITMASK(EnumType) \
inline EnumType operator|(EnumType lhs, EnumType rhs) { \
    return static_cast<EnumType>(static_cast<std::underlying_type_t<EnumType>>(lhs) | static_cast<std::underlying_type_t<EnumType>>(rhs)); \
} \
inline EnumType operator&(EnumType lhs, EnumType rhs) { \
    return static_cast<EnumType>(static_cast<std::underlying_type_t<EnumType>>(lhs) & static_cast<std::underlying_type_t<EnumType>>(rhs)); \
} \
inline EnumType& operator|=(EnumType& lhs, EnumType rhs) { \
    lhs = lhs | rhs; \
    return lhs; \
} \
inline EnumType& operator&=(EnumType& lhs, EnumType rhs) { \
    lhs = lhs & rhs; \
    return lhs; \
} \
inline EnumType operator~(EnumType e) { \
    return static_cast<EnumType>(~static_cast<std::underlying_type_t<EnumType>>(e)); \
} \
inline bool HasFlag(EnumType value, EnumType flag) { \
        using T = std::underlying_type_t<EnumType>; \
        return (static_cast<T>(value) & static_cast<T>(flag)) != 0; \
}