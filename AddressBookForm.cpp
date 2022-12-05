//AddressBookForm.cpp
/************************************************************************************************
���ϸ�Ī: AddressBookForm.cpp
��    ��: �ּҷ� ������������ Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/11
*************************************************************************************************/
#include "AddressBookForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include "Personal.h"
#include <afxcmn.h>
#include <afxdb.h>

/************************************************************************************************
��    ��: Message-Mapping
*************************************************************************************************/
BEGIN_MESSAGE_MAP(AddressBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
��    Ī: AddressBookForm
��    ��: ����Ʈ ������
*************************************************************************************************/
AddressBookForm::AddressBookForm(CWnd* parent)
	:CDialog(AddressBookForm::IDD, parent) {
	this->addressBook = NULL;
}
/************************************************************************************************
��    Ī: Load
��    ��: �ּҷ��� �����ͺ��̽����� �����Ѵ�.
*************************************************************************************************/
void AddressBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name, Personal.address, Personal.telephoneNumber, Personal.emailAddress FROM Personal;";
	
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
��    Ī: Save
��    ��: �ּҷ��� �����ͺ��̽����� �����Ѵ�.
*************************************************************************************************/
void AddressBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString sql = "SELECT Personal.code FROM Personal;";
	Personal personal;
	Long i;
	
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql);
	i = 0;
	while (!rs.IsEOF() && i < this->addressBook->GetLength()) {
		rs.GetFieldValue((short)0, code);
		personal = this->addressBook->GetAt(i);
		sql.Format("INSERT INTO Personal(name, address, telephoneNumber, emailAddress, code) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", personal.GetName().c_str(), personal.GetAddress().c_str(),
			personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)code);
		db.ExecuteSQL(sql);
		i++;
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
��    Ī: Insert
��    ��: �����ͺ��̽����� �����Ѵ�.
*************************************************************************************************/
void AddressBookForm::Insert(Long index) {
	CDatabase db;
	CString sql;
	Personal personal = this->addressBook->GetAt(index);

	sql.Format("INSERT INTO Personal(name, address, telephoneNumber, emailAddress, code) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", personal.GetName().c_str(), personal.GetAddress().c_str(),
		personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)(this->GetCode()));
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	db.ExecuteSQL(sql);
	db.Close();
}
/************************************************************************************************
��    Ī: GetCode
��    ��: �ڵ�(Primary Key)�� �����´�.
*************************************************************************************************/
CString AddressBookForm::GetCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	Long i = 0;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	CString number;
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		number = code.Right(4);
		i = _ttoi(number);
	}
	code.Format("P%04d", i + 1);
	rs.Close();
	db.Close();

	return code;
}
/************************************************************************************************
��    Ī: Modify
��    ��: �����ͺ��̽����� �����Ѵ�.
*************************************************************************************************/
void AddressBookForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	Personal personal = this->addressBook->GetAt(index);
	CString sql = "SELECT Personal.code FROM Personal;";
	CString code;
	Long i;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	i = 0;
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Personal SET address = '%s', telephoneNumber = '%s', emailAddress = '%s' "
		"WHERE Personal.code = '%s';", personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(),
		personal.GetEmailAddress().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}
/************************************************************************************************
��    Ī: Delete
��    ��: �����ͺ��̽����� �����Ѵ�.
*************************************************************************************************/
void AddressBookForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	CString code;
	Long i;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	i = 0;
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM Personal WHERE Personal.code = '%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}
/************************************************************************************************
��    Ī: OnInitDialog
��    ��: �����찡 ������ �� �ó�����.
*************************************************************************************************/
BOOL AddressBookForm::OnInitDialog() {
	CDialog::OnInitDialog();

	//1.1. �ּҷ��� �����.
	this->addressBook = new AddressBook;
	//1.2. �ּҷϿ��� �����Ѵ�.
	this->Load();
	//1.3. ����Ʈ �� ��Ʈ���� ����� �����.
	((CListCtrl *)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_LEFT, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_LEFT, 150);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_LEFT, 90);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_LEFT, 120);
	//1.4. ����Ʈ �� ��Ʈ�ѿ� ��ü���� ����� �����Ѵ�.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//1.5. ������ ������ŭ ����Ʈ �� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	CString number;
	Personal personal;
	Long i = 0;
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
	return FALSE;
}
/************************************************************************************************
��    Ī: OnRecordButtonClicked
��    ��: �����ϱ� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnRecordButtonClicked() {
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Personal personal;

	//2.1. ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//2.2. �ּҷϿ��� �����Ѵ�.
	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	this->Insert(index);
	//2.3. ����Ʈ �� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	personal = this->addressBook->GetAt(index);
	number.Format("%d", index + 1);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, (LPCTSTR)number);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}
/************************************************************************************************
��    Ī: OnFindButtonClicked
��    ��: ã�� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnFindButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}
/************************************************************************************************
��    Ī: OnCorrectButtonClicked
��    ��: ��ġ�� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnCorrectButtonClicked() {
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Personal personal;

	//4.1. ����Ʈ ��  ��Ʈ�ѿ��� ��ġ�� �д´�.
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//4.2. �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//4.3. �ּҷϿ��� ��ģ��.
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	this->Modify(index);
	//4.4. ����Ʈ �� ��Ʈ�ѿ��� �׸��� ��ģ��.
	personal = this->addressBook->GetAt(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}
/************************************************************************************************
��    Ī: OnEraseButtonClicked
��    ��: ����� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnEraseButtonClicked() {
	CString number;
	Long index;
	Long i;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	this->Delete(index);
	this->addressBook->Erase(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);
	i = index;
	while (i < this->addressBook->GetLength()) {
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 0, (LPCTSTR)number);
		i++;
	}
}
/************************************************************************************************
��    Ī: OnArrangeButtonClicked
��    ��: �����ϱ� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnArrangeButtonClicked() {
	CString number;
	Personal personal;
	Long i;

	this->addressBook->Arrange();
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	i = 0;
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
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
void AddressBookForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	name = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	this->GetDlgItem(IDC_EDIT_NAME)->SetWindowText((LPCTSTR)name);
	this->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText((LPCTSTR)address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText((LPCTSTR)telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText((LPCTSTR)emailAddress);
}
/************************************************************************************************
��    Ī: OnClose
��    ��: �ݱ� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void AddressBookForm::OnClose() {
	this->Save();
	if (this->addressBook != NULL) {
		delete this->addressBook;
	}
	this->EndDialog(0);
}