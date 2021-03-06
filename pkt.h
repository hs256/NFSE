#include <map>
#include <string>

#ifndef PKT_H
#define PKT_H

std::map<std::string, std::string> negated_op {
  {"==", "!="},
  {"=", "!=" },
  {"<", ">="},
  {"<=", ">"},
  {">", "<="},
  {">=", "<"}
};

std::map<std::string, std::string> pkt_fields {
  {"sip", "L3+96"},
  {"dip", "L3+128"},
  {"proto", "L3+72"},
  {"sport", "L4+0"},
  {"dport", "L4+16"},
  {"flag_ack", "L4+107"},
  {"flag_rst", "L4+109"},
  {"flag_syn", "L4+110"},
  {"flag_fin", "L4+111"}
};

class packet {
};

#endif

