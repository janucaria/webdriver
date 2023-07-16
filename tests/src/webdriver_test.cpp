#include <gtest/gtest.h>

#include <janucaria/webdriver/webdriver.hpp>

namespace webdriver = janucaria::webdriver;

class WebDriverTest : public ::testing::Test {
protected:
  std::string host_url{};

  auto get_env_var(std::string_view name) -> std::string
  {
    const auto value = std::getenv(name.data());
    if(value == nullptr) {
      return "";
    }

    return value;
  }

  void SetUp() override
  {
    host_url = get_env_var("JANUCARIA_WEBDRIVER_HOST_URL");
  }
};

TEST_F(WebDriverTest, create_and_close_session)
{
  const auto webdriver = webdriver::WebDriver{host_url};
  auto session = webdriver.new_session();

  EXPECT_FALSE(session.session_id().empty());

  session.close();
  EXPECT_TRUE(session.session_id().empty());
}
