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

  void whosewallet::wm_erase(const wwallet& r ) {
    require_auth(_self);

    const auto code = _self;
    const auto scope = _self;
    tb_alwallet t( code, scope );
    t.erase(t.get(r.id));
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

  void whosewallet::wm_erase_local(const wwallet& r ) {
    require_auth(r.a_name);

    const auto code = r.a_name;
    const auto scope = code;
    tb_mywallet t( code, scope );
    t.erase(t.get(r.id));
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
    inrnwal(w_add, w_type, a_name);
    inrnwmy(w_add, w_type, a_name);
  }

  void whosewallet::inrnwal(string w_add, uint32_t w_type, account_name a_name) {
    wm_save(wwallet{hashString(w_add), a_name, w_type, w_add});
  }

  void whosewallet::inrnwmy(string w_add, uint32_t w_type, account_name a_name) {
    wm_save_local(wwallet{hashString(w_add), a_name, w_type, w_add});
  }
  
  void whosewallet::inwinfo(account_name a_name, uint32_t tx_type, string tx_id, string tx_desc) {
    wi_save(a_name, winfo{hashString(tx_id), tx_type, tx_id, tx_desc});
  }

  void whosewallet::rmrnw(string w_add, uint32_t w_type, account_name a_name) {
    rmrnwal(w_add, w_type, a_name);
    rmrnwmy(w_add, w_type, a_name);
  }

  void whosewallet::rmrnwal(string w_add, uint32_t w_type, account_name a_name) {
    wm_erase(wwallet{hashString(w_add), a_name, w_type, w_add});
  }

  void whosewallet::rmrnwmy(string w_add, uint32_t w_type, account_name a_name) {
    wm_erase_local(wwallet{hashString(w_add), a_name, w_type, w_add});
  }
  // register new wallet address --end
  // define actions -- end
}
