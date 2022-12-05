//FindingForm.h
/************************************************************************************************
���ϸ�Ī: FindingForm.h
��    ��: �ּҷ� - ã�� ������ Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/11
*************************************************************************************************/
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include "resource.h"
#include <afxwin.h>

typedef signed long int Long;
class FindingForm : public CDialog {
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
public:
	Long(*indexes);
	Long count;
protected:
	void OnFindButtonClicked();
	void OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result);
	void OnClose();
	DECLARE_MESSAGE_MAP()
};


#endif //_FINDINGFORM_H