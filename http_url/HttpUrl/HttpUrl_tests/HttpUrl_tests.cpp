#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../HttpUrl.h"
#include <sstream>

SCENARIO("Constructing a correct URL")
{
	std::string url;

	WHEN("Different register with http protocol")
	{
		url = "http://www.somesite.com/pages/sayhello.html?page=30&lang=en#title";

		THEN("With no throw")
		{
			REQUIRE_NOTHROW(HttpUrl(url));
		}
	}

	WHEN("Different register with https protocol")
	{
		url = "htTpS://www.sOmesite.com/pages/sayhello.html?page=30&lang=en#title";
		HttpUrl httpUrl = HttpUrl(url);

		THEN("Will be default https protocol port")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
		THEN("Protocol will be https")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTPS);
		}
		THEN("Domain will be mysite.com")
		{
			REQUIRE(httpUrl.GetDomain() == "www.somesite.com");
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.somesite.com:442";
		HttpUrl httpUrl = HttpUrl(url);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 442);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/");
		}
	}

	WHEN("Given URL without domain, localhost has port value")
	{
		url = "http://localhost:42";
		HttpUrl httpUrl = HttpUrl(url);

		THEN("ParseURL will work correctly")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
			REQUIRE(httpUrl.GetPort() == 42);
			REQUIRE(httpUrl.GetDomain() == "localhost");
		}
	}

	WHEN("Given URL without domain")
	{
		url = "http://localhost";
		HttpUrl httpUrl = HttpUrl(url);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTP_PORT);
		REQUIRE(httpUrl.GetDomain() == "localhost");
	}
}

SCENARIO("Construct url using constructor with separate params")
{
	std::string url;
	std::string domain;
	std::string document;
	HttpUrl::Protocol protocol;

	WHEN("Given http URL contains document section without port")
	{
		url = "http://www.somesite.com/pages/sayhello.html?page=30&lang=en#title";
		domain = "www.somesite.com";
		document = "pages/sayhello.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Evaluated protocol will be equal to http")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/pages/sayhello.html?page=30&lang=en#title");
		}
		THEN("Domain will be www.somesite.com")
		{
			REQUIRE(httpUrl.GetDomain() == "www.somesite.com");
		}
	}

	WHEN("Given https URL contains document section without port")
	{
		url = "https:/www.somesite.com/pages/sayhello.html?page=30&lang=en#title";
		domain = "www.somesite.com";
		document = "pages/sayhello.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTPS;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.somesite.com:442";
		domain = "www.somesite.com:442";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/");
		}
	}

	WHEN("Given http URL contains port and document")
	{
		url = "http://www.somesite.com:442/pages/sayhello.html?page=30&lang=en#title";
		domain = "www.somesite.com:442";
		document = "pages/sayhello.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/pages/sayhello.html?page=30&lang=en#title");
		}
	}

	WHEN("Given URL without domain, i.e. localhost that also has proper port value")
	{
		url = "http://localhost:42";
		domain = "localhost:42";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);

		THEN("ParseURL will work correctly")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
			REQUIRE(httpUrl.GetPort() == 80);
			REQUIRE(httpUrl.GetDomain() == "localhost:42");
		}
	}

	WHEN("Given URL without domain, localhost")
	{
		url = "http://localhost";
		domain = "localhost";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTP_PORT);
		REQUIRE(httpUrl.GetDomain() == "localhost");
	}
}

SCENARIO("Reading incorrect input data")
{
	std::string url;

	WHEN("Given a valid URL with invalid port")
	{
		std::domain_error InvalidPortValue("Invalid port value");
		url = "https://www.somesite.com:0/pages/sayhello.html?page=30&lang=en#title";
		REQUIRE_THROWS(HttpUrl(url), InvalidPortValue);
	}

	WHEN("Url port is bigger than port max value")
	{
		std::domain_error PortOutOfRange("Invalid port is out of range");
		url = "http://localhost:65555";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS(HttpUrl(url), PortOutOfRange);
		}
	}
	WHEN("Url also contain invalid document")
	{
		std::domain_error InvalidUrlValue("Invalid url value");
		url = "http://localhost:65537/@#$m!&**_=;";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS(HttpUrl(url), InvalidUrlValue);
		}
	}
	WHEN("Url contain a very long domain value")
	{
		std::domain_error InvalidDomainValue("Invalid domain value");
		url = "http://gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg:32/";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS(HttpUrl(url), InvalidDomainValue);
		}
	}
}