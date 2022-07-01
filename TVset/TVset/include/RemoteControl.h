#pragma once

#include "Include.h"

#include "TVSet.h"

class TVRemoteControl
{
public:
	TVRemoteControl(TVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

	bool WorkflowGoesOn();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// RemoteControl& operator=(const RemoteControl &) = delete;
private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool StopWorkflow(std::istream& args);

	// �������-���������� ������� ������������.
	// ���������� true, ���� ������� ���������� � false, ���� ���� ������
	using Handler = std::function<bool(std::istream& args)>;

	// ���������� �������� ������� �� � ����������
	using ActionMap = std::map<std::string, Handler>;

	TVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;
	
	bool m_workFlowGoesOn;

	const ActionMap m_actionMap;
};