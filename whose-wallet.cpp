/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include "whose-wallet.hpp"

using namespace eosio;
namespace ww {

  uint64_t hashString(string str) {
    uint64_t hash = 5381;
    char c;
    auto s = str.c_str();
    
    while ((c = *s++)) {
      hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
  }
  
  void whosewallet::wm_save(const wwallet& r ) {
    require_auth(_self);

    const auto code = _self;
    const auto scope = _self;
    tb_alwallet t( code, scope );

    // mapping data
    auto f = [&](alwallet& _r) {
      _r.id        = r.id;
      _r.a_name    = r.a_name;
    };
    
    auto itr = t.find( r.id );
    
    if( itr != t.end() ) {
      t.modify( itr, code, f);
    } else {
      t.emplace( code, f);
    }
  }
  
  void whosewallet::wm_save_local(const wwallet& r ) {
    require_auth(r.a_name);

    const auto code = r.a_name;
    const auto scope = code;
    tb_mywallet t( code, scope );

    // mapping data
    auto f = [&](mywallet& _r) {
      _r.id        = r.id;
      _r.w_type    = r.w_type;
      _r.w_add     = r.w_add;
    };
    
    auto itr = t.find( r.id );
    
    if( itr != t.end() ) {
      t.modify( itr, code, f);
    } else {
      t.emplace( code, f);
    }
  }

  void whosewallet::wi_save(const account_name& code, const winfo& r ) {
    require_auth(code);
    // data table should stay on owner account
    const auto scope = _self;
    tbwi t( code, scope );

    // mapping data
    auto f = [&](winfo& _r) {
      _r.id      = r.id;
      _r.tx_type = r.tx_type;
      _r.tx_id   = r.tx_id;
      _r.tx_desc = r.tx_desc;
    };
    
    auto itr = t.find( r.tx_type );
    
    if( itr != t.end() ) {
      t.modify( itr, code, f);
    } else {
      t.emplace( code, f);
    }
  }
  // define common tables -- end

  // common
  // common -- end

  // define actions
  // register new wallet address
  void whosewallet::inrnw(string w_add, uint32_t w_type, account_name a_name) {
    wwallet w;
    w.id = hashString(w_add);
    w.w_add = w_add;
    w.w_type = w_type;
    w.a_name = a_name;

    wm_save(w);
    wm_save_local(w);
  }
  
  void whosewallet::inwinfo(account_name a_name, uint32_t tx_type, string tx_id, string tx_desc) {
    winfo wi;
    wi.id = hashString(tx_id);
    wi.tx_type = tx_type;
    wi.tx_id = tx_id;
    wi.tx_desc = tx_desc;

    wi_save(a_name, wi);
  }
  // register new wallet address --end
  // define actions -- end
}
