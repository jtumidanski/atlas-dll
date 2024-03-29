#include "pch.h"

// BE AWARE ===v
// in order to reference other projects you need to add:
// $(SolutionDir)Common;%(AdditionalIncludeDirectories)
// to project properties -> c/c++ -> additional include directories
#include "ExampleHooks.h"
#include <ZXString.h>
#include <Common.h>
#include <hooker.h>
#include <memedit.h>

// BE AWARE ===v
// in order to fix the detours.lib link error you need to replace
// project properties -> vc++ directories -> library directories 
// with $(SolutionDir)Common;$(LibraryPath)

typedef VOID(__stdcall* _ShowStartUpWndModal_t)();
_ShowStartUpWndModal_t _ShowStartUpWndModal;

VOID __stdcall ShowStartUpWndModal() {
	Log(__FUNCTION__);
	Log("NoOp Patcher Function");
}

const DWORD dwCClientSocketProcessPacket = 0x004965F1;
const DWORD dwCSecurityClientOnPacketCall = dwCClientSocketProcessPacket + 0x7F;

const DWORD dwWinMain = 0x009F19F2;
const DWORD dwWinMainShowStartUpWndModalCall = dwWinMain + 0x212; // 0x009F1C04

const DWORD dwCSecurityClientCreateInstance = 0x009F9F42;
const DWORD dwCSecurityClientInitModule = 0x00A4BB2B;
const DWORD dwCSecurityClientStartModule = 0x00A4BD91;

const DWORD dwCWvsAppInitializeGr2D = 0x009F7A3B;

const DWORD dwFixFullScreen = dwCWvsAppInitializeGr2D + 0x60; // 0x009F7A9B
const DWORD dwFixFullScreenReturn = dwCWvsAppInitializeGr2D + 0x65;

const DWORD dwCWvsAppSetUp = 0x009F5239;
const DWORD dwNukedCWvsAppSetupReturn = dwCWvsAppSetUp + 0xA08;

const DWORD dwCWvsAppInitializeInput = 0x009F7CE1;
const DWORD dwNukedCWvsAppInitializeInputReturn = dwCWvsAppInitializeInput + 0x52F;

const DWORD dwCWvsAppRun= 0x009F5C50;
const DWORD dwNukedCWvsAppRunReturn = dwCWvsAppRun + 0xD2F; //D2F

const DWORD dwCClientSocketConnect= 0x00494CA3;
const DWORD dwNukedCClientSocketConnectReturn = dwCClientSocketConnect + 0x5F; //D2F

const DWORD dwCWvsAppCallUpdate = 0x009F84D0;
const DWORD dwNukedCWvsAppCallUpdateReturn = dwCWvsAppCallUpdate + 0x680;

const DWORD dwEH_prolog = 0x00A60B98;
const DWORD dwCWvsAppInitializeAuth = 0x009F7097;
const DWORD dwTimeGetTime = 0x00BF060C;
const DWORD dwSrand = 0x00A61C60;
const DWORD dwGetSEPrivilege = 0x0044E824;
const DWORD dwCWvsAppInitializePCOM = 0x009F6D77;
const DWORD dwCWvsAppCreateMainWindow = 0x009F6D97;
const DWORD dwCClientSocketCreateInstance = 0x009F9E53;
const DWORD dwCWvsAppConnectLogin = 0x009F6F27;
const DWORD dwCFuncKeyMappedManCreateInstance = 0x009F9E98;
const DWORD dwCQuickslotKeyMappedManCreateInstance = 0x009FA0CB;
const DWORD dwCMacroSysManCreateInstance = 0x009F9EEE;
const DWORD dwCWvsAppInitializeResMan = 0x009F7159;
const DWORD dwCWvsAppInitializeSound = 0x009F82BC;
const DWORD dwCWvsAppInitializeGameData = 0x009F8B61;
const DWORD dwCWvsAppCreateWndManager = 0x009F7034;
const DWORD dwCConfigApplySysOpt = 0x0049EA33;
const DWORD dwCActionManCreateInstance = 0x009F9DA6;
const DWORD dwCMapleTVManInit = 0x00636F4E;
const DWORD dwCQuestManCreateInstance = 0x009F9AC2;
const DWORD dwCQuestManLoadDemand = 0x0071D8DF;
const DWORD dwCxxThrowException = 0x00A60BB7;
const DWORD dwCQuestManLoadPartyQuestInfo = 0x00723341;
const DWORD dwCQuestManLoadExclusive = 0x007247A1;
const DWORD dwCMonsterBookManCreateInstance = 0x009F9B73;
const DWORD dwCMonsterBookManLoadBook = 0x0068487C;
const DWORD dwCRadioManagerCreateInstance = 0x009FA078;
const DWORD dwCWvsAppDir_BackSlashToSlash = 0x009F95FE;
const DWORD dwCWvsAppDir_upDir = 0x009F9644;
const DWORD dwCWvsAppDir_SlashToBackSlash = 0x009F9621;
const DWORD dwZXStringCharGetBuffer = 0x00414617;
const DWORD dwCConfigGetInstance = 0x00538C98;
const DWORD dwCConfigCheckExecPathReg = 0x0049CCF3;
const DWORD dwCLogoCLogo = 0x0062ECE2;
const DWORD dwset_stage = 0x00777347;

const DWORD dwCInputSystemCInputSystem = 0x009F821F;
const DWORD dwCInputSystemCreateInstance = 0x009F9A6A;
const DWORD dwCInputSystemInit = 0x00599EBF;
const DWORD dwZAllocAnonSelectorAlloc = 0x00403065;

const DWORD dwCActionManInit = 0x00406ABD;
const DWORD dwCAnimationDisplayerCreateInstance = 0x009F9DFC;
const DWORD dwCMapleTVManCreateInstance = 0x009F9F87;

const DWORD dwZRefCStage = 0x00496B68;
const DWORD dwCWndManSUpdate = 0x009E47C3;
const DWORD dwComIssueError = 0x00A5FDE4;
const DWORD dwComIssueErrorEx = 0x00A5FDF2;
const DWORD dwZRefCStageDestructor = 0x00496B85;
const DWORD dwCActionManSweepCache = 0x00411BBB;

const DWORD dwCClientSocketManipulatePacket = 0x0049651D;
const DWORD dwCInputSystemUpdateDevice = 0x0059A2E9;
const DWORD dwCInputSystemGetISMessage = 0x0059A306;
const DWORD dwCWvsAppISMsgProc = 0x009F97B7;
const DWORD dwCPatchExceptionCPatchException = 0x0051E834;
const DWORD dwCInputSystemGenerateAutoKeyDown = 0x0059B2D2;
const DWORD dwIWzGr2DGetnextRenderTime = 0x009F6990;
const DWORD dwCWndManRedrawInvalidatedWindows = 0x009E4547;
const DWORD dwIWzGr2DRenderFrame = 0x00777326;
const DWORD dwA61DF2 = 0x00A61DF2;

const DWORD dw494D07 = 0x00494D07;

const DWORD dwCLoginSendCheckPasswordPacket = 0x005F6952;
const DWORD dwNukedCLoginSendCheckPasswordPacketReturn = dwCLoginSendCheckPasswordPacket + 0x30F;

const DWORD dw5FDDE3 = 0x005FDDE3;
const DWORD dw5FDF26 = 0x005FDF26;
const DWORD dwA54B90 = 0x00A54B90;
const DWORD dwA54BD0 = 0x00A54BD0;
const DWORD dwA54EB0 = 0x00A54EB0;
const DWORD dw5F6CFB = 0x005F6CFB;
const DWORD dwA54BC0 = 0x00A54BC0;
const DWORD dwCOutPacketConstructor = 0x006EC9CE;
const DWORD dwZXStringGetBuffer = 0x00414617;
const DWORD dwCOutPacketEncodeStr = 0x0046F3CF;
const DWORD dwCOutPacketEncodeBuffer = 0x0046C00C;
const DWORD dwCOutPacketEncode4 = 0x004065A6;
const DWORD dwCOutPacketEncode1 = 0x00406549;
const DWORD dwCClientSocketSendPacket = 0x0049637B;
const DWORD ZArrayRemoveAll = 0x00428CF1;

const DWORD dw494D2F = 0x00494D2F;
const DWORD dwNuked494D2FReturn = dw494D2F;

const DWORD dwCClientSocketClearSendReceiveCtx = 0x004969EE;
const DWORD dw494857 = 0x00494857;

const DWORD dwCClientSocketOnConnect = 0x00494ED1;

__declspec(naked) void FixFullScreen() {
	__asm {
		mov eax,0
		jmp dword ptr[dwFixFullScreenReturn]
	}
}

__declspec(naked) void NukedCWvsAppSetup() {
	__asm {
			mov eax, dword ptr ds : [0x00AE7DF2]
			call dwEH_prolog
			sub esp, 1012
			push ebx
			push esi
			push edi
			mov [ebp-1008], ecx
			mov ecx, [ebp-1008]
			call dwCWvsAppInitializeAuth
			call dword ptr ds : [0x00BF060C] //timeGetTime
			push eax
			call dwSrand
			pop ecx
			call dwGetSEPrivilege
			jmp label21
		label21:
			// CSecurityClient crap
			xor eax, eax
			cmp dword ptr ds : [0x00BEC3A8], 0
			setnz al
			test eax, eax
			jnz short label20
			call dwCSecurityClientCreateInstance
		label20:
			xor eax, eax
			cmp dword ptr ds : [0x00BEC3A8] , 0
			setnz al
			test eax, eax
			jmp short label22
			mov ecx, dword ptr ds : [0x00BEC3A8]
			call dwCSecurityClientInitModule
		label22:
			xor eax, eax
			cmp dword ptr ds : [0x00BEC3A8] , 0
			setnz al
			test eax, eax
			jmp short label23
			mov ecx, dword ptr ds : [0x00BEC3A8]
			call dwCSecurityClientStartModule
		label23:
			mov dword ptr ds:[0x00BF1AC8], 16
			mov ecx, [ebp-1008]
			call dwCWvsAppInitializePCOM
			mov ecx, [ebp-1008]
			call dwCWvsAppCreateMainWindow
			call dwCClientSocketCreateInstance
			mov ecx, [ebp-1008]
			call dwCWvsAppConnectLogin
			call dwCFuncKeyMappedManCreateInstance
			call dwCQuickslotKeyMappedManCreateInstance
			call dwCMacroSysManCreateInstance
			mov ecx, [ebp-1008]
			call dwCWvsAppInitializeResMan
			lea eax, [ebp-400]
			push eax
			call dword ptr ds : [0x00BF0448]
			push eax
			call dword ptr ds : [0x00BF0444]
			mov eax, 0x00BE7918
			mov eax, [eax+14320]
			mov [ebp-944], eax
			cmp dword ptr [ebp-944], 0
			jz short label1
			push 32
			//mov ecx, dword ptr ds : [0x00BF0B00]
			mov eax, dword ptr [0x00BF0B00]
			mov ecx, eax
			call dwZAllocAnonSelectorAlloc
			mov [ebp-872], eax
			and dword ptr [ebp-4], 0
			cmp dword ptr [ebp-872], 0
			jz short label2
			sub esp, 16
			lea esi, [ebp-400]
			mov edi, esp
			movsd
			movsd
			movsd
			movsd
			mov ecx, [ebp-872]
			call dword ptr ds : [0x0042C3DE]
			mov [ebp-1012], eax
			jmp short label3
		label2:
			and dword ptr [ebp-1012], 0
		label3:
			mov eax, [ebp-1012]
			mov [ebp-868], eax
			or dword ptr [ebp-4], 4294967295
		label1:
			mov ecx, [ebp-1008]
			call dwCWvsAppInitializeGr2D
			mov ecx, [ebp - 1008]
			call dwCWvsAppInitializeInput
			push 300
			call dword ptr ds : [0x00BF02F4]
			mov ecx, [ebp-1008]
			call dwCWvsAppInitializeSound
			push 300
			call dword ptr ds : [0x00BF02F4]
			mov ecx, [ebp - 1008]
			call dwCWvsAppInitializeGameData
			mov ecx, [ebp - 1008]
			call dwCWvsAppCreateWndManager
			push 0
			push 0
			mov ecx, dword ptr ds : [0x00BEBF9C]
			call dwCConfigApplySysOpt
			call dwCActionManCreateInstance
			mov ecx, eax
			call dwCActionManInit
			call dwCAnimationDisplayerCreateInstance
			call dwCMapleTVManCreateInstance
			mov ecx, eax
			call dwCMapleTVManInit
			call dwCQuestManCreateInstance
			mov ecx, eax
			call dwCQuestManLoadDemand
			test eax, eax
			jnz short label4
			mov dword ptr [ebp-880], 570425350
			lea eax, [ebp-880]
			mov [ebp-1016], eax
			mov dword ptr [ebp-4], 1
			mov eax, [ebp-1016]
			mov eax, [eax]
			mov [ebp-876], eax
			push 11814752
			lea eax, [ebp-876]
			push eax
			call dwCxxThrowException
		label4:
			mov ecx, dword ptr ds : [0x00BED614]
			call dwCQuestManLoadPartyQuestInfo
			mov ecx, dword ptr ds : [0x00BED614]
			call dwCQuestManLoadExclusive
			call dwCMonsterBookManCreateInstance
			mov ecx, eax
			call dwCMonsterBookManLoadBook
			test eax, eax
			jnz short label5
			mov dword ptr[ebp - 888], 570425350
			lea eax, [ebp - 888]
			mov[ebp - 1020], eax
			mov dword ptr[ebp - 4], 2
			mov eax, [ebp - 1020]
			mov eax, [eax]
			mov[ebp - 884], eax
			push 11814752
			lea eax, [ebp - 884]
			push eax
			call dwCxxThrowException
		label5:
			call dwCRadioManagerCreateInstance
			push 260
			lea eax, [ebp-292]
			push eax
			push 0
			call dword ptr ds : [0x00BF028C]
			lea eax, [ebp-292]
			push eax
			call dwCWvsAppDir_BackSlashToSlash
			pop ecx
			lea eax, [ebp-292]
			push eax
			call dwCWvsAppDir_upDir
			pop ecx
			lea eax, [ebp - 292]
			push eax
			call dwCWvsAppDir_SlashToBackSlash
			pop ecx
			push ecx
			mov eax, esp
			mov [ebp-892], esp
			mov [ebp-1004], eax
			mov eax, [ebp-1004]
			and dword ptr [eax], 0
			push 4294967295
			lea eax, [ebp-292]
			push eax
			mov ecx, [ebp-1004]
			call dwZXStringCharGetBuffer
			mov dword ptr [ebp-4], 3
			call dwCConfigGetInstance
			mov ecx, eax
			or dword ptr [ebp-4], 4294967295
			call dwCConfigCheckExecPathReg
			push 56
			//mov ecx, dword ptr ds : [0x00BF0B00]
			mov eax, dword ptr[0x00BF0B00]
			mov ecx, eax
			call dwZAllocAnonSelectorAlloc
			mov [ebp-900], eax
			mov dword ptr [ebp-4], 4
			cmp dword ptr [ebp-900], 0
			jz short label6
			mov ecx, [ebp-900]
			call dwCLogoCLogo
			mov [ebp-1024], eax
			jmp short label7
		label6:
			and dword ptr [ebp-1024], 0
		label7:
			mov eax, [ebp-1024]
			mov [ebp-896], eax
			or dword ptr [ebp-4], 4294967295
			push 0
			push dword ptr [ebp-896]
			call dwset_stage
			pop ecx
			pop ecx
			mov dword ptr [ebp-808], 3708088046
			and dword ptr [ebp-312], 0
			jmp short label8
		label15:
			mov eax, [ebp-312]
			inc eax
			mov [ebp-312], eax
		label8:
			cmp dword ptr [ebp-312], 256
			jge label9
			mov eax, [ebp-312]
			mov [ebp-860], eax
			mov dword ptr  [ebp-864], 8
			jmp short label13
		label14:
			mov eax, [ebp-864]
			dec eax
			mov [ebp-864], eax
		label13:
			cmp dword ptr[ebp-864], 0
			jle short label10
			mov eax, [ebp-860]
			and eax, 1
			test eax, eax
			jz short label12
			mov eax, [ebp-860]
			shr eax, 1
			mov ecx, [ebp-808]
			sub ecx, 5421
			xor eax, ecx
			mov [ebp-860], eax
			jmp short label11
		label12:
			mov eax, [ebp-860]
			shr eax, 1
			mov [ebp-860], eax
		label11:
			jmp short label14
		label10:
			mov eax, [ebp-312]
			mov ecx, [ebp-860]
			mov dword ptr ds : [0x00BF167C][eax*4], ecx
			jmp label15
		label9:
			jmp short label16
		label16:
			jmp dword ptr[dwNukedCWvsAppSetupReturn]
	}
}

__declspec(naked) void NukedCWvsAppInitializeInput() {
	__asm {
			mov eax, dword ptr ds : [0x00AE812D]
			call dwEH_prolog
			sub esp, 198h
			push ebx
			push esi
			push edi
			mov [ebp-1A0h], ecx
			jmp short label3
		label3:
			push 9D0h
			//mov ecx, dword ptr ds : [0x00BF0B00]
			mov eax, dword ptr[0x00BF0B00]
			mov ecx, eax
			call dwZAllocAnonSelectorAlloc
			mov [ebp-190h], eax
			and dword ptr [ebp-4], 0
			cmp dword ptr [ebp-190h], 0
			jz label1
			mov ecx, [ebp-190h]
			call dwCInputSystemCInputSystem
			mov [ebp-1A4h], eax
			jmp label2
		label1:
			and dword ptr [ebp-1A4h], 0
		label2:
			mov eax, [ebp- 1A4h]
			mov [ebp-18Ch], eax
			or dword ptr [ebp-4], 0FFFFFFFFh
			mov eax, [ebp-1A0h]
			mov eax, [eax + 4]
			mov [ebp-194h], eax
			mov eax, [ebp-1A0h]
			add eax, 54h
			push eax
			push dword ptr[ebp-194h]
			call dwCInputSystemCreateInstance
			mov ecx, eax
			call dwCInputSystemInit
			jmp label4
		label4:
			jmp dword ptr[dwNukedCWvsAppInitializeInputReturn]
	}
}

__declspec(naked) void NukedCWvsAppRun() {
	__asm {
			mov eax, dword ptr[0x00AE7E2C]
			call dwEH_prolog

			sub esp, 0D3Ch
			push ebx
			push esi
			push edi
			mov [ebp-0D30h], ecx
			and dword ptr [ebp-9Ch], 0

			push 6
			pop ecx
			xor eax, eax
			lea edi, [ebp-98h]
			rep stosd
			and dword ptr [ebp-28h], 0
			xor eax, eax
			lea edi, [ebp-24h]
			stosd
			stosd
			xor eax, eax
			cmp dword ptr ds : [0x00BE7914], 0
			setnz al
			test eax, eax
			jz short label9F5CA3
			mov ecx, dword ptr ds : [0x00BE7914]
			call dwCClientSocketManipulatePacket

		label9F5CA3:
			jmp label9F5FDB

		label9F5FDB:
			and dword ptr [ebp-2Ch], 0

		label9F5FDF:
			push 0FFh
			push 0
			push 0
			mov eax, [ebp-0D30h]
			add eax, 54h
			push eax
			push 3
			call dword ptr ds : [0x00BF04EC]

			mov [ebp-0A8h], eax
			mov eax, [ebp-0A8h]
			mov [ebp-0D34h], eax
			cmp dword ptr [ebp-0D34h], 0
			jb label9F62BB

			cmp dword ptr [ebp-0D34h], 2
			jbe label9F6030

			cmp dword ptr [ebp-0D34h], 3
			jz short label9F6079

			jmp label9F62BB

		label9F6030:
			push dword ptr [ebp-0A8h]
			mov ecx, dword ptr ds : [0x00BEC33C]
			call dwCInputSystemUpdateDevice
		
		label9F6041 :
			lea eax, [ebp-28h]
			push eax
			mov ecx, dword ptr ds : [0x00BEC33C]
			call dwCInputSystemGetISMessage
			test eax, eax
			jz short label9F6074

			push dword ptr [ebp-20h]
			push dword ptr [ebp-24h]
			push dword ptr [ebp-28h]
			mov ecx, [ebp-0D30h]
			call dwCWvsAppISMsgProc

			mov eax, [ebp+8]
			cmp dword ptr [eax], 0
			jz short label9F6072
			jmp label9F6074

		label9F6072 :
			jmp short label9F6041

		label9F6074 :
			jmp label9F694D

		label9F6079:
			push 1
			push 0
			push 0
			push 0
			lea eax, [ebp-9Ch]
			push eax
			call dword ptr ds : [0x00BF04E8]
			test eax, eax
			jz label9F62B6
			lea eax, [ebp-9Ch]
			push eax
			call dword ptr ds : [0x00BF0430]
			lea eax, [ebp-9Ch]
			push eax
			call dword ptr ds : [0x00BF042C]
			mov eax, [ebp-0D30h]
			cmp dword ptr [eax+38h], 0
			jnz short label9F60C5
			and dword ptr [ebp-0D04h], 0
			jmp short label9F60F2

		label9F60C5:
			mov eax, [ebp-0D30h]
			mov eax, [eax+38h]
			mov [ebp-0ACh], eax
			mov eax, [ebp-0D30h]
			and dword ptr [eax+38h], 0
			mov eax, [ebp-0D30h]
			and dword ptr [eax+34h], 0
			mov dword ptr [ebp-0D04h], 1

		label9F60F2:
			cmp dword ptr [ebp-0D04h], 0
			jz short label9F6108
			push 0
			push dword ptr [ebp-0ACh]
			call dwComIssueError

		label9F6108:
			mov eax, [ebp-0D30h]
			cmp dword ptr [eax+34h], 0
			jnz short label9F611D
			and dword ptr [ebp-0D08h], 0
			jmp short label9F614A

		label9F611D:
			mov eax, [ebp-0D30h]
			mov eax, [eax+34h]
			mov [ebp-0ACh], eax
			mov eax, [ebp-0D30h]
			and dword ptr [eax+38h], 0
			mov eax, [ebp-0D30h]
			and dword ptr [eax+34h], 0
			mov dword ptr [ebp-0D08h], 1

		label9F614A:
			cmp dword ptr [ebp-0D08h], 0
			jz label9F629E

			cmp dword ptr [ebp-0ACh], 20000000h

			jnz short label9F61B1

			mov eax, [ebp-0D30h]
			push dword ptr [eax+40h]
			lea ecx, [ebp-0CE8h]
			call dwCPatchExceptionCPatchException

			mov [ebp-0D38h], eax
			mov eax, [ebp-0D38h]
			mov [ebp-0D3Ch], eax

			and dword ptr [ebp-4], 0
			mov esi, [ebp-0D3Ch]
			mov ecx, 142h
			lea edi, [ebp-7E0h]
			rep movsd
			push 0B52FC8h
			lea eax, [ebp-7E0h]
			push eax
			call dwCxxThrowException

		label9F61B1:
			cmp dword ptr [ebp-0ACh], 21000000h

			jl short label9F6213

			cmp dword ptr [ebp-0ACh], 21000006h

			jg short label9F6213

			mov eax, [ebp-0ACh]
			mov [ebp-0D0Ch], eax
			mov eax, [ebp-0D0Ch]
			mov [ebp-0CF0h], eax
			lea eax, [ebp-0CF0h]
			mov [ebp-0D40h], eax
			mov dword ptr [ebp-4], 1
			mov eax, [ebp-0D40h]
			mov eax, [eax]
			mov [ebp-0CECh], eax
			//push offset AVCDisconnectException
			push 0
			lea eax, [ebp-0CECh]
			push eax
			call dwCxxThrowException

		label9F6213:
			cmp dword ptr [ebp-0ACh], 22000000h
			jl short label9F6275

			cmp dword ptr [ebp-0ACh], 2200000Dh

			jg short label9F6275

			mov eax, [ebp - 0ACh]
			mov[ebp - 0D10h], eax
			mov eax, [ebp - 0D10h]
			mov[ebp - 0CF8h], eax
			lea eax, [ebp - 0CF8h]
			mov[ebp - 0D44h], eax
			mov dword ptr[ebp - 4], 1
			mov eax, [ebp - 0D44h]
			mov eax, [eax]
			mov[ebp - 0CF4h], eax
			//push offset AVCDisconnectException
			push 0
			lea eax, [ebp - 0CF4h]
			push eax
			call dwCxxThrowException

		label9F6275:
			mov eax, [ebp - 0ACh]
			mov[ebp - 0D00h], eax
			mov eax, [ebp - 0D00h]
			mov[ebp - 0CFCh], eax
			//push offset AVCDisconnectException
			lea eax, [ebp - 0CFCh]
			push eax
			call dwCxxThrowException

		label9F629E:
			mov eax, [ebp+8]
			cmp dword ptr [eax], 0
			jnz short label9F62AF
			cmp dword ptr [ebp-98h], 12h
			jnz short label9F62B1

		label9F62AF:
			jmp short label9F62B6

		label9F62B1:
			jmp label9F6079

		label9F62B6:
			jmp label9F694D

		label9F62BB:
			lea eax, [ebp-28h]
			push eax
			mov ecx, dword ptr ds : [0x00BEC33C]
			call dwCInputSystemGenerateAutoKeyDown
			test eax, eax
			jz short label9F62E2

			push dword ptr [ebp-20h]
			push dword ptr [ebp-24h]
			push dword ptr [ebp-28h]
			mov ecx, [ebp-0D30h]
			call dwCWvsAppISMsgProc

		label9F62E2:
			mov ecx, dword ptr ds : [0x00BEC3A8]
			nop
			nop
			nop
			nop
			nop
			xor eax, eax
			test eax, eax
			jz short label9F62FD
			push 80004003h
			call dwComIssueError

		label9F62FD:
			xor eax, eax
			cmp dword ptr ds : [0x00BF14EC], 0
			setz al
			movzx eax, al
			neg eax
			sbb eax, eax
			inc eax
			movzx eax, al
			test eax, eax
			jz label9F6945
			jmp short label9F632E

		label9F632E:
			cmp dword ptr ds : [0x00BF14EC], 0
			jnz short label9F6341
			push 80004003h
			call dwComIssueError

		label9F6341:
			mov ecx, dword ptr ds : [0x00BF14EC]
			call dwIWzGr2DGetnextRenderTime
			mov [ebp-0B0h], eax
			push dword ptr [ebp-0B0h]
			mov ecx, [ebp-0D30h]
			call dwCWvsAppCallUpdate
			call dwCWndManRedrawInvalidatedWindows
			cmp dword ptr ds : [0x00BF14EC], 0
			jnz short label9F637B
			push 80004003h
			call dwComIssueError

		label9F637B:
			mov ecx, dword ptr ds : [0x00BF14EC]
			call dwIWzGr2DRenderFrame
			jmp label9F6945

		label9F6945:
			push 1
			call dword ptr ds : [0x00BF02F4]

		label9F694D:
			mov eax, [ebp+8]
			cmp dword ptr [eax], 0
			jnz short label9F695E

			cmp dword ptr [ebp-98h], 12h
			jnz short label9F6960

		label9F695E:
			jmp short label9F6965

		label9F6960:
			jmp label9F5FDF

		label9F6965:
			push dword ptr [ebp-34h]
			call dwA61DF2
			pop ecx
			cmp dword ptr [ebp-98h], 12h
			jnz short label9F697
			push 0
			call dword ptr ds : [0x00BF041C]

		label9F697:
			jmp dword ptr[dwNukedCWvsAppRunReturn]
	}
}

__declspec(naked) void NukedCWvsAppCallUpdate() {
	__asm {
			mov eax, dword ptr ds : [0x00AE823A]
			call dwEH_prolog
			sub esp, 200h
			push ebx
			push esi
			push edi
			mov [ebp-204h], ecx
			jmp short label1

		label1:		
			mov eax, [ebp-204h]
			cmp dword ptr [eax+1Ch], 0
			jz short label2

			mov eax, [ebp-204h]
			mov ecx, [ebp+8]
			mov [eax+18h], ecx
			mov eax, [ebp-204h]
			mov ecx, [ebp+8]
			mov [eax+44h], ecx
			mov eax, [ebp-204h]
			mov ecx, [ebp+8]
			mov[eax + 48h], ecx
			mov eax, [ebp - 204h]
			mov ecx, [ebp + 8]
			mov[eax + 4Ch], ecx
			mov eax, [ebp - 204h]
			mov ecx, [ebp + 8]
			mov[eax + 50h], ecx
			mov eax, [ebp - 204h]
			and dword ptr [eax+1Ch], 0

		label2:
			mov eax, [ebp-204h]
			mov ecx, [ebp+8]
			sub ecx, [eax+18h]
			test ecx, ecx
			jle label4 

			mov eax, dword ptr ds : [0x00BEDED4]
			mov [ebp-14h], eax
			lea ecx, [ebp-18h]
			call dwZRefCStage

			and dword ptr [ebp-4], 0
			mov eax, [ebp-14h]
			mov [ebp-1C0h], eax
			cmp dword ptr [ebp-1C0h], 0
			jz short label5

			mov eax, [ebp-1C4h]
			mov [ebp-208h], eax
			mov eax, [ebp-14h]
			mov [ebp-208h], eax
			mov eax, [ebp-208h]
			mov eax, [eax]
			mov ecx, [ebp-208h]
			call dword ptr [eax]

		label5:
			call dwCWndManSUpdate
			mov eax, [ebp-204h]
			mov eax, [eax+18h]
			add eax, 1Eh
			mov ecx, [ebp-204h]
			mov [ecx+18h], eax
			mov eax, [ebp-204h]
			mov ecx, [ebp+8]
			sub ecx, [eax+18h]
			test ecx, ecx
			jle short label6

			cmp dword ptr ds : [0x00BF14EC], 0
			jnz short label7

			push 80004003h
			call dwComIssueError
		label7:
			mov eax, [ebp-204h]
			mov eax, [eax+18h]
			mov [ebp-1D0h], eax
			mov eax, dword ptr ds : [0x00BF14EC]
			mov [ebp-1CCh], eax
			push dword ptr [ebp-1D0h]
			mov eax, [ebp-1CCh]
			mov eax, [eax]
			push dword ptr [ebp-1CCh]
			call dword ptr [eax+18h]

			mov [ebp-1C8h], eax
			cmp dword ptr [ebp-1C8h], 0
			jge short label6

			push 0BD83B0h
			push dword ptr [ebp-1CCh]
			push dword ptr [ebp-1C8h]
			call dwComIssueErrorEx
		label6:
			or dword ptr [ebp-4], 0FFFFFFFFh
			lea ecx, [ebp-18h]
			call dwZRefCStageDestructor
			jmp label2

		label4:
			cmp dword ptr ds : [0x00BF14EC], 0
			jnz short label9
			push 80004003h
			call dwComIssueError

		label9:
			mov eax, dword ptr ds : [0x00BF14EC]
			mov [ebp-200h], eax
			push dword ptr [ebp+8]
			mov eax, [ebp-200h]
			mov eax, [eax]
			push dword ptr [ebp-200h]
			call dword ptr [eax+18h]
			mov [ebp-1FCh], eax
			cmp dword ptr [ebp-1FCh], 0
			jge short label8

			push 0BD83B0h
			push dword ptr [ebp-200h]
			push dword ptr [ebp-1FCh]
			call dwComIssueErrorEx

		label8:
			mov ecx, dword ptr ds : [0x00BE78D4]
			call dwCActionManSweepCache
			jmp dword ptr[dwNukedCWvsAppCallUpdateReturn]
	}
}


__declspec(naked) void NukedCClientSocketConnect() {
	__asm {
		push ebp
		mov ebp, esp
		push esi
		mov esi, ecx
		push dword ptr [ebp+8]
		lea ecx, [esi+0Ch]
		call dw494D07
		mov eax, [esi+18h]
		mov ecx, eax
		neg ecx
		sbb ecx, ecx
		lea edx, [eax-10h]
		and ecx, edx
		mov [esi+20h], eax
		mov ecx, [ecx+4]
		mov edx, ecx
		add ecx, 10h
		neg edx
		sbb edx, edx
		and edx, ecx
		push eax
		mov ecx, esi
		mov [esi+20h], edx
		call dw494D2F
		jmp dword ptr[dwNukedCClientSocketConnectReturn]
	}
}

__declspec(naked) void NukedCLoginSendCheckPasswordPacket() {
	__asm {
			mov eax, dword ptr ds : [0x00AE7DF2]
			call dwEH_prolog
			sub esp, 1012
			push ebx
			push esi
			push edi
			mov esi, ecx
			xor edi, edi
			cmp [esi+170h], edi
			jnz label5F6B53
			push 1
			pop ebx
			lea ecx, [esi+18Ch]
			mov [esi+170h], ebx
			call dw5FDDE3
			lea ecx, [esi+204h]
			call dw5FDF26
			jmp label5F6B5D

		label5F6B53:
			jmp dword ptr[dwNukedCLoginSendCheckPasswordPacketReturn]

		label5F6B5D:
			lea ecx, [ebp-4Ch]
				call dwA54B90
				lea ecx, [ebp-4Ch]
				mov dword ptr [ebp-4], 2
				call dwA54BD0
				push ebx
				lea ecx, [ebp-1Ch]
				call dwCOutPacketConstructor
				push ecx
				mov ecx, esp
				mov [ebp-28h], esp
				or esi, 0FFFFFFFFh
				push esi
				push dword ptr [ebp+8]
				mov byte ptr [ebp-4], 3
				mov [ecx], edi
				call dwZXStringGetBuffer
				lea ecx, [ebp-1Ch]
				call dwCOutPacketEncodeStr
				push ecx
				mov ecx, esp
				mov [ebp-60h], esp
				push esi
				push dword ptr [ebp+0Ch]
				nop
				nop
				nop
				nop
				mov [ecx], edi
				call dwZXStringGetBuffer
				lea ecx, [ebp - 1Ch]
				call dwCOutPacketEncodeStr
				push 10h
				lea ecx, [ebp-4Ch]
				call dwA54EB0
				push eax
				lea ecx, [ebp-1Ch]
				call dwCOutPacketEncodeBuffer
				lea ecx, [ebp-4Ch]
				call dwA54EB0
				push eax
				lea ecx, [ebp-1Ch]
				call dwCOutPacketEncode4
				mov eax, dword ptr ds : [0x00BE7B38]
				push dword ptr [eax+24h]
				lea ecx, [ebp-1Ch]
				call dwCOutPacketEncode1
				push edi
				lea ecx, [ebp - 1Ch]
				call dwCOutPacketEncode1
				push edi
				lea ecx, [ebp - 1Ch]
				call dwCOutPacketEncode1
				mov ecx, dword ptr ds : [0x00BEBF9C]
				call dw5F6CFB
				push eax
				lea ecx, [ebp-1Ch]
				call dwCOutPacketEncode4
				mov ecx, dword ptr ds : [0x00BE7914]
				lea eax, [ebp-1Ch]
				push eax
				call dwCClientSocketSendPacket
				mov eax, dword ptr ds : [0x00BE7918]
				push esi
				push dword ptr [ebp+8]
				lea ecx, [eax+2048h]
				call dwZXStringGetBuffer
				mov eax, dword ptr ds : [0x00BEDA60]
				cmp eax, edi
				jz short label5F6C48
				lea ecx, [eax+4]
				mov eax, [ecx]
				call dword ptr [eax+34h]

			label5F6C48:
				lea ecx, [ebp-18h]
				mov byte ptr [ebp-4], 2
				call ZArrayRemoveAll
				lea ecx, [ebp-4Ch]
				mov [ebp-4], esi
				call dwA54BC0
				mov eax, ebx
				jmp dword ptr[dwNukedCLoginSendCheckPasswordPacketReturn]
	}
}

__declspec(naked) void Nuked494D2F() {
	__asm {
			push ebp
			mov ebp, esp
			sub esp, 30h
			push ebx
			push esi
			push edi
			mov [ebp-30h], ecx
			jmp label494DEF

		label494DEF:
			mov ecx, [ebp-30h]
			call dwCClientSocketClearSendReceiveCtx
			mov ecx, [ebp-30h]
			add ecx, 8
			call dw494857
			mov eax, [ebp-30h]
			add eax, 8
			mov [ebp-24h], eax
			push 0
			push 1
			push 2
			call dword ptr ds : [0x00AF036C]

			mov ecx, [ebp-24h]
			mov [ecx], eax
			mov eax, [ebp-24h]
			cmp dword ptr [eax], 0FFFFFFFFh
			jnz short label494E47
			call dword ptr ds : [0x00AF0364]
			mov [ebp-20h], eax
			mov eax, [ebp-20h]
			mov [ebp-1Ch], eax
			mov eax, [ebp-1Ch]
			mov [ebp-18h], eax
			push 0B44EE0h
			lea eax, [ebp-18h]
			push eax
			call dwCxxThrowException

		label494E47:
			call dword ptr ds : [0x00BF060C]
			add eax, 1388h
			mov ecx, [ebp - 30h]
			mov[ecx + 38h], eax
			mov eax, [ebp - 30h]
			mov eax, [eax + 8]
			mov[ebp - 28h], eax
			push 33h
			push 401h
			mov eax, [ebp - 30h]
			push dword ptr[eax + 4]
			push dword ptr[ebp - 28h]
			call dword ptr ds : [0x00BF062C]
			cmp eax, 0FFFFFFFFh
			jz short label494EA5
			mov eax, [ebp-30h]
			mov eax, [eax+8]
			mov [ebp-2Ch], eax
			push 10h
			push dword ptr [ebp+8]
			push dword ptr [ebp-2Ch]
			call dword ptr ds : [0x00BF064C]
			cmp eax, 0FFFFFFFFh
			jnz short label494EA5
			call dword ptr ds : [0x00BF0640]
			cmp eax, 2733h
			jz short label494EAF

		label494EA5:
			push 0
			mov ecx, [ebp-30h]
			call dwCClientSocketOnConnect

		label494EAF:
			jmp label494ECA

		label494ECA:
			pop edi
			pop esi
			pop ebx
			leave
			retn 4
	}
}

// executed after the client is unpacked
VOID MainFunc()
{
	Log(__FUNCTION__);

	// Noop Patcher
	MemEdit::PatchNop(dwWinMainShowStartUpWndModalCall, 5);

	// Window Mode Magic
	MemEdit::CodeCave(FixFullScreen, dwFixFullScreen, 5);

	// Noop Call to CSecurityClient::OnPacket
	MemEdit::PatchNop(dwCSecurityClientOnPacketCall, 12);

	// Nuke CWvsApp::Setup
	MemEdit::CodeCave(NukedCWvsAppSetup, dwCWvsAppSetUp, 5);
	MemEdit::CodeCave(NukedCWvsAppInitializeInput, dwCWvsAppInitializeInput, 5);
	MemEdit::CodeCave(NukedCWvsAppRun, dwCWvsAppRun, 5);
	MemEdit::CodeCave(NukedCWvsAppCallUpdate, dwCWvsAppCallUpdate, 5);
	MemEdit::CodeCave(NukedCClientSocketConnect, dwCClientSocketConnect, 5);
	MemEdit::CodeCave(NukedCLoginSendCheckPasswordPacket, dwCLoginSendCheckPasswordPacket, 5);
	MemEdit::CodeCave(Nuked494D2F, dw494D2F, 6);
	return;
}

// prolly don't edit this region if youre a noob
#pragma region EntryThread

// main thread
VOID MainProc()
{
	Log(__FUNCTION__);

	Common::CreateInstance
	(
		TRUE,			// true if you want to hook windows libraries (besides mutex) set this to false if you already edited your IP into the client (eg v83 localhosts)
		MainFunc,		// function to be executed after client is unpacked
		"127.0.0.1",	// IP to connect to (your server IP)
		"63.251.217.4"		// IP to redirect from (nexon IP)
	);
}

// dll entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		Log("DLL_PROCESS_ATTACH");

		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainProc, NULL, 0, 0);
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		Log("DLL_PROCESS_DETACH");
		Common::GetInstance()->~Common();
		break;
	}
	}
	return TRUE;
}

#pragma endregion