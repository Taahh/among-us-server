#ifndef LOG_FORMATTER_HPP
#define LOG_FORMATTER_HPP

#include <plog/Log.h>
#include <plog/WinApi.h>
#include <plog/Appenders/ConsoleAppender.h>

using namespace plog;

template<class Formatter>
class ColoredAppender : public ConsoleAppender<Formatter> {
private:
    util::nstring format(const Record &record) {

        tm t;
        util::localtime_s(&t, &record.getTime().time);

        std::ostringstream ss;

        std::string s;
        std::istringstream((char*)record.getMessage()) >> std::quoted(s);
        if (s == "") {
            ss << std::endl;
        } else {
            ss << t.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-")
               << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":")
               << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0'))
               << std::setw(2) << t.tm_sec << PLOG_NSTR(".") << std::setfill(PLOG_NSTR('0')) << std::setw(3)
               << static_cast<int> (record.getTime().millitm) << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity())
               << PLOG_NSTR(" ");
            ss << PLOG_NSTR("[") << record.getTid() << PLOG_NSTR("] ");
            ss << PLOG_NSTR("[") << record.getFunc() << PLOG_NSTR("@") << record.getLine() << PLOG_NSTR("] ");
            ss << record.getMessage();
        }


        return ss.str();
    }

public:
#ifdef _WIN32
#   ifdef _MSC_VER
#       pragma warning(suppress: 26812) //  Prefer 'enum class' over 'enum'
#   endif
    ColorConsoleAppender(OutputStream outStream = streamStdOut)
        : ConsoleAppender<Formatter>(outStream)
        , m_originalAttr()
    {
        if (this->m_isatty)
        {
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            GetConsoleScreenBufferInfo(this->m_outputHandle, &csbiInfo);

            m_originalAttr = csbiInfo.wAttributes;
        }
    }
#else

    ColoredAppender(OutputStream outStream = streamStdOut)
            : ConsoleAppender<Formatter>(outStream) {}

#endif

    virtual void write(const Record &record) PLOG_OVERRIDE {
        util::nstring str = this->format(record);
        util::MutexLock lock(this->m_mutex);

        setColor(record.getSeverity());
        this->writestr(str);
        resetColor();
    }

protected:
    void setColor(Severity severity) {
        if (this->m_isatty) {
            switch (severity) { //TODO: Make colors match for windows users
#ifdef _WIN32
                case fatal:
                    SetConsoleTextAttribute(this->m_outputHandle, foreground::kRed | foreground::kGreen | foreground::kBlue | foreground::kIntensity | background::kRed); // white on red background
                    break;

                case error:
                    SetConsoleTextAttribute(this->m_outputHandle, static_cast<WORD>(foreground::kRed | foreground::kIntensity | (m_originalAttr & 0xf0))); // red
                    break;

                case warning:
                    SetConsoleTextAttribute(this->m_outputHandle, static_cast<WORD>(foreground::kRed | foreground::kGreen | foreground::kIntensity | (m_originalAttr & 0xf0))); // yellow
                    break;

                case debug:
                case verbose:
                    SetConsoleTextAttribute(this->m_outputHandle, static_cast<WORD>(foreground::kGreen | foreground::kBlue | foreground::kIntensity | (m_originalAttr & 0xf0))); // cyan
                    break;
#else
                case fatal:
                    this->m_outputStream << "\x1B[97m\x1B[41m"; // white on red background
                    break;

                case error:
                    this->m_outputStream << "\x1B[91m"; // red
                    break;

                case warning:
                    this->m_outputStream << "\x1B[93m"; // yellow
                    break;

                case debug:
                case verbose:
                    this->m_outputStream << "\x1B[35m"; // cyan
                    break;
                case info:
                    this->m_outputStream << "\x1B[34m";
                    break;
#endif
                default:
                    break;
            }
        }
    }

    void resetColor() {
        if (this->m_isatty) {
#ifdef _WIN32
            SetConsoleTextAttribute(this->m_outputHandle, m_originalAttr);
#else
            this->m_outputStream << "\x1B[0m\x1B[0K";
#endif
        }
    }

private:
#ifdef _WIN32
    WORD   m_originalAttr;
#endif
};

#endif //LOG_FORMATTER_HPP
