#ifndef CLASSINFO_H
#define CLASSINFO_H

#include "..\swigmod.h"
#include "sprpy.h"
#include <string>
#include <vector>
#include <map>

#include "MethodInfoEx.h"

using namespace std;
namespace SwigSprpy
{;


struct _MethodInfoEx;

enum SprClassType{
	SPR_CLASSTYPE_NONE = 0,
	SPR_CLASSTYPE_IF,		//PHSolidIf�Ȃ�
	SPR_CLASSTYPE_DESC,		//PHSolidDesc�Ȃ�
	SPR_CLASSTYPE_STATE,	//PHSolidState�Ȃ�
	SPR_CLASSTYPE_NOTSPR	//int,char,PyObject�Ȃ�
};

struct _ClassInfo
{	
	Node* node;
	const char* moduleName;
	const char* className;
	const char* classNameEx;
	const char* pyobjectName;
	const char* pysymbolName;
	const char* pytypeobjectName;
	string moduleNameStr;
	string classNameStr;
	string classNameExStr;
	string pyobjectNameStr;
	string pysymbolNameStr;
	string pytypeobjectNameStr;
	map<string,_MethodInfoEx> methods;
	map<string,_MethodInfoEx> mathMethods;
	string methodTable;
	string mathMethodTable;
	string getsetTable;
	string methodTableName;
	string mathMethodTableName;
	string getsetTableName;
	vector<string> getsetTableElems;
	string getsetMethodCode;
	string typeobjectCode;

	_MethodInfoEx* constructors;
	vector<string> bases;
	vector<string> pyBaseTypes;
	bool isInherited;
	bool isStruct;
	bool isUTRef;//UTRef���p�����Ă��邩�ǂ���
	bool useDefaultConstructor;
	SprClassType classType;

	static vector<string> UTRefList;

	struct _ModuleInfo *moduleinfo;

	_ClassInfo();
	_ClassInfo(const _ClassInfo& obj );
	~_ClassInfo();

	void BuildMethodInfoEx(Node* node);
	void UpdateMethodInfos();
	void BuildMemberInfo(Node* node);
	void UpdateClassInfo();
	void SetAdditionalMethods();

	static _ClassInfo CreateClassInfo(Node* _node,const char* moduleName);

private:
	void UpdateMethodInfo(_MethodInfoEx &mex);
};
typedef _ClassInfo ClassInfo;

}

#endif