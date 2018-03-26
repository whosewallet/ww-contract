/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/multi_index.hpp>
#include <functional>

using namespace eosio;
namespace ww {
  using std::string;
  const std::hash<string> hashString;

  // define common tables
  struct wwmaster {
    uint64_t id;
    string w_add;
    uint32_t w_type;
    account_name a_name;

    auto primary_key() const {
      return id;
    }

    EOSLIB_SERIALIZE( wwmaster, (id)(w_add)(w_type)(a_name) )
  };

  struct wwinfo { /* user table */
    uint64_t tx_type;
    string tx_id;
    string tx_desc;

    auto primary_key() const {
      return tx_type;
    }

    EOSLIB_SERIALIZE( wwinfo, (tx_type)(tx_id)(tx_desc) )
  };

  typedef eosio::multi_index<N(wwmaster), wwmaster> tbwm;
  typedef eosio::multi_index<N(wwinfo), wwinfo> tbwi;
  // define common tables -- end

  // define action input
  struct inrnw {
    string w_add;
    uint32_t w_type;
    account_name a_name;

    EOSLIB_SERIALIZE( inrnw, (w_add)(w_type)(a_name) )
  };
  
  struct gwwmaster {
    string w_add;

    EOSLIB_SERIALIZE( gwwmaster, (w_add) )
  };
  // define action input -- end

  class whosewallet {
  private:
    account_name _contract;
    void wm_save(const wwmaster& r );
    void wi_save(const account_name& code, const wwinfo& r );

  public:
    whosewallet( account_name contract = current_receiver() );

    wwmaster wm_get(const account_name& pk);
    wwinfo wi_get(const account_name& code, const account_name& pk);

    // define actions
    // register new wallet address
    void registerNewWallet(const inrnw& data);
    void on(const gwwmaster& data);
    // register new wallet address --end
    // define actions -- end

    void apply( uint64_t code, uint64_t action );

    // common
    wwmaster toWwmaster(const inrnw& data);
    // common -- end
  };
}
