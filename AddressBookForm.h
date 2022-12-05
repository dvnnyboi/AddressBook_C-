//AddressBookForm.h
/************************************************************************************************
���ϸ�Ī: AddressBookForm.h
��    ��: �ּҷ� ������������ Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/11
*************************************************************************************************/
#ifndef _ADDRESSBOOKFORM_H
#define _ADDRESSBOOKFORM_H
#include <afxwin.h>
#include "resource.h"
#include <string>
using namespace std;

typedef signed long int Long;
class AddressBook;
class AddressBookForm : public CDialog {		//Inherit
public:
	enum { IDD = IDD_ADDRESSBOOKFORM };
public:
	AddressBookForm(CWnd* parent = NULL);
	void Load();
	void Save();
	void Insert(Long index);
	void Modify(Long index);
	void Delete(Long index);
	CString GetCode();
	virtual BOOL OnInitDialog();				//Overide CDialog Class
public:
	AddressBook* addressBook;
protected:										//Base Class(CDialog)�����  ���� ����
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif //_ADDRESSBOOKFORM_H