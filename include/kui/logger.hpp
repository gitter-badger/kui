#ifndef KUI_LOGGER_HPP
#define KUI_LOGGER_HPP

#include <cassert>

#include <iostream>
#include <fstream>
#include <memory>

namespace kui {

  class Logger {
  public:
    std::ofstream stream;
  
    static Logger& get_logger() {
      static Logger l;
      return l;
    }
    
    void reset() {
      stream.open("kui.log");
      stream.open("kui.log", std::ios_base::app);
    }
      
  private:
    Logger() {
      stream.open("kui.log", std::ios_base::app);
    }
    ~Logger(){}
  };

}

#define KUI_LOG(STREAM) \
kui::Logger::get_logger().stream << __DATE__ << " " << __TIME__ << "\t" \
                                 << __FILE__ << ":" << __LINE__ << "\t" << STREAM << std::endl;

#endif