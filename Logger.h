#ifndef LOGGER_H
#define LOGGER_H
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

#define LOG_INFO(msg, ...)                                                                   \
    Logger::getInstance().info("[{}:{} {}] {}", Logger::getRelativePath(__FILE__), __LINE__, \
                               __FUNCTION__, fmt::format(FMT_STRING(msg), ##__VA_ARGS__))
#define LOG_DEBUG(msg, ...)                                                                   \
    Logger::getInstance().debug("[{}:{} {}] {}", Logger::getRelativePath(__FILE__), __LINE__, \
                                __FUNCTION__, fmt::format(FMT_STRING(msg), ##__VA_ARGS__))
#define LOG_WARN(msg, ...)                                                                   \
    Logger::getInstance().warn("[{}:{} {}] {}", Logger::getRelativePath(__FILE__), __LINE__, \
                               __FUNCTION__, fmt::format(FMT_STRING(msg), ##__VA_ARGS__))
#define LOG_ERROR(msg, ...)                                                                   \
    Logger::getInstance().error("[{}:{} {}] {}", Logger::getRelativePath(__FILE__), __LINE__, \
                                __FUNCTION__, fmt::format(FMT_STRING(msg), ##__VA_ARGS__))

class Logger {
   public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    template <typename... Args>
    void info(const std::string& msg, Args&&... args) {
        logger->info(msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(const std::string& msg, Args&&... args) {
        logger->debug(msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(const std::string& msg, Args&&... args) {
        logger->warn(msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(const std::string& msg, Args&&... args) {
        logger->error(msg, std::forward<Args>(args)...);
    }

    static std::string getRelativePath(const std::string& fullPath);

   private:
    std::shared_ptr<spdlog::logger> logger;
    static inline std::string m_basePath;

    Logger();
    ~Logger() = default;
};

#endif  // LOGGER_H