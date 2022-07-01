#include "../Include.h"

#include "../../TVset/include/TVSet.h"

TEST_CASE("TVSet. IsOn() tests.")
{
	TVSet tv;
	
	REQUIRE_FALSE(tv.IsOn()); //���������� ��������
	REQUIRE_FALSE(tv.SelectChannel(2)); //������ �������� �����, ���� �� ��������
	REQUIRE(tv.GetChannel() == 0); // ����� ��������, ����� = 0
}

TEST_CASE("TVSet. SelectChannel() test.")
{
	TVSet tv;
	tv.TurnOn();
	REQUIRE(tv.IsOn()); // ����� ��������
	REQUIRE(tv.GetChannel() == TVSet::s_startChannel); // ����� ��������� ����� = 1

	REQUIRE(tv.SelectChannel(1));			//
	REQUIRE(tv.SelectChannel(10));			// ����� �������  
	REQUIRE(tv.SelectChannel(99));			// �� 1 �� 99 �������
	REQUIRE_FALSE(tv.SelectChannel(6000));  //
	REQUIRE_FALSE(tv.SelectChannel('d'));
}

TEST_CASE("TVset. TurnOff test. ")
{
	TVSet tv;
	tv.TurnOn();
	tv.TurnOff();
	REQUIRE_FALSE(tv.IsOn()); // ����� ���������
}

TEST_CASE("TVSet. SelectChannel() after relaunching TV.")
{
	TVSet tv;
	tv.TurnOn();

	const auto expectedChannelBeforeTurningOff = 99;
	tv.SelectChannel(expectedChannelBeforeTurningOff);

	tv.TurnOff();
	tv.TurnOn();

	REQUIRE(tv.GetChannel() == expectedChannelBeforeTurningOff); // ����� ����������� ����������� �����
}																 // �� ������� �� ��� ��������	
