// $(RUBY_INCLUDE)/win32/win32.h, windows.h�̃}�N����`�Ƃ̏Փˉ��
%{
#undef write			// std
#undef read				// std
#undef CreateWindow		// FWAppGLUT
%}

// �^�L���X�g��Warning�𖳌���
%{
#ifdef _MSC_VER
# pragma warning(disable: 4311 4312)
#endif	
%}
