//Personal.cpp
/************************************************************************************************
���ϸ�Ī: Personal.cpp
��    ��: ���� Ŭ���� ���� �� �׽�Ʈ �ó�����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/05
*************************************************************************************************/
#include "Personal.h"

/************************************************************************************************
��    Ī: Personal (default)
��    ��: ����Ʈ ������
��    ��: ����
��    ��: ����
*************************************************************************************************/
Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("") {
}
/************************************************************************************************
��    Ī: Personal (parameter)
��    ��: �Ű������� ���� ������
��    ��: ����, �ּ�, ��ȭ��ȣ, �̸����ּ�
��    ��: ����
*************************************************************************************************/
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	:name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress) {
}
/************************************************************************************************
��    Ī: Personal (copy)
��    ��: ���� ������
��    ��: ����
��    ��: ����
*************************************************************************************************/
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address),
		telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress) {
}
/************************************************************************************************
��    Ī: ~Personal
��    ��: �Ҹ���
��    ��: ����
��    ��: ����
*************************************************************************************************/
Personal::~Personal() {}
/************************************************************************************************
��    Ī: IsEqual
��    ��: ������ Ȯ���Ѵ�.
��    ��: ����
��    ��: Ȯ�ΰ��
*************************************************************************************************/
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0
		&& this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}/************************************************************************************************
��    Ī: IsNotEqual
��    ��: �ٸ��� Ȯ���Ѵ�.
��    ��: ����
��    ��: Ȯ�ΰ��
*************************************************************************************************/
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
��    Ī: opertor ==
��    ��: ������ Ȯ���Ѵ�.
��    ��: ����
��    ��: Ȯ�ΰ��
*************************************************************************************************/
bool Personal::operator==(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0
		&& this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
��    Ī: opertor !=
��    ��: �ٸ��� Ȯ���Ѵ�.
��    ��: ����
��    ��: Ȯ�ΰ��
*************************************************************************************************/
bool Personal::operator!=(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
��    Ī: opertor =
��    ��: ġȯ ������ �Լ�
��    ��: ����
��    ��: ����
*************************************************************************************************/
Personal& Personal::operator=(const Personal& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}
#if 0
/************************************************************************************************/
//�׽�Ʈ�ó�����
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	//����Ʈ ������
	Personal one;
	//�Ű������� ���� ������.
	cout << "***PARAMETER***" << endl;
	Personal two("Hong", "Seoul", "01012345678", "hong@naver.com");
	cout << two.GetName() << endl
		<< two.GetAddress() << endl
		<< two.GetTelephoneNumber() << endl
		<< two.GetEmailAddress() << endl;
	cout << "***************" << endl;
	//���������
	cout << "*****COPY******" << endl;
	Personal three(two);
	cout << three.GetName() << endl
		<< three.GetAddress() << endl
		<< three.GetTelephoneNumber() << endl
		<< three.GetEmailAddress() << endl;
	cout << "***************" << endl;
	//IsNotEqual
	cout << "****IsEqual****" << endl;
	bool boolean;
	boolean = two.IsEqual(three);
	if (boolean == true) {
		cout << "EQUAL" << endl;
	}
	//operator ==
	if (two == three) {
		cout << "EQUAL" << endl;
	}
	cout << "***************" << endl;
	//IsNotEqual
	cout << "**IsNotEqual***" << endl;
	Personal four("Kim", "Busan", three.GetTelephoneNumber(), three.GetEmailAddress());
	boolean = three.IsNotEqual(four);
	if (boolean == true) {
		cout << "NOT EQUAL" << endl;
	}
	//operator !=
	if (three != four) {
		cout << "NOT EQUAL" << endl;
	}
	cout << "***************" << endl;
	//operator =
	one = four;
	cout << one.GetName() << endl
		<< one.GetAddress() << endl
		<< one.GetTelephoneNumber() << endl
		<< one.GetEmailAddress() << endl;
	cout << "***************" << endl;

	return 0;
}
#endif