#ifndef JANUCARIA_WEBDRIVER_WEBDRIVER_HPP
#define JANUCARIA_WEBDRIVER_WEBDRIVER_HPP

#include <string>

#include <janucaria/webdriver/session.hpp>

namespace janucaria::webdriver {

class WebDriver {
public:
  /**
   * @brief Construct a new WebDriver object.
   */
  explicit WebDriver(std::string host_url);

  /**
   * @brief Create a new session.
   */
  auto new_session() const -> Session;

private:
  std::string host_url_;
};

} // namespace janucaria::webdriver

#endif
