// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include "session.h"

using boost::asio::ip::tcp;

/*
 * Generic asynchronous server. Listens for connections and passes them off to
 * a fresh Session object before listening again.
 */
class Server
{
public:
  Server(boost::asio::io_service& io_service, const NginxConfig *conf);

private:
  /*
   * Allocate session for connection and listen for the next one.
   */
  void do_accept();

  // Boost TCP fields
  tcp::acceptor acceptor_;
  tcp::socket socket_;

  // Nginx config fields
  const NginxConfig *conf_;
};

#endif
