#include "Loader.h"
#include "UdsSocketDemo.h"
#include "FwdList.h"
#include <thread>
#include <chrono>
#include <iostream>

// Note: Using endl for flushing output. For performance-critical code, '\n' can be used instead
// since it avoids the overhead of flushing the output buffer.

using namespace std;
using namespace aelzns;

void Loader::init() {
  cout << endl << "**  Application demonstrates basic C++ samples and techniques **" << endl << endl;

  mHandlers.emplace("udsSocket", std::make_unique<UdsSocketDemo>());
  mHandlers.emplace("fwdList", std::make_unique<FwdList>());
}

void Loader::usage() {
  cout << "Usage ./demo <no_args|handlers>" << endl;
  cout << "Handlers:" << endl;

  for (const auto& [name, handler] : mHandlers) {
    cout << "    " << name << endl;
  }
}
Cli* Loader::getHandler(const std::string& arg) {
  auto it = mHandlers.find(arg);
  return (it != mHandlers.end()) ? it->second.get() : nullptr;
}

void Loader::runAll(int argc, char* argv[]) {
  constexpr auto delay = std::chrono::milliseconds(1000);

  for (const auto& [name, handler] : mHandlers) {
    cout << "***\t" << name << " started\t***" << endl;
    handler->processCli(argc, argv);
    cout << "***\t" << name << " finished\t***" << endl << endl << endl;
    std::this_thread::sleep_for(delay);
  }
}

Loader::~Loader() = default;
