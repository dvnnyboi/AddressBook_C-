//FindingForm.cpp
/************************************************************************************************
���ϸ�Ī: FindingForm.cpp
��    ��: �ּҷ� - ã�� ������ Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/11
*************************************************************************************************/
#include "FindingForm.h"
#include "AddressBookForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

/************************************************************************************************
��    ��: Message-Mapping
*************************************************************************************************/
BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
��    Ī: FindingForm
��    ��: ����Ʈ ������
*************************************************************************************************/
FindingForm::FindingForm(CWnd* parent)
	:CDialog(IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}
/************************************************************************************************
��    Ī: OnInitDialog
��    ��: �����찡 ������ �� �ó�����.
*************************************************************************************************/
BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();

	//1.1. ����Ʈ �� ��Ʈ���� ����� �����.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_LEFT, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_LEFT, 150);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_LEFT, 90);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_LEFT, 120);
	//1.2. ����Ʈ �� ��Ʈ�ѿ� ��ü���� ����� �߰��Ѵ�.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return FALSE;
}
/************************************************************************************************
��    Ī: OnFindButtonClicked
��    ��: ã�� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void FindingForm::OnFindButtonClicked() {
	CString name;
	CString number;
	Long index;
	Long i;
	AddressBookForm* addressBookForm;
	Personal personal;

	//2.1. ������ �д´�.
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2. �ּҷ� �����츦 ã�´�.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "�ּҷ�");
	//2.3. �ּҷ� �������� �ּҷϿ��� ã�´�.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	addressBookForm->addressBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));
	//2.4. ����Ʈ �� ��Ʈ���� ��� �׸��� �����.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//2.5. ����Ʈ �� ��Ʈ�ѿ� ã�� ������ŭ �׸���� �߰��Ѵ�.
	i = 0;
	while (i < this->count) {
		personal = addressBookForm->addressBook->GetAt(this->indexes[i]);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
}
/************************************************************************************************
��    Ī: OnListViewItemDoubleClicked
��    ��: ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ �� �ó�����.
*************************************************************************************************/
void FindingForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Long previous;
	AddressBookForm* addressBookForm;
	
	//3.1. ����Ʈ �� ��Ʈ�ѿ��� ��ġ�� �д´�.
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//3.2. ����Ʈ �� ��Ʈ�ѿ��� �׸��� �д´�.
	name = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//3.3. �ּҷ� �����츦 ã�´�.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "�ּҷ�");
	//3.4. �ּҷ� �������� ����Ʈ �� ��Ʈ�ѿ��� �׸��� �����Ѵ�.
	previous = ((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetSelectionMark(this->indexes[index]);
	
	//3.5. �ּҷ� �����쿡 ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� ����.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText((LPCTSTR)name);
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText((LPCTSTR)address);
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText((LPCTSTR)telephoneNumber);
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText((LPCTSTR)emailAddress);

	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetItemState(previous, 0, LVIS_SELECTED);
	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetItemState(this->indexes[index], LVIS_SELECTED, LVIS_SELECTED);
	
	//3.6. ã�� �����츦 �ݴ´�.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);

	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetFocus();
}
/************************************************************************************************
��    Ī: OnClose
��    ��: �ݱ� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void FindingForm::OnClose() {
	//4.1. ã�� �����츦 �ݴ´�.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);
}