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
    account_name a_name;
    uint32_t w_type;
    string w_add;

    auto primary_key() const {
      return id;
    }

    EOSLIB_SERIALIZE( wwallet, (id)(a_name)(w_type)(w_add) )
  };

  struct winfo { /* user table */
    uint64_t id;
    uint32_t tx_type;
    string tx_id;
    string tx_desc;

    auto primary_key() const {
      return id;
    }

    EOSLIB_SERIALIZE( winfo, (id)(tx_type)(tx_id)(tx_desc) )
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

  struct inwinfo {
    account_name a_name;
    uint32_t tx_type;
    string tx_id;
    string tx_desc;

    EOSLIB_SERIALIZE( inwinfo, (a_name)(tx_type)(tx_id)(tx_desc) )
  };
  
  struct gwwallet {
    string w_add;

    EOSLIB_SERIALIZE( gwwallet, (w_add) )
  };
  
  struct gwinfo {
    account_name a_name;
    string tx_id;

    EOSLIB_SERIALIZE( gwinfo, (a_name)(tx_id) )
  };
  // define action input -- end

  class whosewallet {
  private:
    account_name _contract;
    void wm_save(const wwallet& r );
    void wi_save(const account_name& code, const winfo& r );

  public:
    whosewallet(account_name contract);

    wwallet wm_get(const account_name& pk);
    winfo wi_get(const account_name& code, const account_name& pk);

    // define actions
    // register new wallet address
    void on(const inrnw& data);
    void on(const gwwallet& data);
    void on(const inwinfo& data);
    void on(const gwinfo& data);
    // register new wallet address --end
    // define actions -- end

    void apply( uint64_t code, uint64_t action );

    // common
    wwallet toWwallet(const inrnw& data);
    winfo toWinfo(const inwinfo& data);
    // common -- end
  };
}
