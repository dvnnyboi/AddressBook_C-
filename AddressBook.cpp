//AddressBook.cpp
/************************************************************************************************
���ϸ�Ī: AddressBook.cpp
��    ��: �ּҷ� Ŭ���� ���� �� �׽�Ʈ �ó�����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/05
*************************************************************************************************/
#include "AddressBook.h"


/************************************************************************************************
��    Ī: AddressBook (default)
��    ��: ����Ʈ ������
��    ��: �Ҵ緮
��    ��: ����
*************************************************************************************************/
AddressBook::AddressBook(Long capacity)
	:personals(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
��    Ī: AddressBook (copy)
��    ��: ���� ������
��    ��: �ּҷ�
��    ��: ����
*************************************************************************************************/
AddressBook::AddressBook(const AddressBook& source)
	:personals(source.personals) {
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
��    Ī: ~AddressBook 
��    ��: �Ҹ���
��    ��: ����
��    ��: ����
*************************************************************************************************/
AddressBook::~AddressBook() {}
/************************************************************************************************
��    Ī: Record
��    ��: �ּҷϿ��� �����Ѵ�
��    ��: ����, �ּ�, ��ȭ��ȣ, �̸����ּ�
��    ��: ��ġ
*************************************************************************************************/
Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress) {
	Personal personal(name, address, telephoneNumber, emailAddress);
	Long index;

	if (this->length < this->capacity) {
		index = this->personals.Store(this->length, personal);
	}
	else {
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: Find
��    ��: �ּҷϿ��� ã�´�.
��    ��: ����
��    ��: ��ġ��, ����
*************************************************************************************************/
void AddressBook::Find(string name, Long* (*indexes), Long* count) {
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareNames);
}
/************************************************************************************************
��    Ī: Correct
��    ��: �ּҷϿ��� ��ģ��.
��    ��: ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּ�
��    ��: ��ġ
*************************************************************************************************/
Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress) {
	Personal personal;

	personal = this->personals.GetAt(index);
	personal = Personal(personal.GetName(), address, telephoneNumber, emailAddress);
	index = this->personals.Modify(index, personal);

	return index;
}
/************************************************************************************************
��    Ī: Erase
��    ��: �ּҷϿ��� �����.
��    ��: ��ġ
��    ��: ��ġ
*************************************************************************************************/
Long AddressBook::Erase(Long index) {
	index = this->personals.Delete(index);
	this->length--;
	this->capacity--;

	return index;
}
/************************************************************************************************
��    Ī: Arrange
��    ��: �ּҷϿ��� �����Ѵ�.
��    ��: ����
��    ��: ����
*************************************************************************************************/
void AddressBook::Arrange() {
	this->personals.SelectionSort(ComparePersonals);
}
/************************************************************************************************
��    Ī: GetAt
��    ��: �ּҷϿ��� �����´�
��    ��: ��ġ
��    ��: ����
*************************************************************************************************/
Personal& AddressBook::GetAt(Long index) {
	return this->personals.GetAt(index);
}
/************************************************************************************************
��    Ī: operator = 
��    ��: ġȯ������
��    ��: �ּҷ�
��    ��: �ּҷ�
*************************************************************************************************/
AddressBook& AddressBook::operator=(const AddressBook& source) {
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

/************************************************************************************************
 �Լ��������� ������ ���� �Լ���
************************************************************************************************/
int CompareNames(void* one, void* other) {
	Personal* one_ = static_cast<Personal*>(one);
	string* other_ = static_cast<string*>(other);

	return one_->GetName().compare(*other_);
}
int ComparePersonals(void* one, void* other) {
	Personal* one_ = static_cast<Personal*>(one);
	Personal* other_ = static_cast<Personal*>(other);

	return one_->GetName().compare(other_->GetName());
}
#if 0
/************************************************************************************************
�׽�Ʈ �ó�����
************************************************************************************************/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	AddressBook addressBook(3);
	Personal personal;
	Long index;
	
	//�����Ѵ�.
	cout << "*******RECORD*******" << endl;
	index = addressBook.Record("Hong", "SeoCho-Dong, Seoul", "01012345678", "hong@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Kim", "SongPa-Gu, Seoul", "01087654321", "kim@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Go", "Nam-Gu, Pohang", "01056781234", "go@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Choi", "GwangJin-Gu, Seoul", "01043218765", "choi@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Hong", "SeongDong-Gu, Seoul", "01098765432", "hgd@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	//ã�´�.
	cout << "********FIND********" << endl;
	Long(*indexes);
	Long count;
	Long i;

	addressBook.Find("Hong", &indexes, &count);
	i = 0;
	while (i < count) {
		personal = addressBook.GetAt(indexes[i]);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}
	if (indexes != 0) {
		delete[]indexes;
		indexes = 0;
	}
	//��ģ��.
	cout << "*******CORRECT******" << endl;
	index = addressBook.Correct(1, "GangNam-Gu, Seoul", "01087654321", "gdkim@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	//�����.
	index = addressBook.Erase(1);
	if (index < 0) {
		cout << "DELETED!" << endl;
	}
	cout << "********************" << endl;
	//�����Ѵ�.
	cout << "******ARRANGE*******" << endl;
	addressBook.Arrange();
	i = 0;
	while (i < addressBook.GetLength()) {
		personal = addressBook.GetAt(i);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}
	//ġȯ������.
	cout << "*****operator =*****" << endl;
	AddressBook copy(3);

	copy = addressBook;
	i = 0;
	while (i < copy.GetLength()) {
		personal = copy.GetAt(i);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}

	return 0;
}
#endif