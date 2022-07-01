#include <sstream>

#include "../include/RemoteControl.h"

#include "../include/TVSet.h"

#include "../TVSetConst.h"

const std::string QUIT_COMMAND = "Exit";

TVRemoteControl::TVRemoteControl(TVSet& tv, std::istream& input, std::ostream& output)
	: m_workFlowGoesOn(true)
	, m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](std::istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", std::bind(&TVRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "Info", std::bind(&TVRemoteControl::Info, this, std::placeholders::_1) },
		  { "SelectChannel", std::bind(&TVRemoteControl::SelectChannel, this, std::placeholders::_1)},
		  { "Exit", std::bind(&TVRemoteControl::StopWorkflow, this, std::placeholders::_1) },
		})
{
}

bool TVRemoteControl::HandleCommand()
{
	m_output << "> ";

	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);
	std::string action;

	strm >> action;
	if (const auto it = m_actionMap.find(action);
		it != m_actionMap.end())
	{
		return it->second(strm);
	}

	m_output << UnknownCommand << std::endl;
	return false;
}

bool TVRemoteControl::WorkflowGoesOn()
{
	return m_workFlowGoesOn;
}

bool TVRemoteControl::TurnOn(std::istream&)
{
	 m_tv.TurnOn();
	 m_output << TVon << std::endl;
	 return true;
}

bool TVRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << TVoff << std::endl;
	return true;
}

bool TVRemoteControl::Info(std::istream&)
{
	std::string info = (m_tv.IsOn())
		? ("TV is turned on\nChannel is: " + std::to_string(m_tv.GetChannel()) + '\n')
		: "TV is turned off\n";

	m_output << info;

	return true;
}

bool TVRemoteControl::SelectChannel(std::istream& args)
{
	if (!m_tv.IsOn())
	{
		m_output << TVmustBeTurnedOn << std::endl;
		return false;
	}

	TVSet::ChannelType channel;
	if (!(args >> channel))
	{
		m_output << IntChann << std::endl;
		return false;
	}

	if (!m_tv.SelectChannel(channel))
	{
		m_output << Fail << std::endl;
		return false;
	}

	return true;
}

bool TVRemoteControl::StopWorkflow(std::istream& args)
{
	if (m_workFlowGoesOn)
	{
		m_workFlowGoesOn = false;
		return true;
	}
	return false;
}
