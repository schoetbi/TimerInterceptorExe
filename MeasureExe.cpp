#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include <chrono>
#include <ctime>
#include <fstream>

#include "fmt/format.h"
#include "fmt/ostream.h"

int main(int argc, char *argv[]) {
  auto executable = std::string(argv[0]);
  auto last_dot = std::find(executable.rbegin(), executable.rend(), '.');
  std::string name;
  if (last_dot == executable.rend()) {
    name = executable;
  } else {
    name = executable.replace(last_dot.base() - 1, executable.end(), "");
  }

  const auto real_executable = fmt::format("{}_real.exe", name);
  std::string arguments;
  for (int i = 1; i < argc; i++) {
    arguments += fmt::format(" {}", argv[i]);
  }

  PROCESS_INFORMATION ProcessInfo;  // This is what we get as an [out] parameter
  STARTUPINFOA StartupInfo;         // This is an [in] parameter

  ZeroMemory(&StartupInfo, sizeof(StartupInfo));
  StartupInfo.cb = sizeof StartupInfo;  // Only compulsory field

  std::time_t time = std::time(0);
  std::tm *now = std::localtime(&time);
  auto start_time = std::chrono::high_resolution_clock::now();
  CreateProcessA(real_executable.c_str(), const_cast<char *>(arguments.c_str()),
                 nullptr, nullptr, true, 0, nullptr, nullptr, &StartupInfo,
                 &ProcessInfo);
  WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
  CloseHandle(ProcessInfo.hThread);
  CloseHandle(ProcessInfo.hProcess);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = end_time - start_time;

  auto log_file_name = fmt::format("{}.log", name);
  auto mutex = CreateMutexA(nullptr, true, "measure_log_mutex");
  // write to log file
  std::ofstream log;
  log.open(log_file_name, std::ofstream::out | std::ofstream::app);

  fmt::print(
      log, "{:04}/{:02}/{:02} {:02}:{:02}:{:02}\t{}\tms\t{}\n",
      now->tm_year + 1900, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min,
      now->tm_sec,
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(),
      arguments);
  log.close();
  ReleaseMutex(mutex);
  CloseHandle(mutex);
}