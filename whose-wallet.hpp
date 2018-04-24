/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma one
#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;
namespace ww {
  using std::string;
  uint64_t hashString(string s);

  // define common tables
  struct wwallet {
    uint64_t id;
    account_name a_name;
    uint32_t w_type;
    string w_add;
    uint8_t anonymous;
  };
  
  struct idxaname {
    account_name a_name;

    auto primary_key() const {
      return a_name;
    }

    EOSLIB_SERIALIZE( idxaname, (a_name) )
  };
  
  struct alwallet {
    uint64_t id;
    account_name a_name;
    uint32_t w_type;
    string w_add;
    uint8_t anonymous;

    auto primary_key() const {
      return id;
    }

    account_name get_a_name() const {
      return a_name;
    }

    EOSLIB_SERIALIZE( alwallet, (id)(a_name)(w_type)(w_add)(anonymous) )
  };

  struct mywallet {
    uint64_t id;
    uint32_t w_type;
    string w_add;

    auto primary_key() const {
      return id;
    }

    EOSLIB_SERIALIZE( mywallet, (id)(w_type)(w_add) )
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

  typedef eosio::multi_index<N(alwallet), alwallet,
    indexed_by<N(a_name), const_mem_fun<alwallet, account_name, &alwallet::get_a_name> >> tb_alwallet;
    
  typedef eosio::multi_index<N(mywallet), mywallet> tb_mywallet;
  typedef eosio::multi_index<N(winfo), winfo> tbwi;
  typedef eosio::multi_index<N(idxaname), idxaname> tb_idxaname;
  // define common tables -- end

  class whosewallet : public contract {
  private:
    tb_alwallet talwallet;
    tb_idxaname tidxaname;
    /**
     * Storing wallet index
     * Help searching user by wallet address
     * 
    **/
    void wm_save(const wwallet& r );
    void wm_erase(const wwallet& r );

    void idxaname_save(const account_name& a_name);
    void idxaname_erase(const account_name& a_name);

    /**
     * Storing to user-account
     * Help viewing user wallets
     * 
    **/
    void wm_save_local(const wwallet& r );
    void wm_erase_local(const wwallet& r );

    void wi_save(const account_name& code, const winfo& r );

  public:
    whosewallet( action_name self );
    // define actions
    
    // add new wallet address
    void inrnw(string w_add, uint32_t w_type, account_name a_name);
    void inrnwal(string w_add, uint32_t w_type, account_name a_name);
    void inrnwmy(string w_add, uint32_t w_type, account_name a_name);
    
    // store information
    void inwinfo(account_name a_name, uint32_t tx_type, string tx_id, string tx_desc);

    /**
     * Remove a address 
     */
    void rmrnw(string w_add, uint32_t w_type, account_name a_name);
    void rmrnwal(string w_add, uint32_t w_type, account_name a_name);
    void rmrnwmy(string w_add, uint32_t w_type, account_name a_name);

    /**
     * Anonymous user adds new wallet
     */
    void inrnwan(string w_add, uint32_t w_type, account_name a_name);

    /**
     * wallet by account name
     */
    void waacn(account_name a_name);

    // register new wallet address --end
    // define actions -- end

    // common
    // common -- end
  };
}
