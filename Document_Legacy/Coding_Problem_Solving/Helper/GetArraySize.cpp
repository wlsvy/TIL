//출처 Effective Modern C++ 항목 01 : 템플릿 형식 연역 규칙을 숙지하라. 예제 코드

template<typename T, std::size_t N>
constexpr std::size_t GetArraySize(T(&)[N]) noexcept {
	return N;
}
