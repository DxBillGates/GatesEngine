#pragma once
#include <Windows.h>
#include <SetupAPI.h>
#include <hidsdi.h>

namespace GE
{
	namespace HID
	{
		struct HidDevice
		{
			HANDLE handle;
			HIDD_ATTRIBUTES hiddAttribute;
			HIDP_CAPS hidpCaps;

			BYTE* readBuffer;
			DWORD readBufferSize;

			BYTE* writeBuffer;
			DWORD writeBufferSize;

			OVERLAPPED readOverlapped;
			OVERLAPPED writeOverlapped;

			bool isBlocking;
			bool isReadPending;

			HidDevice()
				: handle(nullptr)
				, hiddAttribute()
				, hidpCaps()
				, readBuffer(nullptr)
				, readBufferSize(0)
				, writeBuffer(nullptr)
				, writeBufferSize(0)
				, readOverlapped()
				, writeOverlapped()
				, isBlocking(false)
				, isReadPending(false)
			{
			}

			~HidDevice()
			{
				if (handle)
				{
					CloseHandle(handle);
					handle = nullptr;
				}

				if (readBuffer)delete[] readBuffer;

				if (writeBuffer)delete[] writeBuffer;

				if (readOverlapped.hEvent)
				{
					CloseHandle(readOverlapped.hEvent);
					readOverlapped = {};
				}

				if (writeOverlapped.hEvent)
				{
					CloseHandle(writeOverlapped.hEvent);
					writeOverlapped = {};
				}
			}
		};

		/// <summary>
		/// PC��GUID���擾
		/// </summary>
		/// <returns>PC��GUID</returns>
		GUID* GetHidGuid();

		/// <summary>
		/// HID�̃x���_�[ID�ƃv���_�N�gID���w�肵�A�ڑ�����Ă���Ύ擾
		/// </summary>
		/// <param name="vendorID">�擾�������f�o�C�X�̃x���_�[ID</param>
		/// <param name="productID">�擾�������f�o�C�X�̃v���_�N�gID</param>
		/// <returns>�ڑ�����Ă��ăx���_�[ID�ƃv���_�N�gID����v���Ă����HID�f�o�C�X�̏����|�C���^�ŕԂ�</returns>
		HidDevice* GetNewHidDevice(DWORD vendorID, DWORD productID);

		/// <summary>
		/// ���̓��|�[�g���擾����
		/// </summary>
		/// <param name="pHidDevice">�擾�������|�[�g�����f�o�C�X</param>
		void GetInputReport(HidDevice* pHidDevice);

		/// <summary>
		/// HID�f�o�C�X�Ƀf�[�^�𑗂�
		/// </summary>
		/// <param name="pHidDevice">�f�[�^�𑗐M������HID</param>
		/// <param name="data">���肽���f�[�^</param>
		/// <param name="dataSize">���肽���f�[�^�T�C�Y</param>
		void SetOutputReport(HidDevice* pHidDevice, void* data, int dataSize);

		/// <summary>
		/// HidDevice���������
		/// </summary>
		/// <param name="hidDevice">�������������������HidDevice</param>
		void DeleteHidDevice(HidDevice* hidDevice);

		/// <summary>
		/// �w���HIDDevice�̓��̓��|�[�g���擾����ۂ�HID���̉�����҂�
		/// </summary>
		/// <param name="pHidDevice">�w���HIDDevice</param>
		/// <param name="isBlocking">�҂�</param>
		void SetBlocking(HidDevice* pHidDevice, bool isBlocking);
	}
}
