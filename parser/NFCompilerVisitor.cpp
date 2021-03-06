


#include "NFCompilerVisitor.h"
#include "../symboltable.h"

// Generated from NFCompiler.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "NFCompilerParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by NFCompilerParser.
 */
  /**
   * Visit parse trees produced by NFCompilerParser.
   */
  
void NFCompilerVisitor::print_entries() {
  vector<struct entry*>::iterator it;
  for (it = NFCompilerVisitor::entries.begin(); it != NFCompilerVisitor::entries.end(); it++) {
    vector<struct match_entry_flow*> mf = (*it)->m_f;
    struct action_flow *af = (*it)->a_f;
    vector<struct match_entry_state*> ms = (*it)->m_s;
    vector<struct match_entry_flow*>::iterator it2;
    vector<struct match_entry_state*>::iterator it3;
    for (it2 = mf.begin(); it2 != mf.end(); it2++) {
      cout << (*it2)->op << " ";
      struct match_flow *mff = (*it2)->mf;
      if (mff->match)
	cout << " match ";
      else
	cout << " mismatch ";
      cout << mff->var << " " ;
    }

    cout << " && ";
    for (it3 = ms.begin(); it3 != ms.end(); it3++) {
      struct match_state *mss = (*it3)->ms;
      cout << mss->state_var << " " << mss->op << " " << mss->state_val << "  ";
    }
    cout << af->field << "  " << af->action << endl ;
  }
}

    antlrcpp::Any NFCompilerVisitor::visitProgram(NFCompilerParser::ProgramContext *context) {
      vector<string> per_nf;
      per_nf.push_back("per-nf");
      NFCompilerVisitor::ST.add(context->IDENT()->getText(), "program", "program", "NULL", per_nf);
      NFCompilerVisitor::ST.add("f", "flow", "flow", "NULL", per_nf);
      return visitChildren(context);
    }


    antlrcpp::Any NFCompilerVisitor::visitDeclare_entry(NFCompilerParser::Declare_entryContext *context) {
      std::string type = context->type()->getText();
      if (type == "rule") {
	try {
	antlrcpp::Any a = NFCompilerVisitor::visit(context->expression(0));
	map<string, string> m;
	m = a.as<map<string, string>>();
	vector<string> v_f;
	v_f.push_back(m.begin()->first);
	NFCompilerVisitor::ST.add(context->IDENT()->getText(),type, type, m.begin()->second, v_f);
	//cout << context->IDENT()->getText() << " " << m.begin()->first << " " << m.begin()->second << endl;
	} catch (bad_cast const& e) {
	    try {
	      antlrcpp::Any a = NFCompilerVisitor::visit(context->expression(0));
	      vector<string> m;
	      m = a.as<vector<string>>();
	      //cout << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << " " << m[4] << endl;
	      if (m.size() == 5)
		NFCompilerVisitor::CT.add(context->IDENT()->getText(), m[0], m[1], m[2], m[3], m[4]);
	    } catch (bad_cast const& e) {
	    }
	  }
      } else if (type == "int") {
	if (context->ASSIGN() != NULL && context->expression().size() == 1) {
	  antlrcpp::Any a1 = NFCompilerVisitor::visit(context->expression(0));
	  try {
	    string int_c;
	    int_c = a1.as<string>();
	    if (NFCompilerVisitor::ST.find(int_c) == NULL) {
	      NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, int_c, vector<string>());
	    } else {
	      string int_actual = NFCompilerVisitor::ST.getValuebyName(int_c);
	      NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, int_actual, vector<string>());
	    }
	  } catch (bad_cast const& e) {
	  }
	} else if (context->ASSIGN() != NULL && context->expression().size() == 2) {
	  antlrcpp::Any a0 = NFCompilerVisitor::visit(context->expression(0));
	  antlrcpp::Any a1 = NFCompilerVisitor::visit(context->expression(1));
	  try {
	    vector<string> c00;
	    string int_c;
	    c00 = a0.as<vector<string>>();
	    int_c = a1.as<string>();
	    if (NFCompilerVisitor::ST.find(int_c) == NULL) {
	      NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, int_c, c00);
	    } else {
	      string int_actual = NFCompilerVisitor::ST.getValuebyName(int_c);
	      NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, int_actual, c00);
	    }
	  } catch (bad_cast const& e) {
	  }
	} else if (context->ASSIGN() == NULL && context->expression().size() == 1) {
	  try {
	    antlrcpp::Any a = NFCompilerVisitor::visit(context->expression(0));
	    vector<string> m0;
	    m0 = a.as<vector<string>>();
	    NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, "", m0);
	  } catch (bad_cast const& e) {
	  }
	}
      } else if (type == "float") {
	//cout << context->expression(0)->getText() << " float exp" << endl;
	NFCompilerVisitor::ST.add(context->IDENT()->getText(), type, type, context->expression(0)->getText(), vector<string>());
      }


      return visitChildren(context);
    }

  antlrcpp::Any NFCompilerVisitor::visitEntries(NFCompilerParser::EntriesContext *ctx)  {
    return visitChildren(ctx);
  }

  antlrcpp::Any NFCompilerVisitor::visitEntry(NFCompilerParser::EntryContext *ctx)  {
    struct match_flow *mf = new match_flow;
    struct action_flow *af = new action_flow;
    struct entry *en = new entry;
    vector<struct match_entry_flow *> map_mf;
    vector<struct match_entry_state *> map_ms;
    vector<struct action_state *> asv;
    if (ctx->match_action()->match_flow() != NULL) {
      try {
	//cout << "one expression in match_flow " << endl;
	antlrcpp::Any a_mf = NFCompilerVisitor::visit(ctx->match_action()->match_flow()->condition()->expression(0));
	map<bool, string> m;
	m = a_mf.as<map<bool, string>>();
	mf->match = m.begin()->first;
	mf->var = m.begin()->second;
	struct match_entry_flow *mef = new match_entry_flow;
	mef->op = true;
	mef->mf = mf;
	map_mf.push_back(mef);
      } catch (bad_cast const& e) {
	//cout << "unable to get map match flow " << endl;
	try {
	  antlrcpp::Any a_map_mf = NFCompilerVisitor::visit(ctx->match_action()->match_flow()->condition()->expression(0));
	  map_mf = a_map_mf.as<vector<struct match_entry_flow *>>();
	  //cout << map_mf.size() << "map mf size in visit entry " << endl;
	} catch (bad_cast const &e) {
	  //cout << "unabel to get map mf " << endl;
	}
      }
    }

    if (ctx->match_action()->action_statements()->action_flow()) {
      antlrcpp::Any a_af = NFCompilerVisitor::visit(ctx->match_action()->action_statements()->action_flow()->statement());
      try {
	string action = a_af.as<string>();
	af->field = "";
	af->action = action;
      } catch(bad_cast const& e) {
	  if (ctx->match_action()->action_statements()->action_flow()->statement()->assignment()) {
	    try {
	      antlrcpp::Any a_af2 = NFCompilerVisitor::visit(ctx->match_action()->action_statements()->action_flow()->statement()->assignment());
	      map<string, string> m;
	      m = a_af2.as<map<string, string>>();
	      af->field = m.begin()->first;
	      af->action = m.begin()->second;
	    } catch (bad_cast const& e) {
	      //cout << "can't convert to map " << endl;
	    }
	  }
      }
    } else {
      af->field = "";
      af->action = "pass";
    }

    if (ctx->match_action()->match_state()) {
      int ms_n = ctx->match_action()->match_state()->condition()->expression().size();
      for (int k = 0; k < ms_n; k++) {
	antlrcpp::Any a3 = NFCompilerVisitor::visit(ctx->match_action()->match_state()->condition()->expression(k));
	try {
	  vector<string> t_m;
	  struct match_state *ms = new match_state;
	  t_m = a3.as<vector<string>>();
	  ms->state_var = t_m[0];
	  ms->op = t_m[1];
	  ms->state_val = t_m[2];
	  struct match_entry_state *mes = new match_entry_state;
	  mes->op = true;
	  mes->ms = ms;
	  map_ms.push_back(mes);
	  //cout << t_m[0] << " " << t_m[1] << " " << t_m[2] << " in visit entry  match state" << endl;
	} catch (bad_cast const& e) {
	  //cout << "can't parse match state" << endl;
	}
      }
    }

    if (ctx->match_action()->action_statements()->action_state()) {
    if (ctx->match_action()->action_statements()->action_state()->statement()->assignment()) {
      try {
	struct action_state *as = new action_state;
	antlrcpp::Any a_as = NFCompilerVisitor::visit(ctx->match_action()->action_statements()->action_state()->statement()->assignment());
	map<string, string> m;
	m = a_as.as<map<string, string>>();
	as->state_var = m.begin()->first;
	as->state_val = m.begin()->second;
	asv.push_back(as);
	if (ctx->match_action()->action_statements()->action_state()->statement()->statement().size() > 0) {
	  struct action_state *as2 = new action_state;
	  antlrcpp::Any a_as2 = NFCompilerVisitor::visit(ctx->match_action()->action_statements()->action_state()->statement()->statement(0)->assignment());
	  map<string, string> m2;
	  m2 = a_as2.as<map<string, string>>();
	  as2->state_var = m2.begin()->first;
	  as2->state_val = m2.begin()->second;
	  asv.push_back(as2);
	}
      } catch (bad_cast const& e) {
      }
    }
    }

    en->m_f = map_mf;
    en->a_f = af;
    en->m_s = map_ms;
    en->a_s = asv;
    //NFCompilerVisitor::entry_flow.insert(pair<struct match_flow*, struct action_flow*>(mf, af));  
    NFCompilerVisitor::entries.push_back(en);
    return visitChildren(ctx);
  }

  antlrcpp::Any NFCompilerVisitor::visitMatch_action(NFCompilerParser::Match_actionContext *ctx)  {
    return visitChildren(ctx);
  }

  antlrcpp::Any NFCompilerVisitor::visitAction_statements(NFCompilerParser::Action_statementsContext *ctx)  {
    return visitChildren(ctx);
  }

  antlrcpp::Any NFCompilerVisitor::visitMatch_flow(NFCompilerParser::Match_flowContext *ctx)  {
    return visitChildren(ctx);
  }

  antlrcpp::Any NFCompilerVisitor::visitMatch_state(NFCompilerParser::Match_stateContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitAction_flow(NFCompilerParser::Action_flowContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitAction_state(NFCompilerParser::Action_stateContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitDeclaration(NFCompilerParser::DeclarationContext *ctx)  {
    return visitChildren(ctx);
  }

   //antlrcpp::Any NFCompilerVisitor::visitDeclare_entry(NFCompilerParser::Declare_entryContext *ctx)  {
   // return visitChildren(ctx);
  //}

   antlrcpp::Any NFCompilerVisitor::visitDec_basic(NFCompilerParser::Dec_basicContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitDec_set(NFCompilerParser::Dec_setContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitDec_map(NFCompilerParser::Dec_mapContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitDec_rule(NFCompilerParser::Dec_ruleContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitCondition(NFCompilerParser::ConditionContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitStatement(NFCompilerParser::StatementContext *ctx)  {
     if (ctx->PASS()) {
       //cout << ctx->PASS()->getText() << " in visit statement " << endl;
       return antlrcpp::Any(ctx->PASS()->getText());
    } else if (ctx->RESUBMIT()) {
      return antlrcpp::Any(ctx->RESUBMIT()->getText());
    } else
       return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitAssignment(NFCompilerParser::AssignmentContext *ctx)  {
     //cout << ctx->expression(0)->getText() << " = " << ctx->expression(1)->getText() << " in assignment " << endl;
     if (ctx->expression(0) && ctx->expression(1)) {
      antlrcpp::Any a1 = NFCompilerVisitor::visit(ctx->expression(0));
      antlrcpp::Any a2 = NFCompilerVisitor::visit(ctx->expression(1));
      string s1, s2;
      map<string, string> m;
      try {
	s1 = a1.as<string>();
	s2 = a2.as<string>();
	m.insert(pair<string, string>(s1, s2));
	antlrcpp::Any t(m);
	return t;
      } catch (bad_cast const& e) {
	  //cout << "can't convert any to map in assignment" << endl;
      }
    }
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitSingle(NFCompilerParser::SingleContext *ctx)  {
    //cout << ctx->op()->getText() << " in single context " << endl;
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitDouble(NFCompilerParser::DoubleContext *ctx)  {
     //cout << ctx->expression(0)->getText() << " " << ctx->op()->getText() << " " << ctx->expression(1)->getText() << " in double context " <<  endl;
     if ((ctx->op()->getText() == "matches" || ctx->op()->getText() == "mismatches") && ctx->expression(0)->getText() == "f") {
       string m = ctx->op()->getText();
       bool match;
       if(m == "matches")
	 match = true;
       else if (m == "mismatches")
	 match = false;
       antlrcpp::Any a = NFCompilerVisitor::visit(ctx->expression(1));
	try {
	  string c;
	  map<bool, string> mf;
	  c = a.as<string>();
	  mf.insert(pair<bool, string>(match, c));
	  antlrcpp::Any temp(mf);
	  return temp;
	} catch (bad_cast const& e) {
	}
      } else if ((ctx->op()->getText() == "matches" || ctx->op()->getText() == "mismatches")) {
	  string m = ctx->op()->getText();
	  bool match;
	  if(m == "matches")
	    match = true;
	  else if (m == "mismatches")
	    match = false;
	  string c2;
	  vector<struct match_entry_flow*> map_mft;
	  c2 = ctx->expression(1)->getText();
	  struct match_flow *mf1 = new match_flow;
	  struct match_flow *mf2 = new match_flow;
	  struct match_entry_flow *mef1 = new match_entry_flow;
	  struct match_entry_flow *mef2 = new match_entry_flow;
	  mf2->match = match;
	  mf2->var = c2;
	  try {
	    antlrcpp::Any a1 = NFCompilerVisitor::visit(ctx->expression(0));
	    map<bool, string> c1;
	    c1 = a1.as<map<bool, string>>();
	    mf1->match = c1.begin()->first;
	    mf1->var = c1.begin()->second;
	    //cout << mf1->match << " " << mf1->var << " " << mf2->match << " " << mf2->var << endl;  
	    //map_mft.insert(pair<bool, struct match_flow*>(true, mf1));
	    //map_mft.insert(pair<bool, struct match_flow*>(true, mf2));
	    mef1->op = true;
	    mef1->mf = mf1;
	    mef2->op = true;
	    mef2->mf = mf2;
	    map_mft.push_back(mef1);
	    map_mft.push_back(mef2);
	    return antlrcpp::Any(map_mft);
	  } catch (bad_cast const& e) {
	  }
      } else if (ctx->op()->getText() == "&&") {
	  return NFCompilerVisitor::visit(ctx->expression(0));
      } else if (ctx->op()->getText() == "==") {
	antlrcpp::Any a1 = NFCompilerVisitor::visit(ctx->expression(0));
	antlrcpp::Any a2 = NFCompilerVisitor::visit(ctx->expression(1));
	try {
	  string c1, c2;
	  vector<string> eq_s;
	  c1 = a1.as<string>();
	  c2 = a2.as<string>();
	  //cout << "match state in double " << c1 << " " << ctx->op()->getText() << " "  << c2 << endl;
	  eq_s.push_back(c1);
	  eq_s.push_back("==");
	  eq_s.push_back(c2);
	  antlrcpp::Any temp1(eq_s);
	  return temp1;
	} catch (bad_cast const& e) {
	}
      } else if (ctx->op()->getText() == "&") {
	  string s1 = ctx->expression(0)->getText();
	  string s2 = ctx->expression(1)->getText();
	  vector<string> s12;
	  s12.push_back(s1);
	  s12.push_back(s2);
	  antlrcpp::Any temp12(s12);
	  return temp12;
      } else if (ctx->op()->getText() == "<=") {
	  string op2 = ctx->op()->getText();
	  string cval = ctx->expression(1)->getText();
	  try {
	    antlrcpp::Any an = NFCompilerVisitor::visit(ctx->expression(0));
	    vector<string> ci;
	    ci = an.as<vector<string>>();
	    ci.push_back(op2);
	    ci.push_back(cval);
	    antlrcpp::Any tempi(ci);
	    return tempi;
	  } catch (bad_cast const& e) {
	  }
      } else if (ctx->op()->getText() == "<") {
	  string op2 = ctx->op()->getText();
	  string cval = ctx->expression(1)->getText();
	  try {
	    antlrcpp::Any an = NFCompilerVisitor::visit(ctx->expression(0));
	    string ci;
	    vector<string> eq_si;
	    ci = an.as<string>();
	    eq_si.push_back(ci);
	    eq_si.push_back(op2);
	    eq_si.push_back(cval);
	    antlrcpp::Any tempi(eq_si);
	    return tempi;
	  } catch (bad_cast const& e) {
	  }
      } else if (ctx->op()->getText() == "!=") {
	  string op2 = ctx->op()->getText();
	  string cval = ctx->expression(1)->getText();
	  try {
	    antlrcpp::Any an = NFCompilerVisitor::visit(ctx->expression(0));
	    string ci;
	    vector<string> eq_si;
	    ci = an.as<string>();
	    eq_si.push_back(ci);
	    eq_si.push_back(op2);
	    eq_si.push_back(cval);
	    antlrcpp::Any tempi(eq_si);
	    return tempi;
	  } catch (bad_cast const& e) {
	  }
	} else if (ctx->op()->getText() == "-" && ST.find(ctx->expression(1)->getText())) {
	  //cout << ctx->expression(0)->getText() << " " << ctx->op()->getText() << " " << ctx->expression(1)->getText() << " in double context " <<  endl;
	  string op1 = ctx->op()->getText();
	  vector<string> cn;
	  try {
	    antlrcpp::Any ac1 = NFCompilerVisitor::visit(ctx->expression(0));
	    string c1 = ac1.as<string>();
	    cn.push_back(c1);
	  } catch (bad_cast const &e) {
	  }
	  string c2 = ctx->expression(1)->getText();
	  cn.push_back(op1);
	  cn.push_back(c2);
	  antlrcpp::Any tempn(cn);
	  return cn;
	} else if (ctx->op()->getText() == "-") {
	  string minus_str = ctx->expression(0)->getText() + ctx->op()->getText() + ctx->expression(1)->getText();
	  antlrcpp::Any temp_minus(minus_str);
	  return temp_minus;
	} else if (ctx->op()->getText() == "+") {
	  string plus_str = ctx->expression(0)->getText() + ctx->op()->getText() + ctx->expression(1)->getText();
	  antlrcpp::Any temp_plus(plus_str);
	  return temp_plus;
	} else if (ctx->op()->getText() == "*") {
	  string mul_str = ctx->expression(0)->getText() + ctx->op()->getText() + ctx->expression(1)->getText();
	  antlrcpp::Any temp_mul(mul_str);
	  return temp_mul;
	}
	
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitAtom(NFCompilerParser::AtomContext *ctx)  {
      antlrcpp::Any a = visitChildren(ctx);
	try {
	string c;
	c = a.as<string>();
	//cout << c << " in visit atom" << endl;
	//NFCompilerVisitor::ST.add(context->IDENT()->getText(),type, type, m.begin()->second, m.begin()->first);
	} catch (bad_cast const& e) {
	}
    return a;
  }

   antlrcpp::Any NFCompilerVisitor::visitId(NFCompilerParser::IdContext *ctx)  {
    string c = ctx->IDENT()->getText();
    if (ctx->expression().empty() && ctx->fields() == NULL) {
      //cout << "returning c in visit ID" << endl;
      return antlrcpp::Any(c);
    } else if (ctx->expression().empty() && ctx->fields() != NULL) {
	antlrcpp::Any a1 = NFCompilerVisitor::visit(ctx->fields());
	try {
	  string s1 = a1.as<string>();
	  //cout << s1  << " in visit id" << endl;
	  return antlrcpp::Any(s1);
	} catch (bad_cast const& e) {
	}
      }
      return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitFunc(NFCompilerParser::FuncContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitRule_flow(NFCompilerParser::Rule_flowContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitConst(NFCompilerParser::ConstContext *ctx)  {
    string c = ctx->constant()->getText();
    //cout << c << " in const visitor" << endl;
    return antlrcpp::Any(c);
  }

   antlrcpp::Any NFCompilerVisitor::visitSet(NFCompilerParser::SetContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitMap(NFCompilerParser::MapContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitLrexp(NFCompilerParser::LrexpContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitAction(NFCompilerParser::ActionContext *ctx)  {
    string c = ctx->ACTION()->getText();
     //cout << c << " in action visitor" << endl;
    return antlrcpp::Any(c);
  }

   antlrcpp::Any NFCompilerVisitor::visitField(NFCompilerParser::FieldContext *ctx)  {
     antlrcpp::Any a = visitChildren(ctx);
    try {
      string action = a.as<string>();
      //cout << action << " in visit field" << endl;
    } catch(bad_cast const& e) {
      //cout << "not pass string in visit field" << endl;
    }
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitContents(NFCompilerParser::ContentsContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitKey_pairs(NFCompilerParser::Key_pairsContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitKey_value(NFCompilerParser::Key_valueContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitFunction_call(NFCompilerParser::Function_callContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitFuncs(NFCompilerParser::FuncsContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitExpression_list(NFCompilerParser::Expression_listContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitConst_ip(NFCompilerParser::Const_ipContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitConst_int(NFCompilerParser::Const_intContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitFlow_or_rule_entry(NFCompilerParser::Flow_or_rule_entryContext *ctx)  {
     string field =  ctx->getStart()->getText();
     string c = ctx->getStop()->getText();
     map<string, string> m;
     m.insert(pair<string, string>(field, c));
    return antlrcpp::Any(m);
  }

   antlrcpp::Any NFCompilerVisitor::visitOp(NFCompilerParser::OpContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitExpr_op(NFCompilerParser::Expr_opContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitRel_op(NFCompilerParser::Rel_opContext *ctx)  {
    return visitChildren(ctx);
  }

   antlrcpp::Any NFCompilerVisitor::visitFields(NFCompilerParser::FieldsContext *ctx)  {
    string c = ctx->FIELD()->getText();
     //cout << c << " in field visitor " << endl;
    return antlrcpp::Any(c);;
  }

  antlrcpp::Any NFCompilerVisitor::visitNew_packet(NFCompilerParser::New_packetContext *ctx) {
    return visitChildren(ctx);
  }



