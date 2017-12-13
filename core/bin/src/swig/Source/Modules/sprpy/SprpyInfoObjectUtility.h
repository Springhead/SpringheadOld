#include "SprpyInfoObject.h"

namespace SwigSprpy
{;

typedef vector<char> Chars;
typedef struct _SwigSprpyVars
{
	const char *classnamePrefix;
	const char *filenamePrefix;
	const char *VARNAME_TUPLE;
	const char *VARNAME_SELF;
	const char *VARNAME_ARG;
	vector<string> UTRefList;
	set<Enum> enuminfos;
	Chars spacer;
} SwigSprpyVars;

class SprpyInfoObjectUtility;
struct Variable 
{
	SprpyInfoObjectUtility *Util;
	string cName;
	string cType;
	string cCode;
	string pyName;
	string pyType;
	string pyCode;
		
	Variable(SprpyInfoObjectUtility*);
	// C -> Python �ϐ��̕ϊ��@�@int => PyIntObject*   Vec3d => SPRPYVec3d*  Vec3d* => SPRPYVec3d*
	void WrapValue();

	// Python -> C �ϐ��̕ϊ��@�@PyIntObject* => int SPRPYVec3d* => Vec3d,
	void UnWrapValue();
};




struct CElem
{
	//�N���X�L�[���[�h
	//class,struct,union   ,enum

	//����
	//* �� &
	//cv �C���q�iconst �� volatile�j
	//���O�w��q�istd:: �Ȃǁj
	//() ���̊֐��p�����[�^
	//[] ���̔z��̒���
	//��O�����̎w��
	//�C�j�V�����C�U

	// access storage cv classkeyword usigned nspace::classA::classB::type pr name
	//							                      ^^^^^^^^^^^^^^^^^^^^��fulltype
	// type<child> name
	string nspace;
	//string access;
	string storage;
	string cv;
	string classkeyword;
	string pr;	//* �� & ,const*,const&��
	string type;
	string fulltype;
	string usigned; //unsigned
	//string name;
	struct CElem *child;//template
	CElem();
	CElem(CElem&);
	~CElem();
};

class SprpyInfoObjectUtility
{
public:
	SwigSprpyVars Vars;
	SprpyInfoObjectUtility();


	bool IsSpacer(char c);

	vector<string> ParmtoStrings( DOH* parm );

	vector<string> ParmtoStrings( const char* parm );

	const Enum* GetEnum( string cls );

	string TrimEnd( string str , string key);

	string ResolveTypedef(CElem cls);
	 
	string GetPySymbolName(string cls);
	
	string GetPyObjectName(string cls);

	int DelConst(string& cls);

	void DelRef(string& cls);
	bool IsRef(string& cls);

	void DelSpace(string& cls);

	int DelPointer(string &cls);

	void DelNamespace(string& cls);

	bool DelqConst(string& cls);

	void CreateCElem(string cls,CElem** alloc);

	CElem CreateCElem(string cls);

	int DelArray(string &cls);

	int CountPointer(string &cls);

	void StrReplaceall(string& str, string from , string to);

	/////�^�����񂩂�APython�̌^�`�F�b�N�֐�����Ԃ�
	string GetCheckfuncName(string cls, string name);
	
	string GetPyTypeObjectName(string cls);

	SprClassType GetSprClassType(string cls);

};
}//namespace