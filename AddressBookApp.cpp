//AddressBookApp.cpp
/************************************************************************************************
���ϸ�Ī: AddressBookApp.cpp
��    ��:
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/11
*************************************************************************************************/
#include "AddressBookApp.h"
#include "AddressBookForm.h"

BOOL AddressBookApp::InitInstance() {
	AddressBookForm addressBookForm;

	this->m_pMainWnd = &addressBookForm;
	addressBookForm.DoModal();

	return TRUE;
}
AddressBookApp addressBookApp;