#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ApplicationSettings.h"
#include "CommandLineParser.h"
#include "CommandlineCommandConfig.h"
#include "utilities/CollectOutStream.hpp"

using namespace testing;

namespace commandline {

void PrintTo(const CommandlineCommand::ReturnStatus& status, std::ostream* os) {
  switch(status) {
  case CommandlineCommand::ReturnStatus::CMD_FAILURE:
    *os << "FAILURE";
    return;
  case CommandlineCommand::ReturnStatus::CMD_OK:
    *os << "OK";
    return;
  case CommandlineCommand::ReturnStatus::CMD_QUIT:
    *os << "QUIT";
    return;
  }
}

}    // namespace commandline

using namespace commandline;

struct CommandlineCommandConfigFix : public Test {
  void SetUp() override {
    mParesr = std::make_unique<CommandLineParser>("");
    mConfig = std::make_unique<CommandlineCommandConfig>(mParesr.get());
    mConfig->setup();
  }

  std::unique_ptr<CommandLineParser> mParesr;
  std::unique_ptr<CommandlineCommandConfig> mConfig;
};

TEST_F(CommandlineCommandConfigFix, emptyArgs) {
  std::vector<std::string> args;

  CollectOutStream stream(std::cout);
  const auto ret = mConfig->parse(args);
  stream.close();

  constexpr std::string_view ResultString =
      "Usage:\n\n  Sourcetrail config [option...]\n\nChange preferences relevant to project indexing.\n\n\nConfig Options:\n  -h "
      "[ --help ]                         Print this help message\n  -t [ --indexer-threads ] arg          Set the number of "
      "threads used for \n                                        indexing (0 uses ideal thread count)\n  -p [ --use-processes ] "
      "arg            Enable C/C++ Indexer threads to run in \n                                        different processes. "
      "<true/false>\n  -l [ --logging-enabled ] arg          Enable file/console logging \n                                      "
      "  <true/false>\n  -L [ --verbose-indexer-logging-enabled ] arg\n                                        Enable additional "
      "log of abstract \n                                        syntax tree during the indexing. \n                             "
      "           <true/false> WARNING Slows down \n                                        indexing speed\n  -g [ "
      "--global-header-search-paths ] arg\n                                        Global include paths (once per path or \n     "
      "                                   comma separated)\n  -F [ --global-framework-search-paths ] arg\n                       "
      "                 Global include paths (once per path or \n                                        comma separated)\n  -s "
      "[ --show ]                         displays all settings\n\n";

  ASSERT_EQ(CommandlineCommand::ReturnStatus::CMD_QUIT, ret);
  EXPECT_THAT(stream.str(), StrEq(ResultString));
}

TEST_F(CommandlineCommandConfigFix, passEmptyArg) {
  std::vector<std::string> args = {"--help"};

  CollectOutStream stream(std::cout);
  const auto ret = mConfig->parse(args);
  stream.close();

  constexpr std::string_view ResultString =
      "Usage:\n\n  Sourcetrail config [option...]\n\nChange preferences relevant to project indexing.\n\n\nConfig Options:\n  -h "
      "[ --help ]                         Print this help message\n  -t [ --indexer-threads ] arg          Set the number of "
      "threads used for \n                                        indexing (0 uses ideal thread count)\n  -p [ --use-processes ] "
      "arg            Enable C/C++ Indexer threads to run in \n                                        different processes. "
      "<true/false>\n  -l [ --logging-enabled ] arg          Enable file/console logging \n                                      "
      "  <true/false>\n  -L [ --verbose-indexer-logging-enabled ] arg\n                                        Enable additional "
      "log of abstract \n                                        syntax tree during the indexing. \n                             "
      "           <true/false> WARNING Slows down \n                                        indexing speed\n  -g [ "
      "--global-header-search-paths ] arg\n                                        Global include paths (once per path or \n     "
      "                                   comma separated)\n  -F [ --global-framework-search-paths ] arg\n                       "
      "                 Global include paths (once per path or \n                                        comma separated)\n  -s "
      "[ --show ]                         displays all settings\n\n";

  ASSERT_EQ(CommandlineCommand::ReturnStatus::CMD_QUIT, ret);
  EXPECT_THAT(stream.str(), StrEq(ResultString));
}

TEST_F(CommandlineCommandConfigFix, showArg) {
  std::vector<std::string> args = {"show"};

  CollectOutStream stream(std::cout);
  const auto ret = mConfig->parse(args);
  stream.close();

  constexpr std::string_view ResultString =
      "Sourcetrail Settings:\n\n  indexer-threads: 0\n  use-processes: 1\n  logging-enabled: 1\n  "
      "verbose-indexer-logging-enabled: 0\n  global-header-search-paths:\n    -\n\n  global-framework-search-paths:\n    -\n";

  ASSERT_EQ(CommandlineCommand::ReturnStatus::CMD_QUIT, ret);
  EXPECT_THAT(stream.str(), StrEq(ResultString));
}

TEST_F(CommandlineCommandConfigFix, invalidArg) {
  std::vector<std::string> args = {"--invalid"};

  CollectOutStream stream(std::cerr);
  const auto ret = mConfig->parse(args);
  stream.close();

  constexpr std::string_view ResultString =
      "ERROR: unrecognised option '--invalid'\n\n\nConfig Options:\n  -h [ --help ]                         Print this help "
      "message\n  -t [ --indexer-threads ] arg          Set the number of threads used for \n                                    "
      "    indexing (0 uses ideal thread count)\n  -p [ --use-processes ] arg            Enable C/C++ Indexer threads to run in "
      "\n                                        different processes. <true/false>\n  -l [ --logging-enabled ] arg          "
      "Enable file/console logging \n                                        <true/false>\n  -L [ "
      "--verbose-indexer-logging-enabled ] arg\n                                        Enable additional log of abstract \n     "
      "                                   syntax tree during the indexing. \n                                        "
      "<true/false> WARNING Slows down \n                                        indexing speed\n  -g [ "
      "--global-header-search-paths ] arg\n                                        Global include paths (once per path or \n     "
      "                                   comma separated)\n  -F [ --global-framework-search-paths ] arg\n                       "
      "                 Global include paths (once per path or \n                                        comma separated)\n  -s "
      "[ --show ]                         displays all settings\n\n";

  ASSERT_EQ(CommandlineCommand::ReturnStatus::CMD_FAILURE, ret);
  EXPECT_THAT(stream.str(), StrEq(ResultString));
}

TEST_F(CommandlineCommandConfigFix, setNumberOfThreads) {
  std::vector<std::string> args = {"-t", "1", "-g", "/usr/include/"};

  const auto ret = mConfig->parse(args);

  ASSERT_EQ(CommandlineCommand::ReturnStatus::CMD_QUIT, ret);
  EXPECT_EQ(1, ApplicationSettings::getInstance()->getIndexerThreadCount());
  EXPECT_EQ(std::vector<FilePath> {FilePath {"/usr/include/"}}, ApplicationSettings::getInstance()->getHeaderSearchPaths());
}