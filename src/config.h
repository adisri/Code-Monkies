#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include <unordered_map>
#include <unordered_set>

#include "config_parser.h"

#define PORT_MAX 65535

class Config {
  public:
    Config(const short port,
        const std::unordered_set<std::string> &echo_uris,
        const std::unordered_map<std::string, std::string>
          &file_uri_mappings)
      : port_(port), echo_uris_(echo_uris), file_uri_mappings_(file_uri_mappings)
    {
    }

    std::string toString() const;

    const short port_;
    const std::unordered_set<std::string> echo_uris_;
    const std::unordered_map<std::string, std::string> file_uri_mappings_;
};

class ConfigBuilder {
  public:
    ConfigBuilder();

    /*
     * Given a parsed nginx-style configuration, build a valid server configuration
     * or return false.
     */
    bool build(const NginxConfig &config, Config *&conf);

  private:

    /*
     * Set port. Only fail if port is out of the range [1, 65535].
     */
    bool setPort(int port);

    /*
     * Add entry to echo_uri. Fail if uri is already defined.
     */
    bool addEchoUri(std::string uri);

    /*
     * Add entry to file_uri_mappings. Fail if URI is already defined.
     */
    bool addFileUriMapping(std::string uri, std::string path);

    /*
     * Generate config object. Fail only if port is not set.
     */
    bool build(Config *&config);

    int port_;
    /*
     * URIs at which the server will simply echo requests, e.g. "/echo".
     */
    std::unordered_set<std::string> echo_uris_;
    /*
     * URI-path pairs at which the server will serve files. For example, the
     * tuple ("/static", "/var/www/html") will cause the server to serve
     * requests like "GET /static/index.html HTTP/1.0" from
     * /var/www/static/index.html.
     */
    std::unordered_map<std::string, std::string> file_uri_mappings_;
};

#endif