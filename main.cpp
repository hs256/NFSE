#include <iostream>
#include <vector>
#include <map>

#include "antlr/antlr4-runtime.h"
#include "parser/NFCompilerLexer.h"
#include "parser/NFCompilerParser.h"
#include "parser/NFCompilerVisitor.h"
#include "symboltable.h"
#include "instructions.h"
#include "trace.h"
//#include "pkt.h"

using namespace std;

using namespace antlr4;

map<string, string> pkt_fields {
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


int main(int argc, const char *argv) {
  ifstream stream("model2.txt", ios::in);

  ANTLRInputStream input(stream);
  NFCompilerLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  NFCompilerParser parser(&tokens);

  NFCompilerParser::ProgramContext *nf_name = parser.program();
  cout << "program name " << nf_name->IDENT()->getText() << endl;
  NFCompilerVisitor visitor;
  antlrcpp::Any v = visitor.visitProgram(nf_name);
  visitor.ST.printST();
  visitor.print_entries();

  trace t;
  vector<Symbol *> svt = visitor.ST.state_vars();
  vector<Symbol *>::iterator its;
  for (its = svt.begin(); its != svt.end(); its++) {
    string stvar = (*its)->getName();
    t.add_decl_node(stvar);
    string stval = (*its)->getValue();
    t.add_assign_in(stvar, stoi(stval));
  }

  vector<struct entry*>::iterator it;
  for (it = visitor.entries.begin(); it != visitor.entries.end(); it++) {
    vector<struct match_entry_flow*> mef = (*it)->m_f;
    vector<struct match_entry_flow*>::iterator it2;
    vector<struct tracenode*> tmp1;
    struct action_flow *af = (*it)->a_f;
    struct match_state *ms = (*it)->m_s;
    struct tracenode *t3;
    for (it2 = mef.begin(); it2 != mef.end(); it2++) {
      struct match_flow *mf_temp = (*it2)->mf;
      string v = mf_temp->var;
      vector<string> g = visitor.ST.getGranularitybyName(v);
      string c = visitor.ST.getValuebyName(v);
      int val = stoi(c);
      struct tracenode *t1;
      if (mf_temp->match) {
	t1 = t.new_assert_node(pkt_fields[g[0]], "==", val);
      } else {
	t1 = t.new_assert_node(pkt_fields[g[0]], "!=", val);
      }
	tmp1.push_back(t1);
      }
      if(af->action == "DROP")
	t3 = t.new_assert_node("DROP", "", 0);
      else if(af->action == "pass")
	t3 = t.new_assert_node("pass", "", 0);
      else
	t3 = NULL;
      if(ms != NULL && ms->state_var != "") {
	string stval = ms->state_val;
	string stc = visitor.ST.getValuebyName(stval);
	int stn = stoi(stc);
	struct tracenode *tvar = t.new_assert_node(ms->state_var, "==", stn);
	tmp1.push_back(tvar);
      }

      t.add_mlrite_nodes(t3, tmp1);
  }
  t.print_all_paths();
  t.execute();
  t.print_all_paths();

  return 0;
}

