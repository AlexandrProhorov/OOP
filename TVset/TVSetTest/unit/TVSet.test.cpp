#include "../Include.h"

#include "../../TVset/include/TVSet.h"

TEST_CASE("TVSet. IsOn() tests.")
{
	TVSet tv;
	
	REQUIRE_FALSE(tv.IsOn()); //изначально выключен
	REQUIRE_FALSE(tv.SelectChannel(2)); //Нельзя выбирать канал, пока ТВ выключен
	REQUIRE(tv.GetChannel() == 0); // Когда выключен, канал = 0
}

TEST_CASE("TVSet. SelectChannel() test.")
{
	TVSet tv;
	tv.TurnOn();
	REQUIRE(tv.IsOn()); // Можно включить
	REQUIRE(tv.GetChannel() == TVSet::s_startChannel); // После включения канал = 1

	REQUIRE(tv.SelectChannel(1));			//
	REQUIRE(tv.SelectChannel(10));			// Можно выбрать  
	REQUIRE(tv.SelectChannel(99));			// От 1 до 99 каналов
	REQUIRE_FALSE(tv.SelectChannel(6000));  //
	REQUIRE_FALSE(tv.SelectChannel('d'));
}

TEST_CASE("TVset. TurnOff test. ")
{
	TVSet tv;
	tv.TurnOn();
	tv.TurnOff();
	REQUIRE_FALSE(tv.IsOn()); // Можно выключить
}

TEST_CASE("TVSet. SelectChannel() after relaunching TV.")
{
	TVSet tv;
	tv.TurnOn();

	const auto expectedChannelBeforeTurningOff = 99;
	tv.SelectChannel(expectedChannelBeforeTurningOff);

	tv.TurnOff();
	tv.TurnOn();

	REQUIRE(tv.GetChannel() == expectedChannelBeforeTurningOff); // После перезапуска сохраняется канал
}																 // На котором ТВ был выключен	
