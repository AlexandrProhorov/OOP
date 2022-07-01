#pragma once

class TVSet
{
public:
	using ChannelType = unsigned short;

	static const ChannelType s_startChannel = 1;
	static const ChannelType s_maxChannel = 99;

	TVSet();

	bool IsOn() const;
	void TurnOn();
	void TurnOff();
	ChannelType GetChannel() const;
	bool SelectChannel(ChannelType channel);

private:
	bool m_isOn;
	ChannelType m_channel;
};
