#pragma once
#include "pch.h"
#include "HttpUrls.h"

class HttpUrl
{
public:
	using Port = unsigned short;

	static const Port DEFAULT_HTTP_PORT = 80;
	static const Port DEFAULT_HTTPS_PORT = 443;
	static const Port DEFAULT_NO_PORT = 0;
	static const Port MIN_PORT = 1;
	static const Port MAX_PORT = 65535;

	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	HttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port);

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в эту строку
	// не должен включаться
	std::string GetURL() const;

	// возвращает доменное имя
	std::string GetDomain() const;

	/*
		Возвращает имя документа. Примеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	Port GetPort() const;

private:
	std::string m_domain;
	Protocol m_protocol;
	Port m_port;
	std::string m_document;
};

