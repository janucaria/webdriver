#include <fmt/format.h>
#include <httplib/httplib.h>

#include <janucaria/webdriver/session.hpp>

namespace janucaria::webdriver {

Session::Session(std::string session_id, std::string host_url)
: session_id_{std::move(session_id)}
, host_url_{std::move(host_url)}
{
}

auto Session::session_id() const noexcept -> const std::string_view
{
  return session_id_;
}

void Session::close()
{
  auto client = httplib::Client{host_url_};
  const auto res = client.Delete(fmt::format("/session/{}", session_id_));
  if(res->status != 200) {
    const auto error = res.error();

    std::cerr << fmt::format("Failed to delete session: {}\n", res->body);
  }

  session_id_ = "";
}

} // namespace janucaria::webdriver
