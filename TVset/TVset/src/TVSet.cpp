#include "../include/TVSet.h"

TVSet::TVSet()
	: m_isOn(false)
	, m_channel(s_startChannel)
{
}

bool TVSet::IsOn() const
{
	return m_isOn;
}

void TVSet::TurnOn()
{
	m_isOn = true;
}

void TVSet::TurnOff()
{
	m_isOn = false;
}

using ChannelType = TVSet::ChannelType;

ChannelType TVSet::GetChannel() const
{
	return m_isOn ? m_channel : 0;
}

bool TVSet::SelectChannel(ChannelType channel)
{
	if (channel == 0 || channel > s_maxChannel || m_isOn == false)
	{
		return false;
	}

	m_channel = channel;

	return true;
}








