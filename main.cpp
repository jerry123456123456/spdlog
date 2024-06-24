//g++ main.cpp -o main -std=c++14 -lpthread -I/usr/local/include/

#if 1

#include<spdlog/spdlog.h>
#include<spdlog/async_logger.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#include<spdlog/sinks/basic_file_sink.h>

int main(){
    spdlog::info("hello world");

    //使用工厂方法创建异步日志
    auto logger =spdlog::stdout_color_mt<spdlog::async_factory>("console");
    logger->info("hello world too!");

    //通过console这个名字重新拿到智能指针logger，并继续输出
    spdlog::get("console")->info("get logger!");

    ///////////////////////////////////////////////////////////
    /*
    上面的代码是直接使用全局默认的 logger 自定义的异步 logger 来输出日志消息
    而第二段代码是创建了自定义的 logger 并将多个 sink 添加到其中，用于输出到不同的目的地
    */

    //创建sink,一个sink代表一个输出点（包括控制台，文件，以及一些应用中)
    //`stdout_color_sink_mt` 表示一个多线程（`mt`）的日志输出目标，用于将彩色的日志消息输出到标准输出（控制台）
    auto sink1=std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto sink2=std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/mylog.txt");
    //设置具体的格式
    sink2->set_pattern("[%^%l%$] %v");

    //创建一个sink容器，并将sink1和sink2添加进去
    std::vector<spdlog::sink_ptr> sinks {sink1,sink2};
    auto logger1=std::make_shared<spdlog::logger>("console1",sinks.begin(),sinks.end());
    spdlog::register_logger(logger1);
    spdlog::get("console1")->info("sink1");

    return 0;
}

#endif

#if 0
#include<spdlog/spdlog.h>
#include<spdlog/sinks/basic_file_sink.h>

int main(){
    //初始化日志记录器，将日志输出到文件中
    auto file_logger=spdlog::basic_logger_mt("file_logger","logs/mylog.txt");   //mt多线程,st单线程
    //设置日志级别为info
    file_logger->set_level(spdlog::level::info);

    //记录日志
    file_logger->info("Logging to file");

    return 0;
}

#endif

