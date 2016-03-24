#pragma once

namespace XsbDotNet
{
    public ref class XsbException
        : public System::Exception
    {
    public:
        XsbException(void);
        XsbException(System::String ^message);
        XsbException(System::String ^message, System::Exception ^innerException);
    };

}