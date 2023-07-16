#ifndef JANUCARIA_WEBDRIVER_SESSION_HPP
#define JANUCARIA_WEBDRIVER_SESSION_HPP

#include <string>
#include <string_view>

namespace janucaria::webdriver {

/**
 * @brief A WebDriver Session implementation.
 */
class Session {
public:
  /**
   * @brief Construct a new Session object.
   *
   * @param session_id The session id.
   */
  Session(std::string session_id, std::string host_url);

  /**
   * @brief Get the session id.
   *
   * @return std::string_view The session id.
   */
  auto session_id() const noexcept -> const std::string_view;

  /**
   * @brief Close the session.
   */
  void close();

private:
  std::string session_id_;
  std::string host_url_;
};

} // namespace janucaria::webdriver

#endif
