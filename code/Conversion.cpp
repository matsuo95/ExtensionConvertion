#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previous_extension, CString after_extension)
	:m_PreviousExtension(previous_extension),m_AfterExtension(after_extension)
{

};

CString Conversion::ConvertExtensionString(CString Filepath) {
	// ï∂éöóÒÇÃïœçXÇÃÇ›
	
	string str_PreviousExtension, str_AfterExtension, str_Filepath;
	str_PreviousExtension = CStringA(m_PreviousExtension).GetBuffer();
	str_AfterExtension = CStringA(m_AfterExtension).GetBuffer();
	str_Filepath = CStringA(Filepath).GetBuffer();

	str_Filepath.replace(str_Filepath.find(str_PreviousExtension), str_PreviousExtension.length(), str_AfterExtension);

	CString return_Filepath;
	return_Filepath = str_Filepath.c_str();

	return return_Filepath;
}

void Conversion::RenameExtension(CString Filepath) {

	string str_Filepath = CStringA(Filepath).GetBuffer();
	const char* previous_filepath = str_Filepath.c_str();

	string str_newFilepath = CStringA(ConvertExtensionString(Filepath)).GetBuffer();
	const char* after_filepath = str_newFilepath.c_str();

	rename(previous_filepath, after_filepath);
}