/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;
namespace ww {
  using std::string;

  // define common tables
  struct wwmaster {
    account_name nickname;
    uint32_t wtype;
    string wadd;
    uint32_t ctype;
    string cvalue;

    auto primary_key() const {
      return nickname;
    }

    EOSLIB_SERIALIZE( wwmaster, (nickname)(wtype)(wadd)(ctype)(cvalue) )
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

  class whosewallet {
  private:
    account_name _contract;

  public:
    whosewallet( account_name contract = current_receiver() );

    void wm_save(const wwmaster& r );
    wwmaster wm_get(const account_name& pk);

    void wi_save(const account_name& code, const wwinfo& r );
    wwinfo wi_get(const account_name& code, const account_name& pk);
    // define common tables -- end

    void apply( uint64_t code, uint64_t action );
  };
}
