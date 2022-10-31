#include "../../Header/Input/HidDevice.h"

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib")

GUID* GE::HID::GetHidGuid()
{
	// ����PC��GUID���擾
	static GUID guid;
	static bool isOnceTime = true;

	if (isOnceTime == true)
	{
		HidD_GetHidGuid(&guid);
	}
	return &guid;
}

GE::HID::HidDevice* GE::HID::GetNewHidDevice(DWORD vendorID, DWORD productID)
{
	// hid�f�o�C�X���̃n���h�����擾
	HDEVINFO devinfo;
	// DIGCF_PRESENT : �ڑ�����Ă���HID�f�o�C�X����
	// DIGCF_DEVICEINTERFACE : ?
	auto pHidGuid = GetHidGuid();
	devinfo = SetupDiGetClassDevs(pHidGuid, NULL, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	// �ڑ�����Ă���HID�f�o�C�X������擾
	SP_DEVICE_INTERFACE_DATA spid;
	spid.cbSize = sizeof(spid);

	HidDevice* hidDevice = new HidDevice();
	hidDevice->readOverlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	bool isFind = false;

	for (int index = 0; ; ++index)
	{
		// �擾�ł��Ȃ��Ȃ����烋�[�v���I���
		if (!SetupDiEnumDeviceInterfaces(devinfo, NULL, pHidGuid, index, &spid))
		{
			break;
		}

		// �ڑ�����Ă���HID�f�o�C�X�̏�񂪂���ł��낤�A�h���X���擾?
		unsigned long size;
		SetupDiGetDeviceInterfaceDetail(devinfo, &spid, NULL, 0, &size, 0);
		PSP_INTERFACE_DEVICE_DETAIL_DATA deviceDetailData = new SP_INTERFACE_DEVICE_DETAIL_DATA[size];
		deviceDetailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		SetupDiGetDeviceInterfaceDetail(devinfo, &spid, deviceDetailData, size, &size, 0);

		// HID�f�o�C�X�ɃA�N�Z�X���邽�߂ɕK�v�ȃn���h���̍쐬
		hidDevice->handle = CreateFile(deviceDetailData->DevicePath
			, GENERIC_READ | GENERIC_WRITE
			, FILE_SHARE_READ | FILE_SHARE_WRITE
			, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

		// �m�ۂ������������J��
		delete[] deviceDetailData;

		// HID�ɑ΂��ē��o�͂��ł��Ȃ��f�o�C�X�̓n���h�������Ȃ�?
		if (hidDevice->handle == INVALID_HANDLE_VALUE)continue;

		// �x���ז�������if���Ŗ߂�l���g�p
		if (!HidD_GetAttributes(hidDevice->handle, &hidDevice->hiddAttribute))continue;

		if (hidDevice->hiddAttribute.VendorID == vendorID && hidDevice->hiddAttribute.ProductID == productID)
		{
			isFind = true;
			break;
		}
		else
		{
			CloseHandle(hidDevice->handle);
			hidDevice->handle = nullptr;
			continue;
		}
	}

	// �ړI��HID�f�o�C�X��������Ȃ�������m�ۂ����������͂��ׂč폜
	if (isFind == false)
	{
		DeleteHidDevice(hidDevice);
		return nullptr;
	}

	PHIDP_PREPARSED_DATA pp_data = NULL;

	// HID�f�o�C�X�̎g�p�o�C�g���Ȃǂ��擾
	bool isPreparsed = HidD_GetPreparsedData(hidDevice->handle, &pp_data);
	bool isGetCaps = HidP_GetCaps(pp_data, &hidDevice->hidpCaps);

	// �C���v�b�g�o�b�t�@�[���ǂꂾ�����邩���擾���čő�l��ݒ�
	ULONG numReport = 0;
	bool isGetNumInputBuffer = HidD_GetNumInputBuffers(hidDevice->handle, &numReport);
	bool isSetNumInputBuffer = HidD_SetNumInputBuffers(hidDevice->handle, numReport);

	hidDevice->readBufferSize = hidDevice->hidpCaps.InputReportByteLength;
	hidDevice->writeBufferSize = hidDevice->hidpCaps.OutputReportByteLength;

	hidDevice->readBuffer = new BYTE[hidDevice->readBufferSize];
	hidDevice->writeBuffer = new BYTE[hidDevice->writeBufferSize];

	return hidDevice;
}

void GE::HID::GetInputReport(HidDevice* pHidDevice)
{
	if (pHidDevice == nullptr)return;

	int milisec = pHidDevice->isBlocking ? -1 : 0;
	bool result = false;
	bool isOverlapped = false;

	// �ǂݍ��ݒ����ǂ���
	// �ǂݍ��ݏI����Ă�Ȃ�f�o�C�X����f�[�^���擾
	if (pHidDevice->isReadPending == false)
	{
		pHidDevice->isReadPending = true;
		ResetEvent(pHidDevice->readOverlapped.hEvent);
		DWORD resultReadBufferSize = 0;
		result = ReadFile(pHidDevice->handle, pHidDevice->readBuffer, pHidDevice->readBufferSize, &resultReadBufferSize, &pHidDevice->readOverlapped);
		if (result == false)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				isOverlapped = true;
			}
		}
	}

	if (isOverlapped)
	{
		if (milisec >= 0)
		{
			result = WaitForSingleObject(pHidDevice->readOverlapped.hEvent,0);
			if (result != WAIT_OBJECT_0)
			{
				return;
			}
		}
		DWORD resultOverlappedSize = 0;
		result = GetOverlappedResult(pHidDevice->handle, &pHidDevice->readOverlapped, &resultOverlappedSize, TRUE);
	}

	pHidDevice->isReadPending = false;
}

void GE::HID::SetOutputReport(HidDevice* pHidDevice, void* data, int dataSize)
{
	if (pHidDevice == nullptr)return;

	unsigned char* buffer;
	int bufferSize = 0;

	// �x��Ă����f�[�^�T�C�Y��HidDevice�Ŋm�ۂ���Ă���f�[�^�T�C�Y�ƕs��v���̑Ή�
	if ((unsigned)dataSize >= pHidDevice->writeBufferSize)
	{
		buffer = (unsigned char*)data;
		bufferSize = dataSize;
	}
	else
	{
		buffer = pHidDevice->writeBuffer;
		bufferSize = pHidDevice->writeBufferSize;

		// �f�[�^���R�s�[
		memcpy_s(buffer, bufferSize, data, dataSize);
		// �]��f�[�^��������Ȃ炻����0�Ŗ��߂�
		memset(buffer + dataSize, 0, (INT64)pHidDevice->writeBufferSize - dataSize);
		bufferSize = pHidDevice->writeBufferSize;
	}

	DWORD resultDataSize = 0;
	bool result = WriteFile(pHidDevice->handle, buffer, bufferSize, &resultDataSize, &pHidDevice->writeOverlapped);

	// �������ݏI���҂�
	if (result == false)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			result = WaitForSingleObject(pHidDevice->writeOverlapped.hEvent, 1000);
			if (result == false)return;

			DWORD overlappedSize = 0;
			result = GetOverlappedResult(pHidDevice->handle, &pHidDevice->writeOverlapped, &overlappedSize, FALSE);
		}
	}
}

void GE::HID::DeleteHidDevice(HidDevice* hidDevice)
{
	if (hidDevice == nullptr)return;

	delete hidDevice;
	hidDevice = nullptr;
}

void GE::HID::SetBlocking(HidDevice* pHidDevice, bool isBlocking)
{
	if (pHidDevice == nullptr)return;

	pHidDevice->isBlocking = isBlocking;
}
