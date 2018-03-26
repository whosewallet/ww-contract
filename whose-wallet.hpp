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
  struct wwallet {
    uint64_t id;
    string w_add;
    uint32_t w_type;
    account_name a_name;

    auto primary_key() const {
      return id;
    }

    EOSLIB_SERIALIZE( wwallet, (id)(w_add)(w_type)(a_name) )
  };

  struct winfo { /* user table */
    uint64_t tx_type;
    string tx_id;
    string tx_desc;

    auto primary_key() const {
      return tx_type;
    }

    EOSLIB_SERIALIZE( winfo, (tx_type)(tx_id)(tx_desc) )
  };

  typedef eosio::multi_index<N(wwallet), wwallet> tbwm;
  typedef eosio::multi_index<N(winfo), winfo> tbwi;
  // define common tables -- end

  // define action input
  struct inrnw {
    string w_add;
    uint32_t w_type;
    account_name a_name;

    EOSLIB_SERIALIZE( inrnw, (w_add)(w_type)(a_name) )
  };
  
  struct gwwallet {
    string w_add;

    EOSLIB_SERIALIZE( gwwallet, (w_add) )
  };
  // define action input -- end

  class whosewallet {
  private:
    account_name _contract;
    void wm_save(const wwallet& r );
    void wi_save(const account_name& code, const winfo& r );

  public:
    whosewallet( account_name contract = current_receiver() );

    wwallet wm_get(const account_name& pk);
    winfo wi_get(const account_name& code, const account_name& pk);

    // define actions
    // register new wallet address
    void registerNewWallet(const inrnw& data);
    void on(const gwwallet& data);
    // register new wallet address --end
    // define actions -- end

    void apply( uint64_t code, uint64_t action );

    // common
    wwallet toWwallet(const inrnw& data);
    // common -- end
  };
}
