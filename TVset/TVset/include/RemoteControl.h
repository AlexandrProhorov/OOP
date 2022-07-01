#pragma once

#include "Include.h"

#include "TVSet.h"

class TVRemoteControl
{
public:
	TVRemoteControl(TVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

	bool WorkflowGoesOn();

	// Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
	// RemoteControl& operator=(const RemoteControl &) = delete;
private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool StopWorkflow(std::istream& args);

	// функция-обработчик команды пользователя.
	// Возвращает true, если команда распознана и false, если были ошибки
	using Handler = std::function<bool(std::istream& args)>;

	// Отображает название команды на её обработчик
	using ActionMap = std::map<std::string, Handler>;

	TVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;
	
	bool m_workFlowGoesOn;

	const ActionMap m_actionMap;
};