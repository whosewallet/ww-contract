/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include "whose-wallet.hpp"

using namespace eosio;
namespace ww {
  whosewallet::whosewallet( account_name contract ): _contract(contract) {
    // print("---- current_receiver: ", name(_contract));
  }
  
  void whosewallet::wm_save(const wwmaster& r ) {
      // data table should stay on owner account
      const auto code = _contract;
      const auto scope = _contract;
      tbwm t( code, scope );

      // mapping data
      auto f = [&](wwmaster& _r) {
        _r.id        = r.id;
        _r.w_add     = r.w_add;
        _r.w_type    = r.w_type;
        _r.a_name    = r.a_name;
      };
      
      auto itr = t.find( r.id );
      
      if( itr != t.end() ) {
        t.modify( itr, code, f);
      } else {
        t.emplace( code, f);
      }
    }

    wwmaster whosewallet::wm_get(const uint64_t& pk) {
      // data table should stay on owner account
      const auto code = _contract;
      const auto scope = _contract;
      const tbwm t( code,  scope);

      // iterator
      const auto& itr = t.get( pk );
      t.end();

      return itr;
    }

    void whosewallet::wi_save(const account_name& code, const wwinfo& r ) {
      // data table should stay on owner account
      const auto scope = _contract;
      tbwi t( code, scope );

      // mapping data
      auto f = [&](wwinfo& _r) {
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

    wwinfo whosewallet::wi_get(const account_name& code, const account_name& pk) {
      // data table should stay on owner account
      const auto scope = _contract;
      const tbwi t( code,  scope);

      // iterator
      const auto& itr = t.get( pk );
      t.end();

      return itr;
    }
    // define common tables -- end

    // common
    wwmaster whosewallet::toWwmaster(const inrnw& data) {
      wwmaster res;
      res.id = hashString(data.w_add);
      res.w_add = data.w_add;
      res.w_type = data.w_type;
      res.a_name = data.a_name;

      print("hash address value: ", res.id, "\n ");

      return res;
    }
    // common -- end

    void whosewallet::apply( uint64_t code, uint64_t action ) {
      // print("-- code: ", name(code), "\n  ");
      print("-- action: ", name(action), "\n  ");
      // print("-- sender: ", name(current_sender()), "\n  ");
      // print("-- receiver: ", name(current_receiver()), "\n  ");

      switch (action) {
        case N(rnw):
          registerNewWallet(unpack_action_data<inrnw>());
          break;
        case N(gwwmaster):
          on(unpack_action_data<gwwmaster>());
          break;
      }
    }

    // define actions
    // register new wallet address
    void  whosewallet::registerNewWallet(const inrnw& data) {
      print("-- w_type: ", data.w_type, "\n ");
      print("-- w_add: ", data.w_add.c_str(), "\n ");
      print("-- a_name: ", name(data.a_name), "\n ");

      wm_save(toWwmaster(data));
    }
    
    void  whosewallet::on(const gwwmaster& data) {
      print("-- w_add: ", data.w_add.c_str(), "\n ");
      auto wm = wm_get(hashString(data.w_add));

      print("-- w_type: ", wm.w_type, "\n ");
      print("-- w_add: ", wm.w_add.c_str(), "\n ");
      print("-- a_name: ", name(wm.a_name), "\n ");
    }
    // register new wallet address --end
    // define actions -- end
}
