#include <string>
#include <utility>

#include <fmt/format.h>
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>

#include <janucaria/webdriver/webdriver.hpp>

namespace janucaria::webdriver {

WebDriver::WebDriver(std::string host_url)
: host_url_{std::move(host_url)}
{
}

auto WebDriver::new_session() const -> Session
{
  const auto json_body =
   nlohmann::json{{"capabilities",
                   {{"alwaysMatch",
                     {{"browserName", "MicrosoftEdge"},
                      {"ms:edgeOptions", {{"args", {"--inprivate"}}}}}}}}}
    .dump();

  auto client = httplib::Client{host_url_};
  const auto res = client.Post("/session", json_body, "application/json");
  if(res->status != 200) {
    const auto error = res.error();

    std::cerr << fmt::format("Failed to create new session: {}\n", res->body);

    return Session{"", host_url_};
  }

  const auto res_json = nlohmann::json::parse(res->body);
  const auto value_json = res_json.at("value");
  const auto session_id_json = value_json.at("sessionId");
  const auto session_id = session_id_json.get<std::string>();

  return Session{session_id, host_url_};
}

} // namespace janucaria::webdriver
