/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include "whose-wallet.hpp"

using namespace eosio;
namespace ww {
  whosewallet::whosewallet( account_name contract ): _contract(contract) {
    print("---- current_receiver: ", name(_contract));
  }
  
  void whosewallet::wm_save(const wwmaster& r ) {
      // data table should stay on owner account
      const auto code = _contract;
      const auto scope = _contract;
      tbwm t( code, scope );

      // mapping data
      auto f = [&](wwmaster& _r) {
        _r.nickname = r.nickname;
        _r.wtype    = r.wtype;
        _r.wadd     = r.wadd;
        _r.ctype    = r.ctype;
        _r.cvalue   = r.cvalue;
      };
      
      auto itr = t.find( r.nickname );
      
      if( itr != t.end() ) {
        t.modify( itr, code, f);
      } else {
        t.emplace( code, f);
      }
    }

    wwmaster whosewallet::wm_get(const account_name& pk) {
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

    void whosewallet::apply( uint64_t code, uint64_t action ) {
      print("-- code: ", name(code), "\n  ");
      print("-- action: ", name(action), "\n  ");
      print("-- sender: ", name(current_sender()), "\n  ");
      print("-- receiver: ", name(current_receiver()), "\n  ");

      if (action == N(rnw)) {
        // whosewallet::registerNewWallet(unpack_action_data<wwmaster>());
        return;
      }
    }

    // define actions
    // register new wallet address
    void  whosewallet::registerNewWallet(const wwmaster& data) {
      this->wm_save(data);
    }
    // register new wallet address --end
    // define actions -- end
}
