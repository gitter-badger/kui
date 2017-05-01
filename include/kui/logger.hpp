#ifndef KUI_LOGGER_HPP
#define KUI_LOGGER_HPP

#include <fstream>
#include <sstream>
#include <array>

namespace kui {

    enum class Log_severity: unsigned int {
        trace,
        debug,
        info,
        warning,
        error
    };

    class Logger {
    public:
        static Logger & get_instance(){
            static Logger l;
            return l;
        }

        std::ostream & log(Log_severity severity, const char *date, const char *time, const char *file, unsigned int line) {
            const std::array<const char *, 5> severity_strings = {
                    "TRACE  ",
                    "DEBUG  ",
                    "INFO   ",
                    "WARNING",
                    "ERROR  "
            };

            if((unsigned int)severity >= (unsigned int)_min_severity) {
                _stream << date << " " << time << "\t"
                        << severity_strings[(unsigned int)severity] << "\t"
                        << file << ":" << line << "\t";

                return _stream;
            }
            else {
                return _null_stream;
            }
        }

        void set_min_severity(Log_severity severity) {
            _min_severity = severity;
        }

    private:
        Logger(){
            _stream.open("kui.log", std::ios_base::app);
            _null_stream.open("/dev/null");
            _min_severity = Log_severity::debug;
        }
        ~Logger(){}

        std::ofstream _stream;
        std::ofstream _null_stream;
        Log_severity _min_severity;
    };

}

#define _KUI_BASE_LOG(SEVERITY, STREAM) \
kui::Logger::get_instance().log(kui::Log_severity::SEVERITY, __DATE__, __TIME__, __FILE__, __LINE__) << STREAM << std::endl;

#define KUI_LOG(SEVERITY, STREAM) _KUI_BASE_LOG(SEVERITY, STREAM)

#define KUI_LOG_SEVERITY(SEVERITY) \
kui::Logger::get_instance().set_min_severity(kui::Log_severity::SEVERITY)

#define KUI_LOG_SEVERITY_RESET() KUI_LOG_SEVERITY(debug)

#endif