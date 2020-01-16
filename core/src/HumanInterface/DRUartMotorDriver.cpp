/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
// DRUARTMotorDriver.cpp: DRUARTMotorDriver �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include <Springhead.h>
#include <HumanInterface/DRUartMotorDriver.h>
#include <HumanInterface/DRUartMotorDriver/WROOM/main/softRobot/CommandWROOM.h>
#include <HumanInterface/DRUartMotorDriver/WROOM/main/softRobot/Board.h>
#undef NMOTOR
#undef NTARGET
#undef NFORCE

#ifdef _WIN32
#include <windows.h>
#include <winioctl.h>
#else
#define CreateFile(name, access, mode, pattr, dwDisp, dwFlag, hTemp)	INVALID_HANDLE_VALUE
#define ReadFile(h, b, nb, nr, o)	FALSE
#define WriteFile(h, b, nb, nw, o)	FALSE
#define CloseHandle(h)	FALSE
#define QueryDosDevice(p, buf, nbuf)	FALSE
#define Sleep(x)	
#define SetupComm(h, nIn, nOut)
#define SetCommTimeouts(h, lpTo)
#define SetCommState(h, lpDBC)
#define GetLastError()	0
#define FlushFileBuffers(h)

#define DWORD	unsigned int
#define TRUE	true
#define FALSE	false
#define INVALID_HANDLE_VALUE	NULL
#endif

#include <sstream>

#ifdef USE_HDRSTOP
 #pragma hdrstop
#endif

using namespace std;
namespace Spr {;


struct DeviceMap {
	DeviceMap(int b, int c) : bid(b), ch(c) {}
	int bid;
	int ch;
};
class DRUARTMotorDriverImpl: public BoardCmdBase, public BoardRetBase {
	friend DRUARTMotorDriver;
public:
	std::vector<DeviceMap> motorMap, currentMap, forceMap, touchMap;
	DRUARTMotorDriver* owner;
	DRUARTMotorDriverImpl(DRUARTMotorDriver* o) {
		owner = o;
	}
	Boards boards;
	bool EnumBoards(void* hUART) {
		CommandPacketBD0 cmd;
		ReturnPacketBD0 ret;
		char zero[80];
		memset(zero, 0, sizeof(zero));
		DWORD nDid;
		for (int i = 0; i <= MAXBOARDID; ++i) {
			cmd.commandId = CI_BOARD_INFO;
			cmd.boardId = i;
			WriteFile(hUART, zero, 40, &nDid, NULL);
			WriteFile(hUART, (char*)cmd.bytes, BD0_CLEN_BOARD_INFO, &nDid, NULL);	//	send board info command
			WriteFile(hUART, zero, 26, &nDid, NULL);
			FlushFileBuffers(hUART);
			DWORD rxLen = 0;
			memset(&ret.boardInfo, 0, sizeof(ret.boardInfo));
			ReadFile(hUART, ret.bytes, BD0_RLEN_BOARD_INFO, &rxLen, NULL);
			if (rxLen >= BD0_RLEN_BOARD_INFO){
				//	found a borad
				int s = ret.boardInfo.nMotor + ret.boardInfo.nCurrent + ret.boardInfo.nForce;
				//	Check if the board info is appropriate or not.
				if (ret.boardInfo.modelNumber > 0 && (0 < s && s < 100)) {
					BoardBase* b = boards.Create(ret.boardInfo.modelNumber, i);
					for (int m = 0; m < b->GetNMotor(); ++m) {
						b->motorMap.push_back((char)motorMap.size());
						motorMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNCurrent(); ++m) {
						b->currentMap.push_back((char)currentMap.size());
						currentMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNForce(); ++m) {
						b->forceMap.push_back((char)forceMap.size());
						forceMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNTouch(); ++m) {
						b->touchMap.push_back((char)touchMap.size());
						touchMap.push_back(DeviceMap(i, m));
					}
					printf("%dT%dM%dC%dF%d", ret.boardInfo.modelNumber, ret.boardInfo.nTarget,
						ret.boardInfo.nMotor, ret.boardInfo.nCurrent, ret.boardInfo.nForce);
				}
			}
			else {
				DWORD e = GetLastError();
				DSTR << "ID" << i << "ReadFile() Error = " << e << " rxLen = " << rxLen << std::endl;
			}

		}
		//	set command length for all boards
		for (int i = 0; i < (int)boards.size(); ++i) {
			printf("Board %d CLEN:", boards[i]->GetBoardId());
			for (int c = 0; c < CI_NCOMMAND; ++c) {
				cmd.cmdLen.len[c] = boards[i]->cmdPacketLen[c];
				printf(" %d", (int)boards[i]->cmdPacketLen[c]);
			}
			printf(" RLEN:");
			for (int c = 0; c < CI_NCOMMAND; ++c) {
				printf(" %d", (int)boards[i]->retPacketLen[c]);
			}
			cmd.commandId = CI_SET_CMDLEN;
			cmd.boardId = boards[i]->GetBoardId();
			WriteFile(hUART, cmd.bytes, BD0_CLEN_SET_CMDLEN, &nDid, NULL);	//	send board info command
		}
		WriteFile(hUART, zero, 5, &nDid, NULL);
		owner->ClearComRead();
#if 0	// For UART command test
		for (int i = 0; i < boards.size(); ++i) {
			ets_delay_us(10000);
			cmd.commandId = CI_TORQUE_LIMIT;
			uart_write_bytes(port, (char*)cmd.bytes, boards[i]->cmdPacketLen[cmd.commandId]);	//	send board info command
		}
		uart_write_bytes(port, zero, 5);
#endif
		return true;
	}
	void Update() {
		// write command to boards
		for (auto board : boards) {
			board->WriteCmd(CI_CURRENT, *this);
		}
		// send commands to uart
		SendUart();
		// receive from uart
		int boardPos = -1;
		for (auto board : boards) {
			boardPos++;
			int retLen = board->RetLenForCommand();
			if (retLen) {
				//	receive the header byte
				DWORD readLen = 0;
				ReadFile(owner->hUART, (void*)board->RetStart(), retLen, &readLen, NULL);
				if (readLen != retLen) {
					//	timeout
					unsigned i;
					for (i = 0; i < readLen; ++i) {
						if (board->RetStart()[i] == board->CmdStart()[0]) {
							break;
						}
					}
					DPF("DRUARTMotorDriverImpl::Update(): #%d ReadLen %d != RetLen %d, H%2x C%2x pos%d", boardPos, readLen, retLen,
						(int)board->RetStart()[0], (int)board->CmdStart()[0], i);
					Sleep(2000);
					owner->ClearComRead();
				}
				else {
					if (board->RetStart()[0] != board->CmdStart()[0]) {
						DPF("DRUARTMotorDriverImpl::Update(): Recv #%d H:%x L:%d for Cmd H:%x", boardPos, (int)board->RetStart()[0],
							board->RetLen(), (int)board->CmdStart()[0]);
					}
					board->ReadRet(CI_CURRENT, *this);
				}
			}
		}
	}
	void SendUart() {
		int wait = 0;
		for (auto board: boards) {
			int retLen = board->RetLenForCommand();
			wait = retLen - board->CmdLen() + 20;
			if (wait < 5) wait = 5;
			memset(board->CmdStart() + board->CmdLen(), 0, wait);
			WriteFile(owner->hUART, board->CmdStart(), board->CmdLen() + wait, NULL, NULL);
		}
	}
	//	override BoardCmdBase
	virtual short GetControlMode() {
		return CM_CURRENT;
	}
	virtual short GetMotorPos(int i) {
		return owner->currents[i];
	}
	virtual short GetMotorVel(int i) {
		return 0;
	}
	virtual unsigned short GetPeriod() {
		return 0;
	}
	virtual unsigned short GetTargetCountWrite() {
		return 0;
	}
	virtual short GetForceControlJacob(int j, int i) {
		return 0;
	}
	virtual short GetParamType() { return 0; }
	virtual short GetControlK(int i) { return 0; }
	virtual short GetControlB(int i) { return 0; }
	virtual short GetControlA(int i) { return 0; }
	virtual short GetTorqueMin(int i) { return 0; }
	virtual short GetTorqueMax(int i) { return 0; }
	virtual short GetBoardId() { return 0; }
	typedef ::ResetSensorFlags ResetSensorFlags;		//	in CommandIDs.cs
	virtual short GetResetSensorFlags() { return 0; }	//	

	//	override BoardRetBase
	virtual void SetAll(ControlMode controlMode, unsigned char targetCountReadMin, unsigned char targetCountReadMax,
		unsigned short tickMin, unsigned short tickMax,
		SDEC* pos, SDEC* vel, SDEC* current, SDEC* force, SDEC* touch) {
		for (int i = 0; i < owner->counts.size(); ++i) owner->UpdateCounter(i, pos[i]);
	}
	virtual void SetMotorPos(short p, int i) {  
		owner->UpdateCounter(i, p);
	}
	virtual void SetMotorVel(short v, int i) {}
	virtual void SetTargetCountReadMin(unsigned char c) {}
	virtual void SetTargetCountReadMax(unsigned char c) {}
	virtual void SetTickMin(unsigned short t) {}
	virtual void SetTickMax(unsigned short t) {}
	virtual void SetCurrent(short c, int i) {}
	virtual void SetForce(short f, int i) {}
	virtual void SetTouch(short t, int i) {}
	virtual void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce, int nTouch) {}
	virtual void SetParamType(short type) {}
	virtual void SetParamPD(short k, short b, int i) {}
	virtual void SetParamCurrent(short a, int i) {}
	virtual void SetParamHeat(short limit, short release, int i) {}
	virtual void SetParamTorque(short minimum, short maximum, int i) {}
};

void DRUARTMotorDriverImplUpdateMotorPos(DRUARTMotorDriverImpl* owner, short mpos, int index) {
	owner->owner->UpdateCounter(index, mpos);
}

DRUARTMotorDriver::DRUARTMotorDriver(const DRUARTMotorDriverDesc& d){
	port = d.port;
	hUART = INVALID_HANDLE_VALUE;
	impl = new DRUARTMotorDriverImpl(this);
}

DRUARTMotorDriver::~DRUARTMotorDriver(){
	delete impl;
	if (hUART) {
		CloseHandle(hUART);
		hUART = NULL;
	}
}
bool DRUARTMotorDriver::ClearCom() {
#ifdef _WIN32
	return PurgeComm(hUART, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR) == TRUE;
#else
	return false;
#endif
}
bool DRUARTMotorDriver::ClearComRead() {
#ifdef _WIN32
	return PurgeComm(hUART, PURGE_RXABORT | PURGE_RXCLEAR) == TRUE;
#else
	return false;
#endif
}

bool DRUARTMotorDriver::InitCom() {
#ifdef _WIN32
	if (SetupComm(hUART, 1024, 1024) != TRUE) return false;
	if (!PurgeComm(hUART, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)) return false;
	DWORD comError;
	COMSTAT comStat;
	ClearCommError(hUART, &comError, &comStat);
	DCB dcb;//�\�������L�^����\���̂̐���
	GetCommState(hUART, &dcb);//���݂̐ݒ�l��ǂݍ���
	dcb.DCBlength = sizeof(DCB);//DCB�̃T�C�Y
	dcb.BaudRate = 2000*1000;	//	baudrate 2Mbps
	dcb.ByteSize = 8;			//	8bit
	dcb.fBinary = TRUE;			//	binaly = TRUE
	dcb.fParity = NOPARITY;		//	no paritiy
	dcb.StopBits = ONESTOPBIT;	//	1 stop bit
	dcb.fOutxCtsFlow = FALSE;	//CTS�t���[����:�t���[����Ȃ�
	dcb.fOutxDsrFlow = FALSE;	//DSR�n�[�h�E�F�A�t���[����F�g�p���Ȃ�
	dcb.fDtrControl = DTR_CONTROL_DISABLE;//DTR�L��/����:DTR����
	dcb.fRtsControl = RTS_CONTROL_DISABLE;//RTS�t���[����:RTS����Ȃ�
	dcb.fOutX = FALSE;//���M��XON/XOFF����̗L��:�Ȃ�
	dcb.fInX = FALSE;//��M��XON/XOFF����̗L��:�Ȃ�
	dcb.fTXContinueOnXoff = TRUE;// ��M�o�b�t�@�[���t��XOFF��M��̌p�����M��:���M��
	dcb.XonLim = 512;//XON��������܂łɊi�[�ł���ŏ��o�C�g��:512
	dcb.XoffLim = 512;//XOFF��������܂łɊi�[�ł���ŏ��o�C�g��:512
	dcb.XonChar = 0x11;//���M��XON���� ( ���M�F�r�W�B���� ) �̎w��:XON�����Ƃ���11H ( �f�o�C�X����P�FDC1 )
	dcb.XoffChar = 0x13;//XOFF�����i���M�s�F�r�W�[�ʍ��j�̎w��:XOFF�����Ƃ���13H ( �f�o�C�X����3�FDC3 )

	dcb.fNull = FALSE;// NULL�o�C�g�̔j��:�j������
//	dcb.fAbortOnError = TRUE;//�G���[���̓ǂݏ�������I��:�I������
	dcb.fAbortOnError = FALSE;
	dcb.fErrorChar = FALSE;// �p���e�B�G���[�������̃L�����N�^�iErrorChar�j�u��:�Ȃ�
	dcb.ErrorChar = 0x00;// �p���e�B�G���[�������̒u���L�����N�^
	dcb.EofChar = 0x03;// �f�[�^�I���ʒm�L�����N�^:��ʂ�0x03(ETX)���悭�g���܂��B
	dcb.EvtChar = 0x02;// �C�x���g�ʒm�L�����N�^:��ʂ�0x02(STX)���悭�g���܂�
	if (SetCommState(hUART, &dcb) != TRUE) return false;  //�ݒ�l�̏�������

	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = 1;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 15;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(hUART, &timeouts)) return false;
#endif
	return true;
}

bool DRUARTMotorDriver::Init(){
	std::vector<string> comPorts;
	if (port = -1) {
		char nameBuffer[128 * 1000];
		if (QueryDosDevice(NULL, nameBuffer, sizeof(nameBuffer)) != 0) {
			char* p = nameBuffer;
			while (*p != '\0') {
				if (strncmp(p, "COM", 3) == 0 && p[3] != '\0') {
					comPorts.push_back(std::string(p));
				}
				p += (strlen(p) + 1);
			}
		}
		else {
			DWORD e = GetLastError();
			DSTR << "QueryDosDevice() Error: " << e << std::endl;
		}
	}
	else {
		comPorts.push_back(std::string("COM") + std::to_string(port));
	}
	impl->boards.clear();
	for (auto comPort : comPorts) {
		hUART = CreateFile(comPort.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,				//�|�[�g�̋��L���@���w��:�I�u�W�F�N�g�͋��L���Ȃ�
			NULL,			//�Z�L�����e�B����:�n���h�����q�v���Z�X�֌p�����Ȃ�
			OPEN_EXISTING,
			0,				//�|�[�g�̑������w��:�����@�񓯊��ɂ������Ƃ���FILE_FLAG_OVERLAPPED
			NULL);
		if (InitCom()) {
			impl->EnumBoards(hUART);
			if (impl->boards.size() > 0) {
				break;
			}
		}
	}
	//	�f�o�C�X�̓o�^
	for (int i = 0; i < impl->currentMap.size(); ++i) {
		AddChildObject((DBG_NEW Da(this, i))->Cast());
	}
	for (int i = 0; i < impl->motorMap.size(); ++i) {
		AddChildObject((DBG_NEW Counter(this, i))->Cast());
	}
	return true;
}
void DRUARTMotorDriver::WriteVoltage(int ch, float v) {
	currents[ch] = (int)v * 4096 / 24.0;	
}
void DRUARTMotorDriver::WriteDigit(int ch, int v) {
	currents[ch] = v;
}
void DRUARTMotorDriver::WriteCount(int ch, long c) {
	offsets[ch] = counts[ch] - c;
}
long DRUARTMotorDriver::ReadCount(int ch) {
	return counts[ch] - offsets[ch];
}
void DRUARTMotorDriver::UpdateCounter(int ch, short ct) {
	SDEC diff = ct - (SDEC)(counts[ch]);
	counts[ch] += diff;
}

void DRUARTMotorDriver::Update() {
	impl->Update();
}

void DRUARTMotorDriver::Reset() {
	//	TBW by hase
}



} //namespace Spr

