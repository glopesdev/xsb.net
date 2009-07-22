#include "StdAfx.h"
#include "XsbException.h"

XsbDotNet::XsbException::XsbException(void)
{
}

XsbDotNet::XsbException::XsbException(System::String ^message):
System::Exception(message)
{
}

XsbDotNet::XsbException::XsbException(System::String ^message, System::Exception ^innerException):
System::Exception(message, innerException)
{
}