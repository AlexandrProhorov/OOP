#pragma once
#include "pch.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"



UrlParsingError InvalidUrlObject("Can't construct invalid url object");
UrlParsingError InvalidProtocolNoDefaultPort("Invalid protocol with no default port");
UrlParsingError InvalidDomainValue("Invalid domain value");
UrlParsingError PortOutOfRange("Invalid port is out of range");
UrlParsingError InvalidPortValue("Invalid port value");
UrlParsingError InvalidIpValue("Invalid ip value");
UrlParsingError InvalidUrlValue("Invalid url value");